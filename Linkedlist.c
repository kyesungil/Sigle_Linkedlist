#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked.h"

// Data
typedef struct device_
{
	int  dv_id;
	char dv_name[30];
}device;

typedef device* dv_ptr;

/* Linked list 인터페이스 함수 */

/* 
	1. list_init(List* list, void(*destroy)(void* data))

		- Linked list 초기화 함수

		- list의 linked list를 초기화. 리스트를 사용하기 전에 항상 제일 먼저 호출되어야 한다.
		  destroy는 data에 동적 할당된 메모리를 해제하기 위해 호출되는 함수의 포인터.
		  특별히 할당된 메모리 해제가 필요 없으면 NULL로 지정한다.
*/

void list_init(List* list, void(*destroy)(void* data))
{
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;
}

/*
	2. list_ins_next(List *list, ListElmt *element, const void *data)
		- 데이터를 linked list에 끼워넣는 함수.


	  Parmameter
		- List *list: list 정보.
		- ListElmt* element: 넣고싶은 위치의 전 위치(주소).
		- const void *data: date주소 값.


	  구현
		- 성공하면 return 0, 실패하면 return -1.

		- element의 바로 뒤에 끼워 넣기. 만약 element가 NULL인 경우에는 list의 head에 끼워 넣는다.

		- 순서
			[1] new_element 메모리 할당
			[2] new_element->data에 데이터 연결
			[3] new_element->next 지정
			[4] element-> next 지정
*/

int list_ins_next(List *list, ListElmt *element, const void *data)
{
	// [1] allocate storage for a new element
	ListElmt* new_element = (ListElmt*)malloc(sizeof(ListElmt));

	// allocate check
	if(new_element == NULL)
	{
		printf("Allocate ERROR.");
		return -1;
	}

	// [2] new_element->data link
	new_element->data = (void*)data;



	/* [3] 1. new_element head에 들어올 때, 2. 중간에 들어올때 또는 마지막에 들어올때 */

	// 1. Insert at the head
	if (element == NULL) 
	{
		if (list_size(list) == 0) // 최초인 경우, head와 tail포인터로 지정.
			list->tail = new_element;

		new_element->next = list->head;
		list->head = new_element;
	}
	else // 2. Insert at the end or between
	{
		if (element->next == NULL)
			list->tail = new_element;

		new_element->next = element->next;
		element->next = new_element;
	}

	list->size++;

	return 0;
}

/* 
	3. list_rem_next(List* list, ListElmt* element, void** data) 
		- 데이터를 linked list에서 삭제하는 함수


		 Parmameter
		- List *list: list 정보
		- ListElmt* element: 넣고싶은 위치의 전 위치(주소)
		- void **data: 삭제할 data을 담기위한 매개변수
		  ※ (data안에 연속적으로 동적할당 될 경우때문에 함수 자체 내에서 free하지 않는다.)


	  구현
		- 성공하면 return 0, 실패하면 return -1.

		- element의 바로 다음 element를 삭제한다. 만약 element가 NULL인 경우, 리스트의 head를 삭제.
		  Return시에 삭제되는 element에 연결된 데이터의 포인터가 data에 저장된다.

		- 순서
			[1] 삭제할 element의 data 보관
			[2] element의 next 지정
			[3] 삭제 element의 메모리 해제
*/

int list_rem_next(List* list, ListElmt* element, void** data)
{
	ListElmt* old_element; // element to delete

	if (list_size(list) == 0) return -1;

	if (element == NULL) // head 제거
	{
		*data = list->head->data; // 삭제할 element에 연결된 데이터의 포인터 저장
		old_element = list->head;
		list->head = list->head->next;

		if (list_size(list) == 1) // 1개의 element가 있을 경우, tail 포인터 업데이트
			list->tail = NULL;
	}
	else // Handle removal from elsewhere
	{
		if (element->next == NULL) 
			return -1; // No element to delete

		*data = element->next->data;
		old_element = element->next;
		element->next = element->next->next;

		if (element->next == NULL) // 만약 삭제한 element가 tail일 경우
			list->tail = element;
	}	

	free(old_element);
	list->size--;

	return 0;
}

/*
	4. list_destroy(List *list)
		- 리스트에 있는 모든데이터 삭제


	  구현
		- return 없음

		- 리스트의 모든 element삭제

		- struct List에 함수포인터 즉,void(*destroy)(void* data)에
		  data을 제거할수 있는 함수를 만들어야함(본인이 만든 data구조에 따라서).
		   
		- list_init(List* list, void(*destroy)(void* data)) 처음 초기화 할때
		  매개변수로 함수포인터을 설정한다.

*/

void list_destroy(List* list)
{
	void* data;

	while (list->size > 0)
	{
		if (list_rem_next(list, NULL, &data) == 0 && list->destroy != NULL)
			list->destroy(data);
	}
}

void my_free(void* data)
{
	free(data);

	return;
}

/*
	5. display_list(List* list)
		- 저장된 데이터를 화면에 출력
*/

void display_list(List* list)
{
	ListElmt* search;

	if (list->head == NULL)
	{
		printf("No items\n");
		return;
	}
	// head부터시작해서 next포인터로 하나씩 노드를 지나간다. 마지막으로 next포인터가 NULL이면 종료
	for (search = list->head; search != NULL; search = search->next)
	{
		printf("[ID:%d Name:%s]\n",
			((dv_ptr)search->data)->dv_id, ((dv_ptr)search->data)->dv_name);
	}
	return;
}

/* 응용 - 오름차순으로 데이터 넣기 */
int list_sorted_insert(List* list, device* dev_data)                                                                                                                                                                                                                                          
{
	ListElmt* search;
	ListElmt* prev = NULL; // head 앞에 데이터가 들어갈수 있기 때문에 NULL로 초기화

	// 데이터 오름차순으로
	for (search = list->head; search != NULL; search = search->next)
	{
		if (strcmp(((dv_ptr)search->data)->dv_name, dev_data->dv_name) > 0)
			break;
		else
			prev = search; // 이전 노드 저장
	}
	return list_ins_next(list, prev, dev_data);
}

/* 오름차순으로 정렬하기 */
void list_sorted(List* list, device* tmp_data)
{
	ListElmt* search;
	ListElmt* search2;

	for (search = list->head; search != NULL; search = search->next)
	{
		for (search2 = search->next; search2 != NULL; search2 = search2->next)
		{
			if (strcmp(((dv_ptr)search->data)->dv_name, ((dv_ptr)search2->data)->dv_name) > 0)
			{
				tmp_data = search->data;
				search->data = search2->data;
				search2->data = tmp_data;
			}
		}
	}
	return;
}

int main()
{
	// 초기화.
	List list;
	list_init(&list, my_free);

	// Allocate data
	dv_ptr new_data = (dv_ptr)malloc(sizeof(device));
	if (new_data == NULL)
	{
		printf("Allocate ERROR.");
		exit(1);
	}
	new_data->dv_id = 1;
	strcpy(new_data->dv_name, "AJordan");

	// list에 데이터넣기 (Linked list at head)
	list_ins_next(&list, NULL, new_data);

	// Allocate data
	new_data = (dv_ptr)malloc(sizeof(device));
	if (new_data == NULL)
	{
		printf("Allocate ERROR.");
		exit(1);
	}
	new_data->dv_id = 2;
	strcpy(new_data->dv_name, "James");

	// list에 데이터넣기 (Linked list at head)
	list_ins_next(&list, NULL, new_data);

	// Allocate data
	new_data = (dv_ptr)malloc(sizeof(device));
	if (new_data == NULL)
	{
		printf("Allocate ERROR.");
		exit(1);
	}
	new_data->dv_id = 2;
	strcpy(new_data->dv_name, "ZMEN");

	// list에 데이터넣기 (Linked list at head)
	list_ins_next(&list, NULL, new_data);

	display_list(&list);

	printf("----------------------------------------\n");

	device p;
	list_sorted(&list, &p);

	display_list(&list);

	// 데이터삭제 (delete head)
	void* data;
	list_rem_next(&list, NULL, &data); // 변수에 주소를 넣는이유는 함수에서 그 변수값을 바꾸기 위해서
	free(data);

	list_destroy(&list);

	printf("----------------------------------------\n");

	display_list(&list);

	return 0;
}