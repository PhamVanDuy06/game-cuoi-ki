#include "Graphics.h"
#include <cstdlib>
#include <ctime>
#include "player.h"

using namespace std;

enum GameState {
    MENU,
    PLAYING,
    GAME_OVER
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
        return x + 16*4 < 0;
    }
};

SDL_Rect getDogRect(const Sprite &sprite){
    const SDL_Rect* clip = sprite.getCurrentClip();
    SDL_Rect rect;
    rect.x = 0;
    rect.y = (int)posY;
    rect.w = clip ->w *3;
    rect.h = clip ->h *3;
    return rect;
}
SDL_Rect getobstacleRect(const Obstacle& obs){
    const SDL_Rect* clip = obs.sprite->getCurrentClip();
    SDL_Rect rect;
    rect.x = (int)obs.x;
    rect.y = (int)obs.y;
    rect.w =  clip->w *3;
    rect.h = clip ->h *3;

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
    num_die_count = 3;

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

    TTF_Font* font = graphics.loadFont("Purisa-BoldOblique.ttf",28);

    SDL_Color color = {0, 0, 0, 255};
    SDL_Texture* helloText = graphics.renderText("Heart :", font, color);

    Mix_Chunk *gClickMenu = graphics.loadSound(ClickMenu);
    Mix_Chunk *gJump = graphics.loadSound(ClickJump);
    Mix_Chunk *gVaCham = graphics.loadSound(VaCham);

    Mix_Music *gMusic = graphics.loadMusic(ChoiNhac);
    graphics.playMusic(gMusic);

        float img_ref_width = 800.0f;
        float img_ref_height = 600.0f;

        SDL_Rect playButtonRect = {260, 230, 270, 130};

        SDL_Rect exitButtonRect = {260, 410, 270, 130};

        SDL_Rect restarButtonRect = {260, 230, 270, 130};


    SDL_Texture* menuTexture = graphics.loadTexture(MENU_IMAGE);
    SDL_Texture* restarTexture = graphics.loadTexture(RESTAR_IMAGE);
    SDL_Texture* HeartTexture = graphics.loadTexture(Heart);
    SDL_Texture* playline = graphics.loadTexture(PlayisLine);
    SDL_Texture* exitline = graphics.loadTexture(ExitisLine);
    SDL_Texture* restartline = graphics.loadTexture(RestartisLine);


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

    int num_die = 3;

    GameState currentState = MENU;

    bool isMouseOverPlay = false;
    bool isMouseOverExit = false;
    bool isMouseOverRestart = false;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            if (e.type == SDL_MOUSEMOTION) {

                    int mouseXx = e.motion.x;
                    int mouseYy = e.motion.y;
                    SDL_Point mousePoint = {mouseXx, mouseYy};
                if (currentState == MENU) {

                    if (SDL_PointInRect(&mousePoint, &playButtonRect)) {
                        isMouseOverPlay = true;
                    } else {
                        isMouseOverPlay = false;
                    }
                    if(SDL_PointInRect(&mousePoint, &exitButtonRect)){
                        isMouseOverExit = true;
                    }else {
                        isMouseOverExit = false;
                    }

                }else if(currentState == GAME_OVER){
                    if(SDL_PointInRect(&mousePoint, &restarButtonRect)){
                        isMouseOverRestart = true;
                    }
                    else{
                        isMouseOverRestart = false;
                    }
                }
            }

            if (e.type == SDL_MOUSEBUTTONDOWN){
                if (e.button.button == SDL_BUTTON_LEFT){
                        int mouseX, mouseY;
                        SDL_GetMouseState(&mouseX,&mouseY);
                        SDL_Point mousePoint = {mouseX, mouseY};

                    if (currentState == MENU){
                            if (SDL_PointInRect(&mousePoint, &playButtonRect)) {
                                cout << "EVENT: Play button clicked!" << endl;
                                graphics.playChunk(gClickMenu);
                                currentState = PLAYING;
                                resetGame(obstacles, num_die, nextSpawnTime, lastTime, dog, dogjump);
                            }
                            else if (SDL_PointInRect(&mousePoint, &exitButtonRect)) {
                                cout << "EVENT: Exit button clicked!" << endl;
                                graphics.playChunk(gClickMenu);
                                quit = true;
                                }
                            }
                            else if (currentState == GAME_OVER){
                                if (SDL_PointInRect(&mousePoint, &restarButtonRect)){
                                    graphics.playChunk(gClickMenu);
                                    currentState = MENU;
                                }
                            }
                        }

                    }
                    if (currentState == PLAYING) {
                        if (e.type == SDL_KEYDOWN) {
                            if (e.key.keysym.sym == SDLK_SPACE && !isJumping) {
                                graphics.playChunk(gJump);
                                isJumping = true;
                                velocity = jumpVelocity;
                                jumpTime = 0.0f;
                                cout << "DEBUG: Jump initiated by SPACE!" << endl;
                            }
                        }
                    }

                }


        if (currentState == MENU){
            graphics.prepareScene(nullptr);
            graphics.prepareScene(menuTexture);

            if (isMouseOverPlay && playline) {
                graphics.renderTexture(playline,0,0);
            }
            if(isMouseOverExit && exitline){
                graphics.renderTexture(exitline,0,0);
            }
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

        graphics.renderTexture(helloText, 0, 50);


        int tmp = 16; //kich thuoc anh hear
        for(int i = 0; i < num_die; i++){
            graphics.renderTexture(HeartTexture,tmp*(i+1) + i*15,100);
        }

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
               num_die--;
               cout << "Va cham! So lan: " << num_die << endl;
               graphics.playChunk(gVaCham);
               SDL_Delay(1000);
            }

            if (obstacles[i].isOffScreen()) {
                obstacles.erase(obstacles.begin() + i);
            } else {
                obstacles[i].draw(graphics);
                ++i;
            }

            if (num_die <= 0){

                currentState = GAME_OVER;

            }
          }
        }else if (currentState == GAME_OVER){
            graphics.prepareScene(nullptr);
            graphics.prepareScene(restarTexture);

            if (isMouseOverRestart && restartline) {
            graphics.renderTexture(restartline, 0, 0);
            }
        }

        graphics.presentScene();
        SDL_Delay(16);
    }

    SDL_DestroyTexture( helloText );
    helloText = NULL;
    TTF_CloseFont( font );

    if (gJump != nullptr) Mix_FreeChunk( gJump);
    if (gClickMenu != nullptr) Mix_FreeChunk( gClickMenu);
    if (gVaCham != nullptr) Mix_FreeChunk( gVaCham);
    if (gMusic != nullptr) Mix_FreeMusic( gMusic );
    SDL_DestroyTexture(HeartTexture);
    SDL_DestroyTexture(menuTexture);
    SDL_DestroyTexture(runTexture);
    SDL_DestroyTexture(jumpTexture);
    SDL_DestroyTexture(obstacleTexture);

    graphics.quit();

    return 0;
}
