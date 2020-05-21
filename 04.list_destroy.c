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