#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "PriorityQueue.h"
#include "LinkedList.h"

struct Point* get(struct ResizableArray* pQueue, int index) {
	return &((pQueue->pHead)[index]);
}

inline int compare(struct ResizableArray* pQueue, struct PointInfo** ppTable, int index1, int index2) {
	/*returns >0 if value of index1 is larger than index2
	*		  <0 if value of index1 is smaller than index2
	*		   0 if value of index1 is equal to index2
	*/
	struct Point *pPoint1, *pPoint2;
	struct PointInfo *pPointInfo1, *pPointInfo2;
	int fCostDifference;
	pPoint1 = get(pQueue, index1);
	pPoint2 = get(pQueue, index2);
	pPointInfo1 = getInfo(ppTable, pPoint1->x, pPoint1->y);
	pPointInfo2 = getInfo(ppTable, pPoint2->x, pPoint2->y);
	fCostDifference = (pPointInfo1->fCost) - (pPointInfo2->fCost);
	if (0 == fCostDifference) {
		return (pPointInfo1->hCost) - (pPointInfo2->hCost);
	}
	return fCostDifference;
}

inline void swap(struct ResizableArray* pQueue, struct PointInfo** ppTable, int index1, int index2) {
	struct Point tempPoint, *pPointIndex1, *pPointIndex2;
	pPointIndex1 = get(pQueue, index1);
	pPointIndex2 = get(pQueue, index2);
	getInfo(ppTable, pPointIndex1->x, pPointIndex1->x)->index = index2;
	getInfo(ppTable, pPointIndex2->x, pPointIndex2->x)->index = index1;
	memcpy(&tempPoint, pPointIndex1, sizeof(struct Point));
	memcpy(pPointIndex1, pPointIndex2, sizeof(struct Point));
	memcpy(pPointIndex2, &tempPoint, sizeof(struct Point));
}

inline void bubbleUp(struct ResizableArray* pQueue, struct PointInfo** ppTable, int index) {
	int p;
	p = (index - 1) / 2;
	while (compare(pQueue, ppTable, index, p) < 0) {
		swap(pQueue, ppTable, index, p);
		index = p;
		p = (index - 1) / 2;
	}
}

inline void bubbleDown(struct ResizableArray* pQueue, struct PointInfo** ppTable, int index) {
	int l, r;
	l = 2 * index + 1;
	r = 2 * index + 2;
	while (l < pQueue->length) {
		if (r >= pQueue->length || compare(pQueue, ppTable, l, r) <= 0) { // l is higher prio
			if (compare(pQueue, ppTable, index, l) <= 0) {
				return;
			}
			swap(pQueue, ppTable, index, l);
			index = l;

		}
		else { // r is higher prio
			if (compare(pQueue, ppTable, index, r) <= 0) {
				return;
			}
			swap(pQueue, ppTable, index, r);
			index = r;
		}
		l = 2 * index + 1;
		r = 2 * index + 2;
	}
}

struct ResizableArray* makeQueue() {
#define START_BACKING_LENGTH 16
	struct ResizableArray* pReturnArray;
	pReturnArray = calloc(1, sizeof(struct ResizableArray));
	pReturnArray->length = 0;
	pReturnArray->backingLength = START_BACKING_LENGTH;
	pReturnArray->pHead = calloc(START_BACKING_LENGTH , sizeof(struct Point));
	return pReturnArray;
}

struct Point* pqextractMin(struct ResizableArray* pQueue, struct PointInfo** ppTable, struct Point* pReturnPoint) {
	struct Point *pFirstPoint, *pLastPoint;
	pFirstPoint = get(pQueue, 0);
	pLastPoint = get(pQueue, (pQueue->length) - 1);
	memcpy(pReturnPoint, pFirstPoint, sizeof(struct Point));
	memcpy(pFirstPoint, pLastPoint, sizeof(struct Point));
	//memset(pLastPoint, 0, sizeof(struct Point));
	bubbleDown(pQueue, ppTable, 0);
	getInfo(ppTable, pReturnPoint->x, pReturnPoint->y)->isOpen = FALSE;
	(pQueue->length)--;
	return pReturnPoint;
}

void queueAdd(struct ResizableArray* pQueue, struct PointInfo** ppTable, struct Point* pPoint) {
	struct PointInfo* pInfo;
	pInfo = getInfo(ppTable, pPoint->x, pPoint->y);
	if (TRUE == pInfo->isOpen) {
		bubbleUp(pQueue, ppTable, pInfo->index);
		return;
	}
	(pQueue->length)++;
	if (pQueue->backingLength <= (pQueue->length)) {
		(pQueue->backingLength) *= 2;
		(pQueue->pHead) = realloc((pQueue->pHead), (pQueue->backingLength) * sizeof(struct Point));
		//memcpy((pQueue->ppHead), ppHead, (pQueue->length) * sizeof(struct Point));
 	}
	pInfo->isOpen = TRUE;
	memcpy(get(pQueue, ((pQueue->length) - 1)), pPoint, sizeof(struct Point));
	bubbleUp(pQueue, ppTable, (pQueue->length)-1);
}