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

#define X_SIZE 50
#define Y_SIZE 50

struct PointInfo {
	int gCost;
	int hCost;
	unsigned char isTraversable;
	struct Point* parent;
};


struct PointInfo** makeTable();

struct PointInfo* getInfo(struct PointInfo** ppTable, int x, int y);

void putInfo(struct PointInfo** pTable, int x, int y, int gCost, int hCost, struct Point* pParent);