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
#include <math.h>

#ifdef _WIN32
	//
#else
	#include <unistd.h>
	#include <dirent.h>
#endif



#include "config.h"
#include "stage_backdrop.h"
#include "stage.h"
#include "input.h"
#include "stage_api.h"

extern ProgramInput programInput;
extern unsigned int gameTickCount;

extern short windowWidth;
extern short windowHeight;

extern char** getArgv();
extern int getArgc();


struct vec2
{
	float x;
	float y;
};

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
	_player.setWidth(128);
	_player.setHeight(128);
	//_player.setX(30);
	//_player.setY(30);
	
	if (!_player.initialize())
	{
		cout << "player is already dead, failed to initialize\n";
	}
	
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

	
	
	//_player.addComponent("thruster0", 0, 64, 55, 55);
	//_player.addComponent("thruster0", 0, 64, 25, 25, COMPONENT_ATTACH_LOOSE, 40, 40);
	/*Mob * newMob = new Mob();
	newMob->setX(56);
	newMob->setY(80);
	newMob->setWidth(28);
	newMob->setHeight(28);
	newMob->initialize("thruster0");
	newMob->setIsComponent(true);
	newMob->setParent((Mob *)&_player);
	addMob(newMob);*/
	

	StageBackdrop * nBackdrop = new StageBackdrop();
	//nBackdrop->initialize("Eta_Carinae_Nebula", 1920, 1080);
	nBackdrop->initialize("tiled-background-cave-1", 1200, 540);
	_backdrops.push_back(nBackdrop);
	
	return true;
}

//	Process is called once per world tick.  This should handle all the stuff.
//	Be careful not to do too much stuff at one time because it will stall the
//	next frame from being rendered.
bool Stage::process()
{
	//	Check if it's time to scroll the map
	if(gameTickCount - _lastScrollTick >= getScrollIntervalMS())
	{
		//	This can actually do more precise math.  If the interval is say 10,
		//	and it's been 12 ms, we could leave that 2 left over.  For now I'm
		//	not going to worry about it.
		_lastScrollTick = gameTickCount;
		
		int newMapX = getMapX() + getScrollPixelsPerInterval();
		if(newMapX > getStageWidth() - windowWidth) { newMapX = getStageWidth() - windowWidth; }
		else
		{
			_player.setX(_player.getX() + getScrollPixelsPerInterval());
			
			for(unsigned int emob = 0; emob < _mobs.size(); emob++)
			{
				if(_mobs[emob]->getIsStationary())
				{
					_mobs[emob]->setX(_mobs[emob]->getX() + getScrollPixelsPerInterval());
				}
			}
		}
		
		setMapX(newMapX);
		
		_callback_stageScrollEvent();
	}
	
	//	Check if the player is trying to move around.
	InputData currentInputState = programInput.getCurrentInputState();
	InputData previousInputState = programInput.getPreviousInputState();
	
	if(currentInputState.analogRight > 16384) { _player.setX(_player.getX() + 3); }
	if(currentInputState.analogLeft > 16384) { _player.setX(_player.getX() - 3); }
	if(currentInputState.analogUp > 16384) { _player.setY(_player.getY() - 3); }
	if(currentInputState.analogDown > 16384) { _player.setY(_player.getY() + 3); }
	
	_player.process();
	
	//	Process data for each mob
	for(auto esb : _mobs)
	{
		esb->process();
	}
	
	return true;
}

float Stage::_plasma_effect(float x, float y, float time)
{
	float v1, v2, v3;
	struct vec2 coor;
	
	x = -0.05f + (float)x / 64;
	y = -0.05f + (float)y / 64;
	
	v1 = sin(x * 10 + time);
	v2 = sin(10 * (x * sin(time / 2) + y * cos(time / 3)) + time);
	
	coor.x = x + 0.05f * sin(time / 5);
	coor.y = y + 0.05f * cos(time / 3);
	v3 = sin(sqrt(100 * (coor.x * coor.x * coor.y * coor.y) + 1) + time);
	
	return (v1 + v2 + v3);
}

//	Render is called once per frame to render the screen.  Heavy processing
//	should not be done here.
bool Stage::render()
{
	//	Draw from the back to the front.  Otherwise things will be drawn over
	SDL_SetRenderDrawColor(getSDLRenderer(), 0x00, 0x00, 0x00, 0xff);
	SDL_RenderClear(getSDLRenderer());
	
	//	Render backdrops
	for(auto esb : _backdrops)
	{
		esb->render();
	}
	
	
	
	/*for(list<StageBackdrop *>::iterator esb = _backdrops.begin(); esb != _backdrops.end(); esb++)
	{
		(*esb)->render();
	}*/
	
	//	Totally awesome white snake
	/*
	int x,y;
	float value;
	for(x = 0; x < 128; x++)
	{
		for(y = 0; y < 128; y++)
		{
			value = _plasma_effect(x, y, gameTickCount * .0025);
			SDL_SetRenderDrawColor(
				getSDLRenderer(),
				10 * (sin(value * 3.1415926)),
				10 * (cos(value * 3.1415926)),
				0,
				255
			);
			SDL_RenderDrawPoint(getSDLRenderer(), x, y);
		}
	}*/
	
	_player.render();
	
	//	Render mobs
	for(auto esb : _mobs)
	{
		esb->render();
	}
	
	//	TODO
	//	Loop...
	//		EachMob.render()

	//	Set draw color to green
	//SDL_SetRenderDrawColor(getSDLRenderer(), 0x00, 0xff, 0x00, 0xff);
	//SDL_RenderFillRect(getSDLRenderer(), &box);
	SDL_RenderPresent(getSDLRenderer());
	return true;
}

void Stage::addMob(Mob * mob)
{
	_mobs.push_back(mob);
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
	if(method == "setPlayerX") { return _script_setPlayerX(self, args); }
	if(method == "setPlayerY") { return _script_setPlayerY(self, args); }
	if(method == "getPlayerHP") { return PyLong_FromLong(_player.getHitPoints()); }
	if(method == "getPlayerWidth") { return PyLong_FromLong(_player.getWidth()); }
	if(method == "getPlayerHeight") { return PyLong_FromLong(_player.getHeight()); }
	if(method == "getStageScrollPixelsPerInterval") { return PyLong_FromLong(getScrollPixelsPerInterval()); }
	if(method == "setStageScrollPixelsPerInterval") { return _script_setStageScrollPixelsPerInterval(self, args); }
	if(method == "getStageScrollInterval") { return PyLong_FromLong(getScrollIntervalMS()); }
	if(method == "setStageScrollInterval") { return _script_setStageScrollInterval(self, args); }
	if(method == "createMob") { return _script_createMob(self, args); }
	if(method == "getMobX") { return _script_getMobX(self, args); }
	if(method == "getMobY") { return _script_getMobY(self, args); }
	if(method == "setMobX") { return _script_setMobX(self, args); }
	if(method == "setMobY") { return _script_setMobY(self, args); }
	if(method == "getMobWidth") { return _script_getMobWidth(self, args); }
	if(method == "getMobHeight") { return _script_getMobHeight(self, args); }
	if(method == "setMobWidth") { return _script_setMobWidth(self, args); }
	if(method == "setMobHeight") { return _script_setMobHeight(self, args); }
	if(method == "getMobAngle") { return _script_getMobAngle(self, args); }
	if(method == "setMobAngle") { return _script_setMobAngle(self, args); }
	if (method == "getMobIsComponent") { return _script_getMobIsComponent(self, args); }
	if (method == "setMobIsComponent") { return _script_setMobIsComponent(self, args); }
	if(method == "getMobParent") { return _script_getMobParent(self, args); }
	if(method == "setMobParent") { return _script_setMobParent(self, args); }
	if (method == "getMobIsStationary") { return _script_getMobIsStationary(self, args); }
	if (method == "setMobIsStationary") { return _script_setMobIsStationary(self, args); }

	return NULL;
}

PyObject * Stage::_script_setPlayerX(PyObject * self, PyObject * args)
{
	int newPlayerX;
	if(!PyArg_ParseTuple(args, "i", &newPlayerX)) { return NULL; }
	
	_player.setX(newPlayerX);
	Py_RETURN_TRUE;
}

PyObject * Stage::_script_setPlayerY(PyObject * self, PyObject * args)
{
	int newPlayerY;
	if(!PyArg_ParseTuple(args, "i", &newPlayerY)) { return NULL; }

	_player.setY(newPlayerY);
	Py_RETURN_TRUE;
}

PyObject * Stage::_script_setStageScrollPixelsPerInterval(PyObject * self, PyObject * args)
{
	int ssp;
	if(!PyArg_ParseTuple(args, "i", &ssp)) { return NULL; }

	setScrollPixelsPerInterval(ssp);
	Py_RETURN_TRUE;
}

PyObject * Stage::_script_setStageScrollInterval(PyObject * self, PyObject * args)
{
	int ssi;
	if(!PyArg_ParseTuple(args, "i", &ssi)) { return NULL; }

	setScrollIntervalMS(ssi);
	Py_RETURN_TRUE;
}

void Stage::_callback_stageScrollEvent()
{
	_scriptFunction = PyObject_GetAttrString(_scriptModule, "stageScrollEvent");
	if(_scriptFunction && PyCallable_Check(_scriptFunction))
	{
		PyObject_CallObject(_scriptFunction, NULL);
	}
}

PyObject * Stage::_script_createMob(PyObject * self, PyObject * args)
{
	char * pymobtype;
	
	
	if(!PyArg_ParseTuple(args, "s", &pymobtype)) { return NULL; }
	printf("FIlename: %s\n", pymobtype);
	//string mobtype = (char *)&pymobtype;
	
	Mob * newMob = new Mob();
	newMob->initialize((string)pymobtype);

	_mobs.push_back(newMob);
	ssize_t mobid = _mobs.size() - 1;

	return PyLong_FromSsize_t(mobid);
}

PyObject * Stage::_script_getMobX(PyObject * self, PyObject * args)
{
	int mobid;
	if(!PyArg_ParseTuple(args, "i", &mobid)) { return NULL; }
	
	return PyLong_FromLong(_mobs[mobid]->getX());
}

PyObject * Stage::_script_getMobY(PyObject * self, PyObject * args)
{
	int mobid;
	if(!PyArg_ParseTuple(args, "i", &mobid)) { return NULL; }
	
	return PyLong_FromLong(_mobs[mobid]->getY());
}

PyObject * Stage::_script_setMobX(PyObject * self, PyObject * args)
{
	int mobid;
	int newvalue;
	
	if(!PyArg_ParseTuple(args, "ii", &mobid, &newvalue)) { return NULL; }
	_mobs[mobid]->setX(newvalue);
	
	Py_RETURN_TRUE;
}

PyObject * Stage::_script_setMobY(PyObject * self, PyObject * args)
{
	int mobid;
	int newvalue;
	
	if(!PyArg_ParseTuple(args, "ii", &mobid, &newvalue)) { return NULL; }
	_mobs[mobid]->setY(newvalue);
	
	Py_RETURN_TRUE;
}

PyObject * Stage::_script_getMobWidth(PyObject * self, PyObject * args)
{
	int mobid;
	if(!PyArg_ParseTuple(args, "i", &mobid)) { return NULL; }
	
	return PyLong_FromLong(_mobs[mobid]->getWidth());
}

PyObject * Stage::_script_getMobHeight(PyObject * self, PyObject * args)
{
	int mobid;
	if(!PyArg_ParseTuple(args, "i", &mobid)) { return NULL; }
	
	return PyLong_FromLong(_mobs[mobid]->getHeight());
}

PyObject * Stage::_script_setMobWidth(PyObject * self, PyObject * args)
{
	int mobid;
	int newvalue;
	
	if(!PyArg_ParseTuple(args, "ii", &mobid, &newvalue)) { return NULL; }
	_mobs[mobid]->setWidth(newvalue);
	
	Py_RETURN_TRUE;
}

PyObject * Stage::_script_setMobHeight(PyObject * self, PyObject * args)
{
	int mobid;
	int newvalue;
	
	if(!PyArg_ParseTuple(args, "ii", &mobid, &newvalue)) { return NULL; }
	_mobs[mobid]->setHeight(newvalue);
	
	Py_RETURN_TRUE;
}

PyObject * Stage::_script_getMobAngle(PyObject * self, PyObject * args)
{
	int mobid;
	if(!PyArg_ParseTuple(args, "i", &mobid)) { return NULL; }
	
	return PyFloat_FromDouble(_mobs[mobid]->getRenderAngle());
}

PyObject * Stage::_script_setMobAngle(PyObject * self, PyObject * args)
{
	int mobid;
	double newvalue;
	
	if(!PyArg_ParseTuple(args, "id", &mobid, &newvalue)) { return NULL; }
	_mobs[mobid]->setRenderAngle(newvalue);
	
	Py_RETURN_TRUE;
}

PyObject * Stage::_script_getMobParent(PyObject * self, PyObject * args)
{
	int mobid;
	if(!PyArg_ParseTuple(args, "i", &mobid)) { return NULL; }

	//	In most cases, we can just return the mobid from the vector of _mobs.
	//	However, there might be a special case where the parent is the _player
	//	or some other special mob.
	
	//	Check if this mob even HAS a parent
	if(_mobs[mobid]->getParent()) { return PyLong_FromLong(-1); }
	
	//	Check if the mob's parent is the player
	if(_mobs[mobid]->getParent() == &_player) { return PyLong_FromLong(-2); }
	
	for(unsigned int emob = 0; emob < _mobs.size(); emob++)
	{
		Mob * tMob = _mobs[emob]->getParent();
		if(tMob != NULL
		&& tMob == _mobs[emob])
		{
			return PyLong_FromLong(emob);
		}
	}
	
	//	No parent was found for this mob
	return PyLong_FromLong(-1);
}

PyObject * Stage::_script_setMobParent(PyObject * self, PyObject * args)
{
	printf("setting mob parent\n");
	
	int mobid;
	int newvalue;
	
	if(!PyArg_ParseTuple(args, "ii", &mobid, &newvalue)) { return NULL; }
	
	if(newvalue == -2)
	{
		printf("Assigning player as mob %d parent.\n", mobid);
		_mobs[mobid]->setParent((Mob *)&_player);
		Py_RETURN_TRUE;
	}
	
	_mobs[mobid]->setParent(_mobs[newvalue]);
	
	Py_RETURN_TRUE;
}

PyObject * Stage::_script_getMobIsComponent(PyObject * self, PyObject * args)
{
	int mobid;
	if(!PyArg_ParseTuple(args, "i", &mobid)) { return NULL; }
	
	return (_mobs[mobid]->getIsComponent() ? Py_True : Py_False);
}

PyObject * Stage::_script_setMobIsComponent(PyObject * self, PyObject * args)
{
	int mobid;
	int newvalue;
	
	printf("c setting mob component\n");
	
	if(!PyArg_ParseTuple(args, "ii", &mobid, &newvalue)) { return NULL; }
	_mobs[mobid]->setIsComponent((newvalue == 1 ? true : false));
	
	printf("setMobIsComponent: %d\n", newvalue);
	
	Py_RETURN_TRUE;
}

PyObject* Stage::_script_getMobIsStationary(PyObject* self, PyObject* args)
{
	int mobid;
	if (!PyArg_ParseTuple(args, "i", &mobid)) { return NULL; }

	return (_mobs[mobid]->getIsStationary() ? Py_True : Py_False);
}

PyObject* Stage::_script_setMobIsStationary(PyObject* self, PyObject* args)
{
	int mobid;
	int newvalue;

	printf("c setting mob stationary\n");

	if (!PyArg_ParseTuple(args, "ii", &mobid, &newvalue)) { return NULL; }
	_mobs[mobid]->setIsStationary((newvalue == 1 ? true : false));

	printf("setMobIsStationary: %d\n", newvalue);

	Py_RETURN_TRUE;
}


