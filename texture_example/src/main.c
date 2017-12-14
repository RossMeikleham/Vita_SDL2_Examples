// Example of Initializing and Updating a SDL2 Texture

#include <SDL2/SDL.h>

#ifdef PSVITA
#include <psp2/kernel/processmgr.h>
#endif

#define TEXTURE_PIXELS_X 160
#define TEXTURE_PIXELS_Y 140

#define VITA_SCREEN_WIDTH 960 
#define VITA_SCREEN_HEIGHT 544

static SDL_Window *screen;
static SDL_Renderer *renderer;
static SDL_Texture *texture;
static Uint32 texture_pixels[TEXTURE_PIXELS_X * TEXTURE_PIXELS_Y];


/*  Initialise graphics and create win_x by win_y pixel
 *  screen. Returns 1 if successful, 0 otherwise */
int init_screen(int win_x, int win_y) {
    
    if((SDL_Init(SDL_INIT_VIDEO)==-1)) {
        return 0;
     }

    // Setup Window
    screen = SDL_CreateWindow("Vita Texture Example", 
                   SDL_WINDOWPOS_UNDEFINED, 
                   SDL_WINDOWPOS_UNDEFINED,
                   win_x, win_y, 
                   0); 
   
    if (screen == NULL) {
        return 0;
    } 

    // Setup Renderer
    renderer = SDL_CreateRenderer(screen, -1, 0);
    if (renderer == NULL) {
        return 0;
    } 

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    
    // Setup texture for blitting the pixels
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                    SDL_TEXTUREACCESS_STREAMING, TEXTURE_PIXELS_X, TEXTURE_PIXELS_Y);


    if (texture == NULL) {
        return 0;
    }

    return 1;
}


/*  Update the texture and render it to the screen */
void draw_screen() {
    
    SDL_DisplayMode current;
	
	SDL_UpdateTexture(texture, NULL, texture_pixels, TEXTURE_PIXELS_X * sizeof (Uint32));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
   
    SDL_RenderPresent(renderer);
}


int main() {

    if (!init_screen(VITA_SCREEN_WIDTH, VITA_SCREEN_HEIGHT)) {
        return 1;
    };

    // Red
    for (int i = 0; i < TEXTURE_PIXELS_X * TEXTURE_PIXELS_Y; i++) {
        texture_pixels[i] = 0xFFFF0000;
    } 
    draw_screen(); 
    SDL_Delay(3000);        
    
    // Green
    for (int i = 0; i < TEXTURE_PIXELS_X * TEXTURE_PIXELS_Y; i++) {
        texture_pixels[i] = 0xFF00FF00;
    } 
    draw_screen(); 
    SDL_Delay(3000);        
    
    // Blue
    for (int i = 0; i < TEXTURE_PIXELS_X * TEXTURE_PIXELS_Y; i++) {
        texture_pixels[i] = 0xFF0000FF;
    } 
    draw_screen();  
    SDL_Delay(3000);        

#ifdef PSVITA
    sceKernelExitProcess(0);
#endif
}

