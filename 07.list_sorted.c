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