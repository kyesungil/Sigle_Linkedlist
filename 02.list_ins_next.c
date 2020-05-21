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

int list_ins_next(List* list, ListElmt* element, const void* data)
{
	// [1] allocate storage for a new element
	ListElmt* new_element = (ListElmt*)malloc(sizeof(ListElmt));

	// allocate check
	if (new_element == NULL)
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