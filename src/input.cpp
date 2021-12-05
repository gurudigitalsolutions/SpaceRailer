#include "input.h"
#include "in_joystick.h"

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

void ProgramInput::process()
{
	previousInputState = currentInputState;
	currentInputState = getInput();
	
	//	Some joystick magic.  This works, but is not really fleshed out at
	//	all yet.
	//joystick_main();
}
