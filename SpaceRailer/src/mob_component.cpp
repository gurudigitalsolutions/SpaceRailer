
#include "mob_componet.h"

bool MobComponent::process() {
	return false;
}
bool MobComponent::render() {
	return false;
}
bool MobComponent::initialize(string compName, string parentMob) {
	return false;
}
bool MobComponent::initialize() {
	return false;
}
bool MobComponent::loadSprites() {
	//	Check game data path for additional sprites to load for this mob
	// loops through available sprites
	return true;
}
bool MobComponent::loadSprite(string spriteName) {
	Graphics::loadTexture("")
}

