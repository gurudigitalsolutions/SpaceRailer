import spacerailer
print("I'm printed from a python file :) :) :)")

def initialize():
	print("I'm initializing from within the python script for the stage!")
	print("Number of arguments: ",spacerailer.numargs())
	print("x,y: ", spacerailer.getMapX(), spacerailer.getMapY())
	print("px,py: ", spacerailer.getPlayerX(), spacerailer.getPlayerY())
