import spacerailer
from mob import Mob
from enemy1 import FirstEnemy
import os

playerThrusterID = 0
firstMob = {}

mobs = {}

print("CWD: ", os.getcwd())

def initialize():
	global mobs
	global firstMob
	
	spacerailer.setPlayerX(50)
	spacerailer.setPlayerY(256)
	
	spacerailer.setStageScrollPixelsPerInterval(3)
	spacerailer.setStageScrollInterval(50)
	
	
	firstMob = Mob()
	firstMob.ID = spacerailer.createMob("thruster0")
	print("MobID: ", firstMob)

	firstMob.setX(2000)
	firstMob.setY(200)
	firstMob.setWidth(128)
	firstMob.setHeight(128)
	firstMob.setAngle(90)
	
	#	Create the thruster for the player
	playerThrusterID = spacerailer.createMob("thruster0")
	spacerailer.setMobX(playerThrusterID, 56)
	spacerailer.setMobY(playerThrusterID, 80)
	spacerailer.setMobWidth(playerThrusterID, 28)
	spacerailer.setMobHeight(playerThrusterID, 28)
	spacerailer.setMobParent(playerThrusterID, -2)
	
	spacerailer.setMobIsComponent(playerThrusterID, True)

	temp = FirstEnemy()
	temp.setX(512)
	temp.setY(80)
	temp.setIsStationary(True)
	
	mobs = { 
		temp.ID: {
			"name": "firstenemy",
			"data": temp
		}
	}


def stageScrollEvent():
	global firstMob	
	
	
	firstMob.setAngle(firstMob.getAngle() + 3)
	if firstMob.getAngle() > 360:
		firstMob.setAngle(firstMob.getAngle() - 360)


def mobProcess():
	#	Process stuff that mobs should do
	processEnemyType1("firstenemy")
	processEnemyType1("james")
	processEnemyType1("jamal")
	
		
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
		
	del mobs[mobid]
	
	
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
