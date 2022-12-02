#include <stdlib.h>
#include "AStarCode.h"
#include "LinkedList.h"
#include "Table.h"
#define DIAGONAL_DISTANCE 14
#define ORTHOGONAL_DISTANCE 10

int getHCost(int x, int y, int endX, int endY) {
	int xDist, yDist;
	xDist = abs(x - endX);
	yDist = abs(y - endY);
	if (xDist > yDist) {
		return (yDist * DIAGONAL_DISTANCE + (xDist - yDist) * ORTHOGONAL_DISTANCE);
	}
	return (xDist * DIAGONAL_DISTANCE + (yDist - xDist) * ORTHOGONAL_DISTANCE);
}

struct LinkedList* buildPath(struct PointInfo** ppTable, struct Point* pEndPoint) {
	struct LinkedList* pPath;
	struct PointInfo* pPointInfo;
	pPath = malloc(sizeof(struct LinkedList));
	(pPath->pFirst) = NULL;
	add(pPath, pEndPoint);
	pPointInfo = getInfo(ppTable, pEndPoint->x, pEndPoint->y);
	pEndPoint = pPointInfo->parent;
	
	while (pEndPoint != NULL) {
		add(pPath, pEndPoint);
		pPointInfo = getInfo(ppTable, pEndPoint->x, pEndPoint->y);
		pEndPoint = pPointInfo->parent;
	}
	return pPath;
}

struct LinkedList* findPath(struct PointInfo** ppTable, int startX, int startY, int endX, int endY) {
	struct LinkedList* pEndList, priorityList;// , closedList;
	struct PointInfo *pCurrentInfo, *pAdjacentInfo;
	struct Point startPoint, *pCurrent, minPoint, adjacentPoint;
	int i, j, currentFCost, maybeGCost, adjacent[8][3];
	{
		adjacent[0][0] = 1; adjacent[0][1] = 1; adjacent[0][2] = DIAGONAL_DISTANCE;
		adjacent[1][0] = -1; adjacent[1][1] = -1; adjacent[1][2] = DIAGONAL_DISTANCE;
		adjacent[2][0] = -1; adjacent[2][1] = 1; adjacent[2][2] = DIAGONAL_DISTANCE;
		adjacent[3][0] = 1; adjacent[3][1] = -1; adjacent[3][2] = DIAGONAL_DISTANCE;
		adjacent[4][0] = 0; adjacent[4][1] = 1; adjacent[4][2] = ORTHOGONAL_DISTANCE;
		adjacent[5][0] = 1; adjacent[5][1] = 0; adjacent[5][2] = ORTHOGONAL_DISTANCE;
		adjacent[6][0] = 0; adjacent[6][1] = -1; adjacent[6][2] = ORTHOGONAL_DISTANCE;
		adjacent[7][0] = -1; adjacent[7][1] = 0; adjacent[7][2] = ORTHOGONAL_DISTANCE;
	}
	priorityList.pFirst = NULL;
	(startPoint.x) = startX;
	(startPoint.y) = startY;
	putInfo(ppTable, startX, startY, 0, getHCost(startX, startY, endX, endY), NULL);

	j = 0;
	add(&priorityList, &startPoint);

	while (1) {
		j++;
		extractMin(&priorityList, ppTable, &minPoint);
		pCurrent = &minPoint;
		if (NULL == pCurrent) {
			return NULL;
		}
		pCurrentInfo = getInfo(ppTable, pCurrent->x, pCurrent->y);
		currentFCost = pCurrentInfo->gCost + pCurrentInfo->hCost;
		if (pCurrent->x == endX && pCurrent->y == endY) {
			pEndList = buildPath(ppTable, pCurrent);
			printf("%d\n", j);
			break;
		}
		for (i = 0; i < 8; i++){
			(adjacentPoint.x) = pCurrent->x + adjacent[i][0];
			(adjacentPoint.y) = pCurrent->y + adjacent[i][1];
			if (adjacentPoint.x < 0 || adjacentPoint.y < 0 || adjacentPoint.x >= X_SIZE || adjacentPoint.y >= Y_SIZE) continue;
			maybeGCost = pCurrentInfo->gCost + adjacent[i][2];
			pAdjacentInfo = getInfo(ppTable, adjacentPoint.x, adjacentPoint.y);
			if (TRUE == pAdjacentInfo->isObstacle) continue;
			if (pAdjacentInfo->gCost > maybeGCost) {
				putInfo(ppTable, adjacentPoint.x, adjacentPoint.y, maybeGCost, getHCost(adjacentPoint.x, adjacentPoint.y, endX, endY), pCurrent);
				add(&priorityList, &adjacentPoint);
			}
		}
	}
	return pEndList;
}