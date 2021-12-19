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
#include "input.h"
#include "stage_api.h"

extern ProgramInput programInput;

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
	
	//if(!newStage->_initialize()) { return NULL; }
	
	return newStage;
}

//	Initialize this stage.  This method will attempt to create a scripting
//	interpreter for the stage, and then run the initialization sequence for
//	the scripting engine.  If this fails, it will return false.
bool Stage::initialize()
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
	
	_scriptFunction = PyObject_GetAttrString(_scriptModule, "initialize");
	if(_scriptFunction && PyCallable_Check(_scriptFunction))
	{
		PyObject_CallObject(_scriptFunction, NULL);
	}

	_player.setWidth(128);
	_player.setHeight(128);
	_player.setX(30);
	_player.setY(30);
	
	if (!_player.initialize())
	{
		cout << "player is already dead, failed to initialize";
	}
	
	//_player.addComponent("thruster0", 0, 64, 55, 55);
	_player.addComponent("thruster0", 0, 64, 55, 55, COMPONENT_ATTACH_LOOSE, 40, 40);

	
	return true;
}

//	Process is called once per world tick.  This should handle all the stuff.
//	Be careful not to do too much stuff at one time because it will stall the
//	next frame from being rendered.
bool Stage::process()
{
	//	Check if the player is trying to move around.
	InputData currentInputState = programInput.getCurrentInputState();
	InputData previousInputState = programInput.getPreviousInputState();
	
	if(currentInputState.analogRight > 16384) { _player.setX(_player.getX() + 3); }
	if(currentInputState.analogLeft > 16384) { _player.setX(_player.getX() - 3); }
	if(currentInputState.analogUp > 16384) { _player.setY(_player.getY() - 3); }
	if(currentInputState.analogDown > 16384) { _player.setY(_player.getY() + 3); }
	
	_player.process();
	return true;
}

//	Render is called once per frame to render the screen.  Heavy processing
//	should not be done here.
bool Stage::render()
{
	SDL_SetRenderDrawColor(getSDLRenderer(), 0x00, 0x00, 0x00, 0xff);
	SDL_RenderClear(getSDLRenderer());
	
	_player.render();
	
	//	TODO
	//	Loop...
	//		EachMob.render()

	//	Set draw color to green
	//SDL_SetRenderDrawColor(getSDLRenderer(), 0x00, 0xff, 0x00, 0xff);
	//SDL_RenderFillRect(getSDLRenderer(), &box);
	SDL_RenderPresent(getSDLRenderer());
	return true;
}

//	Initialize the scripting engine for this stage.
bool Stage::_initializeScripting()
{
	
	//	First, check that the stage python script exists.
	FILE * fh = fopen((_stageDirectory + "__init__.py").c_str(), "r");
	if(fh == NULL)
	{
		cout << "stage.py missing for this stage.\n";
		return false;
	}
	fclose(fh);
	
	//	Script exists, so lets initialize the API.  This must be done before
	//	the call to Py_Initialize()
	PyImport_AppendInittab("spacerailer", &PyInit_pySpaceRailerModule);

	Py_Initialize();

	PyRun_SimpleString("import sys");
	string dpath = "sys.path.append(\"" + Path_Tools::getGameDataPath() + "resources/stages\")";
	
	PyRun_SimpleString(dpath.c_str());
	
	_scriptFilename = PyUnicode_DecodeFSDefault("stage_0");
	_scriptModule = PyImport_Import(_scriptFilename);
	Py_DECREF(_scriptFilename);
	
	//	Check if importing was successful.
	if(_scriptModule == NULL)
	{
		PyErr_Print();
		return false;
	}
	
	//	Looks like the python module has been loaded!
	
	return true;
}

//	Handle incoming functions from the Python API
PyObject * Stage::processAPI(PyObject * self, PyObject * args, string method)
{
	if(method == "numargs") { return PyLong_FromLong(420); }
	if(method == "getMapX") { return PyLong_FromLong(getMapX()); }
	if(method == "getMapY") { return PyLong_FromLong(getMapY()); }
	if(method == "getPlayerX") { return PyLong_FromLong(_player.getX()); }
	if(method == "getPlayerY") { return PyLong_FromLong(_player.getY()); }
	if(method == "getPlayerHP") { return PyLong_FromLong(_player.getHitPoints()); }
	if(method == "getPlayerWidth") { return PyLong_FromLong(_player.getWidth()); }
	if(method == "getPlayerHeight") { return PyLong_FromLong(_player.getHeight()); }
	
	return NULL;
}
