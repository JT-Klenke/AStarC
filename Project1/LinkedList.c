#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "LinkedList.h"
#include "Table.h"

void add(struct LinkedList* pList, struct Point* pPoint) {
	/*inserts new point into the beginning of pList*/
	
	//create new node with next pFirst and pPoint p
	struct LinkedListNode* pNew;
	pNew = (struct LinkedListNode*)malloc(sizeof(struct LinkedListNode));
	memcpy(&(pNew->p), pPoint, sizeof(*pPoint));
	pNew->pNext = pList->pFirst;
	
	pList->pFirst = pNew;
};

unsigned char contains(struct LinkedList* pList, struct Point* pPoint) {
	/*traversed the list, if the point of interest is found returns TRUE
	if the end of the list is reached returns FALSE*/
	struct LinkedListNode* pCurrent;
	pCurrent = pList->pFirst;
	while (pCurrent != NULL) {
		if ((pCurrent->p).x == pPoint->x && (pCurrent->p).y == pPoint->y) {
			return TRUE;
		}
		pCurrent = pCurrent->pNext;
	}
	return FALSE;
}

void extractMin(struct LinkedList* pList, struct PointInfo** ppTable, struct Point* pReturnPoint) {  
	/*Searches through the linked list in order for each node: check its fCost in ppTable
	if the node's fCost is lower than min, min related values are updated.
	Upon reaching the end of the list the node before the minimum node is updated to splice out
	the minimum node and the minimum point is returned*/
	struct LinkedListNode **ppMinPrevious, *pCurrent, *pPrevious;
	struct Point *pMinPoint;
	struct PointInfo *pMinInfo, *pCurrentInfo;
	int minFCost;
	if (NULL == pList->pFirst) {//empty list
		pReturnPoint = NULL;
		return;
	}
	pPrevious = pList->pFirst;
	pCurrent = pPrevious->pNext;

	//sets min node info to first in list
	ppMinPrevious = &(pList->pFirst);
	pMinPoint = &(pPrevious->p);
	pMinInfo = getInfo(ppTable, pMinPoint->x, pMinPoint->y);
	minFCost = pMinInfo->gCost + pMinInfo->hCost;

	while (pCurrent != NULL) {//traverses list
		pCurrentInfo = getInfo(ppTable, (pCurrent->p).x, (pCurrent->p).y);
		if ((pCurrentInfo->gCost + pCurrentInfo->hCost) < minFCost) {
			//update min point info
			ppMinPrevious = &(pPrevious->pNext);
			pMinPoint = &(pCurrent->p);
			pMinInfo = getInfo(ppTable, pMinPoint->x, pMinPoint->y);
			minFCost = pMinInfo->gCost + pMinInfo->hCost;
		}
		pPrevious = pCurrent;
		pCurrent = pCurrent->pNext;
	}
	
	//stores minimum point information in safe place to be returned
	//returnPoint = malloc(sizeof(struct Point*));
	pReturnPoint->x = pMinPoint->x;
	pReturnPoint->y = pMinPoint->y;

	//splices out minimum point's node
	pCurrent = (*ppMinPrevious);
	(*ppMinPrevious) = pCurrent->pNext;
	
	return;
}


void printPoint(struct Point* pPoint) {
	printf("%d,%d\n", pPoint->x, pPoint->y);
}

void printList(struct LinkedList* pList) {
	struct LinkedListNode* pNode;
	pNode = pList->pFirst;
	while (pNode != 0) {
		printPoint(&(pNode->p));
		pNode = pNode->pNext;
	}
}
