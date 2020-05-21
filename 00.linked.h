
/* Element Configuration */
typedef struct ListElmt_
{
	void*			 data;	/* Pointer data storage */
	struct ListElmt_* next;	/* next pointer */
}ListElmt;

/* 
	Linked list Configuration

	- Linked list는 여러개의 element로 한줄로 연결 되있다. 그리고
	  시작과 끝의 정보(head pointer, tail pointer)을 알고 있다. 
	  각각의 연결은 각 elemnet의 next poiner에 다음 list element에 주소를 써준다.

	- 각 element가 메모리에 산재해 있기 때문에 리스트의 첫 element를 알아야한다.
		(Head pointer)
		(Tail pointer)

	- 리스트의 마지막을 알기위해서 리스트의 마지막 element의 next값 NULL
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