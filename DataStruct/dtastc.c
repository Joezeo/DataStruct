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

	_list->m_base = (void **)malloc(LISTINITSIZE * _size);
	if (!(_list->m_base)) {

		exit(OVERFLOW);

	}

	_list->m_length = 0;
	_list->m_listsize = LISTINITSIZE;

	return _list;

}
// ��ʼ��һ�����Ա�


Status
FreeList(PLIST plist) {

	assert(plist != NULL);

	free(plist->m_base);
	plist->m_base = NULL;

	free(plist);
	plist = NULL;

	return OK;

}
// ����һ�����Ա��ͷ��ڴ���Դ


Status
EmptyList(const PLIST plist) {

	assert(plist != NULL);

	if (plist->m_length == 0) {

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

	for (UINT i = 0; i < plist->m_length; i++) {

		*(plist->m_base + i) = 0;

	}

	plist->m_length = 0;

	return OK;

}
// ���һ�����Ա�������Ϊ�ձ�


int
ListLength(const PLIST plist) {

	assert(plist != NULL);

	return plist->m_length;

}
// �������Ա��ȣ�����Ԫ�ظ�����


void *
GetElem(const PLIST plist, const UINT i) {

	assert(plist != NULL);

	if (EmptyList(plist)) {

		return NULL;

	}

	if (i > plist->m_length || i <= 0) {

		return NULL;

	}

	return *(plist->m_base + i - 1);

}
// ��ȡ���Ա�ĵ�i������Ԫ��,�����Ա�Ϊ�ձ���NULL,iԽ�緵��NULL


Status
Located(const PLIST plist, const void * e) {

	assert(plist != NULL);

	if (EmptyList(plist)) {

		return FALSE;

	}

	for (UINT i = 0; i < plist->m_length; i++) {

		if (*(plist->m_base + i) == e) {

			return TRUE;

		}

	}

	return FALSE;

}
// �ж����Ա����Ƿ����ֵΪ�ڶ�������������Ԫ��


Status
ListInsert(PLIST plist, const UINT i, const void * e, const int _size) {

	assert(plist != NULL);

	if (i <= 0 || i > plist->m_length + 1) {

		return ERROR;

	}

	if (plist->m_length == plist->m_listsize) {

		AddlistSize(plist);

	}

	if(EmptyList(plist)){

		memcpy(plist->m_base, e, _size);

		goto fend;
	
	}
	else if (i == plist->m_length + 1) {

		memcpy(plist->m_base + i - 1, e, _size);

		goto fend;

	}
	else {

		for (UINT j = plist->m_length; j >= i; j--) {

			memcpy(plist->m_base + j, plist->m_base + j - 1, _size);

		}

		memcpy(plist->m_base + i - 1, e, _size);

		goto fend;

	}

fend:
	plist->m_length++;
	return OK;

}
// ���Ա��������Ԫ�أ��ڵڶ�������λ�ò���Ԫ�أ�ֵΪ������������ֵ�����ĸ�����Ϊ����Ԫ�صĴ�С��


Status
ListRemove(PLIST plist, const UINT i) {

	assert(plist != NULL);

	if (i <= 0 || i > plist->m_length) {

		return ERROR;

	}

	if (EmptyList(plist)) {

		return ERROR;

	}

	if (i == plist->m_length) {

		*(plist->m_base + i - 1) = 0;

		goto fend;

	}
	else {

		for (UINT j = i - 1; j < plist->m_length - 1; j++) {

			*(plist->m_base + j) = *(plist->m_base + j + 1);

			goto fend;

		}

	}

fend:
	plist->m_length--;
	return OK;

}
// ���Ա�ɾ������Ԫ�أ�ɾ��λ��Ϊ�ڶ���������


static Status
AddlistSize(PLIST plist) {

	assert(plist != NULL);

	void ** add = (void **)realloc(plist->m_base,
		(plist->m_listsize + LISTINCREMENT) * sizeof(void *));

	if (!add) {

		exit(OVERFLOW);

	}

	plist->m_base = add;
	plist->m_listsize += LISTINCREMENT;

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

	memcpy(newnode->m_data, e, _size);
	newnode->m_next = NULL;
	newnode->m_pre = NULL;

	return newnode;

}
// ����һ���µĽڵ㣬��������Ϊ����Ĳ�����ֵ


Status
FreeNode(PNODE node) {

	assert(node != NULL);

	if (node->m_pre != NULL) {

		PNODE tmp = node->m_pre;
		tmp->m_next = node->m_next;

	}
	if (node->m_next != NULL) {

		PNODE tmp = node->m_next;
		tmp->m_pre = node->m_pre;

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

	lklist->m_cnt = 0;
	lklist->m_head = NULL;
	lklist->m_tail = NULL;

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
	PNODE cur = lklist->m_head;

	while (cur != NULL) {

		pre = cur->m_next;
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
	PNODE cur = lklist->m_head;

	while (cur != NULL) {

		pre = cur->m_next;
		free(cur);
		cur = pre;

	}

	lklist->m_head = NULL;
	lklist->m_tail = NULL;
	lklist->m_cnt = 0;

	return OK;

}
// �������Ϊ������


Status
EmptylkList(const PLINKLIST lklist) {

	assert(lklist != NULL);

	if (lklist->m_cnt == 0) {

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

		lklist->m_head = newnode;
		lklist->m_tail = newnode;

	}
	else {

		PNODE tmp = NULL;
		tmp = lklist->m_tail;
		lklist->m_tail->m_next = newnode;
		lklist->m_tail = newnode;
		lklist->m_tail->m_pre = tmp;

	}

	lklist->m_cnt++;

	return OK;

}
// Ϊ�����½�һ���ڵ㣬��������Ϊ����ĵڶ���������ֵ��Ĭ�ϲ���˳���β�����룩������������Ϊ����Ԫ�صĴ�С


Status
RemoveNode(PLINKLIST lklist) {

	assert(lklist != NULL);

	PNODE tmp = lklist->m_tail;

	if (EmptylkList(lklist)) {

		return ERROR;

	}

	lklist->m_tail = lklist->m_tail->m_pre;
	lklist->m_tail->m_next = NULL;
	lklist->m_cnt--;

	free(tmp);
	tmp = NULL;

	return OK;

}
// ����ɾ��һ����㡣(Ĭ�ϴ�β��ɾ��)


int
lkListLength(const PLINKLIST lklist) {

	assert(lklist != NULL);

	return lklist->m_cnt;

}
// ��������ĳ���(Ԫ�ظ���)


PNODE
GetNode(const PLINKLIST lklist, void * e) {

	assert(lklist != NULL);

	if (EmptylkList(lklist)) {

		return NULL;

	}

	PNODE node = lklist->m_head;

	for (; node != NULL; node = node->m_next) {

		if (node->m_data == e) {

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

	PNODE tmp = node->m_next;
	PNODE newnode = NewNode(e, _size);

	newnode->m_next = tmp;
	newnode->m_pre = node;

	node->m_next = newnode;
	tmp->m_pre = newnode;

	return OK;


}
// �ڵ�һ�����������������Ϊ�ڶ����������½ڵ㣬 ����������Ϊ����Ԫ�صĴ�С


Status
InsertNodeBefore(PNODE node, void * e, const int _size) {

	assert(node != NULL);

	PNODE tmp = node->m_pre;
	PNODE newnode = NewNode(e, _size);

	newnode->m_pre = tmp;
	newnode->m_next = node;

	tmp->m_next = newnode;
	node->m_pre = newnode;

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

	sqs->m_base = (void **)malloc(STACKINITSIZE * _size);
	if (!(sqs->m_base)) {

		exit(OVERFLOW);

	}	
	
	sqs->m_top = sqs->m_base;
	sqs->m_stacksize = STACKINITSIZE;
	sqs->m_cnt = 0;

	return sqs;

}
// ����һ����ջ


Status
DestroyStack(PSTACK sqs) {

	assert(sqs != NULL);

	free(sqs->m_base);
	sqs->m_base = NULL;
	sqs->m_top = NULL;

	free(sqs);
	sqs = NULL;

	return OK;

}
// ����ջ���ͷ���Դ


Status
ClearStack(PSTACK sqs) {

	assert(sqs != NULL);

	sqs->m_top = sqs->m_base;
	sqs->m_cnt = 0;

	return OK;

}
// ��ջԪ����գ���Ϊ��ջ


Status
StackEmpty(const PSTACK sqs) {

	assert(sqs != NULL);

	if (sqs->m_cnt == 0)
		return TRUE;

	return FALSE;

}
// ��ջΪ��ջ������TRUE�����򷵻�FALSE


int
StackLength(const PSTACK sqs) {

	assert(sqs != NULL);

	return sqs->m_cnt;

}
// ����ջԪ�صĸ�������ջ�ĳ���


Status
GetTop(const PSTACK sqs, void * e, const int _size) {

	assert(sqs != NULL);

	if (StackEmpty(sqs)) {

		return ERROR;

	}

	memcpy(e, sqs->m_top - 1, _size);

	return OK;

}
// ��ջ���գ�����ջ��Ԫ�ص�ֵ�����򷵻�NULL���ڶ�������Ϊ����Ԫ�صĴ�С


Status
Push(PSTACK sqs, const void * e, const int _size) {

	assert(sqs != NULL);

	if (sqs->m_cnt == sqs->m_stacksize) {

		AddStackSize(sqs);

	}

	memcpy(sqs->m_top, e, _size);

	sqs->m_top++;
	sqs->m_cnt++;

	return OK;

}
// ����Ԫ��eΪ�µ�ջ��Ԫ�أ�����������������Ԫ�صĴ�С


Status
Pop(PSTACK sqs, void * e, const int _size) {

	assert(sqs != NULL);

	if (StackEmpty(sqs)) {

		return ERROR;

	}

	sqs->m_top--;
	sqs->m_cnt--;

	memcpy(e, sqs->m_top, _size);

	return OK;

}
// ��ջ���գ���ɾ��ջ��Ԫ�أ���������ֵ������������������Ԫ�صĴ�С


static Status
AddStackSize(PSTACK sqs) {

	assert(sqs != NULL);

	void **add = (void **)realloc(sqs->m_base,
		(sqs->m_stacksize + STACKINCREMENT) * sizeof(*(sqs->m_top)));

	if (!add) {

		exit(OVERFLOW);

	}

	sqs->m_base = add;
	sqs->m_stacksize += STACKINCREMENT;

	return OK;

}
// ����ջ������

/*
-----------------------------------------------------------------------------
*/
