#include <string>
#include <filesystem>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <SDL2/SDL.h>
#include <fstream>
#include <string>
#include <math.h>

#ifdef _WIN32
	#include <Windows.h>
#define sleep Sleep
#else
	#include <unistd.h>
	#include <dirent.h>
#endif

#include "particles/particle.h"
#include "particles/particleemitter.h"
#include "particles/particleemitter.mobexplosion.h"
#include "particles/particleemitter.simpleexplosion.h"
#include "config.h"
#include "stage_backdrop.h"
#include "stage.h"
#include "input.h"
#include "stage_api.h"


extern ProgramInput programInput;
extern unsigned int gameTickCount;

extern short windowWidth;
extern short windowHeight;

extern char** getArgv();
extern int getArgc();


struct vec2
{
	float x;
	float y;
};

using namespace std;

//	Static method to create a new Stage object.  This object will handle all
//	interaction with the stage.
Stage * Stage::load(unsigned char stageid)
{
	cout << "Game data path: '" << Path_Tools::getGameDataPath() << "'\n";

	//string stageDir = config.getStageDir() + "stage_" + to_string(stageid) + "/";
	string stageDir = Path_Tools::getStageDataPath("stage_" + to_string(stageid)) + "/";
	cout << "Loading stage: " << stageDir << "\n";
	
	
	if (!Path_Tools::pathExists(stageDir)) {
		printf("stageDir not found in Stage::load (%s)\n", stageDir.c_str());
		return NULL;
	}

	//	Sweet, the stage directory exists.  Now to check the files within
	//	to make sure there is something to load.
	Stage * newStage = new Stage();
	newStage->_stageDirectory = stageDir;
	newStage->_stageID = stageid;
	
	//if(!newStage->_initialize()) { return NULL; }
	
	//	Attempt to read and parse the stage's map file.
	string mapFile = Path_Tools::getStageDataPath("stage_" + to_string(stageid)) + "/map.srm";
	ifstream fileStream;
	fileStream.open(mapFile.c_str());
	
	if(fileStream.is_open()) {
		
		//	the mapFile does exist
	} else {
		cout << "Could not find the map.srm file for the stage\n";
		cout << mapFile + "\n";
		return NULL;
	}
	
	char * mapHeader = new char[128];
	
	fileStream.read(mapHeader, 128);
	
	if(mapHeader[0] != 'S'
	|| mapHeader[1] != 'R'
	|| mapHeader[2] != 'M'
	|| mapHeader[3] != 'F')
	{
		cout << "Missing appropriate map format header.\n";
		return NULL;
	}
	
	if(mapHeader[4] != 0x01
	|| mapHeader[5] != 0x00)
	{
		cout << "Only map version 0x0001 is supported.\n";
		return NULL;
	}
	
	//	Now there are 16 bytes for the map layer sizes
	unsigned short mapForegroundWidth = mapHeader[6] + (mapHeader[7] * 256);
	unsigned short mapForegroundHeight = mapHeader[8] + (mapHeader[9] * 256);
	unsigned short mapActiveWidth = mapHeader[10] + (mapHeader[11] * 256);
	unsigned short mapActiveHeight = mapHeader[12] + (mapHeader[13] * 256);
	unsigned short mapBackgroundWidth = mapHeader[14] + (mapHeader[15] * 256);
	unsigned short mapBackgroundHeight = mapHeader[16] + (mapHeader[17] * 256);
	unsigned short mapBackdropWidth = mapHeader[18] + (mapHeader[19] * 256);
	unsigned short mapBackdropHeight = mapHeader[20] + (mapHeader[21] * 256);
	
	//	32 bytes for the map title
	string mapTitle = "";
	for(short etb = 0x0016; etb < 0x0036; etb++)
	{
		if(mapHeader[etb] == 0) { break ; }
		mapTitle += mapHeader[etb];
	}
	
	cout << "Map title: " + mapTitle + "\n";
	
	//	Load the sprite list
	string tilePath = "";
	unsigned short tileID = 1;
	bool lNull = false;
	bool keepSearching = true;
	char * inByte = new char[1];
	
	while(keepSearching)
	{
		fileStream.read(inByte, 1);
		
		if(inByte[0] == 0)
		{
			//	We've hit the end of a string.  This is the name of a image
			//	file to use.
			if(lNull)
			{
				//	The previous byte was also null.  We are done searching
				//	for tile names.
				keepSearching = false;
			}
			else
			{
				lNull = true;
				cout << "Tile: " + tilePath + "\n";
				
				//	Load this resource, or do something to indicate something
				//	about it.  We load the first sprite twice so that index 0
				//	is taken by something.  (This is rendered as nothing, but
				//	we still need something there)
				newStage->_loadSprite(tilePath);
				if(tileID < 2) { newStage->_loadSprite(tilePath); }
				
				//	Reset the tile path so we can read another
				tilePath = "";
				
				if(tileID == 0xFFFF)
				{
					//	Too many tiles defined!!!@!
					cout << "Too many tiles defined for stage.\n";
				}
				else { tileID++; }
			}
		}
		else
		{
			lNull = false;
			tilePath += inByte[0];
		}
	}
	
	//	Now all the map data can be loaded
	char * mapDataBuffer = new char[4096 * 4096];
	
	//	Foreground
	fileStream.read(mapDataBuffer, (mapForegroundWidth * mapForegroundHeight * 4));
	newStage->_mapForegroundLayer = new StageMapLayer();
	newStage->_mapForegroundLayer->initialize(mapForegroundWidth, mapForegroundHeight, (unsigned char *)mapDataBuffer);
	
	//	Active Layer
	fileStream.read(mapDataBuffer, (mapActiveWidth * mapActiveHeight * 4));
	newStage->_mapActiveLayer = new StageMapLayer();
	newStage->_mapActiveLayer->initialize(mapActiveWidth, mapActiveHeight, (unsigned char *)mapDataBuffer);
	
	//	Background
	fileStream.read(mapDataBuffer, (mapBackgroundWidth * mapBackgroundHeight * 4));
	newStage->_mapBackgroundLayer = new StageMapLayer();
	newStage->_mapBackgroundLayer->initialize(mapBackgroundWidth, mapBackgroundHeight, (unsigned char *)mapDataBuffer);
	
	//	Backdrop
	fileStream.read(mapDataBuffer, (mapBackdropWidth * mapBackdropHeight * 4));
	newStage->_mapBackdropLayer = new StageMapLayer();
	newStage->_mapBackdropLayer->initialize(mapBackdropWidth, mapBackdropHeight, (unsigned char *)mapDataBuffer);
	
	fileStream.close();
	
	return newStage;
}

//	Initialize this stage.  This method will attempt to create a scripting
//	interpreter for the stage, and then run the initialization sequence for
//	the scripting engine.  If this fails, it will return false.
bool Stage::initialize()
{
	if(_stageDirectory == "")
	{
		cout << "Failed to initialize.  Stage directory not found.\n";
		return false;
	}
	
	// TODO	Check if the proper resources are available
	//	Start with the graphics directory
	_player.setWidth(128);
	_player.setHeight(128);
	//_player.setX(30);
	//_player.setY(30);
	
	if (!_player.initialize())
	{
		cout << "player is already dead, failed to initialize\n";
	}
	
	//	Attempt to launch the scripting engine for this stage
	if(!_initializeScripting())
	{
		cout << "Scripting engine could not be initialized.\n";
		return NULL;
	}
	
	_scriptFunction = PyObject_GetAttrString(_scriptModule, "initialize");
	if(_scriptFunction && PyCallable_Check(_scriptFunction))
	{
		PyObject_CallObject(_scriptFunction, NULL);
	}

	
	
	//_player.addComponent("thruster0", 0, 64, 55, 55);
	//_player.addComponent("thruster0", 0, 64, 25, 25, COMPONENT_ATTACH_LOOSE, 40, 40);
	/*Mob * newMob = new Mob();
	newMob->setX(56);
	newMob->setY(80);
	newMob->setWidth(28);
	newMob->setHeight(28);
	newMob->initialize("thruster0");
	newMob->setIsComponent(true);
	newMob->setParent((Mob *)&_player);
	addMob(newMob);*/
	

	StageBackdrop * nBackdrop = new StageBackdrop();
	//nBackdrop->initialize("Eta_Carinae_Nebula", 1920, 1080);
	nBackdrop->initialize("space-background-1", 1024, 600);
	_backdrops.push_back(nBackdrop);
	
	//	Test for particle engine
	/*ParticleEmitter * testEmitter = new ParticleEmitter();
	testEmitter->setX(900);
	testEmitter->setY(200);
	testEmitter->setTexture(_player.sprites.front());
	testEmitter->initialize();
	_emitters.push_back(testEmitter);*/
	
	return true;
}

//	Process is called once per world tick.  This should handle all the stuff.
//	Be careful not to do too much stuff at one time because it will stall the
//	next frame from being rendered.
bool Stage::process()
{
	//	Check if it's time to scroll the map
	/*if(gameTickCount - _lastScrollTick >= getScrollIntervalMS())
	{
		//	This can actually do more precise math.  If the interval is say 10,
		//	and it's been 12 ms, we could leave that 2 left over.  For now I'm
		//	not going to worry about it.
		_lastScrollTick = gameTickCount;
		
		int newMapX = getMapX() + getScrollPixelsPerInterval();
		if(newMapX > getStageWidth() - windowWidth) { newMapX = getStageWidth() - windowWidth; }
		else
		{
			_player.setX(_player.getX() + getScrollPixelsPerInterval());
			
			for(unsigned int emob = 0; emob < _mobs.size(); emob++)
			{
				if(_mobs[emob]->getIsStationary())
				{
					_mobs[emob]->setX(_mobs[emob]->getX() + getScrollPixelsPerInterval());
				}
			}
		}
		
		setMapX(newMapX);
		
		_callback_stageScrollEvent();
		
		
	}*/
	
	//	Check if the player is trying to move around.
	InputData currentInputState = programInput.getCurrentInputState();
	InputData previousInputState = programInput.getPreviousInputState();
	
	/*if(currentInputState.analogRight > 16384) { _player.setX(_player.getX() + 3); }
	if(currentInputState.analogLeft > 16384) { _player.setX(_player.getX() - 3); }
	if(currentInputState.analogUp > 16384) { _player.setY(_player.getY() - 3); }
	if(currentInputState.analogDown > 16384) { _player.setY(_player.getY() + 3); }*/
	
	if(currentInputState.analogRight > 16384) { _player.changeTileXOffset(3); }
	if(currentInputState.analogLeft > 16384) { _player.changeTileXOffset(-3); }
	if(currentInputState.analogUp > 16384) { _player.changeTileYOffset(-3); }
	if(currentInputState.analogDown > 16384) { _player.changeTileYOffset(3); }
	
	//	Make sure that the player is not too close to the edges of the map
	if(_player.getTileX() < 13)
	{
		_player.setTileX(13);
		_player.setTileXOffset(0);
	}
	
	if(_player.getTileY() < 7)
	{
		_player.setTileY(7);
		_player.setTileYOffset(0);
	}
	
	//	Set the viewport to be in a contant position compared to the player
	setViewportX(_player.getTileX() - 13);
	setViewportY(_player.getTileY() - 7);
	setViewportXOffset(_player.getTileXOffset());
	setViewportYOffset(_player.getTileYOffset());
	
	//	Check if we are at a boundary of the screen
	/*if(_player.getTileX() > (getViewportX() + 17))
	{
		short newX = _player.getTileX() - getViewportX();
		if(newX == getViewportX() - 17)
		{
			setViewportXOffset(_player.getTileXOffset());
		}
		else
		{
			setViewportX(getViewportX() + newX - 17);
			setViewportXOffset(_player.getTileXOffset());
		}
	}
	else if(_player.getTileX() < (getViewportX() + 11)
	&& _player.getTileX() > 12)
	{
		short newX = _player.getTileX() - getViewportX();
		setViewportX(getViewportX() - newX + 9);
		
		setViewportXOffset(_player.getTileXOffset());
	}
	
	if(_player.getTileY() > (getViewportY() + 10))
	{
		short newY = _player.getTileY() - getViewportY();
		setViewportY(getViewportY() + newY - 10);
		
		setViewportYOffset(_player.getTileYOffset());
	}
	else if(_player.getTileY() < (getViewportY() + 7)
	&& _player.getTileY() > 8)
	{
		short newY = _player.getTileY() - getViewportY();
		setViewportY(getViewportY() - newY + 5);
		
		setViewportYOffset(_player.getTileYOffset());
	}*/

	// make it shoot something?
	if (currentInputState.buttonFire) {
		if (!previousInputState.buttonFire) {
			if(gameTickCount - _player.getLastShotTick() > _player.getShotCooldown_ms())
			{
				_player.setLastShotTick(gameTickCount);
				_player.createProjectile();
				cout << "shoot \n";
			}
		}
	}
	
	if(currentInputState.buttonPause) {
		while(1)
		{
			sleep(1);
		}
	}
	
	_player.process();
	
	//	Process data for each mob
	_callback_mobProcess();
	for(int emob = 0; emob < (int)_mobs.size(); emob++)
	{
		_mobs[emob]->process();
		
		if(_mobs[emob]->getMarkForDestroy())
		{
			//	Whatever happened during this mob's processing has indicated
			//	that the mob should be destroyed.
			
			//	Check if an explosion should be created.  If so, then we need
			//	to initialize the effect here.
			if(!_mobs[emob]->getIsProjectile())
			{
				MobExplosion * nEmitter = new MobExplosion();
				nEmitter->setX(_mobs[emob]->getX());
				nEmitter->setY(_mobs[emob]->getY());
				nEmitter->setTexture(_mobs[emob]->sprites.front());
				nEmitter->initialize();
				_emitters.push_back((ParticleEmitter *)nEmitter);
				
				//	Make a second emitter for the fireball explosion
				SimpleExplosion * fEmitter = new SimpleExplosion();
				fEmitter->setX(_mobs[emob]->getX() + (_mobs[emob]->getWidth() / 2));
				fEmitter->setY(_mobs[emob]->getY() + (_mobs[emob]->getHeight() / 2));
				//fEmitter->setTexture(Graphics::loadTexture(Path_Tools::getGameDataPath() + "resources/particles/star.png"));
				fEmitter->setTextureName(Path_Tools::getGameDataPath() + "resources/particles/round.png");
				fEmitter->initialize();
				_emitters.push_back((ParticleEmitter *)fEmitter);
			}
			
			_callback_mobDestroyed(emob);
			_mobs[emob] = new Mob();
		}
	}
	
	
	//	Check for collisions.  First, look through ALL mobs, starting with
	//	the player and continuing on with all others.
	for(int emob = -1; emob < (int)_mobs.size(); emob++)
	{
		//	Get a pointer to the mob we are checking
		Mob * tmob;
		Mob * inmob;
		
		if(emob == -1) { tmob = (Mob *)&_player; }
		else { tmob = _mobs[emob]; }
		
		if(tmob != nullptr)
		{
			//	Loop through each other mob in the list and check if this mob
			//	has collided with the sub-mob
			for(int ecol = emob + 1; ecol < (int)_mobs.size(); ecol++)
			{
				inmob = _mobs[ecol];
				if(inmob != nullptr)
				{
					if(_mobs[ecol]->checkCollision(
						tmob->getXWithHitbox(),
						tmob->getYWithHitbox(),
						tmob->getHitboxWidth(),
						tmob->getHitboxHeight()
					))
					{
						//	The outer mob has collided with the inner mob.
						tmob->registerCollision(inmob);
					}
				}
			}
		}
	}
	
	//	Process all particle emitters
	for(int eemit = 0; eemit < (int)_emitters.size(); eemit++)
	{
		if(_emitters[eemit]->getActive()) { _emitters[eemit]->process(); }
	}
	
	return true;
}

float Stage::_plasma_effect(float x, float y, float time)
{
	float v1, v2, v3;
	struct vec2 coor;
	
	x = -0.05f + (float)x / 64;
	y = -0.05f + (float)y / 64;
	
	v1 = sin(x * 10 + time);
	v2 = sin(10 * (x * sin(time / 2) + y * cos(time / 3)) + time);
	
	coor.x = x + 0.05f * sin(time / 5);
	coor.y = y + 0.05f * cos(time / 3);
	v3 = sin(sqrt(100 * (coor.x * coor.x * coor.y * coor.y) + 1) + time);
	
	return (v1 + v2 + v3);
}

//	Render is called once per frame to render the screen.  Heavy processing
//	should not be done here.
bool Stage::render()
{
	//	Draw from the back to the front.  Otherwise things will be drawn over
	StageMapLayer * tMapLayer;
	for(unsigned char eml = 0; eml < 4; eml++)
	{
		if(eml == 0) { tMapLayer = _mapBackdropLayer; }
		else if(eml == 1) { tMapLayer = _mapBackgroundLayer; }
		else if(eml == 2) { tMapLayer = _mapActiveLayer; }
		else { tMapLayer = _mapForegroundLayer; }
		
		//	layervpx / layerwidth = activepx / activewidth
		unsigned short vpX = (tMapLayer->getWidth() * getViewportX()) / _mapActiveLayer->getWidth();
		unsigned short vpY = (tMapLayer->getHeight() * getViewportY()) / _mapActiveLayer->getHeight();
		
		//	Calculate the offset needed for background and backdrop layers
		unsigned short layerOffsetX = 0;
		unsigned short layerOffsetY = 0;
		
		if(eml == 0
		|| eml == 1)
		{
			layerOffsetX = ceil(_mapActiveLayer->getWidth() / tMapLayer->getWidth());
			layerOffsetX = (32 / layerOffsetX) * (getViewportX() % layerOffsetX);
			
			layerOffsetY = ceil(_mapActiveLayer->getHeight() / tMapLayer->getHeight());
			layerOffsetY = (32 / layerOffsetY) * (getViewportY() % layerOffsetY);
		}
		
		for(unsigned short my = 0; my < 18; my++)
		{
			for(unsigned short mx = 0; mx < 32; mx++)
			{
				unsigned short spriteid = tMapLayer->getTile(
					/*mx + getViewportX(),
					my + getViewportY()*/
					mx + vpX,
					my + vpY
				)->getSpriteID();
				
				SDL_Rect box;
				box.w = 32;
				box.h = 32;
				box.y = my * 32 - (eml == 2 ? getViewportYOffset() : layerOffsetY);
				box.x = mx * 32 - (eml == 2 ? getViewportXOffset() : layerOffsetX);
				
				//SDL_RenderCopy(getSDLRenderer(), sprites.front(), NULL, &box);
				/*if(eml == 1)
				{
					cout << "Rendering sprite id: " + to_string(spriteid) + " Layer " + to_string(eml) + "\n";
				}*/
				
				if(spriteid > 0)
				{
					SDL_RenderCopyEx(
						getSDLRenderer(), 
						_sprites[spriteid], 
						NULL, 
						&box, 
						0.0, //_renderAngle, 
						NULL, 
						SDL_FLIP_NONE
					);
				}
			}
		}
	}
	
	//	Render backdrops
	/* disabled to implement the new tile system
	for(auto esb : _backdrops)
	{
		esb->render();
	}*/
	

	
	_player.render();
	
	//	Render mobs
	for(int emob = 0; emob < (int)_mobs.size(); emob++)
	{
		if(_mobs[emob] != nullptr)
		{
			_mobs[emob]->render();
		}
	}
	
	//	Render particle emitters and particles
	for(int eemit = 0; eemit < (int)_emitters.size(); eemit++)
	{
		if(_emitters[eemit]->getActive()) { _emitters[eemit]->render(); }
	}
	
	
	return true;
}

void Stage::addMob(Mob * mob)
{
	_mobs.push_back(mob);
}

//	Initialize the scripting engine for this stage.
bool Stage::_initializeScripting()
{
	
	//	First, check that the stage python script exists.
	FILE * fh = fopen((_stageDirectory + "__init__.py").c_str(), "r");
	if(fh == NULL)
	{
		cout << "__init__.py missing for this stage.\n";
		return false;
	}
	fclose(fh);
	
	//	Script exists, so lets initialize the API.  This must be done before
	//	the call to Py_Initialize()
	PyImport_AppendInittab("spacerailer", &PyInit_pySpaceRailerModule);

	Py_Initialize();

	PyRun_SimpleString("import sys");
	
	string dpath = "sys.path.append(\"" + Path_Tools::getGameDataPath() + "resources/stages\")";
	PyRun_SimpleString(dpath.c_str());
	
	dpath = "sys.path.append(\"" + Path_Tools::getMobsDataPath() + "\")";
	PyRun_SimpleString(dpath.c_str());
	
	_scriptFilename = PyUnicode_DecodeFSDefault("stage_0");
	_scriptModule = PyImport_Import(_scriptFilename);
	Py_DECREF(_scriptFilename);
	
	//	Check if importing was successful.
	if(_scriptModule == NULL)
	{
		PyErr_Print();
		return false;
	}
	
	//	Looks like the python module has been loaded!
	_scriptFilename = PyUnicode_DecodeFSDefault("enemy1");
	PyImport_Import(_scriptFilename);
	Py_DECREF(_scriptFilename);
	
	return true;
}


bool Stage::_loadSprite(string spritename)
{
	_sprites.push_back(
		Graphics::loadTexture(Path_Tools::getGameDataPath() + "resources/" + spritename)
	);
	
	return true;
}
