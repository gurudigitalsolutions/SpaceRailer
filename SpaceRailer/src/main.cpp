////////////////////////////////////////////////////////////////////////////////
//
//	Space Railer
//
////////////////////////////////////////////////////////////////////////////////

#ifdef _WIN32
	#include "C:\vclib\SDL2-2.0.18\include\SDL.h"
#else
	#include <SDL2/SDL.h>
#endif

#include <cstdlib>
#include <iostream>

using namespace std;

#include "particles/particle.h"
#include "particles/particleemitter.h"
#include "stage_backdrop.h"
#include "main.h"



//	Setting window size to be a quarter of a 1080 display
short windowWidth = 960;
short windowHeight = 540;

//	keepRunning determines when the program should stop looping
bool keepRunning = true;

//	Initialize a configuration object
Config config;

//	Initialize an input object
ProgramInput programInput;

//	Initialize stage information.  currentStageID will be the number for
//	the stage you are on, and currentStage will be the actual object that
//	is and manipulates the world.
unsigned char currentStageID = 0;
Stage * currentStage;

//	Initialize gameTickCount to 0.  This will be updated every process loop
unsigned int gameTickCount = 0;
unsigned int gameLastFrameTick = 0;

programMode currentProgramMode = PROGRAM_BOOT;

int _argc;
char ** _argv;

int main(int argc, char ** argv)
{
	cout << "SpaceRailer\n";
	
	cout << "Initializing...\n";
	
	//	"Globalize" command line arguments
	_argc = argc;
	_argv = argv;
	
	if(!init())
	{
		cout << "Failed to initialize.\n";
		cout << "That seriously sucks.\n";
		return 1;
	}
	
	cout << "Stage Dir: " << config.getStageDir() << "\n";
	
	cout << "Reticulating splines...\n";
	currentStage = Stage::load(currentStageID);
	if(currentStage == NULL || !currentStage->initialize())
	{
		cout << "Splines deticulated.  Sorry.\n";
		return 0; 
	}
	
	
	execute();
	
	return 0;
}

void handleRender()
{
	switch(currentProgramMode)
	{
		case PROGRAM_BOOT		: break;
		case PROGRAM_MAINMENU	: break;
		case PROGRAM_GAME		:
			currentStage->render();
			break;
	}
	
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
		case PROGRAM_GAME		: 
			currentStage->process();
			break;
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


//	handleSDLEvent is called if there are any SDL Events to process.  These
//	include stuff like window resizing, input, and I'm not really sure yet.
void handleSDLEvent(SDL_Event * Event)
{
	switch(Event->type) {
		case SDL_MOUSEMOTION: break;
		case SDL_MOUSEBUTTONDOWN: break;
		case SDL_MOUSEBUTTONUP: break;
		case SDL_MOUSEWHEEL: break;
		
		//	Pass input events to the input controller
		case SDL_CONTROLLERAXISMOTION: 
		case SDL_CONTROLLERBUTTONDOWN:
		case SDL_CONTROLLERBUTTONUP:
		case SDL_KEYDOWN:
		case SDL_KEYUP:
		case SDL_JOYAXISMOTION:
		case SDL_JOYBALLMOTION:
		case SDL_JOYHATMOTION:
		case SDL_JOYBUTTONDOWN:
		case SDL_JOYBUTTONUP:
			programInput.handleInputEvent(Event);
			break;

		//	These will be handy :)
		case SDL_CONTROLLERDEVICEADDED:
		case SDL_CONTROLLERDEVICEREMOVED:
		case SDL_CONTROLLERDEVICEREMAPPED:
		case SDL_JOYDEVICEADDED:
		case SDL_JOYDEVICEREMOVED:
			programInput.handleConnectionEvent(Event);
			break;
		
		case SDL_SYSWMEVENT: break;
		case SDL_WINDOWEVENT: break;
		default:
			printf("some SDL event\n");
			break;
	}
}


bool init()
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
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
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
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
	
	
	//	Initialize the input system
	if(!programInput.initialize())
	{
		cout << "Unable to initialize input.  No way to play like that :(\n";
		return false;
	}
	
	//	Initialize the audio system
	
	return true;
}

void execute()
{
	cout << "Splines reticulated.\n";
	
	SDL_Event Event;
	
	currentProgramMode = PROGRAM_GAME;
	
	while(keepRunning)
	{
		//	Set gameTickCount.  This is a timer that is accurate to a millisecond
		gameTickCount = SDL_GetTicks();
		
		while(SDL_PollEvent(&Event) != 0)
		{
			handleSDLEvent(&Event);
			
			if(Event.type == SDL_QUIT) { keepRunning = false; }
		}
		
		//	Run process every game tick
		handleLoop();
		
		//	Run render every 16ms.  This is just over 60fps, but the timer
		//	isn't actually that accurate
		if(gameTickCount - gameLastFrameTick > 16)
		{
			gameLastFrameTick = gameTickCount;
			handleRender();
		}
		
		//	Delayage
		SDL_Delay(1);
	}
	
	handleCleanup();
	
	return;
}

SDL_Window * getSDLWindow() { return Window; }
SDL_Renderer * getSDLRenderer() { return Renderer; }
SDL_Surface * getSDLPrimarySurface() { return PrimarySurface; }

char ** getArgv()
{
	return _argv;
}

int getArgc()
{
	return _argc;
}
