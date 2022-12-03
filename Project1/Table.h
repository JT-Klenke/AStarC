#pragma once
/*
From point table:
- get gCost
	- gCost =  gCost of parent + traversal distance
- get fCost
	- fCost = gCost + hCost (distance from end)
- get isTraversable
- change parent, gCost
	
*/

#define X_SIZE 1000
#define Y_SIZE 1000
#define TRUE 1
#define FALSE 0

struct PointInfo {
	int gCost;
	int hCost;
	int fCost;
	int index;
	unsigned char isObstacle;
	unsigned char isOpen;
	struct Point* parent;
};


struct PointInfo** makeTable();

void makeObstacle(struct PointInfo** ppTable, int x, int y);

void removeObstacle(struct PointInfo** ppTable, int x, int y);

inline struct PointInfo* getInfo(struct PointInfo** ppTable, int x, int y);

void putInfo(struct PointInfo** pTable, int x, int y, int gCost, int hCost, struct Point* pParent);