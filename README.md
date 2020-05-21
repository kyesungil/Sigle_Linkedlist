# Sigle_Linked list
## 1. Linked list 구성
- __데이터들을 연결선을 통해서 연결된 자료들__


![Linkedlist](https://user-images.githubusercontent.com/41607872/82530263-e85c5480-9b77-11ea-8b35-fdbc7041574e.jpg)


- __그림상의 네모를 노드라 할때, 각 노드의 주소는 각 노드의 전노드 공간에 next 포인터에 저장된다.__
- __각 노드가 메모리에 여기저기 흩어져 있기 때문에 리스트의 첫 노드(elemnet)주소를 기억해야한다.__  
  1. _head pointer_: 첫 노드의 주소 저장  
  2. _tail pointer_: 마지막 노드의 주소 저장  
  3. 리스트의 마지막 노드의 next값은 NULL로 지정(마지막 노드 체크을 위해서)  
#### code  

```c
typedef struct List_
{
	int       size;  // 데이터 개수
	ListElmt* head;
	ListElmt* tail;

	int	(*match)(const void* key1, const void* key2);
	void    (*destroy)(void* data); // 할당 메모리 해제를 위한 함수 포인터
}List;
```
***  
## 2. 노드(또는 element)의 구성(ListElmt)  
- __데이터 포인터(void* data):__  저장할 데이터의 주소를 가진다.  
  _자료형 void*인 이유는? 테이터의 타입이 정해져 있지 않기 때문이다. 예로 학생데이터 또는 로봇데이터가 저장되있을 수 있다. 그래서 나중에 캐스팅해준다._
- __next 포인터(ListElmt* next):__  뒤에 나오는 노드의 주소를 저장, 즉 연결선  
#### code  

```c
typedef struct ListElmt_
{
	void*  data;
	struct ListElmt_* next;

}ListElmt;
```
***
## 3. Linled list 인터페이스 함수
### 3-1. Linked lsit 초기화 함수: list_init(List* list, void(*destroy)(void* data))  
- list(Linked list 전체)의 linked list를 초기화. 리스트를 사용하기 전에 항상 제일 먼저 호출되어야 한다. destroy는 data에 동적 할당된 메모리를 해제하기 위해 호출되는 함수의 포인터. 
특별히 할당된 메모리 해제가 필요 없으면 NULL로 지정한다.  
- head와 tail은 NULL 값으로 지정, list의 size 즉, 데이터의 개수 0으로 지정  
#### code  

```c
void list_init(List* list, void(*destroy)(void* data))
{
	list->size = 0; // 데이터 개수
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;
}
```
### 3-2. 데이터를 Linked list에 끼워넣는 함수: list_ins_next(List *list, ListElmt *element, const void *data)  
- Parmameter
  1. _List *list:_  list 정보.
  2. _ListElmt* element:_  넣고싶은 위치의 전 위치(주소).
  3. _const void *data:_  date주소 값.
- 구현
  1. 성공하면 return 0, 실패하면 return -1.
  2. element의 바로 뒤에 끼워 넣기. 만약 element가 NULL인 경우에는 list의 head에 끼워 넣는다.
  3. 순서  
    [1] new_element 메모리 할당  
    [2] new_element->data에 데이터 연결  
    [3] new_element->next 지정  
    [4] element-> next 지정  
#### 1) 노드가 중간 또는 마지막에 들어올 때  
![insert](https://user-images.githubusercontent.com/41607872/82536942-38411880-9b84-11ea-9488-4ce398ee28ca.jpg)  
#### 2) 노드가 head로 들어올 때
<img src="https://user-images.githubusercontent.com/41607872/82537049-645c9980-9b84-11ea-8193-0bb7bfa3ac41.jpg" width="500" height="350">  

#### code    

```c  

int list_ins_next(List* list, ListElmt* element, const void* data)
{
	// [1] allocate storage for a new element(메모리 할당)
	ListElmt* new_element = (ListElmt*)malloc(sizeof(ListElmt));

	// allocate check
	if (new_element == NULL)
	{
		printf("Allocate ERROR.");
		return -1;
	}

	// [2] new_element->data link(데이터 연결)
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
```  
### 3-3. 데이터를 linked list에서 삭제하는 함수: list_rem_next(List* list, ListElmt* element, void** data)  
- parmamter
  1. _List *list:_ list 정보
  2. _ListElmt* element:_ 삭제할 위치의 전 위치(주소)
  3. _void **data:_ 삭제할 data을 담기위한 매개변수
  ※ (data안에 연속적으로 동적할당 될 경우때문에 함수 자체 내에서 free하지 않는다.)  
- 구현  
  1. 성공하면 return 0, 실패하면 return -1.  
  2. element(노드)의 바로 다음 element(노드)를 삭제한다. 만약 element가 NULL인 경우, 리스트의 head를 삭제. Return시에 삭제되는 element에 연결된 데이터의 포인터가 data에 저장된다.  
  3. 순서  
    [1] 삭제할 element의 data 보관  
    [2] element의 next 지정  
    [3] 삭제 element의 메모리 해제
#### 1) 중간에 데이터를 삭제할 때  
![removal](https://user-images.githubusercontent.com/41607872/82539931-388fe280-9b89-11ea-9844-487dee998806.jpg)  
    
#### code  

```c

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

```  
### 3-4. - 리스트에 있는 모든데이터 삭제함수: list_destroy(List *list)  
- 구현
  1. return 없음  
  2. struct List에 함수포인터 즉,void(*destroy)(void* data)에 data을 제거할수 있는 함수를 만들어야함(본인이 만든 data구조에 따라서).  
  3. list_init(List* list, void(*destroy)(void* data)) 처음 초기화 할때 매개변수로 함수포인터을 설정한다.  
#### code  

```c  
void list_destroy(List* list)
{
	void* data;

	while (list->size > 0)
	{
		if (list_rem_next(list, NULL, &data) == 0 && list->destroy != NULL)
			list->destroy(data);
	}
}

void my_free(void* data) // data 제거함수
{
	free(data);

	return;
}  
```  
#### 저장된 데이터를 화면에 출력:  display_list(List* list)함수 - 코드파일 참조
#### 오름차순 데이터 넣기: list_sorted_insert(List* list, device* dev_data) - 코드파일 참조
#### 오름차순으로 데이터 정렬: list_sorted(List* list, device* tmp_data) - 코드파일 참조  
[강릉원주대 박래정교수님 수업 참조]  

