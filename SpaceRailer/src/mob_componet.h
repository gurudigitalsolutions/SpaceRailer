#pragma once
#include <list>
#include <string>

#include "graphics.h"
#include "path_tools.h"

enum componentAttachMode { COMPONENT_ATTACH_STUCK, COMPONENT_ATTACH_LOOSE };

class MobComponent {
	public:
		int getX() { return _coordX; }
		int getY() { return _coordY; }

		void setX(int value) { _coordX = value; }
		void setY(int value) { _coordY = value; }
		
		int getTempX() { return _tempX; }
		int getTempY() { return _tempY; }
		
		void setTempX(int value) { _tempX = value; }
		void setTempY(int value) { _tempY = value; }
		
		int getParentX() { return _parentX; }
		int getParentY() { return _parentY; }
		
		void setParentX(int value) { _parentX = value; }
		void setParentY(int value) { _parentY = value; }

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

		componentAttachMode getAttachMode() { return _attachMode; }
		void setAttachMode(componentAttachMode value) { _attachMode = value; }
		
		unsigned char getAttachMaxDistanceX() { return _attachMaxDistanceX; }
		unsigned char getAttachMaxDistanceY() { return _attachMaxDistanceY; }
		void setAttachMaxDistanceX(unsigned char value) { _attachMaxDistanceX = value; }
		void setAttachMaxDistanceY(unsigned char value) { _attachMaxDistanceY = value; }
		
		unsigned int getLastUpdateTick() { return _lastUpdateTick; }

	private:
		int _coordX = 0;
		int _coordY = 0;
		int _tempX = 0;
		int _tempY = 0;
		int _parentX = 0;
		int _parentY = 0;
		int _width = 0;
		int _height = 0;
		componentAttachMode _attachMode = COMPONENT_ATTACH_STUCK;
		unsigned char _attachMaxDistanceX = 0;
		unsigned char _attachMaxDistanceY = 0;
		unsigned int _lastUpdateTick = 0;
};
