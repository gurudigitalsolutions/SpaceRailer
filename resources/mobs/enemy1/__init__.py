import spacerailer
from mob import Mob

print("I'm enemy1")

class FirstEnemy(Mob):
	def __init__(self):
		Mob.mobType = "enemy1"
		Mob.ID = spacerailer.createMob(Mob.mobType)
		
		Mob.setWidth(self, 128)
		Mob.setHeight(self, 128)
		Mob.setIsStationary(self, True)
