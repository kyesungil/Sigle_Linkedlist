#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Memo.h"



int main()
{
	List list;
	list_init(&list, NULL);


	Total_menu(&list);

	return 0;
}