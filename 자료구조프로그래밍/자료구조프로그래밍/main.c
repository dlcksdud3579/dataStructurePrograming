// 9���� �ǽ� 2014105076 ������ ��Ʈ���� ����  

#include <stdio.h>
#include <stdlib.h>
#define MAX(x,y) ((x) > (y) ? (x) : (y))
typedef struct node  
{
	int bitnum;
	char bit[32];  //��Ʈ�� ��
	struct node* leftChild;
	struct node* rightChild;

}node;


node* search(node* t, char* k);  // �˻�
void insert(node **t, char* theElement);
int bit(char* a, int b);  // ����ġ�� �ε����� ����
void levelOrder(node* node, int level);  // ���� ����������ϴ� �Լ�

int height(node* t)  // Ʈ���� ���̸� ��ٸ��� 
{
	int left = 0, right = 0;

	if (t == NULL) 
		return 0;
	if (t->leftChild != NULL && t->bitnum < t->leftChild->bitnum) // �������� ���ϴ� ��
		left = height(t->leftChild);
	
	if (t->rightChild != NULL && t->bitnum < t->rightChild->bitnum) //����������  ���ϴ±�
		right = height(t->rightChild);


	return MAX(left, right) + 1;  // ���̰� ū���� ���� 
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


		h = height(root);   //Ʈ�� 2���� ��Ʈ ���

		for (int i = 1; i <= h; i++)  // ���Ͽ� ���������� ���
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

node* search(node* t, char* k)  // Ž��
{ 
	node *currentNode, *nextNode;  

	if (t == NULL)return NULL;
	nextNode = t->leftChild;
	currentNode = t;
	while (nextNode->bitnum > currentNode->bitnum)  // 
	{
		currentNode = nextNode;
		nextNode = (bit(k, nextNode->bitnum)) ? nextNode->rightChild : nextNode->leftChild;  // ���� ��Ʈ�� ��ġ�� Ʈ�� Ž��
	}
	return nextNode;
}

void insert(node **t, char* theElement)  // �� �߰� 
{
	node* current = NULL, *parent = NULL, *lastNode = NULL, *newNode =NULL;
	int i;

	if (!(*t)) {   // ��Ʈ�� ���ϰ�� 
		*t = malloc(sizeof(node));
		(*t)->bitnum = 0; 
		strcpy((*t)->bit,theElement);
		(*t)->leftChild = *t;
		(*t)->rightChild = NULL;
		return;
	}
	lastNode = search(*t, theElement);  
	if (strcmp(theElement, lastNode->bit) ==0 ) {  // �̹� �����Ѵ� ��Ʈ �ϰ�� 
		printf("�̹������ϴº���\n\n");
		return;
	}
	for (i = 1; bit(theElement, i) == bit(lastNode->bit, i); i++);  // 
	current = (*t)->leftChild; parent = *t;
	while (current->bitnum > parent->bitnum && current->bitnum < i)
	{
		parent = current;
		current = (bit(theElement, current->bitnum)) ? current->rightChild : current->leftChild;
	}  // ��ġ�� ã�´� 

	newNode = malloc(sizeof(node));  //  �ش� ��ġ�� ����带 �����Ѵ�.
	strcpy(newNode->bit, theElement);
	newNode->bitnum = i;
	newNode->leftChild = (bit(theElement, i)) ? current : newNode;
	newNode->rightChild = (bit(theElement, i)) ? newNode : current;
	if (current == parent->leftChild)
		parent->leftChild = newNode;
	else
		parent->rightChild = newNode;
}
int bit(char* a, int b)  // b��ġ�� ��Ʈ�� ���
{
	return a[b] - '0';
}
void levelOrder(node* node, int level)  // �������� �� ���
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
			levelOrder(node->leftChild, level - 1);   // �ڽĵ� Ž��
		else if(node->leftChild == NULL)
			levelOrder(node->leftChild, level - 1);
		
		if (node->rightChild != NULL && node->bitnum < node->rightChild->bitnum)
			levelOrder(node->rightChild, level - 1); // �ڽĵ� Ž��
		else if(node->rightChild == NULL)
			levelOrder(node->rightChild, level - 1);

	}
}
