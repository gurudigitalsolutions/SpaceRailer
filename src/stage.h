#include <string>
#include <filesystem>
#include <unistd.h>

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
		
	private:
		unsigned char _stageID = 0;
		string _stageDirectory = "";
		
		bool _initialize();
		
};
