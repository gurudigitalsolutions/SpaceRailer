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
		
		unsigned char getStageID() { return _stageID; }
		
		bool process();
		bool render();

		Player _player;
		
	private:
		PyObject * _scriptFilename;
		PyObject * _scriptModule;
		PyObject * _scriptFunction;
		
		unsigned char _stageID = 0;
		string _stageDirectory = "";
		
		//	It's unclear to me if this should be an array, linked list, vector,
		//	or something else.  
		vector<Mob> _mobs;
		
		bool _initialize();
		bool _initializeScripting();
};
