#include "DList.h"
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <assert.h>
void DListInit(PDLNode* pHead) {
	assert(pHead);
	*pHead = (PDLNode)malloc(sizeof(DLNode));
	if (*pHead == NULL) {
		assert(0);
		return;
	}
	(*pHead)->_pNext = *pHead;
	(*pHead)->_pPre = *pHead;
}

PDLNode BuyDListNode(DLDataType data) {
	PDLNode pNewNode = (PDLNode)malloc(sizeof(DLNode));
	if (pNewNode == NULL) {
		assert(0);
		return NULL;
	}
	pNewNode->_pNext = NULL;
	pNewNode->_pPre = NULL;
	pNewNode->_data = data;
	return pNewNode;
}
void DListPushBack(PDLNode pHead, DLDataType data) {
	PDLNode pNewNode = BuyDListNode(data);
	pNewNode->_pNext = pHead;
	pNewNode->_pPre = pHead->_pPre;
	pHead->_pPre->_pNext = pNewNode;
	pHead->_pPre = pNewNode;
}
void DListPopBack(PDLNode pHead) {
	assert(pHead);
	if (pHead == pHead->_pNext)
		return;

	PDLNode pDelNode = pHead->_pPre;
	pDelNode->_pPre->_pNext = pHead;
	pHead->_pPre = pDelNode->_pPre;
	free(pDelNode);
}
void DListPushFront(PDLNode pHead, DLDataType data) {
	PDLNode pNewNode = BuyDListNode(data);
	pNewNode->_pNext = pHead->_pNext;
	pNewNode->_pPre = pHead;
	pHead->_pNext->_pPre = pNewNode;
	pHead->_pNext = pNewNode;
}
void DListPopFront(PDLNode pHead) {
	assert(pHead);
	if (pHead->_pNext == pHead)
		return;
	PDLNode pDelNode = pHead->_pNext;
	pHead->_pNext = pDelNode->_pNext;
	pDelNode->_pNext->_pPre = pHead;
	free(pDelNode);
}
void DListInsert(PDLNode pos, DLDataType data) {
	if (pos == NULL)
		return;
	PDLNode pNewNode = BuyDListNode(data);
	pNewNode->_pNext = pos;
	pNewNode->_pPre = pos->_pPre;
	pos->_pPre->_pNext = pNewNode;
	pos->_pPre = pNewNode;
}
void DListErase(PDLNode pos) {
	if (pos == NULL)
		return;
	pos->_pPre->_pNext = pos->_pNext;
	pos->_pNext->_pPre = pos->_pPre;
	free(pos);
}
PDLNode DListFind(PDLNode pHead, DLDataType data) {
	PDLNode pCur = pHead->_pNext;
	while (pCur != pHead) {
		if (pCur->_data == data)
			return pCur;
		pCur = pCur->_pNext;
	}
	return NULL;
}
void DListClear(PDLNode pHead) {
	PDLNode pCur = pHead->_pNext;
	while (pCur != pHead) {
		pHead->_pNext = pCur->_pNext;
		free(pCur);
		pCur = pHead->_pNext;
	}
	pHead->_pNext = pHead;
	pHead->_pPre = pHead;
}
void DListDestroy(PDLNode* pHead) {
	DListClear(*pHead);
	free(*pHead);
	*pHead = NULL;
}
void DListPrint(PDLNode pHead) {
	PDLNode pCur = pHead->_pNext;
	if (pCur == pHead)
		return;
	while (pCur != pHead) {
		printf("%d--->", pCur->_data);
		pCur = pCur->_pNext;
	}
	printf("\n");
}
void main() {
	PDLNode pHead = NULL;
	DListInit(&pHead);
	DListPushBack(pHead, 1);
	DListPushBack(pHead, 2);
	DListPushBack(pHead, 3);
	DListPrint(pHead);
	DListPushFront(pHead, 0);
	DListPrint(pHead);
	DListInsert(DListFind(pHead,1), 1);
	DListPrint(pHead);
	system("pause");
	return;
}