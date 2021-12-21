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
		void setMapX(int value) { _mapX = value; }
		
		int getMapY() { return _mapY; }
		void setMapY(int value) { _mapY = value; }
		
		int getStageWidth() { return _stageWidth; }
		int getStageHeight() { return _stageHeight; }
		void setStageWidth(int value) { _stageWidth = value; }
		void setStageHeight(int value) { _stageHeight = value; }
		
		int getScrollPixelsPerInterval() { return _scrollPixelsPerInterval; }
		unsigned int getScrollIntervalMS() { return _scrollIntervalMS; }
		void setScrollPixelsPerInterval(int value) { _scrollPixelsPerInterval = value; }
		void setScrollIntervalMS(int value) { _scrollIntervalMS = value; }
		
	private:
		PyObject * _scriptFilename;
		PyObject * _scriptModule;
		PyObject * _scriptFunction;

		unsigned char _stageID = 0;
		string _stageDirectory = "";
		
		int _mapX = 0;
		int _mapY = 0;
		int _stageWidth = 1920 * 4;
		int _stageHeight = 1080 * 4;
		
		unsigned int _lastScrollTick = 0;
		int _scrollPixelsPerInterval = 10;
		unsigned int _scrollIntervalMS = 50;
		
		//	It's unclear to me if this should be an array, linked list, vector,
		//	or something else.  
		vector<Mob> _mobs;
		vector<StageBackdrop *> _backdrops;
		
		float _plasma_effect(float x, float y, float time);
		
		bool _initializeScripting();
		
		PyObject * _script_setPlayerX(PyObject * self, PyObject * args);
		PyObject * _script_setPlayerY(PyObject * self, PyObject * args);
		PyObject * _script_setStageScrollPixelsPerInterval(PyObject * self, PyObject * args);
		PyObject * _script_setStageScrollInterval(PyObject * self, PyObject * args);
};
