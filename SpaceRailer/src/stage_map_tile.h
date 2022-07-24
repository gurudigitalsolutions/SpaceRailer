#include <string>
#include <filesystem>

using namespace std;

class StageMapTile
{
	public:
		void _initialize(unsigned short spriteID);

		unsigned short getSpriteID() { return _spriteID; }
		
		bool getIsSolid();
		void setIsSolid(bool value) { _isSolid = value; }
		
		bool getIsWater() { return _isWater; }
		void setIsWater(bool value) { _isWater = value; }
		
		bool getDoesDamage() { return _doesDamage; }
		void setDoesDamage(bool value) { _doesDamage = value; }
	
	private:
		unsigned short _spriteID = 0;
		bool _isSolid = true;
		bool _isWater = false;
		bool _doesDamage = false;
		
};
