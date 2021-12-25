import spacerailer
print("I'm printed from a python file :) :) :)")

playerThrusterID = 0
firstMob = 0

enemies = {}

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
	print(enemies)
	print("did i crash?")
	



def stageScrollEvent():
	"""spacerailer.setStageScrollInterval(spacerailer.getStageScrollInterval() + 1)
	
	if spacerailer.getStageScrollInterval() > 100:
		spacerailer.setStageScrollInterval(1)"""
	
	spacerailer.setMobAngle(firstMob, spacerailer.getMobAngle(firstMob) + 3)
	if spacerailer.getMobAngle(firstMob) > 360:
		spacerailer.setMobAngle(firstMob, spacerailer.getMobAngle(firstMob) - 360)
		

def mobProcess():
	#	Process stuff that mobs should do
	tenemyid = findMobID("firstenemy")
	
	if tenemyid > -1:
		
		tx = spacerailer.getMobX(tenemyid)
		ty = spacerailer.getMobY(tenemyid)
		px = spacerailer.getPlayerX()
		py = spacerailer.getPlayerY()
		pw = spacerailer.getPlayerWidth()
		

		if py > ty:
			ty = ty + 1
			
		if py < ty:
			ty = ty - 1
			
		if tx - (px + pw) < 100:
			tx = tx + 1
			
		if tx - (px + pw) > 100:
			tx = tx - 1
			
		if tx < 250:
			tx = tx + 1
		
		#print("Setting mob y")
		spacerailer.setMobX(tenemyid, tx)
		spacerailer.setMobY(tenemyid, ty)
	
def findMobID(mobname):
	global enemies
	
	
	for key in enemies:
		if enemies[key]["name"] == mobname:
			return key
			
	return -1
