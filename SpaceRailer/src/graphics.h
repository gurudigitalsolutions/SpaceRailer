#pragma once
#include <string>
#ifdef _WIN32
	#include "C:\vclib\SDL2-2.0.18\include\SDL.h"
	#include "C:\vclib\SDL2-2.0.18\include\SDL_image.h"
#else
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
#endif


using namespace std;

class Graphics {
private:
public:
	static SDL_Texture* loadTexture(string path);
};

SDL_Renderer* getSDLRenderer();