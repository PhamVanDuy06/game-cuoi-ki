#ifndef _DEFS__H
#define _DEFS__H

#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>

const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 170;
#define WINDOW_TITLE  "Meo meo"
#define DOGY 120

#define DOG_RUN_MOVE "imageRUN.png"
#define BACK_GROUND "bg1.png"
#define DOG_JUMP_MOVE "imageJUMP.png"
#define OBSTACLE_TREE "imageObstacle.png"

const int DOG_CLIPS_RUN [][4] = {
    {0, 0, 32, 20},
    {32, 0, 32, 20},
    {64, 0, 32, 20},
    {96, 0, 31, 20}
};
const int DOG_FRAMES_RUN = sizeof(DOG_CLIPS_RUN) / sizeof(int) / 4;

const int DOG_CLIPS_JUMP [][4] = {
    {32, 0, 32, 20}
};
const int DOG_FRAMES_JUMP = sizeof(DOG_CLIPS_JUMP) / sizeof(int) / 4;

const int OBSTACLE_CLIP_TREE [][4] = {
    {0, 0, 41, 90},
    {41, 0, 41, 90},
    {82, 0, 41, 90},
    {123, 0, 41, 90},
    {164, 0, 41, 90}
};
const int OBSTACLE_FRAMES_TREE = sizeof(OBSTACLE_CLIP_TREE) / sizeof(int) / 4;


#endif
