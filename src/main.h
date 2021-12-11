#include <SDL2/SDL.h>
#include <cstdlib>
#include <iostream>

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

enum programMode { PROGRAM_BOOT, PROGRAM_MAINMENU, PROGRAM_GAME };

SDL_Window * Window;
SDL_Renderer * Renderer;
SDL_Surface * PrimarySurface;
