#include <stdlib.h>
#include <memory.h>
#include "Table.h"

int getOffset(int x, int y) {
	return (X_SIZE * y + x) * 1;// sizeof(struct PointInfo*);
}

struct PointInfo** makeTable() {
	return (struct PointInfo*)calloc(X_SIZE * Y_SIZE, sizeof(struct PointInfo*));
}

struct PointInfo* getInfo(struct PointInfo** ppTable, int x, int y) {
	return (struct PointInfo*)(ppTable + getOffset(x,y));
}

void putInfo(struct PointInfo** ppTable, int x, int y, int gCost, int hCost, struct Point* pParent) {
	struct PointInfo* pPoint;
	pPoint = getInfo(ppTable, x, y);
	if (pPoint == NULL) {
		pPoint = malloc(sizeof(struct PointInfo));
		memset(pPoint, 0, sizeof(struct PointInfo));
		memcpy((ppTable + getOffset(x, y)), pPoint, sizeof(struct PointInfo*));
	}
	pPoint->gCost = gCost;
	pPoint->hCost = hCost;
	pPoint->parent = pParent;
}