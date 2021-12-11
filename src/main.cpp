////////////////////////////////////////////////////////////////////////////////
//
//	Space Railer
//
////////////////////////////////////////////////////////////////////////////////

#include <SDL2/SDL.h>
#include <cstdlib>
#include <iostream>

using namespace std;

#include "main.h"
#include "input.h"
#include "scripting.h"



//	Setting window size to be a quarter of a 1080 display
short windowWidth = 960;
short windowHeight = 540;

//	keepRunning determines when the program should stop looping
bool keepRunning = true;

programMode currentProgramMode = PROGRAM_BOOT;

int main(int argc, char ** argv)
{
	cout << "SpaceRailer\n";
	
	cout << "Initializing...\n";
	if(!init())
	{
		cout << "Failed to initialize.\n";
		cout << "That seriously sucks.\n";
		return 1;
	}
	
	cout << "Reticulating splines...\n";
	execute();
	
	return 0;
}

void handleRender()
{
	
}

/*void handleReshape(GLint newWidth, GLint newHeight)
{
	return;
}*/

//	handleLoop is where the main processing for the program goes.  This will
//	determine what state the program is currently in and hand it off to the
//	appropriate subsystem.
void handleLoop()
{
	switch(currentProgramMode)
	{
		case PROGRAM_BOOT		: break;
		case PROGRAM_MAINMENU	: break;
		case PROGRAM_GAME		: break;
	}
	
	return;
}

//	handleCleanup will destroy windows, free up file pointers and other
//	related stuff.
void handleCleanup()
{
	cout << "Dereticulating splinial units...\n";
	
	if(Renderer)
	{
		SDL_DestroyRenderer(Renderer);
		Renderer = NULL;
	}
	
	if(Window)
	{
		SDL_DestroyWindow(Window);
		Window = NULL;
	}
	
	SDL_Quit();
}


//	onSDLEvent is called if there are any SDL Events to process.  These include
//	stuff like window resizing, input, and I'm not really sure yet.
void onSDLEvent(SDL_Event * Event)
{

}


bool init()
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "Unable to init SDL.\n";
		return false;
	}
	
	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		cout << "Unable to init hinting.\n";
		return false;
	}
	
	Window = SDL_CreateWindow(
		"SpaceRailer",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		windowWidth,
		windowHeight,
		SDL_WINDOW_SHOWN
	);
	
	if(Window == NULL)
	{
		cout << "Unable to create SDL window.\n";
		return false;
	}
	
	PrimarySurface = SDL_GetWindowSurface(Window);
	
	if((Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED)) == NULL)
	{
		cout << "Unable to create renderer.\n";
		return false;
	}
	
	//	Set draw color to fully opaque black (RGBA)
	SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0x00, 0xFF);
	
	return true;
}

void execute()
{
	cout << "Splines reticulated.\n";
	
	SDL_Event Event;
	
	while(keepRunning)
	{
		while(SDL_PollEvent(&Event) != 0)
		{
			onSDLEvent(&Event);
			
			if(Event.type == SDL_QUIT) { keepRunning = false; }
		}
		
		handleLoop();
		handleRender();
		
		//	Delayage
		SDL_Delay(1);
	}
	
	handleCleanup();
	
	return;
}
