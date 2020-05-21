
/* Element Configuration */
typedef struct ListElmt_
{
	void*			 data;	/* Pointer data storage */
	struct ListElmt_* next;	/* next pointer */
}ListElmt;

/* 
	Linked list Configuration

	- Linked list�� �������� element�� ���ٷ� ���� ���ִ�. �׸���
	  ���۰� ���� ����(head pointer, tail pointer)�� �˰� �ִ�. 
	  ������ ������ �� elemnet�� next poiner�� ���� list element�� �ּҸ� ���ش�.

	- �� element�� �޸𸮿� ������ �ֱ� ������ ����Ʈ�� ù element�� �˾ƾ��Ѵ�.
		(Head pointer)
		(Tail pointer)

	- ����Ʈ�� �������� �˱����ؼ� ����Ʈ�� ������ element�� next�� NULL
*/

/* Define a structure for linked lists */
typedef struct List_
{
	int			size;			/* the number of element */
	ListElmt*	head;			/* head pointer */
	ListElmt*	tail;			/* tail pointer */
	int			(*match)(const void* key1, const void* key2);
	void		(*destroy)(void* data);
}List;

#define list_size(list) ((list)->size)

#define list_head(list) ((list)->head)

#define list_tail(list) ((list)->tail)

#pragma