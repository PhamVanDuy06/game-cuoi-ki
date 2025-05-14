#ifndef __PLAYER_H
#define __PLAYER_H

#include "defs.h"

using namespace std;

const float gravity = 1300.0f;
const float jumpVelocity = -750.0f;
const float groundY = 500.0f;

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
    int leftA = a.x ;
    int rightA = (a.x + a.w);
    int topA = a.y;
    int bottomA = (a.y + a.h);

    int leftB = b.x;
    int rightB = (b.x + b.w);
    int topB = b.y;
    int bottomB = (b.y + b.h);

    if (bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB) {
        return false;
    }
    return true;
}


#endif // __PLAYER_H
