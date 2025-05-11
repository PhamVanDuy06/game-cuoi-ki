#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include "defs.h"
using namespace std;

struct Sprite {
    SDL_Texture* texture;
    vector<SDL_Rect> clips;
    int currentFrame = 0;
    int frameDelay = 5;
    int frameCounter = 0;

    void init(SDL_Texture* _texture, int frames, const int _clips [][4]) {
        texture = _texture;

        SDL_Rect clip;
        for (int i = 0; i < frames; i++) {
            clip.x = _clips[i][0];
            clip.y = _clips[i][1];
            clip.w = _clips[i][2];
            clip.h = _clips[i][3];
            clips.push_back(clip);
        }
    }
    void tick() {
        frameCounter++;
        if (frameCounter >= frameDelay) {
            frameCounter = 0;
            currentFrame = (currentFrame + 1) % clips.size();
        }
    }

    const SDL_Rect* getCurrentClip() const {
        return &(clips[currentFrame]);
    }
};

struct ScrollingBackground {
    SDL_Texture* texture;
    int scrollingOffset = 0;
    int width, height;

    void setTexture(SDL_Texture* _texture) {
        texture = _texture;
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    }

    void scroll(int distance) {
        scrollingOffset -= distance;
        if( scrollingOffset < 0 ) { scrollingOffset = width; }
    }
};


struct Graphics {
    SDL_Renderer *renderer;
	SDL_Window *window;

	void logErrorAndExit(const char* msg, const char* error);
	void init();

	void prepareScene(SDL_Texture * background = nullptr);

    void presentScene();

    SDL_Texture *loadTexture(const char *filename);

    void renderTexture(SDL_Texture *texture, int x, int y);

    void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y);

    void quit();

    void render(int x, int y, const Sprite& sprite) {
        const SDL_Rect* clip = sprite.getCurrentClip();
        SDL_Rect renderQuad = {x, y, clip->w*2, clip->h*2};
        SDL_RenderCopy(renderer, sprite.texture, clip, &renderQuad);
    }
    void renderbg(const ScrollingBackground& bgr) {
        renderTexture(bgr.texture, bgr.scrollingOffset,0);
        renderTexture(bgr.texture, bgr.scrollingOffset - bgr.width,0);
    }

};

#endif // _GRAPHICS__H
