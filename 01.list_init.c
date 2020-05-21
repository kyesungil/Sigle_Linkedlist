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