#ifdef _WIN32
	#include "C:\vclib\SDL2-2.0.18\include\SDL.h"
#else
	#include <SDL2/SDL.h>
#endif

#include <cstdlib>
#include <iostream>
#include "config.h"
#include "stage.h"

void handleRender();
//void handleReshape(GLint newWidth, GLint newHeight);
void handleLoop();
void handleCleanup();
bool init();
void execute();

SDL_Window * getSDLWindow();
SDL_Renderer * getSDLRenderer();
SDL_Surface * getSDLPrimarySurface();

void handleSDLEvent(SDL_Event * Event);

extern short windowWidth;
extern short windowHeight;

extern bool keepRunning;

extern Config config;

extern unsigned char currentStageID;
extern Stage * currentStage;

enum programMode { PROGRAM_BOOT, PROGRAM_MAINMENU, PROGRAM_GAME };

SDL_Window * Window;
SDL_Renderer * Renderer;
SDL_Surface * PrimarySurface;

extern unsigned int gameTickCount;
