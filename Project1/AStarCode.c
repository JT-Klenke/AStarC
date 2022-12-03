#include <stdlib.h>
#include <stdio.h>
#include "AStarCode.h"
#include "LinkedList.h"
#include "Table.h"
#include "PriorityQueue.h"
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

struct LinkedList* buildPath(struct PointInfo** ppTable, int endPointX, int endPointY) {
	struct LinkedList* pPath;
	struct PointInfo* pPointInfo;
	struct Point point;

	pPath = malloc(sizeof(struct LinkedList));
	(pPath->pFirst) = NULL;
	point.x = endPointX;
	point.y = endPointY;
	add(pPath, &point);
	pPointInfo = getInfo(ppTable, point.x, point.y);
	point.x = pPointInfo->parentX;
	point.y = pPointInfo->parentY;
	
	while (pPointInfo->x != pPointInfo->parentX && pPointInfo->y != pPointInfo->parentY) {
		add(pPath, &point);
		pPointInfo = getInfo(ppTable, point.x, point.y);
		point.x = pPointInfo->parentX;
		point.y = pPointInfo->parentY;
	}
	return pPath;
}

struct LinkedList* findPath(struct PointInfo** ppTable, int startX, int startY, int endX, int endY) {
	struct LinkedList* pEndList, priorityList;// , closedList;
	struct PointInfo *pCurrentInfo, *pAdjacentInfo;
	struct ResizableArray* pPriorityQueue;
	struct Point startPoint, *pCurrent, minPoint, adjacentPoint;
	int i, maybeGCost, adjacent[8][3];
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
	pPriorityQueue = makeQueue();
	priorityList.pFirst = NULL;
	(startPoint.x) = startX;
	(startPoint.y) = startY;
	putInfo(ppTable, startX, startY, 0, getHCost(startX, startY, endX, endY), startX, startY);

	queueAdd(pPriorityQueue, ppTable, &startPoint);
	//add(&priorityList, &startPoint);

	while (0 != pPriorityQueue->length) {
		pqextractMin(pPriorityQueue, ppTable, &minPoint);
		pCurrent = &minPoint;
		//pCurrent = extractMin(&priorityList, ppTable);
		
		pCurrentInfo = getInfo(ppTable, pCurrent->x, pCurrent->y);
		if (pCurrent->x == endX && pCurrent->y == endY) {
			pEndList = buildPath(ppTable, minPoint.x, minPoint.y);
			return pEndList;
		}
		for (i = 0; i < 8; i++){
			(adjacentPoint.x) = pCurrent->x + adjacent[i][0];
			(adjacentPoint.y) = pCurrent->y + adjacent[i][1];
			if (adjacentPoint.x < 0 || adjacentPoint.y < 0 || adjacentPoint.x >= X_SIZE || adjacentPoint.y >= Y_SIZE) continue;
			maybeGCost = pCurrentInfo->gCost + adjacent[i][2];
			pAdjacentInfo = getInfo(ppTable, adjacentPoint.x, adjacentPoint.y);
			if (TRUE == pAdjacentInfo->isObstacle) continue;
			if (pAdjacentInfo->gCost > maybeGCost) {
				putInfo(ppTable, adjacentPoint.x, adjacentPoint.y, maybeGCost, getHCost(adjacentPoint.x, adjacentPoint.y, endX, endY), minPoint.x, minPoint.y);
				
				queueAdd(pPriorityQueue, ppTable, &adjacentPoint);
				//add(&priorityList, &adjacentPoint);
			}
		}
	}
	return NULL;
}