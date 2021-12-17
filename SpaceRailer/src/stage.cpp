#include <string>
#include <filesystem>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <SDL2/SDL.h>
#include <fstream>
#include <string>


#ifdef _WIN32
	//
#else
	#include <unistd.h>
	#include <dirent.h>
#endif



#include "config.h"
#include "stage.h"
#include "path_tools.h"


extern char** getArgv();
extern int getArgc();



using namespace std;

//	Static method to create a new Stage object.  This object will handle all
//	interaction with the stage.
Stage * Stage::load(unsigned char stageid)
{
	cout << "Game data path: '" << Path_Tools::getGameDataPath() << "'\n";

	string stageDir = config.getStageDir() + "stage_" + to_string(stageid) + "/";
	cout << "Loading stage: " << stageDir << "\n";
	
	
	if (!Path_Tools::pathExists(stageDir)) {
		return NULL;
	}

	//	Sweet, the stage directory exists.  Now to check the files within
	//	to make sure there is something to load.
	Stage * newStage = new Stage();
	newStage->_stageDirectory = stageDir;
	newStage->_stageID = stageid;
	
	if(!newStage->_initialize()) { return NULL; }
	
	return newStage;
}

//	Initialize this stage.  This method will attempt to create a scripting
//	interpreter for the stage, and then run the initialization sequence for
//	the scripting engine.  If this fails, it will return false.
bool Stage::_initialize()
{
	if(_stageDirectory == "")
	{
		cout << "Failed to initialize.  Stage directory not found.\n";
		return false;
	}
	
	// TODO	Check if the proper resources are available
	//	Start with the graphics directory

	
	//	Attempt to launch the scripting engine for this stage
	if(!_initializeScripting())
	{
		cout << "Scripting engine could not be initialized.\n";
		return NULL;
	}

	_player.setWidth(256);
	_player.setHeight(256);
	if (!_player.initialize())
	{
		cout << "player is already dead, failed to initialize";
	}

	
	return true;
}

//	Process is called once per world tick.  This should handle all the stuff.
//	Be careful not to do too much stuff at one time because it will stall the
//	next frame from being rendered.
bool Stage::process()
{
	return true;
}

//	Render is called once per frame to render the screen.  Heavy processing
//	should not be done here.
bool Stage::render()
{
	SDL_SetRenderDrawColor(getSDLRenderer(), 0x00, 0x00, 0x00, 0xff);
	SDL_RenderClear(getSDLRenderer());
	
	SDL_Rect box;
	box.w = 30;
	box.h = 30;
	box.x = 50;
	box.y = 50;
	
	//	Set draw color to green
	SDL_SetRenderDrawColor(getSDLRenderer(), 0x00, 0xff, 0x00, 0xff);
	SDL_RenderFillRect(getSDLRenderer(), &box);
	SDL_RenderPresent(getSDLRenderer());
	return true;
}

//	Initialize the scripting engine for this stage.
bool Stage::_initializeScripting()
{
	return true;
	//	First, check that the stage python script exists.
	FILE * fh = fopen((_stageDirectory + "stage.py").c_str(), "r");
	if(fh == NULL)
	{
		cout << "stage.py missing for this stage.\n";
		return false;
	}
	fclose(fh);
	
	//	Open and import the script.
	Py_Initialize();
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append(\"./data/stages/stage_0/\")");
	PyRun_SimpleString("print(sys.path)");
	
	_scriptFilename = PyUnicode_DecodeFSDefault((_stageDirectory + "stage").c_str());
	_scriptModule = PyImport_Import(_scriptFilename);
	Py_DECREF(_scriptFilename);
	
	//	Check if importing was successful.
	if(_scriptModule == NULL)
	{
		PyErr_Print();
		return false;
	}
	
	//	Looks like the python module has been loaded!  We aren't calling any
	//	functions at this point.
	return true;
}
