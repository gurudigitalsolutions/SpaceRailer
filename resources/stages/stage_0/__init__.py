import spacerailer
from mob import Mob
from enemy1 import FirstEnemy
import os

playerThrusterID = 0
firstMob = {}

mobs = {}

#	stageWave and stageCounter are used to keep track of how for into the stage
#	the player is.  These can be used by the script to know when to change
#	stage properties, spawn enemies, etc.
stageWave = 0
stageCounter = 0

print("CWD: ", os.getcwd())

def initialize():
	global mobs
	global firstMob
	global stageWave
	global stageCounter
	
	spacerailer.setPlayerX(50)
	spacerailer.setPlayerY(256)
	
	#spacerailer.setStageScrollPixelsPerInterval(3)
	spacerailer.setStageScrollPixelsPerInterval(0)
	spacerailer.setStageScrollInterval(50)
	
	#	Create the thruster for the player
	playerThrusterID = spacerailer.createMob("thruster0")
	spacerailer.setMobX(playerThrusterID, 56)
	spacerailer.setMobY(playerThrusterID, 80)
	spacerailer.setMobWidth(playerThrusterID, 28)
	spacerailer.setMobHeight(playerThrusterID, 28)
	spacerailer.setMobParent(playerThrusterID, -2)
	spacerailer.setMobIsComponent(playerThrusterID, True)
	
	stageWave = 0
	stageCounter = 0
	
	#	Load backdrops for the stage
	#	Setup any other details
	


def stageScrollEvent():
	global mobs
	global firstMob
	global stageWave
	global stageCounter
	
	if(stageWave == 0 
		and spacerailer.getMapX() >= 100
		and stageCounter == 0):
	
		spacerailer.setStageScrollPixelsPerInterval(0)
		stageCounter = stageCounter + 1
		
		temp = FirstEnemy()
		temp.setX(2000)
		temp.setY(180)
		temp.setIsStationary(True)
		
		mobs = { 
			temp.ID: {
				"name": "firstenemy",
				"data": temp
			}
		}
		
	if(stageWave == 0
		and stageCounter == 1):
		fenemyid = findMobID("firstenemy")
		jamesid = findMobID("james")
		jamalid = findMobID("jamal")
		
		if(fenemyid == -1
			and jamesid == -1
			and jamalid == -1):
			
			stageCounter = 2
			spacerailer.setStageScrollPixelsPerInterval(5)
			
			temp = FirstEnemy()
			temp.setX(spacerailer.getPlayerX() + 1000)
			temp.setY(-500)
			addMobID(temp.ID, "bob", temp)
			
			temp = FirstEnemy()
			temp.setX(spacerailer.getPlayerX() + 1000)
			temp.setY(-300)
			addMobID(temp.ID, "billy", temp)
			
			temp = FirstEnemy()
			temp.setX(spacerailer.getPlayerX() + 1000)
			temp.setY(-100)
			addMobID(temp.ID, "jerry", temp)
			
			temp = FirstEnemy()
			temp.setX(spacerailer.getPlayerX() + 1000)
			temp.setY(300)
			addMobID(temp.ID, "lester", temp)
			
			temp = FirstEnemy()
			temp.setX(spacerailer.getPlayerX() + 1000)
			temp.setY(500)
			addMobID(temp.ID, "dave", temp)
			
			
	"""firstMob.setAngle(firstMob.getAngle() + 3)
	if firstMob.getAngle() > 360:
		firstMob.setAngle(firstMob.getAngle() - 360)"""


def mobProcess():
	#	Process stuff that mobs should do
	processEnemyType1("firstenemy")
	processEnemyType1("james")
	processEnemyType1("jamal")
	processEnemyType1("bob")
	processEnemyType1("billy")
	processEnemyType1("jerry")
	processEnemyType1("lester")
	processEnemyType1("dave")
	
		
def processEnemyType1(name):
	tenemyid = findMobID(name)
	
	if tenemyid > -1:
		
		tx = spacerailer.getMobX(tenemyid)
		ty = spacerailer.getMobY(tenemyid)
		px = spacerailer.getPlayerX()
		py = spacerailer.getPlayerY()
		pw = spacerailer.getPlayerWidth()
		

		if py > ty:
			if spacerailer.checkMobCollisionAt(tenemyid, tx, ty + 1) == -1:
				ty = ty + 1
			
		if py < ty:
			if spacerailer.checkMobCollisionAt(tenemyid, tx, ty - 1) == -1:
				ty = ty - 1
			
		if tx - (px + pw) < 100:
			if spacerailer.checkMobCollisionAt(tenemyid, tx + 1, ty) == -1:
				tx = tx + 1
			
		if tx - (px + pw) > 100:
			if spacerailer.checkMobCollisionAt(tenemyid, tx - 1, ty) == -1:
				tx = tx - 1
			
		if tx < 250:
			tx = tx + 1
		
		#print("Setting mob y")
		spacerailer.setMobX(tenemyid, tx)
		spacerailer.setMobY(tenemyid, ty)
		

def mobDestroyed(mobid):
	global mobs
	
	#	Check if it was the first enemy that was destroyed.  If so, then spawn
	#	3 new ships in it's place
	fenemyid = findMobID("firstenemy")
	if mobid == fenemyid:
		temp = FirstEnemy()
		temp.setX(spacerailer.getPlayerX() + 1000)
		temp.setY(-500)
		addMobID(temp.ID, "james", temp)
		
		temp = FirstEnemy()
		temp.setX(spacerailer.getPlayerX() + 1000)
		temp.setY(1000)
		addMobID(temp.ID, "jamal", temp)
	
	if mobid in mobs:
		mobs.pop(mobid)
	
	
def findMobID(mobname):
	global mobs

	for key in mobs:
		if mobs[key]["name"] == mobname:
			return key
	
	return -1

def addMobID(mobid, mobname, mobobject):
	global mobs
	
	mobs[mobid] = {
		"name": mobname,
		"data": mobobject
	}
