#include<stdio.h> //표준 입출력 라이브러리, printf, scanf등의 입/출력 함수를 사용할 수 있음.
#include<malloc.h> //동적 메모리 할당 함수 malloc, calloc, realloc, free등을 제공하는 헤더파일
 
#define NULL (0) //NULL을 0으로 지정, 주로 포인터가 아무것도 가리키지 않을 때 사용하는 값값

//------------ListNode 구조체--------------------//

typedef struct ListNode //struct ListNode 구조체 정의, typedef를 사용하여 간단하게 ListNode로 사용 가능
{
    int data; //정수형 변수 data선언, 노드가 저장할 실제 데이터를 보관
    struct ListNode* prev; //변수 prev 포인터 선언
    struct ListNode* next; //변수 next 포인터 선언
}ListNode; //앞으로 사용할 별명을 적는 자리, 이 구조체는 이제 ListNode로 사용할 수 있음

//------------ListNode 구조체--------------------//

ListNode* list_create(int _data) //list_create라는 함수 정의, (int _data)정수형 매개변수
{
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    //malloc(sizeof(ListNode)): ListNode 하나 크기(sizeof)의 메모리를 동적으로 할당함(malloc). heap에 할당됨.
    //(ListNode*): malloc 함수가 반환하는 void* 포인터를 ListNode* 포인터형으로 형 변환함. node변수 ListNode가리키는 포인터 가능
    //ListNode* node = : 동적 할당된 메모리의 주소를 저장할 node라는 포인터 변수를 선언하면서, node는 ListNode타입의 데이터를 가리키는 포인터임을 의미미
 
    node->prev = NULL; //NULL로 초기화하여 현재 노드가 다른 노드와 연결 되지 않았음을 나타냄
    node->next = NULL; 
 
    node->data = _data; //함수의 매개변수로 전달된 _data값을 노드의 data멤버의 저장, 노드에는 사용자가 입력한 정수값이 담기게 됨
 
    return node; //동적 메모리로 생성된 노드의 주소를 반환함 
}
 
ListNode* list_insert(ListNode* _head, ListNode* new_node) //_head 현재 노드, new_node 새로 삽입할 노드
{
    ListNode* NEXT = _head->next; //기존 _head노드가 가리키고 있던 next의 주소(임시로 A노드라고 명시)를 로컬변수 NEXT에 저장 
 
    _head->next = new_node; //_head의 next포인터를 새 노드(next_node)로 바꿈, _head가 새 노드를 가리킴
    new_node->next = NEXT; //새로운 노드의 next 포인터는 기존에 _head에 저장 되있던 NEXT값(A노드)으로 설정
    new_node->prev = _head;//새로운 노드의 prev 포인터는 _head가 되어 _head노드와 new_node가 서로 연결
     
    if (NEXT != NULL) //기존 _head의 원래 노드(A노드)가 존재한다면면
    {
        NEXT->prev = new_node;//A노드의 prev포인터를 new_node로 바꿈
    }
 
    return new_node; //새로운 노드를 반환하면서 끝
}
 
int list_erase(ListNode* head, int _data)//정수형 함수를 선언, 정수형 값을 반환
{
    ListNode* it = head->next;//head의 next포인터가 가리키는 주소를 it이라는 로컬 변수에 저장
    int ret = 0; //정수형 ret의 값을 0으로 초기화
 
    while (it != NULL) //head의 next 포인터가 가리키는 주소가 존재한다면
    {
        if (it->data == _data)
        {
            ListNode* prev = it->prev;
            ListNode* next = it->next;
            ListNode* tmp = it;
            it = it->next;
 
            prev->next = next;
            if (next != NULL)
            {
                next->prev = prev;
            }
             
            free(tmp);
            ret++;
        }
        else
        {
            it = it->next;
        }
    }
 
    return ret;
}
 
int main(int argc, char* argv[])
{
    int T, N;
    setbuf(stdout, NULL);
 
    scanf("%d", &T);
 
    for (int test_case = 1; test_case <= T; test_case++)
    {
        scanf("%d", &N);
 
        ListNode* head = list_create(NULL);
        printf("#%d", test_case);
        for (int i = 0; i < N; i++)
        {
            int mode, data;
            scanf("%d%d", &mode, &data);
 
            if (mode == 1)
            {
                ListNode* node = list_create(data);
 
                list_insert(head, node);
            }
            else if (mode == 2)
            {
                printf(" %d", list_erase(head, data));
            }
        }
 
        while (head != NULL)
        {
            ListNode* tmp = head;
            head = head->next;
            free(tmp);
        }
        printf("\n");
    }
    return 0;
}