#include <stdlib.h>
#include <memory.h>
#include "PriorityQueue.h"
#include "LinkedList.h"

inline void bubbleUp(struct ResizableArray* pQueue, struct PointInfo** ppTable, int index) {

}

inline void bubbleDown(struct ResizableArray* pQueue, struct PointInfo** ppTable, int index) {

}

inline void swap(struct ResizableArray* pQueue, struct PointInfo** ppTable, int index1, int index2) {
	struct Point temp;

}

inline struct Point* get(struct ResizableArray* pQueue, int index) {
	return (pQueue->head)[index];
}

struct Point* pqextractMin(struct ResizableArray* pQueue, struct PointInfo** ppTable) {
	struct Point *pReturnPoint, *pFirstPoint, *pLastPoint;
	pFirstPoint = get(pQueue, 0);
	pLastPoint = get(pQueue, (pQueue->size) - 1);
	pReturnPoint = malloc(sizeof(struct Point));
	memcpy(pReturnPoint, pFirstPoint, sizeof(struct Point));
	memcpy(pFirstPoint, pLastPoint, sizeof(struct Point));
	memset(pLastPoint, 0, sizeof(struct Point));
	bubbleDown(pQueue, ppTable, 0);
	getInfo(ppTable, pReturnPoint->x, pReturnPoint->y)->isOpen = FALSE;
	(pQueue->size)--;
	return pReturnPoint;
}

void queueAdd(struct ResizableArray* pQueue, struct PointInfo** ppTable, struct Point* pPoint) {
	struct PointInfo* pInfo;
	struct Point **ppHead;
	pInfo = getInfo(ppTable, pPoint->x, pPoint->y);
	if (TRUE == pInfo->isOpen) {
		bubbleUp(pQueue, ppTable, pInfo->index);
		return;
	}
	(pQueue->size)++;
	if (pQueue->backingSize == (pQueue->size)) {
		ppHead = (pQueue->head);
		(pQueue->head) = calloc(2 * (pQueue->backingSize), sizeof(struct Point));
		memcpy((pQueue->head), ppHead, (pQueue->size) * sizeof(struct Point));
		(pQueue->backingSize) *= 2;
 	}
	pInfo->isOpen = TRUE;
	memcpy(get(pQueue, (pQueue->size)), pPoint, sizeof(struct Point));
	bubbleUp(pQueue, ppTable, (pQueue->size));
}
