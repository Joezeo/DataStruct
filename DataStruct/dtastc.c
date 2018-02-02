/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2017.12.21 / 18：23
+
-             修改时间：2018.02.02 / 15：01
+
-             文件名称：dtastc.c
+
-             功能：数据结构库的函数定义
+
*/

#include "dtastc.h"

/*
----------------------------------- SqList -----------------------------------
*/

static Status
__addlistSize(PLIST);
// 静态函数，增加线性表的容量

/*
+
-               函数定义
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
// 初始化一个线性表


Status
FreeList(PLIST plist) {

	assert(plist != NULL);

	free(plist->m_base);
	plist->m_base = NULL;

	free(plist);
	plist = NULL;

	return OK;

}
// 销毁一个线性表，释放内存资源


Status
EmptyList(const PLIST plist) {

	assert(plist != NULL);

	if (plist->m_length == 0) {

		return TRUE;

	}

	return FALSE;

}
// 判断线性表是否为空表。是返回TRUE，否则返回FALSE


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
// 清空一个线性表，将其置为空表


int
ListLength(const PLIST plist) {

	assert(plist != NULL);

	return plist->m_length;

}
// 返回线性表长度（数据元素个数）


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
// 获取线性表的第i个数据元素,如线性表为空表返回NULL,i越界返回NULL


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
// 判断线性表中是否存在值为第二个参数的数据元素


Status
ListInsert(PLIST plist, const UINT i, const void * e, const int _size) {

	assert(plist != NULL);

	if (i <= 0 || i > plist->m_length + 1) {

		return ERROR;

	}

	if (plist->m_length == plist->m_listsize) {

		__addlistSize(plist);

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
// 线性表插入数据元素（在第二个参数位置插入元素，值为第三个参数的值，第四个参数为数据元素的大小）


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
// 线性表删除数据元素（删除位置为第二个参数）


static Status
__addlistSize(PLIST plist) {

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
// 静态函数，增加线性表的容量

/*
------------------------------------------------------------------------------
*/





/*
---------------------------------- LinkList ----------------------------------
*/

static PNODE
__newNode(void *, const int);
// 创建一个新的节点，其数据域为传入的参数的值

/*
+
-               函数定义
+
*/

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
// 释放此节点的内存空间


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
// 初始化一个不带头结点的空链表


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
// 销毁链表，释放内存空间


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
// 清空链表为空链表


Status
EmptylkList(const PLINKLIST lklist) {

	assert(lklist != NULL);

	if (lklist->m_cnt == 0) {

		return TRUE;

	}

	return FALSE;

}
// 判断一个链表是否为空，是则返回TRUE；否则返回FALSE


Status
AddNode(PLINKLIST lklist, void * e, const int _size) {

	assert(lklist != NULL);

	PNODE newnode = __newNode(e, _size);

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
// 为链表新建一个节点，其数据域为传入的第二个参数的值（默认插入顺序从尾部插入），第三个参数为数据元素的大小


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
// 链表删除一个结点。(默认从尾部删除)


int
lkListLength(const PLINKLIST lklist) {

	assert(lklist != NULL);

	return lklist->m_cnt;

}
// 返回链表的长度(元素个数)


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
// 在链表中查找数据域为第二个参数值的节点，并返回其地址,如没找到，返回NULL


Status
InsertNodeAfter(PNODE node, void * e, const int _size) {

	assert(node != NULL);

	PNODE tmp = node->m_next;
	PNODE newnode = __newNode(e, _size);

	newnode->m_next = tmp;
	newnode->m_pre = node;

	node->m_next = newnode;
	tmp->m_pre = newnode;

	return OK;


}
// 在第一参数结点后插入数据域为第二个参数的新节点， 第三个参数为数据元素的大小


Status
InsertNodeBefore(PNODE node, void * e, const int _size) {

	assert(node != NULL);

	PNODE tmp = node->m_pre;
	PNODE newnode = __newNode(e, _size);

	newnode->m_pre = tmp;
	newnode->m_next = node;

	tmp->m_next = newnode;
	node->m_pre = newnode;

	return OK;

}
// 在第一参数结点前插入数据域为第二个参数的新节点，第三个参数为数据元素的大小


static PNODE
__newNode(void * e, const int _size) {

	PNODE newnode = (PNODE)malloc(sizeof(NODE));
	if (!newnode) {

		exit(OVERFLOW);

	}

	memcpy(newnode->m_data, e, _size);
	newnode->m_next = NULL;
	newnode->m_pre = NULL;

	return newnode;

}
// 创建一个新的节点，其数据域为传入的参数的值

/*
------------------------------------------------------------------------------
*/





/*
----------------------------------- Stack -----------------------------------
*/

static Status
__addStackSize(PSTACK);
// 增加栈的容量

/*
+
-               函数定义
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
// 构造一个空栈


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
// 销毁栈，释放资源


Status
ClearStack(PSTACK sqs) {

	assert(sqs != NULL);

	sqs->m_top = sqs->m_base;
	sqs->m_cnt = 0;

	return OK;

}
// 将栈元素清空，置为空栈


Status
StackEmpty(const PSTACK sqs) {

	assert(sqs != NULL);

	if (sqs->m_cnt == 0)
		return TRUE;

	return FALSE;

}
// 若栈为空栈，返回TRUE，否则返回FALSE


int
StackLength(const PSTACK sqs) {

	assert(sqs != NULL);

	return sqs->m_cnt;

}
// 返回栈元素的个数，即栈的长度


Status
GetTop(const PSTACK sqs, void * e, const int _size) {

	assert(sqs != NULL);

	if (StackEmpty(sqs)) {

		return ERROR;

	}

	memcpy(e, sqs->m_top - 1, _size);

	return OK;

}
// 若栈不空，返回栈顶元素的值；否则返回NULL。第二个参数为数据元素的大小


Status
Push(PSTACK sqs, const void * e, const int _size) {

	assert(sqs != NULL);

	if (sqs->m_cnt == sqs->m_stacksize) {

		__addStackSize(sqs);

	}

	memcpy(sqs->m_top, e, _size);

	sqs->m_top++;
	sqs->m_cnt++;

	return OK;

}
// 插入元素e为新的栈顶元素，第三个参数是数据元素的大小


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
// 若栈不空，则删除栈顶元素，并返回其值，第三个参数是数据元素的大小


static Status
__addStackSize(PSTACK sqs) {

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
// 增加栈的容量

/*
-----------------------------------------------------------------------------
*/




/*
----------------------------------- Quene -----------------------------------
*/

static PQNODE
__newQnode(const void *, const int);
// 静态函数，创建一个新的队列结点

static Status
__destroyQnode(PQNODE);
// 静态函数，删除传入的结点

/*
+
-              函数定义
+
*/

PQUENE
InitQuene() {

	PQUENE pQuene = (PQUENE)malloc(sizeof(QUENE));
	if (!pQuene)
		exit(OVERFLOW);

	pQuene->m_front = NULL;
	pQuene->m_rear  = NULL;
	pQuene->m_cnt   = 0;

	return pQuene;

}
// 构造一个空队列


Status
DestroyQuene(PQUENE pQuene) {

	assert(pQuene != NULL);

	ClearQuene(pQuene);

	free(pQuene);
	pQuene = NULL;

	return OK;

}
// 销毁队列，释放内存资源


Status
ClearQuene(PQUENE pQuene) {

	assert(pQuene != NULL);

	if (!EmptyQuene(pQuene)) {

		PQNODE pPre = NULL;
		PQNODE pCur = pQuene->m_front;

		while (pCur != NULL) {

			pPre = pCur->m_nex;
			__destroyQnode(pCur);
			pCur = pPre;

		}

	}

	pQuene->m_cnt = 0;

	return OK;

}
// 将队列清空为空队列


Status
EmptyQuene(const PQUENE pQuene) {

	assert(pQuene != NULL);

	if (pQuene->m_cnt == 0)
		return TRUE;

	return FALSE;

}
// 若队列为空队列，返回TRUE，否则返回FALSE


UINT
QueneLength(const PQUENE pQuene) {

	assert(pQuene != NULL);

	return pQuene->m_cnt;

}
// 返回队列元素个数，及队列长度


Status
GetHead(const PQUENE pQuene, void * e, const int _size) {

	assert(pQuene != NULL);
	assert(e != NULL);

	memcpy(e, pQuene->m_front->m_data, _size);

	return OK;

}
// 用第二个参数获取队头元素的值，第三个参数传入数据元素的大小，不删除队头元素的值


Status
EnQuene(PQUENE pQuene, const void * e, const int _size) {

	assert(pQuene != NULL);
	assert(e != NULL);

	PQNODE newNode = __newQnode(e, _size);

	if (EmptyQuene(pQuene)) {

		pQuene->m_front = newNode;
		pQuene->m_rear  = newNode;

	}
	else {

		pQuene->m_rear->m_nex = newNode;
		newNode->m_pre = pQuene->m_rear;

		pQuene->m_rear = newNode;

	}

	pQuene->m_cnt++;

	return OK;

}
// 插入元素e为队列的新队尾元素


Status
DeQuene(PQUENE pQuene, void * e, const int _size) {

	assert(pQuene != NULL);
	assert(e != NULL);

	if (EmptyQuene(pQuene)) {

		return ERROR;

	}

	memcpy(e, pQuene->m_front->m_data, _size);

	PQNODE pTmp = pQuene->m_front;

	pQuene->m_front = pTmp->m_nex;

	pQuene->m_cnt--;

	__destroyQnode(pTmp);

	return OK;

}
// 若队列不空，删除队列的头元素，并用第二个参数返回其值


static PQNODE
__newQnode(const void * e, const int _size) {

	assert(e != NULL);

	PQNODE newNode = (PQNODE)malloc(sizeof(PQNODE));
	if (!newNode)
		exit(OVERFLOW);

	newNode->m_data = (void **)malloc(_size);
	if (!(newNode->m_data))
		exit(OVERFLOW);

	memcpy(newNode->m_data, e, _size);

	newNode->m_nex = NULL;
	newNode->m_pre = NULL;

	return newNode;

}
// 静态函数，创建一个新的队列结点


static Status
__destroyQnode(PQNODE pQnode) {

	assert(pQnode != NULL);

	free(pQnode->m_data);
	pQnode->m_data = NULL;

	free(pQnode);
	pQnode = NULL;

	return OK;

}
// 静态函数，删除传入的结点


/*
-----------------------------------------------------------------------------
*/
