// Example of using the PSVita Buttons with SDL2

#include <SDL2/SDL.h>

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>
#include <stdio.h>

#include "debugScreen.h"

#define printf psvDebugScreenPrintf

#define VITA_SCREEN_WIDTH 960 
#define VITA_SCREEN_HEIGHT 544

#define SDLK_VITA_TRIANGLE 0
#define SDLK_VITA_CIRCLE 1 
#define SDLK_VITA_CROSS 2
#define SDLK_VITA_SQUARE 3

#define SDLK_VITA_LTRIGGER 4
#define SDLK_VITA_RTRIGGER 5

#define SDLK_VITA_DOWN 6
#define SDLK_VITA_LEFT 7
#define SDLK_VITA_UP 8
#define SDLK_VITA_RIGHT 9

#define SDLK_VITA_SELECT 10
#define SDLK_VITA_START 11

static SDL_Joystick *joystick;

int init_joypad() {
    
    if((SDL_Init(SDL_INIT_JOYSTICK)==-1)) {
        return 0;
     }
    
    joystick = 0;
    if (SDL_NumJoysticks() > 0) {
        joystick = SDL_JoystickOpen(0);
    }

    return 1;
}

void display_joypad_change(int button, int pressed) {
    switch (button) {
        case SDLK_VITA_TRIANGLE:
            printf("Triangle ");
            break;
        case SDLK_VITA_CROSS:
            printf("Cross ");
            break;
        case SDLK_VITA_CIRCLE:
            printf("Circle ");
            break;
        case SDLK_VITA_SQUARE:
            printf("Square ");
            break;
        case SDLK_VITA_LTRIGGER:
            printf("Left Trigger ");
            break;
        case SDLK_VITA_RTRIGGER:
            printf("Right Trigger ");
            break;
        case SDLK_VITA_DOWN:
            printf("Down ");
            break;
        case SDLK_VITA_LEFT:
            printf("Left ");
            break;
        case SDLK_VITA_UP:
            printf("Up ");
            break;
        case SDLK_VITA_RIGHT:
            printf("Right ");
            break;
        case SDLK_VITA_SELECT:
            printf("Select ");
            break;
        case SDLK_VITA_START:
            printf("Start ");
            break;
        default: 
            printf("Unknown ");
    }

    printf("button %s\n", pressed ? "pressed" : "released");
}

void check_joypad() {
        SDL_Event event;

        if (SDL_PollEvent(&event)) {

            switch (event.type) {
                case SDL_JOYBUTTONDOWN:
                case SDL_JOYBUTTONUP:
                    display_joypad_change(event.jbutton.button, event.jbutton.state == SDL_PRESSED);
                    break;
            }
        }
}


int main() {
    
    psvDebugScreenInit();
	printf("Press Buttons\n");
	
    if (!init_joypad()) {
        printf("Unable to intiialize SDL2 Joypad\n");
        return 1;
    }

    while (1) {
        check_joypad();
        SDL_Delay(100);
    }

    return 0;
}

