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
	else
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