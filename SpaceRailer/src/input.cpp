#include <iostream>
#include "input.h"

using namespace std;

InputData ProgramInput::getInput()
{
	InputData tInput;
	tInput.buttonFire = false;
	tInput.buttonActivate = false;
	tInput.buttonPause = false;
	
	tInput.analogDown = 0;
	tInput.analogUp = 0;
	tInput.analogLeft = 0;
	tInput.analogRight = 0;
	
	return tInput;
}

//	Initialize input.  This needs to find any connected controllers and try
//	to use those.  It will also need to cross reference any button mappings
//	the user may have made for each controller.
//
//	If no controllers are found, this should default to keyboard input.  If
//	that fails somehow, then just return false.
bool ProgramInput::initialize() {
	
	if(SDL_NumJoysticks() < 1)
	{
		cout << "No controllers found.  Defaulting to keyboard.\n";
	}
	else
	{
		//	A controller was found.  For now, we will open the first one
		//	and just go with it.
		_controller = SDL_JoystickOpen(0);
		if(_controller == NULL)
		{
			cout << "Unable to open game controller!\n";
		}
	}
	
	return true;
}

void ProgramInput::process()
{
	previousInputState = currentInputState;
	currentInputState = getInput();
	
	//	Some joystick magic.  This works, but is not really fleshed out at
	//	all yet.
	//joystick_main();
}

//	This will store the data for an input event.  It will not actually fire
//	any events or anything.  That needs to be handled by the appropriate
//	subsystem.
void ProgramInput::handleInputEvent(SDL_Event * Event)
{
	printf("Input event received.\n");
}

void ProgramInput::handleConnectionEvent(SDL_Event * Event)
{
	printf("Input connection event received.\n");
}
