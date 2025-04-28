#include "Graphics.h"
#include <cstdlib>
#include <ctime>

using namespace std;

const float gravity = 1000.0f;
const float jumpVelocity = -450.0f;
const float groundY = 120.0f;

float posY = groundY;
float velocity = 0.0f;
bool isJumping = false;
float jumpTime = 0.0f;


struct Obstacle {
    float x, y;
    Sprite* sprite;

    Obstacle(float _x, float _y, Sprite* _sprite) {
        x = _x;
        y = _y;
        sprite = _sprite;
    }

    void update(float speed) {
        x -= speed;
    }

    void draw(Graphics& graphics) {
        graphics.render((int)x, (int)y, *sprite);
    }

    bool isOffScreen() {
        return x + 64 < 0;
    }
};

void update(float deltaTime) {
    if (isJumping) {
        jumpTime += deltaTime;
        posY = groundY + jumpVelocity * jumpTime + 0.5f * gravity * jumpTime * jumpTime;

        if (posY >= groundY) {
            posY = groundY;
            isJumping = false;
            jumpTime = 0.0f;
        }
    }
}
SDL_Rect getDogRect(const Sprite &sprite){
    const SDL_Rect* clip = sprite.getCurrentClip();
    SDL_Rect rect;
    rect.x = 0;
    rect.y = (int)posY;
    rect.w = clip ->w *2;
    rect.h = clip ->h *2;
    return rect;
}
SDL_Rect getobstacleRect(const Obstacle& obs){
    const SDL_Rect* clip = obs.sprite->getCurrentClip();
    SDL_Rect rect;
    rect.x = (int)obs.x;
    rect.y = (int)obs.y;
    rect.w =  clip->w *2;
    rect.h = clip ->h *2;

    return rect;
}

bool check (const SDL_Rect& a, const SDL_Rect& b){
    return SDL_HasIntersection(&a, &b);
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    Graphics graphics;
    graphics.init();

    ScrollingBackground background;
    background.setTexture(graphics.loadTexture(BACK_GROUND));

    Sprite dog;
    SDL_Texture* runTexture = graphics.loadTexture(DOG_RUN_MOVE);
    dog.init(runTexture, DOG_FRAMES_RUN, DOG_CLIPS_RUN);

    Sprite dogjump;
    SDL_Texture* jumpTexture = graphics.loadTexture(DOG_JUMP_MOVE);
    dogjump.init(jumpTexture, DOG_FRAMES_JUMP, DOG_CLIPS_JUMP);


    Sprite obstacle;
    SDL_Texture* obstacleTexture = graphics.loadTexture(OBSTACLE_TREE);
    obstacle.init(obstacleTexture, OBSTACLE_FRAMES_TREE, OBSTACLE_CLIP_TREE);


    vector<Obstacle> obstacles;
    Uint32 nextSpawnTime = SDL_GetTicks() + rand() % 1500;

    bool quit = false;
    SDL_Event e;

    Uint32 lastTime = SDL_GetTicks();

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_SPACE && !isJumping) {
                    isJumping = true;
                    velocity = jumpVelocity;
                    jumpTime = 0.0f;
                }
            }
        }

        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        update(deltaTime);


        if (currentTime >= nextSpawnTime) {
            Obstacle obs(SCREEN_WIDTH + rand() % 100, groundY, &obstacle);
            obstacles.push_back(obs);

            nextSpawnTime = currentTime + 1500 + rand() % 1500;
        }


        graphics.prepareScene();
        background.scroll(3);
        graphics.renderbg(background);


        if (isJumping) {
            graphics.render(0, posY, dogjump);
        } else {
            dog.tick();
            graphics.render(0, DOGY, dog);
        }

        SDL_Rect dogRect = getDogRect(isJumping ? dogjump : dog);


        float scrollSpeed = 3.0f;
        for (size_t i = 0; i < obstacles.size(); ) {
            obstacles[i].update(scrollSpeed);

            SDL_Rect obstacleRect = getobstacleRect(obstacles[i]);

            if (check(dogRect, obstacleRect)){
                quit = true;
                break;
            }

            if (obstacles[i].isOffScreen()) {
                obstacles.erase(obstacles.begin() + i);
            } else {
                obstacles[i].draw(graphics);
                ++i;
            }
        }

        graphics.presentScene();
        SDL_Delay(16);
    }

    SDL_DestroyTexture(runTexture);
    SDL_DestroyTexture(jumpTexture);
    SDL_DestroyTexture(obstacleTexture);

    graphics.quit();

    return 0;
}
