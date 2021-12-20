#include <string>
#include <list>

#include "graphics.h"
#include "path_tools.h"

class StageBackdrop
{
	public:
		bool process();
		bool render();
		
		int getWidth() { return _width; }
		int getHeight() { return _height; }
		void setWidth(int value) { _width = value; }
		void setHeight(int value) { _height = value; }
		
		int getRenderWidth() { return _renderWidth; }
		int getRenderHeight() { return _renderHeight; }
		void setRenderWidth(int value) { _renderWidth = value; }
		void setRenderHeight(int value) { _renderHeight = value; }
		
		string getBackdropName() { return _backdropName; }
		void setBackdropName(string value) { _backdropName = value; }
		
		bool loadSprite();
		bool initialize(string backdropName, int width, int height);
		bool initialize(string backdropName);
		bool initialize();
		
		list<SDL_Texture*> sprites;
	
	private:
		string _backdropName = "";
		int _width = 0;
		int _height = 0;
		int _renderWidth = 0;
		int _renderHeight = 0;
};
