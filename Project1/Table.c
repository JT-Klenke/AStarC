#include <stdlib.h>
#include <memory.h>
#include "Table.h"

struct PointInfo* getPointInfoMem() {
	static int i = 0; //number of units parsed out
#define NUM_BLOCKS 100000
	static struct PointInfo* pNextOpenBlock;
	struct PointInfo* pReturnBlock;

	if (0 == i) pNextOpenBlock = calloc(NUM_BLOCKS, sizeof(*pNextOpenBlock));
	pReturnBlock = pNextOpenBlock;
	pNextOpenBlock++;
	i++;
	if (i >= NUM_BLOCKS) i = 0;
	return pReturnBlock;
}

inline int getOffset(int x, int y) {
	return (X_SIZE * y + x);
}

struct PointInfo** makeTable() {
	return calloc(X_SIZE * Y_SIZE, sizeof(struct PointInfo*));
}

void makeObstacle(struct PointInfo** ppTable, int x, int y) {
	struct PointInfo* pPoint;
	pPoint = getInfo(ppTable, x, y);
	pPoint->isObstacle = TRUE;
}

void removeObstacle(struct PointInfo** ppTable, int x, int y) {
	struct PointInfo* pPoint;
	pPoint = getInfo(ppTable, x, y);
	pPoint->isObstacle = FALSE;
}

inline struct PointInfo* getInfo(struct PointInfo** ppTable, int x, int y) {
	int offset;
	offset = getOffset(x, y);
	if (NULL == ppTable[offset]) {
		ppTable[offset] = getPointInfoMem();
		ppTable[offset]->gCost = 1000000;
	}
	return ppTable[offset];
}
/*
void putInfo(struct PointInfo** ppTable, int x, int y, int gCost, int hCost, struct Point* pParent) {
	struct PointInfo* pPoint;
	pPoint = getInfo(ppTable, x, y);
	pPoint->gCost = gCost;
	pPoint->hCost = hCost;
	pPoint->fCost = gCost+hCost;
	pPoint->parent = pParent;
}
*/

void putInfo(struct PointInfo** ppTable, int x, int y, int gCost, int hCost, int parentX, int parentY) {
	struct PointInfo* pPoint;
	pPoint = getInfo(ppTable, x, y);
	pPoint->x = x;
	pPoint->y = y;
	pPoint->gCost = gCost;
	pPoint->hCost = hCost;
	pPoint->fCost = gCost+hCost;
	pPoint->parentX = parentX;
	pPoint->parentY = parentY;
}