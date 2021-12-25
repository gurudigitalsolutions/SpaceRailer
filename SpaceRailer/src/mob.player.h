#include "mob.h"

class Player : public Mob {
private:

public:
	bool initialize() override;
	bool process() override;
};
