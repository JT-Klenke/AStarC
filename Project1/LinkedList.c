#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "LinkedList.h"
#include "Table.h"

void add(struct LinkedList* pList, struct Point* pPoint) {
	//create new node with next pFirst and pPoint p
	//set pFisrt to this new node
	struct LinkedListNode* pNew;
	pNew = (struct LinkedListNode*)malloc(sizeof(struct LinkedListNode));
	memcpy(&(pNew->p), pPoint, sizeof(*pPoint));
	pNew->pNext = pList->pFirst;
	pList->pFirst = pNew;
};

unsigned char contains(struct LinkedList* pList, struct Point* pPoint) {
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

struct Point* extractMin(struct LinkedList* pList, struct PointInfo** ppTable) {   
	struct LinkedListNode *pMinPrevious, *pCurrent, *pPrevious;
	struct Point *pMinPoint, *pReturnPoint;
	struct PointInfo *pMinInfo, *pCurrentInfo;
	int minFCost;
	if (pList->pFirst == NULL) return NULL; //empty list
	pPrevious = pList->pFirst;
	pCurrent = pPrevious->pNext;

	pMinPrevious = pPrevious;
	pMinPoint = &(pPrevious->p);
	pMinInfo = getInfo(ppTable, pMinPoint->x, pMinPoint->y);
	minFCost = pMinInfo->gCost + pMinInfo->hCost;

	while (pCurrent != NULL) {
		pCurrentInfo = getInfo(ppTable, (pCurrent->p).x, (pCurrent->p).y);
		if ((pCurrentInfo->gCost + pCurrentInfo->hCost) < minFCost) {
			pMinPrevious = pPrevious;
			pMinPoint = &(pCurrent->p);
			pMinInfo = getInfo(ppTable, pMinPoint->x, pMinPoint->y);
			minFCost = pMinInfo->gCost + pMinInfo->hCost;
		}
		pPrevious = pCurrent;
		pCurrent = pCurrent->pNext;
	}

	
	pReturnPoint = malloc(sizeof(struct Point*));
	pReturnPoint->x = pMinPoint->x;
	pReturnPoint->y = pMinPoint->y;

	pCurrent = pMinPrevious->pNext;

	if (pCurrent != NULL){
		pMinPrevious->pNext = pCurrent->pNext;
	}else{
		pMinPrevious->pNext = NULL;
	}
	
	return pReturnPoint;

		
	/*
	memcpy(&pMinPrevious, &(pMinPrevious->pNext), sizeof(struct LinkedListNode*));
	return pMinPoint;
	*/
	
}


void printPoint(struct Point* pPoint) {
	printf("%d,%d\n", pPoint->x, pPoint->y);
	//printf("%d",);
}

void printList(struct LinkedList* pList) {
	struct LinkedListNode* pNode;
	pNode = pList->pFirst;
	while (pNode != 0) {
		printPoint(&(pNode->p));
		pNode = pNode->pNext;
	}
}
