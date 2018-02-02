/*
+
-             ���ߣ�Joezeo < joezeo@outlook.com >
+
-             ����ʱ�䣺2017.12.21 / 18��23
+
-             �޸�ʱ�䣺2018.02.02 / 15��01
+
-             �ļ����ƣ�dtastc.c
+
-             ���ܣ����ݽṹ��ĺ�������
+
*/

#include "dtastc.h"

/*
----------------------------------- SqList -----------------------------------
*/

/*
+
-               ��������
+
*/
PLIST
InitList(const int _size) {

	PLIST _list = (PLIST)malloc(sizeof(LIST));
	if (!_list) {

		exit(OVERFLOW);

	}

	_list->_base = (void **)malloc(LISTINITSIZE * _size);
	if (!(_list->_base)) {

		exit(OVERFLOW);

	}

	_list->_length = 0;
	_list->_listsize = LISTINITSIZE;

	return _list;

}
// ��ʼ��һ�����Ա�


Status
FreeList(PLIST plist) {

	assert(plist != NULL);

	free(plist->_base);
	plist->_base = NULL;

	free(plist);
	plist = NULL;

	return OK;

}
// ����һ�����Ա��ͷ��ڴ���Դ


Status
EmptyList(const PLIST plist) {

	assert(plist != NULL);

	if (plist->_length == 0) {

		return TRUE;

	}

	return FALSE;

}
// �ж����Ա��Ƿ�Ϊ�ձ��Ƿ���TRUE�����򷵻�FALSE


Status
ClearList(PLIST plist) {

	assert(plist != NULL);

	if (EmptyList(plist)) {

		return OK;

	}

	for (UINT i = 0; i < plist->_length; i++) {

		*(plist->_base + i) = 0;

	}

	plist->_length = 0;

	return OK;

}
// ���һ�����Ա�������Ϊ�ձ�


int
ListLength(const PLIST plist) {

	assert(plist != NULL);

	return plist->_length;

}
// �������Ա��ȣ�����Ԫ�ظ�����


void *
GetElem(const PLIST plist, const UINT i) {

	assert(plist != NULL);

	if (EmptyList(plist)) {

		return NULL;

	}

	if (i > plist->_length || i <= 0) {

		return NULL;

	}

	return *(plist->_base + i - 1);

}
// ��ȡ���Ա�ĵ�i������Ԫ��,�����Ա�Ϊ�ձ���NULL,iԽ�緵��NULL


Status
Located(const PLIST plist, const void * e) {

	assert(plist != NULL);

	if (EmptyList(plist)) {

		return FALSE;

	}

	for (UINT i = 0; i < plist->_length; i++) {

		if (*(plist->_base + i) == e) {

			return TRUE;

		}

	}

	return FALSE;

}
// �ж����Ա����Ƿ����ֵΪ�ڶ�������������Ԫ��


Status
ListInsert(PLIST plist, const UINT i, const void * e, const int _size) {

	assert(plist != NULL);

	if (i <= 0 || i > plist->_length + 1) {

		return ERROR;

	}

	if (plist->_length == plist->_listsize) {

		AddlistSize(plist);

	}

	if(EmptyList(plist)){

		memcpy(plist->_base, e, _size);

		goto fend;
	
	}
	else if (i == plist->_length + 1) {

		memcpy(plist->_base + i - 1, e, _size);

		goto fend;

	}
	else {

		for (UINT j = plist->_length; j >= i; j--) {

			memcpy(plist->_base + j, plist->_base + j - 1, _size);

		}

		memcpy(plist->_base + i - 1, e, _size);

		goto fend;

	}

fend:
	plist->_length++;
	return OK;

}
// ���Ա��������Ԫ�أ��ڵڶ�������λ�ò���Ԫ�أ�ֵΪ������������ֵ�����ĸ�����Ϊ����Ԫ�صĴ�С��


Status
ListRemove(PLIST plist, const UINT i) {

	assert(plist != NULL);

	if (i <= 0 || i > plist->_length) {

		return ERROR;

	}

	if (EmptyList(plist)) {

		return ERROR;

	}

	if (i == plist->_length) {

		*(plist->_base + i - 1) = 0;

		goto fend;

	}
	else {

		for (UINT j = i - 1; j < plist->_length - 1; j++) {

			*(plist->_base + j) = *(plist->_base + j + 1);

			goto fend;

		}

	}

fend:
	plist->_length--;
	return OK;

}
// ���Ա�ɾ������Ԫ�أ�ɾ��λ��Ϊ�ڶ���������


static Status
AddlistSize(PLIST plist) {

	assert(plist != NULL);

	void ** add = (void **)realloc(plist->_base,
		(plist->_listsize + LISTINCREMENT) * sizeof(void *));

	if (!add) {

		exit(OVERFLOW);

	}

	plist->_base = add;
	plist->_listsize += LISTINCREMENT;

	return OK;

}
// ��̬�������������Ա������

/*
------------------------------------------------------------------------------
*/





/*
---------------------------------- LinkList ----------------------------------
*/

/*
+
-               ��������
+
*/
static PNODE
NewNode(void * e, const int _size) {

	PNODE newnode = (PNODE)malloc(sizeof(NODE));
	if (!newnode) {

		exit(OVERFLOW);

	}

	memcpy(newnode->_data, e, _size);
	newnode->_next = NULL;
	newnode->_pre = NULL;

	return newnode;

}
// ����һ���µĽڵ㣬��������Ϊ����Ĳ�����ֵ


Status
FreeNode(PNODE node) {

	assert(node != NULL);

	if (node->_pre != NULL) {

		PNODE tmp = node->_pre;
		tmp->_next = node->_next;

	}
	if (node->_next != NULL) {

		PNODE tmp = node->_next;
		tmp->_pre = node->_pre;

	}

	free(node);
	node = NULL;

	return OK;

}
// �ͷŴ˽ڵ���ڴ�ռ�


PLINKLIST
Initlklist() {

	PLINKLIST lklist = (PLINKLIST)malloc(sizeof(LINKLIST));
	if (!lklist) {

		exit(OVERFLOW);

	}

	lklist->_cnt = 0;
	lklist->_head = NULL;
	lklist->_tail = NULL;

	return lklist;

}
// ��ʼ��һ������ͷ���Ŀ�����


Status
FreelkList(PLINKLIST lklist) {

	assert(lklist != NULL);

	if (EmptylkList(lklist)) {

		free(lklist);
		lklist = NULL;
		
		return OK;

	}

	PNODE pre = NULL;
	PNODE cur = lklist->_head;

	while (cur != NULL) {

		pre = cur->_next;
		free(cur);
		cur = pre;

	}

	free(lklist);
	lklist = NULL;

	return OK;

}
// ���������ͷ��ڴ�ռ�


Status
ClearlkList(PLINKLIST lklist) {

	assert(lklist != NULL);

	if (EmptylkList(lklist)) {

		return ERROR;

	}

	PNODE pre = NULL;
	PNODE cur = lklist->_head;

	while (cur != NULL) {

		pre = cur->_next;
		free(cur);
		cur = pre;

	}

	lklist->_head = NULL;
	lklist->_tail = NULL;
	lklist->_cnt = 0;

	return OK;

}
// �������Ϊ������


Status
EmptylkList(const PLINKLIST lklist) {

	assert(lklist != NULL);

	if (lklist->_cnt == 0) {

		return TRUE;

	}

	return FALSE;

}
// �ж�һ�������Ƿ�Ϊ�գ����򷵻�TRUE�����򷵻�FALSE


Status
AddNode(PLINKLIST lklist, void * e, const int _size) {

	assert(lklist != NULL);

	PNODE newnode = NewNode(e, _size);

	if (EmptylkList(lklist)) {

		lklist->_head = newnode;
		lklist->_tail = newnode;

	}
	else {

		PNODE tmp = NULL;
		tmp = lklist->_tail;
		lklist->_tail->_next = newnode;
		lklist->_tail = newnode;
		lklist->_tail->_pre = tmp;

	}

	lklist->_cnt++;

	return OK;

}
// Ϊ�����½�һ���ڵ㣬��������Ϊ����ĵڶ���������ֵ��Ĭ�ϲ���˳���β�����룩������������Ϊ����Ԫ�صĴ�С


Status
RemoveNode(PLINKLIST lklist) {

	assert(lklist != NULL);

	PNODE tmp = lklist->_tail;

	if (EmptylkList(lklist)) {

		return ERROR;

	}

	lklist->_tail = lklist->_tail->_pre;
	lklist->_tail->_next = NULL;
	lklist->_cnt--;

	free(tmp);
	tmp = NULL;

	return OK;

}
// ����ɾ��һ����㡣(Ĭ�ϴ�β��ɾ��)


int
lkListLength(const PLINKLIST lklist) {

	assert(lklist != NULL);

	return lklist->_cnt;

}
// ��������ĳ���(Ԫ�ظ���)


PNODE
GetNode(const PLINKLIST lklist, void * e) {

	assert(lklist != NULL);

	if (EmptylkList(lklist)) {

		return NULL;

	}

	PNODE node = lklist->_head;

	for (; node != NULL; node = node->_next) {

		if (node->_data == e) {

			break;

		}

	}

	if (node == NULL) {

		return NULL;

	}

	return node;

}
// �������в���������Ϊ�ڶ�������ֵ�Ľڵ㣬���������ַ,��û�ҵ�������NULL


Status
InsertNodeAfter(PNODE node, void * e, const int _size) {

	assert(node != NULL);

	PNODE tmp = node->_next;
	PNODE newnode = NewNode(e, _size);

	newnode->_next = tmp;
	newnode->_pre = node;

	node->_next = newnode;
	tmp->_pre = newnode;

	return OK;


}
// �ڵ�һ�����������������Ϊ�ڶ����������½ڵ㣬 ����������Ϊ����Ԫ�صĴ�С


Status
InsertNodeBefore(PNODE node, void * e, const int _size) {

	assert(node != NULL);

	PNODE tmp = node->_pre;
	PNODE newnode = NewNode(e, _size);

	newnode->_pre = tmp;
	newnode->_next = node;

	tmp->_next = newnode;
	node->_pre = newnode;

	return OK;

}
// �ڵ�һ�������ǰ����������Ϊ�ڶ����������½ڵ㣬����������Ϊ����Ԫ�صĴ�С

/*
------------------------------------------------------------------------------
*/





/*
----------------------------------- Stack -----------------------------------
*/

/*
+
-               ��������
+
*/
PSTACK
InitStack(const int _size) {

	PSTACK sqs = (PSTACK)malloc(sizeof(STACK));
	if (!sqs) {

		exit(OVERFLOW);

	}

	sqs->_base = (void **)malloc(STACKINITSIZE * _size);
	if (!(sqs->_base)) {

		exit(OVERFLOW);

	}	
	
	sqs->_top = sqs->_base;
	sqs->_stacksize = STACKINITSIZE;
	sqs->_cnt = 0;

	return sqs;

}
// ����һ����ջ


Status
DestroyStack(PSTACK sqs) {

	assert(sqs != NULL);

	free(sqs->_base);
	sqs->_base = NULL;
	sqs->_top = NULL;

	free(sqs);
	sqs = NULL;

	return OK;

}
// ����ջ���ͷ���Դ


Status
ClearStack(PSTACK sqs) {

	assert(sqs != NULL);

	sqs->_top = sqs->_base;
	sqs->_cnt = 0;

	return OK;

}
// ��ջԪ����գ���Ϊ��ջ


Status
StackEmpty(const PSTACK sqs) {

	assert(sqs != NULL);

	if (sqs->_cnt == 0)
		return TRUE;

	return FALSE;

}
// ��ջΪ��ջ������TRUE�����򷵻�FALSE


int
StackLength(const PSTACK sqs) {

	assert(sqs != NULL);

	return sqs->_cnt;

}
// ����ջԪ�صĸ�������ջ�ĳ���


Status
GetTop(const PSTACK sqs, void * e, const int _size) {

	assert(sqs != NULL);

	if (StackEmpty(sqs)) {

		return ERROR;

	}

	memcpy(e, sqs->_top - 1, _size);

	return OK;

}
// ��ջ���գ�����ջ��Ԫ�ص�ֵ�����򷵻�NULL���ڶ�������Ϊ����Ԫ�صĴ�С


Status
Push(PSTACK sqs, const void * e, const int _size) {

	assert(sqs != NULL);

	if (sqs->_cnt == sqs->_stacksize) {

		AddStackSize(sqs);

	}

	memcpy(sqs->_top, e, _size);

	sqs->_top++;
	sqs->_cnt++;

	return OK;

}
// ����Ԫ��eΪ�µ�ջ��Ԫ�أ�����������������Ԫ�صĴ�С


Status
Pop(PSTACK sqs, void * e, const int _size) {

	assert(sqs != NULL);

	if (StackEmpty(sqs)) {

		return ERROR;

	}

	sqs->_top--;
	sqs->_cnt--;

	memcpy(e, sqs->_top, _size);

	return OK;

}
// ��ջ���գ���ɾ��ջ��Ԫ�أ���������ֵ������������������Ԫ�صĴ�С


static Status
AddStackSize(PSTACK sqs) {

	assert(sqs != NULL);

	void **add = (void **)realloc(sqs->_base,
		(sqs->_stacksize + STACKINCREMENT) * sizeof(*(sqs->_top)));

	if (!add) {

		exit(OVERFLOW);

	}

	sqs->_base = add;
	sqs->_stacksize += STACKINCREMENT;

	return OK;

}
// ����ջ������

/*
-----------------------------------------------------------------------------
*/
