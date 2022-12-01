#include <stdlib.h>
#include "AStarCode.h"
#include "LinkedList.h"
#include "Table.h"
#define DIAGONAL_DISTANCE 14
#define ORTHOGONAL_DISTANCE 10

int getHCost(int x, int y, int endX, int endY) {
	int xDist, yDist, ans;
	xDist = abs(x - endX);
	yDist = abs(y - endY);
	if (xDist > yDist) {
		ans = (yDist * DIAGONAL_DISTANCE + (xDist - yDist) * ORTHOGONAL_DISTANCE);
		return ans;
	}
	ans = (xDist * DIAGONAL_DISTANCE + (yDist - xDist) * ORTHOGONAL_DISTANCE);
	return ans;
}

struct LinkedList* buildPath(struct Table** ppTable, struct Point* pEndPoint) {
	struct LinkedList* pPath;
	struct PointInfo* pPointInfo;
	add(pPath, pEndPoint);
	pPointInfo = getInfo(ppTable, pEndPoint->x, pEndPoint->y);

	while (pPointInfo->parent != NULL) {
		add(pPath, pEndPoint);
		pEndPoint = pPointInfo->parent;
		pPointInfo = getInfo(ppTable, pEndPoint->x, pEndPoint->y);
	}
	return pPath;
}

struct LinkedList* findPath(struct PointInfo** ppTable, int startX, int startY, int endX, int endY) {
	struct LinkedList *pEndList, *pPriorityList, *pClosedList;
	struct PointInfo *pCurrentInfo, *pAdjacentInfo;
	struct Point *pCurrent, *pAdjacent;
	int i, currentFCost, maybeGCost, adjacent[8][3];
	{
		adjacent[0][0] =  1; adjacent[0][1] =  1; adjacent[0][1] = DIAGONAL_DISTANCE;
		adjacent[1][0] = -1; adjacent[1][1] = -1; adjacent[1][1] = DIAGONAL_DISTANCE;
		adjacent[2][0] = -1; adjacent[2][1] =  1; adjacent[2][1] = DIAGONAL_DISTANCE;
		adjacent[3][0] =  1; adjacent[3][1] = -1; adjacent[3][1] = DIAGONAL_DISTANCE;
		adjacent[4][0] =  0; adjacent[4][1] =  1; adjacent[4][1] = ORTHOGONAL_DISTANCE;
		adjacent[5][0] =  1; adjacent[5][1] =  0; adjacent[5][1] = ORTHOGONAL_DISTANCE;
		adjacent[6][0] =  0; adjacent[6][1] = -1; adjacent[6][1] = ORTHOGONAL_DISTANCE;
		adjacent[7][0] = -1; adjacent[7][1] =  0; adjacent[7][1] = ORTHOGONAL_DISTANCE;
	}
	while (1) {
		pCurrent = extractMin(pPriorityList, ppTable);
		if (NULL == pCurrent) return NULL;
		pCurrentInfo = getInfo(ppTable, pCurrent->x, pCurrent->y);
		currentFCost = pCurrentInfo->gCost + pCurrentInfo->hCost;
		if (pCurrent->x == endX && pCurrent->y == endY) {
			pEndList = buildPath(ppTable, pCurrent);
			break;
		}
		for (i = 0; i < 8; i++){
			(pAdjacent->x) = pCurrent->x + adjacent[i][0];
			(pAdjacent->y) = pCurrent->y + adjacent[i][1];
			maybeGCost = pCurrentInfo->gCost + adjacent[i][2];
			if (TRUE == contains(pClosedList, pAdjacent) && maybeGCost >= pAdjacentInfo->gCost) continue;
			if (pAdjacentInfo->gCost < maybeGCost) {
				putInfo(ppTable, pAdjacent->x, pAdjacent->y, maybeGCost, getHCost(pAdjacent->x, pAdjacent->y, endX, endY), pCurrent);
				add(pPriorityList, pAdjacent);
			}
		}
	}
}