
using namespace std;

class ParticleEmitter
{
	public:
		unsigned int getLastUpdateTick() { return _lastUpdateTick; }
		void setLastUpdateTick(unsigned int value) { _lastUpdateTick = value; }
		
		int getX() { return _x; }
		void setX(int value) { _x = value; }
		
		int getY() { return _y; }
		void setY(int value) { _y = value; }
		
		SDL_Texture * getTexture() { return _texture; }
		void setTexture(SDL_Texture * value) { _texture = value; }
		
		bool process();
		bool render();
	
	private:
		unsigned int _lastUpdateTick = 0;
		int _x = 0;
		int _y = 0;
		unsigned int _particles[4096];
		
		SDL_Texture * _texture;
};
