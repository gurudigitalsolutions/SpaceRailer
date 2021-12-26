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

//	Handle incoming functions from the Python API
PyObject* Stage::processAPI(PyObject* self, PyObject* args, string method)
{
	if (method == "numargs") { return PyLong_FromLong(420); }
	if (method == "getMapX") { return PyLong_FromLong(getMapX()); }
	if (method == "getMapY") { return PyLong_FromLong(getMapY()); }
	if (method == "getPlayerX") { return PyLong_FromLong(_player.getX()); }
	if (method == "getPlayerY") { return PyLong_FromLong(_player.getY()); }
	if (method == "setPlayerX") { return _script_setPlayerX(self, args); }
	if (method == "setPlayerY") { return _script_setPlayerY(self, args); }
	if (method == "getPlayerHP") { return PyLong_FromLong(_player.getHitPoints()); }
	if (method == "getPlayerWidth") { return PyLong_FromLong(_player.getWidth()); }
	if (method == "getPlayerHeight") { return PyLong_FromLong(_player.getHeight()); }
	if (method == "getStageScrollPixelsPerInterval") { return PyLong_FromLong(getScrollPixelsPerInterval()); }
	if (method == "setStageScrollPixelsPerInterval") { return _script_setStageScrollPixelsPerInterval(self, args); }
	if (method == "getStageScrollInterval") { return PyLong_FromLong(getScrollIntervalMS()); }
	if (method == "setStageScrollInterval") { return _script_setStageScrollInterval(self, args); }
	if (method == "createMob") { return _script_createMob(self, args); }
	if (method == "getMobX") { return _script_getMobX(self, args); }
	if (method == "getMobY") { return _script_getMobY(self, args); }
	if (method == "setMobX") { return _script_setMobX(self, args); }
	if (method == "setMobY") { return _script_setMobY(self, args); }
	if (method == "getMobWidth") { return _script_getMobWidth(self, args); }
	if (method == "getMobHeight") { return _script_getMobHeight(self, args); }
	if (method == "setMobWidth") { return _script_setMobWidth(self, args); }
	if (method == "setMobHeight") { return _script_setMobHeight(self, args); }
	if (method == "getMobAngle") { return _script_getMobAngle(self, args); }
	if (method == "setMobAngle") { return _script_setMobAngle(self, args); }
	if (method == "getMobIsComponent") { return _script_getMobIsComponent(self, args); }
	if (method == "setMobIsComponent") { return _script_setMobIsComponent(self, args); }
	if (method == "getMobParent") { return _script_getMobParent(self, args); }
	if (method == "setMobParent") { return _script_setMobParent(self, args); }
	if (method == "getMobIsStationary") { return _script_getMobIsStationary(self, args); }
	if (method == "setMobIsStationary") { return _script_setMobIsStationary(self, args); }

	return NULL;
}

PyObject* Stage::_script_setPlayerX(PyObject* self, PyObject* args)
{
	int newPlayerX;
	if (!PyArg_ParseTuple(args, "i", &newPlayerX)) { return NULL; }

	_player.setX(newPlayerX);
	Py_RETURN_TRUE;
}

PyObject* Stage::_script_setPlayerY(PyObject* self, PyObject* args)
{
	int newPlayerY;
	if (!PyArg_ParseTuple(args, "i", &newPlayerY)) { return NULL; }

	_player.setY(newPlayerY);
	Py_RETURN_TRUE;
}

PyObject* Stage::_script_setStageScrollPixelsPerInterval(PyObject* self, PyObject* args)
{
	int ssp;
	if (!PyArg_ParseTuple(args, "i", &ssp)) { return NULL; }

	setScrollPixelsPerInterval(ssp);
	Py_RETURN_TRUE;
}

PyObject* Stage::_script_setStageScrollInterval(PyObject* self, PyObject* args)
{
	int ssi;
	if (!PyArg_ParseTuple(args, "i", &ssi)) { return NULL; }

	setScrollIntervalMS(ssi);
	Py_RETURN_TRUE;
}

void Stage::_callback_stageScrollEvent()
{
	_scriptFunction = PyObject_GetAttrString(_scriptModule, "stageScrollEvent");
	if (_scriptFunction && PyCallable_Check(_scriptFunction))
	{
		PyObject_CallObject(_scriptFunction, NULL);
	}
}

void Stage::_callback_mobProcess()
{
	_scriptFunction = PyObject_GetAttrString(_scriptModule, "mobProcess");
	if (_scriptFunction && PyCallable_Check(_scriptFunction))
	{
		PyObject_CallObject(_scriptFunction, NULL);
	}
}

void Stage::_callback_mobDestroyed(int mobid)
{
	_scriptFunction = PyObject_GetAttrString(_scriptModule, "mobDestroyed");
	if(_scriptFunction && PyCallable_Check(_scriptFunction))
	{
		PyObject * args;
		args = Py_BuildValue("(i)", mobid);
		PyObject_CallObject(_scriptFunction, args);
		Py_DECREF(args);
	}
}

PyObject* Stage::_script_createMob(PyObject* self, PyObject* args)
{
	char* pymobtype;


	if (!PyArg_ParseTuple(args, "s", &pymobtype)) { return NULL; }
	printf("FIlename: %s\n", pymobtype);
	//string mobtype = (char *)&pymobtype;

	Mob* newMob = new Mob();
	newMob->initialize((string)pymobtype);

	_mobs.push_back(newMob);
	ssize_t mobid = _mobs.size() - 1;

	return PyLong_FromSsize_t(mobid);
}

PyObject* Stage::_script_getMobX(PyObject* self, PyObject* args)
{
	//printf("Getting mobx");
	int mobid;
	if (!PyArg_ParseTuple(args, "i", &mobid)) { return NULL; }

	return PyLong_FromLong(_mobs[mobid]->getX());
}

PyObject* Stage::_script_getMobY(PyObject* self, PyObject* args)
{
	int mobid;
	if (!PyArg_ParseTuple(args, "i", &mobid)) { return NULL; }

	return PyLong_FromLong(_mobs[mobid]->getY());
}

PyObject* Stage::_script_setMobX(PyObject* self, PyObject* args)
{
	int mobid;
	int newvalue;

	if (!PyArg_ParseTuple(args, "ii", &mobid, &newvalue)) { return NULL; }
	_mobs[mobid]->setX(newvalue);

	Py_RETURN_TRUE;
}

PyObject* Stage::_script_setMobY(PyObject* self, PyObject* args)
{
	int mobid;
	int newvalue;

	if (!PyArg_ParseTuple(args, "ii", &mobid, &newvalue)) { return NULL; }
	_mobs[mobid]->setY(newvalue);

	Py_RETURN_TRUE;
}

PyObject* Stage::_script_getMobWidth(PyObject* self, PyObject* args)
{
	int mobid;
	if (!PyArg_ParseTuple(args, "i", &mobid)) { return NULL; }

	return PyLong_FromLong(_mobs[mobid]->getWidth());
}

PyObject* Stage::_script_getMobHeight(PyObject* self, PyObject* args)
{
	int mobid;
	if (!PyArg_ParseTuple(args, "i", &mobid)) { return NULL; }

	return PyLong_FromLong(_mobs[mobid]->getHeight());
}

PyObject* Stage::_script_setMobWidth(PyObject* self, PyObject* args)
{
	int mobid;
	int newvalue;

	if (!PyArg_ParseTuple(args, "ii", &mobid, &newvalue)) { return NULL; }
	_mobs[mobid]->setWidth(newvalue);

	Py_RETURN_TRUE;
}

PyObject* Stage::_script_setMobHeight(PyObject* self, PyObject* args)
{
	int mobid;
	int newvalue;

	if (!PyArg_ParseTuple(args, "ii", &mobid, &newvalue)) { return NULL; }
	_mobs[mobid]->setHeight(newvalue);

	Py_RETURN_TRUE;
}

PyObject* Stage::_script_getMobAngle(PyObject* self, PyObject* args)
{
	int mobid;
	if (!PyArg_ParseTuple(args, "i", &mobid)) { return NULL; }

	return PyFloat_FromDouble(_mobs[mobid]->getRenderAngle());
}

PyObject* Stage::_script_setMobAngle(PyObject* self, PyObject* args)
{
	int mobid;
	double newvalue;

	if (!PyArg_ParseTuple(args, "id", &mobid, &newvalue)) { return NULL; }
	_mobs[mobid]->setRenderAngle(newvalue);

	Py_RETURN_TRUE;
}

PyObject* Stage::_script_getMobParent(PyObject* self, PyObject* args)
{
	int mobid;
	if (!PyArg_ParseTuple(args, "i", &mobid)) { return NULL; }

	//	In most cases, we can just return the mobid from the vector of _mobs.
	//	However, there might be a special case where the parent is the _player
	//	or some other special mob.

	//	Check if this mob even HAS a parent
	if (_mobs[mobid]->getParent()) { return PyLong_FromLong(-1); }

	//	Check if the mob's parent is the player
	if (_mobs[mobid]->getParent() == &_player) { return PyLong_FromLong(-2); }

	for (unsigned int emob = 0; emob < _mobs.size(); emob++)
	{
		Mob* tMob = _mobs[emob]->getParent();
		if (tMob != NULL
			&& tMob == _mobs[emob])
		{
			return PyLong_FromLong(emob);
		}
	}

	//	No parent was found for this mob
	return PyLong_FromLong(-1);
}

PyObject* Stage::_script_setMobParent(PyObject* self, PyObject* args)
{
	printf("setting mob parent\n");

	int mobid;
	int newvalue;

	if (!PyArg_ParseTuple(args, "ii", &mobid, &newvalue)) { return NULL; }

	if (newvalue == -2)
	{
		printf("Assigning player as mob %d parent.\n", mobid);
		_mobs[mobid]->setParent((Mob*)&_player);
		Py_RETURN_TRUE;
	}

	_mobs[mobid]->setParent(_mobs[newvalue]);

	Py_RETURN_TRUE;
}

PyObject* Stage::_script_getMobIsComponent(PyObject* self, PyObject* args)
{
	int mobid;
	if (!PyArg_ParseTuple(args, "i", &mobid)) { return NULL; }

	return (_mobs[mobid]->getIsComponent() ? Py_True : Py_False);
}

PyObject* Stage::_script_setMobIsComponent(PyObject* self, PyObject* args)
{
	int mobid;
	int newvalue;

	printf("c setting mob component\n");

	if (!PyArg_ParseTuple(args, "ii", &mobid, &newvalue)) { return NULL; }
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
