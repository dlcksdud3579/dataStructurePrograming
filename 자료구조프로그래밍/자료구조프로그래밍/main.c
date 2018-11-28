// 9주차 실습 2014105076 이찬영 패트리샤 구현  

#include <stdio.h>
#include <stdlib.h>
#define MAX(x,y) ((x) > (y) ? (x) : (y))
typedef struct node  
{
	int bitnum;
	char bit[32];  //비트를 담
	struct node* leftChild;
	struct node* rightChild;

}node;


node* search(node* t, char* k);  // 검색
void insert(node **t, char* theElement);
int bit(char* a, int b);  // ㅠ위치의 인덱스를 리턴
void levelOrder(node* node, int level);  // 레벨 오더로출력하는 함수

int height(node* t)  // 트리의 높이를 기다리는 
{
	int left = 0, right = 0;

	if (t == NULL) 
		return 0;
	if (t->leftChild != NULL && t->bitnum < t->leftChild->bitnum) // 왼쪽으로 구하는 길
		left = height(t->leftChild);
	
	if (t->rightChild != NULL && t->bitnum < t->rightChild->bitnum) //오른쪽으로  구하는길
		right = height(t->rightChild);


	return MAX(left, right) + 1;  // 높이가 큰것을 선택 
}

int main(int argc,char** argv)
{
	node* root = NULL;
	int n,h;
	char temp[32] = { 0, };
	int tempInt = 0;

	FILE f1, f2;
	freopen_s(&f1, argv[1], "r", stdin);
	freopen_s(&f2, argv[2], "w", stdout);
	scanf_s("%d", &n);

	for (int i = 0; i < n; i++)
	{
		scanf_s("%s",temp,32);
		insert(&root, temp);


		h = height(root);   //트리 2번의 루트 노드

		for (int i = 1; i <= h; i++)  // 파일에 레벨오더로 출력
		{
			levelOrder(root, i);
			printf("\n");
		}
		printf("\n");
	}


	fclose(stdin);
	fclose(stdout);
	return 0;
}

node* search(node* t, char* k)  // 탐색
{ 
	node *currentNode, *nextNode;  

	if (t == NULL)return NULL;
	nextNode = t->leftChild;
	currentNode = t;
	while (nextNode->bitnum > currentNode->bitnum)  // 
	{
		currentNode = nextNode;
		nextNode = (bit(k, nextNode->bitnum)) ? nextNode->rightChild : nextNode->leftChild;  // 다음 비트로 서치로 트리 탐색
	}
	return nextNode;
}

void insert(node **t, char* theElement)  // 값 추가 
{
	node* current = NULL, *parent = NULL, *lastNode = NULL, *newNode =NULL;
	int i;

	if (!(*t)) {   // 루트가 널일경우 
		*t = malloc(sizeof(node));
		(*t)->bitnum = 0; 
		strcpy((*t)->bit,theElement);
		(*t)->leftChild = *t;
		(*t)->rightChild = NULL;
		return;
	}
	lastNode = search(*t, theElement);  
	if (strcmp(theElement, lastNode->bit) ==0 ) {  // 이미 존재한는 비트 일경우 
		printf("이미존재하는변수\n\n");
		return;
	}
	for (i = 1; bit(theElement, i) == bit(lastNode->bit, i); i++);  // 
	current = (*t)->leftChild; parent = *t;
	while (current->bitnum > parent->bitnum && current->bitnum < i)
	{
		parent = current;
		current = (bit(theElement, current->bitnum)) ? current->rightChild : current->leftChild;
	}  // 위치를 찾는다 

	newNode = malloc(sizeof(node));  //  해당 위치에 새노드를 삽입한다.
	strcpy(newNode->bit, theElement);
	newNode->bitnum = i;
	newNode->leftChild = (bit(theElement, i)) ? current : newNode;
	newNode->rightChild = (bit(theElement, i)) ? newNode : current;
	if (current == parent->leftChild)
		parent->leftChild = newNode;
	else
		parent->rightChild = newNode;
}
int bit(char* a, int b)  // b위치에 비트를 출력
{
	return a[b] - '0';
}
void levelOrder(node* node, int level)  // 레벨오더 로 출력
{
	if (node == NULL &&level != 1)
	{
		return;
	}
	if (level == 1)
	{
		if(node  == NULL)
			printf(" null");
		else
		{
			printf("%s", node->bit);
		}
	}
	
	if (level > 1)
	{
		if(node->leftChild != NULL && node->bitnum < node->leftChild->bitnum)
			levelOrder(node->leftChild, level - 1);   // 자식들 탐색
		else if(node->leftChild == NULL)
			levelOrder(node->leftChild, level - 1);
		
		if (node->rightChild != NULL && node->bitnum < node->rightChild->bitnum)
			levelOrder(node->rightChild, level - 1); // 자식들 탐색
		else if(node->rightChild == NULL)
			levelOrder(node->rightChild, level - 1);

	}
}
