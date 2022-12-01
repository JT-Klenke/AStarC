#include <stdlib.h>
#include <memory.h>
#include "Table.h"

int getOffset(int x, int y) {
	return (X_SIZE * y + x);
}

struct PointInfo** makeTable() {
	return calloc(X_SIZE * Y_SIZE, sizeof(struct PointInfo*));
}

struct PointInfo* getInfo(struct PointInfo** ppTable, int x, int y) {
	return ppTable[getOffset(x, y)];
}

void putInfo(struct PointInfo** ppTable, int x, int y, int gCost, int hCost, struct Point* pParent) {
	struct PointInfo* pPoint, *pIntoTable;
	pPoint = getInfo(ppTable, x, y);
	if (NULL == pPoint) {
		pPoint = calloc(1, sizeof(struct PointInfo));
		ppTable[getOffset(x, y)] = pPoint;
	}
	pPoint->gCost = gCost;
	pPoint->hCost = hCost;
	pPoint->parent = pParent;
}