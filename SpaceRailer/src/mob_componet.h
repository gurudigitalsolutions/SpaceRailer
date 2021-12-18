#pragma once
#include <list>
#include <string>

#include "graphics.h"
#include "path_tools.h"


class MobComponent {
	public:
		int getX() { return _coordX; }
		int getY() { return _coordY; }

		void setX(int value) { _coordX = value; }
		void setY(int value) { _coordY = value; }

		int getWidth() { return _width; }
		int getHeight() { return _height; }

		void setWidth(int value) { _width = value; }
		void setHeight(int value) { _height = value; }

		list<SDL_Texture*> sprites;
		string componentName;
		string parentName;

		bool process();

		bool render();
		bool initialize(string componentName, string parentName);
		bool initialize();

		bool loadSprites();
		bool loadSprite();


	private:
		int _coordX = 0;
		int _coordY = 0;
		int _width = 0;
		int _height = 0;

};
