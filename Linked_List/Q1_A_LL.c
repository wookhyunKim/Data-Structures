//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode; // You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList; // You should not change the definition of LinkedList

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;

	// Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			printf("size ---- %d\n", ll.size);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			// removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int insertSortedLL(LinkedList *ll, int item)
{
	// /* add your code here */

	// int index = 0;
	// int rs;

	// // LL에 노드가 아무것도 없을 때
	// if (ll->head == NULL)
	// {
	// 	rs = insertNode(ll, index, item);
	// 	return index + 1;
	// }
	// else
	// { // LL에 노드가 하나이상 있을 때
	// 	ListNode *cur; // 노드 하나를 불러오기
	// 	cur = ll->head; // 리스트의 헤드의 주소를 cur 포인터 변수에 넣기
	// 	while (index < ll->size) // index가 리스트의 크기보다 작을 때 작동
	// 	{
	// 		if (cur->item == item)
	// 		{
	// 			// 중복된 값이 발견된 경우 - 삽입하지 않음
	// 			return -1; // 실패를 나타내기 위해 -1 반환
	// 		}
	// 		if (cur->item < item)
	// 		{ // cur 값은 노드의 값, item 은 입력받은 값 /. 입력받은 값이 더 클때 패스 --> index +1을 의미 또한 next 노드로 이동하여 반복문비교
	// 			index++;
	// 			cur = cur->next;
	// 			continue;
	// 		}
	// 		else
	// 		{
	// 			break;
	// 		}
	// 	}

	// 	rs = insertNode(ll, index, item);
	// 	rs = index;
	// 	return rs + 1;
	// }



	ListNode *newNode = malloc(sizeof(ListNode));
	// 링크드 리스트가 없을때
	if (ll == NULL) return -1;  // == 위에 하는 게 좋을 듯 ?

	newNode->item = item;   // ==  이거랑 말록 노드 할당한거랑 붙이는 게 좋을듯 ?
	newNode->next = NULL;

	// 링크드 리스트가 비었을때  // == 주석 순서를 이해하기 쉽게 바꾸는 것도 낫배드 ? 왜냐하면 이 주석 다음 if 가 나오면 다음 나오는 것이 이해가 되는데 갑자기 cur 선언함
	int index = 0;
	ListNode* cur = ll->head;
	if (ll->head == NULL){
		ll->head = newNode;
		ll->size = 1;
		return 0;
	}

	if (item < cur->item){
		newNode->next = cur;
		ll->head = newNode;
		ll->size++;
		return 0;
	}
	// 링크드 리스트 첫번째 값과 입력 데이터를 비교했을때 입력값이 더 작다면 맨 앞에

	while (cur->next != NULL && cur->next->item < item)
	{
		cur = cur->next;
		index++;
	}

	if (cur->next != NULL && cur->next->item == item){
		free(newNode);
		return -1;
	}

	newNode->next = cur->next;
	cur->next = newNode;
	ll->size++;

	return index + 1;
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll)
{

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL)
	{
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}

ListNode *findNode(LinkedList *ll, int index)
{

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0)
	{
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value)
{

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0)
	{
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}

	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL)
	{
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}

int removeNode(LinkedList *ll, int index)
{

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0)
	{
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL)
	{

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
