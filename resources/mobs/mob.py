import spacerailer

print("I'm printing from inside the Mob.py module")

class Mob:
	ID = -1
	mobType = ""
	
	def __init__(self):
		pass
		
	def getX(self):
		return spacerailer.getMobX(self.ID)

	def getY(self):
		return spacerailer.getMobY(self.ID)
		
	def setX(self, newvalue):
		return spacerailer.setMobX(self.ID, newvalue)
		
	def setY(self, newvalue):
		return spacerailer.setMobY(self.ID, newvalue)
		
	def getWidth(self):
		return spacerailer.getMobWidth(self.ID)
		
	def setWidth(self, newvalue):
		return spacerailer.setMobWidth(self.ID, newvalue)
		
	def getHeight(self):
		return spacerailer.getMobHeight(self.ID)
		
	def setHeight(self, newvalue):
		return spacerailer.setMobHeight(self.ID, newvalue)
		
	def getAngle(self):
		return spacerailer.getMobAngle(self.ID)
		
	def setAngle(self, newvalue):
		return spacerailer.setMobAngle(self.ID, newvalue)
		
	def getParent(self):
		return spacerailer.getMobParent(self.ID)
		
	def setParent(self, newvalue):
		return spacerailer.setMobParent(self.ID, newvalue)
		
	def getIsComponent(self):
		return spacerailer.getMobIsComponent(self.ID)
		
	def setIsComponent(self, newvalue):
		return spacerailer.setMobIsComponent(self.ID, newvalue)
		
	def getIsStationary(self):
		return spacerailer.getMobIsStationary(self.ID)
		
	def setIsStationary(self, newvalue):
		return spacerailer.setMobIsStationary(self.ID, newvalue)
		
	def checkCollisionAt(self, x, y):
		return spacerailer.checkCollisionAt(self.ID, x, y)
