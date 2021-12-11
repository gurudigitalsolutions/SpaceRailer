#include <SDL2/SDL.h>
#include <cstdlib>
#include <iostream>
#include "config.h"

void handleRender();
//void handleReshape(GLint newWidth, GLint newHeight);
void handleLoop();
void handleCleanup();
bool init();
void execute();

void onSDLEvent(SDL_Event * Event);

extern short windowWidth;
extern short windowHeight;

extern bool keepRunning;

extern Config config;

extern unsigned char currentStage;

enum programMode { PROGRAM_BOOT, PROGRAM_MAINMENU, PROGRAM_GAME };

SDL_Window * Window;
SDL_Renderer * Renderer;
SDL_Surface * PrimarySurface;
