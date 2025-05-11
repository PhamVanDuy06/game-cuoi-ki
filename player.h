#ifndef __PLAYER_H
#define __PLAYER_H

#include "defs.h"

using namespace std;

const float gravity = 1200.0f;
const float jumpVelocity = -550.0f;
const float groundY = 400.0f;

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


bool check (const SDL_Rect& a, const SDL_Rect& b){
    int leftA = a.x - 30;
    int rightA = a.x + a.w - 30;
    int topA = a.y - 30;
    int bottomA = a.y + a.h - 30;

    int leftB = b.x - 30;
    int rightB = b.x + b.w - 30;
    int topB = b.y - 30;
    int bottomB = b.y + b.h - 30;

    if (bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB) {
        return false;
    }
    return true;
}


#endif // __PLAYER_H
