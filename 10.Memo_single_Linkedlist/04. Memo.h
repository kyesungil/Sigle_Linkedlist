#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Linkedlist.h"
#include "mData.h"

#define SLEN 1000

void clear_buffer();
void display_menu();			// TODO: menu �����ֱ�
void New_mamo(List* list);		// TODO: ���ο� ���̾ ����
void Print_memo(List* list);	// TODO: ��� diary ���
void Find_memo(List* list);		// TODO: diary���� ã��
bool Load_file(List* list);		// TODO: file load
bool Save_file(List* list);		// TODO: save file

void Total_menu(List* list)
{
	char ch;

	while (1)
	{
		display_menu(); // menu �����ֱ�

		ch = getchar();

		clear_buffer();

		switch (ch)
		{
		case 'N':
			New_mamo(list);
			break;
		case 'P':
			Print_memo(list);
			break;
		case 'F':
			Find_memo(list);
			break;
		case 'E':
			exit(1);
			break;
		case 'L':
			if(Load_file(list))
				printf("Load file success\n");
			break;
		case 'S':
			if (Save_file(list))
				printf("Save file success\n");
			break;
		default:
			printf("Error! Please input again\n");
			break;
		}
	}
}

void clear_buffer()
{
	while (getchar() != '\n')
		continue;
}


void display_menu()
{
	printf("(N)ew a memo\n(P)rint a memo\n(F)ind a memo\n(E)xit\n");
	printf("(L)oad a file\n(S)ave to a file\n>>");
}



/* 
*TODO: ���ο� ���̾ ����
*/
void New_mamo(List* list)
{
	printf("-----------------------------------------\n");

	// ������ �����Ҵ�
	Memo* new_memo = (Memo*)malloc(sizeof(Memo));

	// �����Ҵ� Ȯ��
	if (new_memo == NULL)
	{
		printf("Allocate Error!");
	}

	// diary���� �Է���, ��ũ�帮��Ʈ�� ����
	printf("Diary Write\n>>");
	while (1)
	{
		if (new_memo != NULL)
		{
			// diary�Է� ���� ������ Ȯ��
			if (scanf("%d %[^\n]%*c", &new_memo->day, new_memo->diary) == 0)
			{
				printf("Please enter a sentence\n>>");
				clear_buffer(); // ���۸� �������� ������ ���� �ݺ��ȴ�.
			}
			else
				break;
		}
	}
	
	// ��ũ�帮��Ʈ�� ����
	if (list_ins_next(list, NULL, new_memo) == 0)
		printf("--------------Save success---------------\n\n");
	else
		printf("Save fail\n");
}


/*
 * TODO: ��� diary ���
 */
void Print_memo(List* list)
{
	printf("-----------------------------------------\n");

	ListElmt* search;
	int i = 1;

	for (search = list->head; search != NULL; search = search->next,i++)
	{
		printf("[Diary%d] : %d %s\n", i,((Memo*)search->data)->day, ((Memo*)search->data)->diary);
	}
	printf("--------------End of Diary---------------\n\n");
}


/*
 * TODO: diary���� ã��
 */
void Find_memo(List* list)
{
	printf("-----------------------------------------\n");

	char mfind[20];
	ListElmt* search;
	int i = 1;
	bool flag = true;

	// ã�� �ܾ� �Է�
	printf("Find memo word input\n>>");
	while (1)
	{
		// mfind�� �Է� �ߴ��� Ȯ��
		if (scanf("%[^\n]%*c", mfind) == 0)
		{
			printf("Please enter a word to find\n>>");
			clear_buffer(); // ���۸� �������� ������ ���� �ݺ��ȴ�.
		}
		else
			break;
	}

	// mfind�� ���Ե� diary���
	for (search = list->head; search != NULL; search = search->next, i++)
	{
		if (strstr(((Memo*)search->data)->diary, mfind) != NULL)
		{
			printf("[Diary%d] : %d %s\n", i, ((Memo*)search->data)->day, ((Memo*)search->data)->diary);
			flag = false;
		}
	}

	if (flag)
		printf("No matching words\n");
	printf("-----------------------------------------\n");
}


/* file save */
bool Save_file(List* list)
{
	ListElmt* search;
	FILE* fp = fopen("diary.txt", "wt");

	if (fp == NULL)
		return false;

	for (search = list->head; search != NULL; search = search->next)
	{
		fprintf(fp,"%d %s\n",((Memo*)search->data)->day, ((Memo*)search->data)->diary);
	}
	fclose(fp);

	return true;
}


bool Load_file(List* list)
{
	char buffer[SLEN];	// ���� diary�� ������ ����
	int   mday;			// ���� day�� ������ ����
	char* find;			// ���ڱ�ü�� �̿��� ����
	FILE*   fp;

	fp = fopen("diary.txt", "rb");
	if (fp == NULL)
	{
		printf("file_load_error");
		return false;
	}

	/*
		- ���� �����͸� char buffer[], int mday������ ���� ��, ��ũ�帮��Ʈ�� ������ ����
	*/
	while (!feof(fp))
	{
		if (fscanf(fp, "%d %[^\n]%*c", &mday, buffer) == 2)
		{

			Memo* new_memo = (Memo*)malloc(sizeof(Memo));

			if (new_memo != NULL)
			{
				// ���ڱ�ü: ('\n'�� '\0'�� ��ü)
				find = strchr(buffer, '\n');
				if (find)
					*find = '\0';
		
				new_memo->day = mday;
				strcpy(new_memo->diary, buffer);
			}
			// ��ũ�帮��Ʈ�� ����
			list_ins_next(list, NULL, new_memo);
		}
	}
	fclose(fp);

	return true;
}