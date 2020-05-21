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