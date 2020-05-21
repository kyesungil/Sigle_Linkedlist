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