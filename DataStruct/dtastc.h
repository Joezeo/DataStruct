/*
+
-             ���ߣ�Joezeo < joezeo@outlook.com >
+
-             ����ʱ�䣺2017.12.21 / 18��23
+
-             �޸�ʱ�䣺2018.02.02 / 15��01
+
-             �ļ����ƣ�dtastc.h
+
-             ���ܣ����ݽṹ���ͷ�ļ��������ꡢ�ṹ��Ķ��壬����ǰ������
+
*/

#ifndef __DTA_STC_H__
#define __DTA_STC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <assert.h>
#include <stdlib.h>
#include <string.h>

/*
+
-              ״̬�붨��
+
*/
#define TRUE           1      
#define FALSE          0
#define OK             0
#define ERROR         -1
#define OVERFLOW      -2

typedef unsigned int UINT;
typedef int Status;

/*
----------------------------------- SqList -----------------------------------
*/

#define LISTINITSIZE  50
// ˳����ʼ����

#define LISTINCREMENT 10
// ˳�����������

/*
+
-              �ṹ�嶨��
+
*/
typedef struct {

	void ** m_base;    // ���Ա����ַ
	UINT m_length;     // ���Ա���
	UINT m_listsize;   // ���Ա�����

}LIST, * PLIST;

/*
+
-              ����ǰ������
+
*/
PLIST
InitList(const int);
// ��ʼ��һ�����Ա�


Status
FreeList(PLIST);
// ����һ�����Ա��ͷ��ڴ���Դ


Status
EmptyList(const PLIST);
// �ж����Ա��Ƿ�Ϊ�ձ��Ƿ���TRUE�����򷵻�FALSE


Status
ClearList(PLIST);
// ���һ�����Ա�������Ϊ�ձ�


int
ListLength(const PLIST);
// �������Ա��ȣ�����Ԫ�ظ�����


void *
GetElem(const PLIST, const UINT);
// ��ȡ���Ա�ĵ�i������Ԫ��,�����Ա�Ϊ�ձ���NULL��,iԽ�緵��NULL


Status
Located(const PLIST, const void *);
// �ж����Ա����Ƿ����ֵΪ�ڶ�������������Ԫ��


Status
ListInsert(PLIST, const UINT, const void *, const int);
// ���Ա��������Ԫ�أ��ڵڶ�������λ�ò���Ԫ�أ�ֵΪ������������ֵ�����ĸ�����Ϊ����Ԫ�صĴ�С��


Status
ListRemove(PLIST, const UINT);
// ���Ա�ɾ������Ԫ�أ�ɾ��λ��Ϊ�ڶ���������

/*
------------------------------------------------------------------------------
*/





/*
---------------------------------- LinkList ----------------------------------
*/

/*
+
-              �ṹ�嶨��
+
*/
typedef struct NODE {

	void * m_data;
	struct NODE * m_next;
	struct NODE * m_pre;

}NODE, * PNODE;

typedef struct {

	PNODE m_head;    // ͷָ��
	PNODE m_tail;    // βָ��
	UINT  m_cnt;     // Ԫ�ظ���

}LINKLIST, * PLINKLIST;

/*
+
-              ����ǰ������
+
*/

Status
FreeNode(PNODE);
// �ͷŴ˽ڵ���ڴ�ռ�


PLINKLIST
Initlklist();
// ��ʼ��һ������ͷ���Ŀ�����


Status
FreelkList(PLINKLIST);
// ���������ͷ��ڴ�ռ�


Status
ClearlkList(PLINKLIST);
// �������Ϊ������


Status
EmptylkList(const PLINKLIST);
// �ж�һ�������Ƿ�Ϊ�գ����򷵻�TRUE�����򷵻�FALSE


Status
AddNode(PLINKLIST, void *, const int);
// Ϊ�����½�һ���ڵ㣬��������Ϊ����ĵڶ���������ֵ��Ĭ�ϲ���˳���β�����룩������������Ϊ����Ԫ�صĴ�С


Status
RemoveNode(PLINKLIST);
// ����ɾ��һ����㡣(Ĭ�ϴ�β��ɾ��)


int
lkListLength(const PLINKLIST);
// ��������ĳ���(Ԫ�ظ���)


PNODE
GetNode(const PLINKLIST, void *);
// �������в���������Ϊ�ڶ�������ֵ�Ľڵ㣬���������ַ,��û�ҵ�������NULL


Status
InsertNodeAfter(PNODE, void *, const int);
// �ڵ�һ�����������������Ϊ�ڶ����������½ڵ�


Status
InsertNodeBefore(PNODE, void *, const int);
// �ڵ�һ�������ǰ����������Ϊ�ڶ����������½ڵ�

/*
------------------------------------------------------------------------------
*/





/*
----------------------------------- Stack -----------------------------------
*/

#define STACKINITSIZE  50
// ջ��ʼ��ʱ����ʼ����

#define STACKINCREMENT 10
// ջ��������

/*
+
-              �ṹ�嶨��
+
*/
typedef struct {

	void ** m_base;          // ջ��ָ��
	void ** m_top;           // ջ��ָ��
	UINT m_stacksize;        // ջ����
	UINT m_cnt;              // ��ǰջԪ�ظ���

}STACK, * PSTACK;

/*
+
-              ����ǰ������
+
*/
PSTACK
InitStack(const int);
// ����һ����ջ


Status
DestroyStack(PSTACK);
// ����ջ���ͷ���Դ


Status
ClearStack(PSTACK);
// ��ջԪ����գ���Ϊ��ջ

Status
StackEmpty(const PSTACK);
// ��ջΪ��ջ������TRUE�����򷵻�FALSE


int
StackLength(const PSTACK);
// ����ջԪ�صĸ�������ջ�ĳ���


Status
GetTop(const PSTACK, void *, const int);
// ��ջ���գ�����ջ��Ԫ�ص�ֵ�����򷵻�NULL


Status
Push(PSTACK, const void *, const int);
// ����Ԫ��eΪ�µ�ջ��Ԫ��


Status
Pop(PSTACK, void *, const int);
// ��ջ���գ���ɾ��ջ��Ԫ�أ���������ֵ


/*
-----------------------------------------------------------------------------
*/





/*
----------------------------------- Quene -----------------------------------
*/

// ����˫������Ķ��У���ʵ�ֶ�̬�����ڴ�

/*
+
-              �ṹ�嶨��
+
*/
typedef struct QNODE {
	
	void ** m_data;

	struct QNODE * m_nex;
	struct QNODE * m_pre;

}QNODE, * PQNODE;

typedef struct  {
	
	PQNODE m_front; // ��ͷָ��
	PQNODE m_rear;  // ��βָ��

	UINT   m_cnt;   // ����Ԫ�ظ���

}QUENE, * PQUENE;

/*
+
-              ����ǰ������
+
*/

PQUENE
InitQuene();
// ����һ���ն���

Status
DestroyQuene(PQUENE);
// ���ٶ��У��ͷ��ڴ���Դ


/*
-----------------------------------------------------------------------------
*/

#ifdef __cplusplus
}
#endif

#endif // __DTA_STC_H__ //
