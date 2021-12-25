#include "mob.h"

class Projectile : public Mob 
{
	public:
		bool initialize() override;
		bool initialize(string mobname) override;
		bool process() override;
		bool render() override;

		short getTracer() { return _tracer; }
		void setTracer(short value) { _tracer = value; }
		
	private:
		short _tracer = 0;


};
