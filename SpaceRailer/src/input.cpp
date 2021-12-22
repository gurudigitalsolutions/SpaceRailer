#include <iostream>
#include <cmath>
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
	//printf("Input event received.\n");
	previousInputState = currentInputState;
	
	if(Event->type == SDL_KEYDOWN
	|| Event->type == SDL_KEYUP)
	{
		//	Keyboard events.  These should also be mapped for player control.
		if(((SDL_KeyboardEvent *)Event)->keysym.sym == SDLK_a)
		{	currentInputState.analogLeft = (((SDL_KeyboardEvent *)Event)->type == SDL_KEYDOWN ? 32767 : 0);	}
		
		if(((SDL_KeyboardEvent *)Event)->keysym.sym == SDLK_d)
		{	currentInputState.analogRight = (((SDL_KeyboardEvent *)Event)->type == SDL_KEYDOWN ? 32767 : 0);	}
		
		if(((SDL_KeyboardEvent *)Event)->keysym.sym == SDLK_w)
		{	currentInputState.analogUp = (((SDL_KeyboardEvent *)Event)->type == SDL_KEYDOWN ? 32767 : 0);	}
		
		if(((SDL_KeyboardEvent *)Event)->keysym.sym == SDLK_s)
		{	currentInputState.analogDown = (((SDL_KeyboardEvent *)Event)->type == SDL_KEYDOWN ? 32767 : 0);	}
		
		if(((SDL_KeyboardEvent *)Event)->keysym.sym == SDLK_SPACE)
		{	currentInputState.buttonFire = (((SDL_KeyboardEvent *)Event)->type == SDL_KEYDOWN ? true : false);	}
		
		if(((SDL_KeyboardEvent *)Event)->keysym.sym == SDLK_r)
		{	currentInputState.buttonActivate = (((SDL_KeyboardEvent *)Event)->type == SDL_KEYDOWN ? true: false);	}
		
		if(((SDL_KeyboardEvent *)Event)->keysym.sym == SDLK_ESCAPE)
		{	currentInputState.buttonPause = (((SDL_KeyboardEvent *)Event)->type == SDL_KEYDOWN ? true : false);	}
	}
	
	//	Start with button up/down events
	if(Event->type == SDL_JOYBUTTONDOWN
	|| Event->type == SDL_JOYBUTTONUP)
	{
		//	These are the mappings of the controller that I currently have
		//	connected.  This will need to be updated to be dynamic
		//		fire		2
		//		activate	1
		//		pause		9
		if(((SDL_ControllerButtonEvent *)Event)->button == 2)
		{	currentInputState.buttonFire = (((SDL_ControllerButtonEvent *)Event)->state == 0 ? false : true); }
		
		if(((SDL_ControllerButtonEvent *)Event)->button == 1)
		{	currentInputState.buttonActivate = (((SDL_ControllerButtonEvent *)Event)->state == 0 ? false : true); }
		
		if(((SDL_ControllerButtonEvent *)Event)->button == 9)
		{	currentInputState.buttonPause = (((SDL_ControllerButtonEvent *)Event)->state == 0 ? false : true); }
		
		/*printf("Button, State:  %d, %d\n", 
			((SDL_ControllerButtonEvent *)Event)->button,
			((SDL_ControllerButtonEvent *)Event)->state
		);*/
	}
	
	//	Update analog stick info
	if(Event->type == SDL_JOYAXISMOTION)
	{
		//	Values on the controller currently plugged in:
		//		Axis Left <-> Right:	0
		//		Axis Up <-> Down:		1
		//
		//	Pushing down or right are positive integers
		
		if(((SDL_JoyAxisEvent *)Event)->axis == 1)
		{
			//	Start with vertical axis.  Check if the player is pushing
			//	up or down and set the input state accordingly
			if(abs(((SDL_JoyAxisEvent *)Event)->value) < 400)
			{
				//	The '400' is for the dead zone.  This magic number really
				//	needs to be defined in the controller config file.
				currentInputState.analogDown = 0;
				currentInputState.analogUp = 0;
			}
			else if((((SDL_JoyAxisEvent *)Event)->value) > 0)
			{
				//	The player is pushing down on the analog stick
				currentInputState.analogDown = abs((((SDL_JoyAxisEvent *)Event)->value));
				currentInputState.analogUp = 0;
			}
			else if((((SDL_JoyAxisEvent *)Event)->value) < 0)
			{
				//	The player is pushing up on the analog stick
				//	Since a short can only go from -32768 to 32767, the absolute
				//	value of -32768 is still -32768.  Because of this, we need
				//	to add 1 to the value here.
				currentInputState.analogUp = abs(((SDL_JoyAxisEvent *)Event)->value + 1);
				currentInputState.analogDown = 0;
				
			}
		}
		else
		{
			//	And now the horizontal axis.  Check if the player is pushing
			//	left or right and do the right thing with that information.
			if(abs(((SDL_JoyAxisEvent *)Event)->value) < 400)
			{
				//	The '400' is for the dead zone.  This magic number really
				//	needs to be defined in the controller config file.
				currentInputState.analogLeft = 0;
				currentInputState.analogRight = 0;
			}
			else if((((SDL_JoyAxisEvent *)Event)->value) > 0)
			{
				//	The player is pushing right on the analog stick
				currentInputState.analogRight = abs((((SDL_JoyAxisEvent *)Event)->value));
				currentInputState.analogLeft = 0;
			}
			else if((((SDL_JoyAxisEvent *)Event)->value) < 0)
			{
				//	The player is pushing left on the analog stick
				currentInputState.analogLeft = abs(((SDL_JoyAxisEvent *)Event)->value + 1);
				currentInputState.analogRight = 0;
			}
		}
		
		/*printf("JoyAxis: %d %d\n",
			((SDL_JoyAxisEvent *)Event)->axis,
			((SDL_JoyAxisEvent *)Event)->value
		);*/
	}
}

void ProgramInput::handleConnectionEvent(SDL_Event * Event)
{
	printf("Input connection event received.\n");
}
