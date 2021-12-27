
using namespace std;

class Particle
{
	public:
		float getX() { return _x; }
		void setX(float value) { _x = value; }
		float getY() { return _y; }
		void setY(float value) { _y = value; }
		float getZ() { return _z; }
		void setZ(float value) { _z = value; }
		
		float getVelocityX() { return _velocityX; }
		float getVelocityY() { return _velocityY; }
		float getVelocityZ() { return _velocityZ; }
		void setVelocityX(float value) { _velocityX = value; }
		void setVelocityY(float value) { _velocityY = value; }
		void setVelocityZ(float value) { _velocityZ = value; }
		
		void setTexture(SDL_Texture * value) { _texture = value; }
		void setTextureCoords(int x1, int x2, int y1, int y2);
		
		bool process();
		bool render();
	
	private:
		float _x = 0.0;
		float _y = 0.0;
		float _z = 0.0;
		
		float _velocityX = 0.0;
		float _velocityY = 0.0;
		float _velocityZ = 0.0;
		
		SDL_Texture * _texture;
		int _textureX1 = 0;
		int _textureX2 = 0;
		int _textureY1 = 0;
		int _textureY2 = 0;
};
