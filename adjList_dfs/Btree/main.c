// 2014105076 ������ 8���� �ǽ� BƮ�� ���� 

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
	node *child[3];
	node *parent;
	int data[2];
	int n;
	bool leaf;
} node;

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
	freopen(argv[1],"r",stdin);
	freopen(argv[2],"w",stdout);

	scanf_s("%d", &nodeNum);

	for (int i = 0; i < nodeNum; i++)  // �Է��ϴ� �Լ� 
	{
		scanf_s("%d", &temp);
		avlInsert(&root, temp, &unbalanced);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}

void Insert(int a)
{
	int i, temp;
	node* x = root;

	if (x == NULL)
	{
		root = createNode(a,NULL);
		return;
	}
	while (x->leaf != true)  // ������� �� ��� ��ġ�� ����
	{
		
		if (a < x->data[0])
		{
			x = x->child[0];
		}
		else if (a < x->data[1])
		{
			x = x->child[1];
		}
		else if(a > x->data[1])
		{
			x = x->child[2];
		}
		else
		{
			printf_s("�̹� �����ϴ� Ű�Դϴ�.");
		}
	}
	if (x->n < 2)  // ���� ��忡 �ڸ��� ���� ���
	{
		x->data[1] = a;
		if (x->data[1] < x->data[0])
			swap(x->child[0], x->child[1]);
		return;
	}
	else  // ���� ��忡 �ڸ��� ���� ���
	{
		int insetKey = a;
		while (x->parent != NULL)
		{
			x->n = 1;
			if (insetKey < x->data[0])
			{
				swap(x->data[0], insetKey);
				x = x->parent;
			}
			else if (insetKey < x->data[1])
			{
				x = x->parent;
			}
			else if (insetKey > x->data[1])
			{
				swap(x->data[1], insetKey);
				x = x->parent;
			}
			else
			{
				printf_s("�̹� �����ϴ� Ű�Դϴ�.");
			}
		}



	}


}
node* createNode(int x,node* parent)
{
	node* temp = (node*)malloc(sizeof(node));
	temp->n = 1;
	temp->child[0] = NULL;
	temp->child[1] = NULL;
	temp->child[2] = NULL;

	temp->data[0] = x;
	temp->data[1] = 0;
	temp->leaf = true;
	temp->parent = parent;
	return temp;
}