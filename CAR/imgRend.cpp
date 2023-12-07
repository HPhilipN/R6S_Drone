#include "imgRend.h"
// Loads a png and displays it on the window with the given xpos and ypos

#define IMAGE_SIZE 20
#define POS 2
#define WP "/wasdxBMP/wpressed.bmp"
#define WR "/wasdxBMP/wreleased.bmp"
#define AP "/wasdxBMP/apressed.bmp"
#define AR "/wasdxBMP/areleased.bmp"
#define SP "/wasdxBMP/spressed.bmp"
#define SR "/wasdxBMP/sreleased.bmp"
#define DP "/wasdxBMP/dpressed.bmp"
#define DR "/wasdxBMP/dreleased.bmp"
#define XP "/wasdxBMP/xpressed.bmp"
#define XR "/wasdxBMP/xreleased.bmp"

// change values for position on window
static int w[POS] = {1,1};
static int a[POS] = {1,1};
static int s[POS] = {1,1};
static int d[POS] = {1,1};
static int x[POS] = {1,1};


// Main function to load an image and display to the passed window and renderer
static void loadImage(SDL_Window *window, SDL_Renderer *renderer, const char *image, int xpos, int ypos){
    SDL_Rect dstrect = {xpos, ypos, IMAGE_SIZE, IMAGE_SIZE};
    
    // SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    
    SDL_Surface * img = SDL_LoadBMP(image);
    
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, img);
    
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_RenderPresent(renderer);
    
    return;
}

// functions to be called from main, change last two integer values to change positioning
void wPress(SDL_Window *wind, SDL_Renderer *rend){
    loadImage(wind, rend, WP, w[0],w[1]);
}

void wRelease(SDL_Window *wind, SDL_Renderer *rend){
    loadImage(wind, rend, WR, w[0],w[1]);
}

void aPress(SDL_Window *wind, SDL_Renderer *rend){
    loadImage(wind, rend, AP, a[0],a[1]);
}

void aRelease(SDL_Window *wind, SDL_Renderer *rend){
    loadImage(wind, rend, AR, a[0],a[1]);
}

void sPress(SDL_Window *wind, SDL_Renderer *rend){
    loadImage(wind, rend, SP, s[0],s[1]);
}

void sRelease(SDL_Window *wind, SDL_Renderer *rend){
    loadImage(wind, rend, SR, s[0],s[1]);
}

void dPress(SDL_Window *wind, SDL_Renderer *rend){
    loadImage(wind, rend, DP, d[0],d[1]);
}

void dRelease(SDL_Window *wind, SDL_Renderer *rend){
    loadImage(wind, rend, DR, d[0],d[1]);
}

void xPress(SDL_Window *wind, SDL_Renderer *rend){
    loadImage(wind, rend, XP, x[0],x[1]);
}

void xRelease(SDL_Window *wind, SDL_Renderer *rend){
    loadImage(wind, rend, XR, x[0],x[1]);
}

// remove all images
void destroyImages(void){
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
