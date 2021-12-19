#include <string>
#include <filesystem>
//#include <unistd.h>
#include <vector>
#include <Python.h>
//#include "mob.h"
#include "player.h"


extern Config config;

//	These are actually defined in main.cpp
SDL_Window * getSDLWindow();
SDL_Renderer * getSDLRenderer();
SDL_Surface * getSDLPrimarySurface();

using namespace std;

class Stage
{
	public:
		static Stage * load(unsigned char stageid);
		bool initialize();
		
		unsigned char getStageID() { return _stageID; }
		
		bool process();
		bool render();
		PyObject * processAPI(PyObject * self, PyObject * args, string method);

		Player _player;
		
		int getMapX() { return _mapX; }
		//PyObject * script_getMapX(PyObject * self, PyObject * args) { return PyLong_FromLong(getMapX()); }
		void setMapX(int value) { _mapX = value; }
		
		int getMapY() { return _mapY; }
		//PyObject * script_getMapY(PyObject * self, PyObject * args) { return PyLong_FromLong(getMapY()); }
		void setMapY(int value) { _mapY = value; }
		
	private:
		PyObject * _scriptFilename;
		PyObject * _scriptModule;
		PyObject * _scriptFunction;

		unsigned char _stageID = 0;
		string _stageDirectory = "";
		
		int _mapX = 0;
		int _mapY = 0;
		
		//	It's unclear to me if this should be an array, linked list, vector,
		//	or something else.  
		vector<Mob> _mobs;
		
		
		bool _initializeScripting();
		
		PyObject * _script_setPlayerX(PyObject * self, PyObject * args);
		PyObject * _script_setPlayerY(PyObject * self, PyObject * args)
};
