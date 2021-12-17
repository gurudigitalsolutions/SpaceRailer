typedef struct
{
	bool buttonFire;
	bool buttonActivate;
	bool buttonPause;
	
	short analogUp;
	short analogDown;
	short analogLeft;
	short analogRight;
} InputData;


class ProgramInput
{
	private:
		InputData currentInputState;
		InputData previousInputState;
		
		//	getInput will actually read player input.  This can come from any
		//	type of source, such as a joystick, keyboard, network, etc.
		InputData getInput();

		
	public:
		
		InputData getCurrentInputState() { return currentInputState; }
		InputData getPreviousInputState() { return previousInputState; }
		
		//	Process input events.  This needs to record the previous state as
		//	well as record the current state.
		void process();
	
};
