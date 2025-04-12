#include "Graphics.h"

using namespace std;

const float gravity = 1000.0f;
const float jumpVelocity = -450.0f;
const float groundY = 120.0f;

float posY = groundY;
float velocity = 0.0f;
bool isJumping = false;
float jumpTime = 0.0f;

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

int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();

    ScrollingBackground background;
    background.setTexture(graphics.loadTexture(BACK_GROUND));

    ScrollingBackground obstacle_tree;
    obstacle_tree.setTexture(graphics.loadTexture(OBSTACLE_TREE));

    Sprite dog;
    SDL_Texture* runTexture = graphics.loadTexture(DOG_RUN_MOVE);
    dog.init(runTexture, DOG_FRAMES_RUN, DOG_CLIPS_RUN);

    Sprite dogjump;
    SDL_Texture* jumpTexture = graphics.loadTexture(DOG_JUMP_MOVE);
    dogjump.init(jumpTexture, DOG_FRAMES_JUMP, DOG_CLIPS_JUMP);

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

        graphics.prepareScene();
        background.scroll(3);
        //obstacle_tree.scroll(3);
        //graphics.renderbg(obstacle_tree);
        graphics.renderbg(background);

        if (isJumping) {
            graphics.render(0, posY, dogjump);
        } else {
            dog.tick();
            graphics.render(0, DOGY, dog);
        }

        graphics.presentScene();

        SDL_Delay(16);
    }

    SDL_DestroyTexture(runTexture);
    SDL_DestroyTexture(jumpTexture);
    graphics.quit();

    return 0;
}
