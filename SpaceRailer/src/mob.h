
class Mob
{
	public:
		unsigned int getHitPoints() { return _hitPoints; }
		void setHitPoints(unsigned int value) { _hitPoints = value; }
		
		unsigned int getMagicPoints() { return _magicPoints; }
		void setMagicPoints(unsigned int value) { _magicPoints = value; }
		
		int X() { return _coordX; }
		int Y() { return _coordY; }
		
		bool process();
	
	private:
		unsigned int _hitPoints = 100;
		unsigned int _magicPoints = 0;
		int _coordX = 0;
		int _coordY = 0;
		short _accelerationX = 0;
		short _accelerationY = 0;
		short _accelerationMaxX = 40;
		short _accelerationMaxY = 40;
};
