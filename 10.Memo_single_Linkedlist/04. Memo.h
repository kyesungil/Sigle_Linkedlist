#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Linkedlist.h"
#include "mData.h"

#define SLEN 1000

void clear_buffer();
void display_menu();			// TODO: menu 보여주기
void New_mamo(List* list);		// TODO: 새로운 다이어리 생성
void Print_memo(List* list);	// TODO: 모든 diary 출력
void Find_memo(List* list);		// TODO: diary내용 찾기
bool Load_file(List* list);		// TODO: file load
bool Save_file(List* list);		// TODO: save file

void Total_menu(List* list)
{
	char ch;

	while (1)
	{
		display_menu(); // menu 보여주기

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
*TODO: 새로운 다이어리 생성
*/
void New_mamo(List* list)
{
	printf("-----------------------------------------\n");

	// 데이터 동적할당
	Memo* new_memo = (Memo*)malloc(sizeof(Memo));

	// 동적할당 확인
	if (new_memo == NULL)
	{
		printf("Allocate Error!");
	}

	// diary내용 입력후, 링크드리스트에 연결
	printf("Diary Write\n>>");
	while (1)
	{
		if (new_memo != NULL)
		{
			// diary입력 내용 없는지 확인
			if (scanf("%d %[^\n]%*c", &new_memo->day, new_memo->diary) == 0)
			{
				printf("Please enter a sentence\n>>");
				clear_buffer(); // 버퍼를 지워주지 않으면 무한 반복된다.
			}
			else
				break;
		}
	}
	
	// 링크드리스트에 연결
	if (list_ins_next(list, NULL, new_memo) == 0)
		printf("--------------Save success---------------\n\n");
	else
		printf("Save fail\n");
}


/*
 * TODO: 모든 diary 출력
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
 * TODO: diary내용 찾기
 */
void Find_memo(List* list)
{
	printf("-----------------------------------------\n");

	char mfind[20];
	ListElmt* search;
	int i = 1;
	bool flag = true;

	// 찾을 단어 입력
	printf("Find memo word input\n>>");
	while (1)
	{
		// mfind에 입력 했는지 확인
		if (scanf("%[^\n]%*c", mfind) == 0)
		{
			printf("Please enter a word to find\n>>");
			clear_buffer(); // 버퍼를 지워주지 않으면 무한 반복된다.
		}
		else
			break;
	}

	// mfind가 포함된 diary출력
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
	char buffer[SLEN];	// 파일 diary을 보관할 변수
	int   mday;			// 파일 day을 보관할 변수
	char* find;			// 문자교체시 이용할 변수
	FILE*   fp;

	fp = fopen("diary.txt", "rb");
	if (fp == NULL)
	{
		printf("file_load_error");
		return false;
	}

	/*
		- 파일 데이터를 char buffer[], int mday변수에 보관 후, 링크드리스트에 데이터 연결
	*/
	while (!feof(fp))
	{
		if (fscanf(fp, "%d %[^\n]%*c", &mday, buffer) == 2)
		{

			Memo* new_memo = (Memo*)malloc(sizeof(Memo));

			if (new_memo != NULL)
			{
				// 문자교체: ('\n'을 '\0'로 교체)
				find = strchr(buffer, '\n');
				if (find)
					*find = '\0';
		
				new_memo->day = mday;
				strcpy(new_memo->diary, buffer);
			}
			// 링크드리스트에 연결
			list_ins_next(list, NULL, new_memo);
		}
	}
	fclose(fp);

	return true;
}