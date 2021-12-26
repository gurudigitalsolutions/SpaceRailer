import spacerailer
import enemy1
import os

playerThrusterID = 0
firstMob = 0

enemies = {}

print("CWD: ", os.getcwd())

def initialize():
	global enemies
	
	print("I'm initializing from within the python script for the stage!")
	print("Number of arguments: ",spacerailer.numargs())
	print("x,y: ", spacerailer.getMapX(), spacerailer.getMapY())
	print("px,py: ", spacerailer.getPlayerX(), spacerailer.getPlayerY())
	spacerailer.setPlayerX(50)
	spacerailer.setPlayerY(256)
	
	spacerailer.setStageScrollPixelsPerInterval(3)
	spacerailer.setStageScrollInterval(50)
	
	firstMob = spacerailer.createMob("thruster0")
	
	print("MobID: ", firstMob)
	spacerailer.setMobX(firstMob, 2000)
	spacerailer.setMobY(firstMob, 200)
	spacerailer.setMobWidth(firstMob, 128)
	spacerailer.setMobHeight(firstMob, 128)
	spacerailer.setMobAngle(firstMob, 90)
	
	#	Create the thruster for the player
	playerThrusterID = spacerailer.createMob("thruster0")
	spacerailer.setMobX(playerThrusterID, 56)
	spacerailer.setMobY(playerThrusterID, 80)
	spacerailer.setMobWidth(playerThrusterID, 28)
	spacerailer.setMobHeight(playerThrusterID, 28)
	spacerailer.setMobParent(playerThrusterID, -2)
	
	spacerailer.setMobIsComponent(playerThrusterID, True)

	temp = spacerailer.createMob("enemy1")
	spacerailer.setMobX(temp, 512)
	spacerailer.setMobY(temp, 80)
	spacerailer.setMobWidth(temp, 128)
	spacerailer.setMobHeight(temp, 128)
	spacerailer.setMobIsStationary(temp, True)
	
	enemies = {temp: {"name": "firstenemy"}}
	


def stageScrollEvent():
	"""spacerailer.setStageScrollInterval(spacerailer.getStageScrollInterval() + 1)
	
	if spacerailer.getStageScrollInterval() > 100:
		spacerailer.setStageScrollInterval(1)"""
	
	spacerailer.setMobAngle(firstMob, spacerailer.getMobAngle(firstMob) + 3)
	if spacerailer.getMobAngle(firstMob) > 360:
		spacerailer.setMobAngle(firstMob, spacerailer.getMobAngle(firstMob) - 360)
		

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
	global enemies
	
	#	Check if it was the first enemy that was destroyed.  If so, then spawn
	#	3 new ships in it's place
	fenemyid = findMobID("firstenemy")
	if mobid == fenemyid:
		print("spawning james and jamal")
		temp = spacerailer.createMob("enemy1")
		spacerailer.setMobX(temp, spacerailer.getPlayerX() + 1000)
		spacerailer.setMobY(temp, -500)
		spacerailer.setMobWidth(temp, 128)
		spacerailer.setMobHeight(temp, 128)
		spacerailer.setMobIsStationary(temp, True)
		
		print("adding james to enemy list")
		enemies[temp] = {"name": "james"}
		
		print("spawning jamal")
		temp = spacerailer.createMob("enemy1")
		spacerailer.setMobX(temp, spacerailer.getPlayerX() + 1000)
		spacerailer.setMobY(temp, 1500)
		spacerailer.setMobWidth(temp, 128)
		spacerailer.setMobHeight(temp, 128)
		spacerailer.setMobIsStationary(temp, True)
		
		enemies[temp] = {"name": "jamal"}
		print("james and jamal spawned")
		
	del enemies[mobid]
	
	
def findMobID(mobname):
	global enemies
	
	
	for key in enemies:
		if enemies[key]["name"] == mobname:
			return key
			
	return -1
