#include <string>
#ifdef _WIN32
#include "C:\vclib\SDL2-2.0.18\include\SDL.h"
#include "C:\vclib\SDL2-2.0.18\include\SDL_image.h"
#else
#include <SDL2/SDL.h>
#endif
#include "graphics.h"

using namespace std;

SDL_Texture* Graphics::loadTexture(string path) {
	// The final texture
	SDL_Texture* newTexture = NULL;

	// load the image from path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		// create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(getSDLRenderer(), loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		// clear old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}
