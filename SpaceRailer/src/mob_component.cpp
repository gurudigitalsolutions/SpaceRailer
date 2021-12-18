
#include "mob_componet.h"

bool MobComponent::process() {
	return false;
}
bool MobComponent::render() {
	return false;
}
bool MobComponent::initialize(string componentName, string parentName) {
	this->componentName = componentName;
	this->parentName = parentName;
	loadSprite();
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
bool MobComponent::loadSprite() {
	sprites.push_back(
		Graphics::loadTexture(Path_Tools::getGameDataPath() + "resources/mobs/" + parentName + "/sprites/mob_" + componentName)
	);
	return true;
}

