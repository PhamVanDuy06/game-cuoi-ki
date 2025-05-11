#include "Graphics.h"
#include <cstdlib>
#include <ctime>
#include "player.h"
#include <SDL_ttf.h>
#include <SDL_mixer.h>
using namespace std;

enum GameState {
    MENU,
    PLAYING
};

struct Obstacle {
    float x, y;
    Sprite* sprite;
    bool vacham = false;

    Obstacle(float _x, float _y, Sprite* _sprite) {
        x = _x;
        y = _y;
        sprite = _sprite;
    }
    void dabivacham(){
        vacham = true;
    }

    bool daBiVaChamRoi() const {
        return vacham;
    }

    void update(float speed) {
        x -= speed;
    }

    void draw(Graphics& graphics) {
        graphics.render((int)x, (int)y, *sprite);
    }

    bool isOffScreen() {
        return x + 32 < 0;
    }
};

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

void resetGame(vector<Obstacle>& obstacles_list,
               int& num_die_count,
               Uint32& next_spawn_time_ref,
               Uint32& last_game_time_ref,
               Sprite& player_dog_sprite,
               Sprite& player_dog_jump_sprite)
{
    obstacles_list.clear();
    num_die_count = 0;

    posY = groundY;
    isJumping = false;
    velocity = 0.0f;
    jumpTime = 0.0f;

    player_dog_sprite.currentFrame = 0;
    player_dog_sprite.frameCounter = 0;
    player_dog_jump_sprite.currentFrame = 0;
    player_dog_jump_sprite.frameCounter = 0;

    last_game_time_ref = SDL_GetTicks();
    next_spawn_time_ref = last_game_time_ref + 1500 + (rand() % 1500);

    cout << "INFO: Game reset." << endl;
}
int main(int argc, char *argv[]) {
    srand(time(NULL));

    Graphics graphics;
    graphics.init();

        float img_ref_width = 800.0f;
        float img_ref_height = 600.0f;

        SDL_Rect playButtonRect = {
            (int)(280.0f / img_ref_width * SCREEN_WIDTH),
            (int)(120.0f / img_ref_height * SCREEN_HEIGHT),
            (int)(300.0f / img_ref_width * SCREEN_WIDTH),
            (int)(110.0f / img_ref_height * SCREEN_HEIGHT)
        };

        SDL_Rect exitButtonRect = {
            (int)(280.0f / img_ref_width * SCREEN_WIDTH),
            (int)(290.0f / img_ref_height * SCREEN_HEIGHT),
            (int)(300.0f / img_ref_width * SCREEN_WIDTH),
            (int)(110.0f / img_ref_height * SCREEN_HEIGHT)
        };

        SDL_Rect helpButtonRect = { // Sẽ dùng sau
            (int)(280.0f / img_ref_width * SCREEN_WIDTH),
            (int)(460.0f / img_ref_height * SCREEN_HEIGHT),
            (int)(300.0f / img_ref_width * SCREEN_WIDTH),
            (int)(110.0f / img_ref_height * SCREEN_HEIGHT)
        };


    SDL_Texture* menuTexture = graphics.loadTexture(MENU_IMAGE);
    if (menuTexture == nullptr) {
        cerr << "Failed to load menu image: " << "MENU" << " - SDL_Error: " << IMG_GetError() << endl;
        graphics.quit();
        return 0;
    }

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

    int num_die = 0;

    GameState currentState = MENU;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN){
                if (e.button.button == SDL_BUTTON_LEFT){
                    if (currentState == MENU){
                        int mouseX, mouseY;
                        SDL_GetMouseState(&mouseX,&mouseY);
                        SDL_Point mousePoint = {mouseX, mouseY};

                            if (SDL_PointInRect(&mousePoint, &playButtonRect)) {
                                cout << "EVENT: Play button clicked!" << endl;
                                currentState = PLAYING;
                                resetGame(obstacles, num_die, nextSpawnTime, lastTime, dog, dogjump);
                            }
                            else if (SDL_PointInRect(&mousePoint, &exitButtonRect)) {
                                cout << "EVENT: Exit button clicked!" << endl;
                                quit = true;
                                }
                            }
                        }

                    }
                    if (currentState == PLAYING) {
                        if (e.type == SDL_KEYDOWN) {
                            if (e.key.keysym.sym == SDLK_SPACE && !isJumping) {
                                isJumping = true;
                                velocity = jumpVelocity;
                                jumpTime = 0.0f;
                                cout << "DEBUG: Jump initiated by SPACE!" << endl;
                            }
                        }
                    }
                }


        if (currentState == MENU){
            graphics.prepareScene(menuTexture);
            cout << "da ve len buffer" << endl;
        }
        else if (currentState == PLAYING){
            cout << "dang o playing" << endl;
            Uint32 currentTime = SDL_GetTicks();
            float deltaTime = (currentTime - lastTime) / 1000.0f;
            lastTime = currentTime;

            graphics.prepareScene(nullptr);

            update(deltaTime);

            if (currentTime >= nextSpawnTime) {
                Obstacle obs(SCREEN_WIDTH + rand() % 100, groundY, &obstacle);

                obstacles.push_back(obs);

                nextSpawnTime = currentTime + 1500 + rand() % 1500;
            }

        background.scroll(3);
        graphics.renderbg(background);


        if (isJumping) {
            graphics.render(0, posY, dogjump);
        } else {
            dog.tick();
            graphics.render(0, DOGY, dog);
        }

        SDL_Rect dogRect = getDogRect(isJumping ? dogjump : dog);


        float scrollSpeed = 4.0f;

        for (size_t i = 0; i < obstacles.size();) {
            obstacles[i].update(scrollSpeed);

            SDL_Rect obstacleRect = getobstacleRect(obstacles[i]);

           if (!obstacles[i].daBiVaChamRoi() && check(dogRect, obstacleRect)) {
               obstacles[i].dabivacham();
               num_die++;
               cout << "Va cham! So lan: " << num_die << endl;
               SDL_Delay(1000);
            }

            if (obstacles[i].isOffScreen()) {
                obstacles.erase(obstacles.begin() + i);
            } else {
                obstacles[i].draw(graphics);
                ++i;
            }

            if (num_die >= 3){
                cout << "Game Over! Quay ve Menu." << endl;
                currentState = MENU;
                SDL_Delay(2000);
                break;
            }
        }
        }
        graphics.presentScene();
        SDL_Delay(16);
    }

    SDL_DestroyTexture(menuTexture);
    SDL_DestroyTexture(runTexture);
    SDL_DestroyTexture(jumpTexture);
    SDL_DestroyTexture(obstacleTexture);

    graphics.quit();

    return 0;
}
