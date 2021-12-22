import spacerailer
print("I'm printed from a python file :) :) :)")

def initialize():
	print("I'm initializing from within the python script for the stage!")
	print("Number of arguments: ",spacerailer.numargs())
	print("x,y: ", spacerailer.getMapX(), spacerailer.getMapY())
	print("px,py: ", spacerailer.getPlayerX(), spacerailer.getPlayerY())
	spacerailer.setPlayerX(50)
	spacerailer.setPlayerY(256)
	
	spacerailer.setStageScrollPixelsPerInterval(6)
	spacerailer.setStageScrollInterval(10)
	
	mobid = spacerailer.createMob("thruster0")
	
	#print("MobID: ", mobid)
	#spacerailer.setMobX(mobid, 500)
	#spacerailer.setMobY(mobid, 200)


"""def stageScrollEvent():
	spacerailer.setStageScrollInterval(spacerailer.getStageScrollInterval() + 1)
	
	if spacerailer.getStageScrollInterval() > 100:
		spacerailer.setStageScrollInterval(1)"""
