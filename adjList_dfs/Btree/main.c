// 2014105076 ������ 8���� �ǽ� BƮ�� ���� 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FALSE 0
#define TRUE 1
#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define SWAP(a, b, type) do { \
    type temp; \
    temp = a;  \
    a = b;     \
    b = temp;  \
} while (0)


typedef struct node
{
	struct node left;
	struct node right;
	struct node bro;
	struct node parent;
	int data;
}node;

void Insert(int x); //  �μ�Ʈ�ϴ� �Լ�
node* createNode(int x, node* parent);
node* root = NULL; // ��Ʈ 
int m = 3;


int main(int argc, char* argv[])
{
	FILE *fp, *fp2;  // �Է�, ��� ���� 
	int nodeNum;
	int temp = 0;
	int unbalanced = 0;
	freopen(argv[1],"r", stdin);
	freopen(argv[2],"w",stdout);

	scanf("%d", &nodeNum);

	for (int i = 0; i < nodeNum; i++)  // �Է��ϴ� �Լ� 
	{
		scanf("%d", &temp);
		Insert(temp);

	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}

void Insert(int a)
{
	int i, temp;
	node* x = root;

	if (x == NULL)  // ��Ʈ�� 0�ΰ�� 
	{
		root = createNode(a,NULL);
		return;
	}
	while (x->left != NULL)  // ������� �� ��� ��ġ�� ����
	{
		if (a < x->data)
		{
			x = x->left;
		}
		else if (a < x->bro->data)
		{
			x = x->right;
		}
		else if(a > x->bro->data)
		{
			x = x->bro->right;
		}
		else
		{
			printf_s("�̹� �����ϴ� Ű�Դϴ�.");
		}
	}
	if (x->bro == NULL)  // ���� ������ �ڸ��� ���� ���
	{
		x->bro =createNode(a,NULL);
		if (x->data < x->bro->data)
			SWAP(x->data, x->bro->data);
		return;
	}
	else
	{
		node *tempNode = createNode(a, NULL);
		node *nextParent = NULL;
		while (x->parent != NULL)
		{
			if (tempNode->data < x->data)
			{
				SWAP(x->data, tempNode->data);
				tempNode->right = x;
				tempNode->right = x->bro;
				nextParent = x->parent;
				x->parent = tempNode->parent;
			}
			else if (tempNode->data < x->bro->data)
			{
				
			}
			else if (tempNode->data > x->bro->data)
			{
				SWAP(x->bro->data, tempNode->data);
				
			}
			else
			{
				printf_s("�̹� �����ϴ� Ű�Դϴ�.");
				return;
			}
			if (x->n < 2)
			{
				x->data[1] = insetKey;
				if (x->data[1] < x->data[0])
					SWAP(x->child[0], x->child[1]);
				x->n = 2;
				return;
			}
			x = x->parent;
		}


		node* newRoot = createNode(insetKey,NULL);
		node* rootrightChild = createNode(root->data[1], newRoot);

		root->data[1] = 0;
		root->n = 0;
		root->parent = newRoot;


		

	}
}

node* createNode(int x,node* parent)
{
	node* temp = (node*)malloc(sizeof(node));
	temp->left = NULL;
	temp->right = NULL;
	temp->bro = NULL;
	temp->data = x;
	temp->parent = parent;
	return temp;
}