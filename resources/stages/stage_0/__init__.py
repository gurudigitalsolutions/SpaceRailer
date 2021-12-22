import spacerailer
print("I'm printed from a python file :) :) :)")

firstMob = 0

def initialize():
	print("I'm initializing from within the python script for the stage!")
	print("Number of arguments: ",spacerailer.numargs())
	print("x,y: ", spacerailer.getMapX(), spacerailer.getMapY())
	print("px,py: ", spacerailer.getPlayerX(), spacerailer.getPlayerY())
	spacerailer.setPlayerX(50)
	spacerailer.setPlayerY(256)
	
	spacerailer.setStageScrollPixelsPerInterval(6)
	spacerailer.setStageScrollInterval(10)
	
	firstMob = spacerailer.createMob("thruster0")
	
	print("MobID: ", firstMob)
	spacerailer.setMobX(firstMob, 2000)
	spacerailer.setMobY(firstMob, 200)
	spacerailer.setMobWidth(firstMob, 128)
	spacerailer.setMobHeight(firstMob, 128)
	spacerailer.setMobAngle(firstMob, 90)


def stageScrollEvent():
	"""spacerailer.setStageScrollInterval(spacerailer.getStageScrollInterval() + 1)
	
	if spacerailer.getStageScrollInterval() > 100:
		spacerailer.setStageScrollInterval(1)"""
	
	spacerailer.setMobAngle(firstMob, spacerailer.getMobAngle(firstMob) + 3)
	if spacerailer.getMobAngle(firstMob) > 360:
		spacerailer.setMobAngle(firstMob, spacerailer.getMobAngle(firstMob) - 360)
