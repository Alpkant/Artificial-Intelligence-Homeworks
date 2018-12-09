from constraint import *
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import numpy as np

class Block:
	# x,y,z are 2d coordinate tuples
	# False is horizontal, True is vertical block 
	def __init__(self,x,y,z):
		self.start = x
		self.middle = y
		self.end = z
		self.orientation = self.calcOrientation()
	
	def calcOrientation(self):
		# Return true if it's vertical, false if its horizontal
		return (self.start[0] - self.middle[0]) == 0

	def isGround(self):
		return self.start[1] == 0 or self.end[1] == 0

	def __str__(self):
	    return str(self.start) + " " + str(self.middle) + " " + str(self.end)

	def __unicode__(self):
	    return  ustr(self.start) + u" " + ustr(self.middle) + u" " + ustr(self.end)

	def __repr__(self):
	    return str(self.start) + " " + str(self.middle) + " " + str(self.end)



def createRangeList(pointTuple):
	pointTupleLeft = (pointTuple[0]-1,pointTuple[1])
	pointTupleRight = (pointTuple[0]+1,pointTuple[1])
	return [pointTupleLeft,pointTuple,pointTupleRight]


def checkMiddle(blockList,currentBlock):
	middlePoint = currentBlock.middle
	belowMiddle = (middlePoint[0], middlePoint[1] - 2)

	for block in blockList:
		if belowMiddle in [block.start, block.middle, block.end]:
			return True
	return False

def checkEdges(blockList,currentBlock):
	possiblePoints = []

	for block in blockList:
		possiblePoints.append(block.start)
		possiblePoints.append(block.middle)
		possiblePoints.append(block.end)

	belowStart = createRangeList((currentBlock.start[0],currentBlock.start[1]-2))
	belowEnd = createRangeList((currentBlock.end[0],currentBlock.end[1]-2))

	flag = 0
	if any(map(lambda each: each in belowStart, possiblePoints )):
		flag += 1

	if any(map(lambda each: each in belowEnd, possiblePoints )): 
		flag += 1

	if flag != 2:
		return False
	return True

def horizontalCheck(blockList, currentBlock):
	middleCheck = checkMiddle(blockList, currentBlock)
	edgeCheck = checkEdges(blockList,currentBlock)
	return (middleCheck or edgeCheck)


def verticalCheck(blockList,currentBlock):
	bottomCoordinate = (0,0)
	if currentBlock.start[1]-currentBlock.end[1] > 0:
		bottomCoordinate = currentBlock.end
	else:
		bottomCoordinate = currentBlock.start
	bottomCoordinate = (bottomCoordinate[0],bottomCoordinate[1]-2) 

	for block in blockList:
		if ( any(map(lambda each: each in createRangeList(bottomCoordinate),[block.start, block.middle, block.end] )) ):
			return True

	return False


def isSupported(blockList,currentBlock):
	if currentBlock.orientation: # Vertical
	    return verticalCheck(blockList,currentBlock)
	else:
		return horizontalCheck(blockList,currentBlock)		

def checkConstraint(*args):
	i = 0
	flag = False
	while i < len(args):
		flag = args[i].isGround() or isSupported( args[:i], args[i] )
		if not flag:
			return flag 
		i+=1
	return flag


choice = int(input("Enter 1 if you want to test input 1 in the project pdf or enter 2 if you want to test solution for the second structure in the pdf\n"))


domain = []
if choice == 1:
	b0 = Block((0,0),(2,0),(4,0))
	b1 = Block((2,2),(2,4),(2,6))	
	b2 = Block((6,0),(6,2),(6,4))	
	b3 = Block((12,0),(12,2),(12,4))	
	b4 = Block((4,6),(6,6),(8,6))	
	b5 = Block((10,6),(12,6),(14,6))	
	b6 = Block((2,8),(4,8),(6,8))	
	b7 = Block((8,8),(10,8),(12,8))	
	b8 = Block((5,10),(7,10),(9,10))	
	domain = [b0,b1,b2,b3,b4,b5,b6,b7,b8]
else:
	""" Structure that will not give any solution"""
	b0 = Block((0,0),(0,2),(0,4))
	b1 = Block((10,0),(10,2),(10,4))
	b2 = Block((0,6),(2,6),(4,6))
	b3 = Block((6,6),(8,6),(10,6))
	b4 = Block((3,8),(3,10),(3,12))
	b5 = Block((7,8),(7,10),(7,12))
	b6 = Block((3,14),(5,14),(7,14))
	domain = [b0,b1,b2,b3,b4,b5,b6]

variables = range(len(domain))
problem = Problem()
problem.addVariables(variables,domain)
problem.addConstraint(AllDifferentConstraint())
problem.addConstraint(checkConstraint,variables)
print("Please wait for the solution")
solutions = problem.getSolutions()
# Get a random solution from the solution set
print(len(solutions),"number of solutions found.")
if(len(solutions) == 0):
	print("Since no solutions found visualization is not possible.")
	exit(0)
solution = solutions[np.random.randint(len(solutions))]

plt.figure()
ax = plt.gca()
ax.set_ylim([0,32])
ax.set_xlim([0,32])
start, end = ax.get_xlim()
ax.xaxis.set_ticks(np.arange(start, end, 1))
ax.yaxis.set_ticks(np.arange(start, end, 1))
blockSize = (2,6)
for key,value in solution.items():
	if value.orientation:
		ax.add_patch(patches.Rectangle(value.start, blockSize[0], blockSize[1],fill=True,edgeColor='red',linewidth=4))
	else:
		ax.add_patch(patches.Rectangle(value.start, blockSize[1], blockSize[0],fill=True,edgeColor='red',linewidth=4))

	ax.text( 0.5*(value.start[0]+value.end[0])+1, 1+ value.middle[1] , str(key+1),
	        horizontalalignment='center',
	        verticalalignment='center',
	        fontsize=18, color='red')
	
plt.grid(True)
plt.show()

