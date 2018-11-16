// 2014105076 ������ 7���� �ǽ� AVL Ʈ�� ���� 

#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define MAX(x,y) ((x) > (y) ? (x) : (y))

typedef struct node
{
	node *rightChild;
	node *leftChild;
	int bf;
	int data;
} node;
void levelOrder(FILE*fp, node* node, int level);  //  ���� ������ ����ϴ� �Լ� 
void avlInsert(node** parent,int x, int *unbalanced); // AVL �� ���缭 �μ�Ʈ�ϴ� �Լ� 
void rightRotation(node **parent, int *unbalanced); //  RR �� RL �����̼� �ϴ� �Լ� 
void leftRotation(node **parent, int *unbalanced);  // LL �� LR �����̼� �ϴ� �Լ� 
int h(node* node);  // ��Ʈ ���̸� ���ϴ� �Լ� 
node* root = NULL; // ��Ʈ 


int main(int argc,char* argv[])
{
	FILE *fp,*fp2;  // �Է�, ��� ���� 
	int nodeNum;
	int temp = 0;
	int unbalanced = 0;
	fopen_s(&fp, argv[1], "r");  
	fopen_s(&fp2, argv[2], "w");
	
	fscanf_s(fp,"%d", &nodeNum);

	for (int i = 0; i < nodeNum; i++)  // �Է��ϴ� �Լ� 
	{
		fscanf_s(fp, "%d", &temp);
		avlInsert(&root,temp, &unbalanced); 
		int height = h(root);  // 1�� Ʈ���� ����
		for (int i = 0; i < height; i++)  // ���Ͽ� ���������� ���
		{
			levelOrder(fp2, root, i);  // �Է� 
			fprintf(fp2, "\n");

		}
		fprintf(fp2, "\n");  
	}

	

	return 0;
}


void avlInsert(node** parent, int x, int *unbalanced)  
{
	if (!*parent) { /*insert element into null tree */
		*unbalanced = true;
		(*parent) = (node*)malloc(sizeof(node));
		(*parent)->leftChild = NULL;
		(*parent)->rightChild = NULL;
		(*parent)->bf = 0; 
		(*parent)->data = x;
	}
	else if (x < (*parent)->data) {  // ����Ű ���� ��� 
		avlInsert(&(*parent)->leftChild, x, unbalanced);
		if (*unbalanced)
			/* left branch has grown higher */
			switch ((*parent)->bf) {
			case -1: (*parent)->bf = 0;
				*unbalanced = FALSE; break;
			case 0: (*parent)->bf = 1; break;
			case 1: leftRotation(parent, unbalanced);
			}
	}
	else if (x > (*parent)->data) { // ��� ��Ű�� Ŭ��� 
		avlInsert(&(*parent)->rightChild, x, unbalanced);
		if (*unbalanced)
			/*right branch has grown higher */
			switch ((*parent)->bf) {
			case 1: (*parent)->bf = 0;  
				*unbalanced = FALSE; break;
			case 0: (*parent)->bf = -1; break;
			case -1: rightRotation(parent, unbalanced);
			}
	}
	else {  // �̹� �ִ� Ű�ϰ�� 
		*unbalanced = FALSE;
		printf(" The key is already in the tree");
	}

}

void leftRotation(node **parent, int *unbalanced)
{
	node* grandChild = NULL,*child = NULL;
	child = (*parent)->leftChild;
	if (child->bf == 1) {
		/* LL rotation */  
		(*parent)->leftChild = child->rightChild;
		child->rightChild = *parent;
		(*parent)->bf = 0;
		(*parent) = child;
	}
	else {
		/*LR rotation */
		grandChild = child->rightChild;
		child->rightChild = grandChild->leftChild;
		grandChild->leftChild = child;
		(*parent)->leftChild = grandChild->rightChild;

		switch (grandChild->bf) {
		case 1: (*parent)->bf = -1;
			child->bf = 0;  break;
		case 0: (*parent)->bf = child->bf = 0;
			break;
		case -1: (*parent)->bf = 0;
			child->bf = 1;
		}
		grandChild->rightChild = *parent;
		*parent = grandChild;
	}
	
	(*parent)->bf = 0;
	*unbalanced = FALSE;
}

void rightRotation(node **parent, int *unbalanced)
{
	node* grandChild = NULL, *child = NULL;
	child = (*parent)->rightChild;
	if (child->bf == -1) {
		/* RR rotation */
		(*parent)->rightChild = child->leftChild;
		child->leftChild = *parent;
		(*parent)->bf = 0;
		(*parent) = child;
	}
	else {
		/* RL rotation */
		grandChild = child->leftChild;
		child->leftChild = grandChild->rightChild;
		grandChild->rightChild = child;
		(*parent)->rightChild = grandChild->leftChild;

		switch (grandChild->bf) {
		case 1: (*parent)->bf = 0;
			child->bf = -1;  break;
		case 0: (*parent)->bf = child->bf = 0;
			break;
		case -1: (*parent)->bf = 1;
			child->bf = 0;
		}
		grandChild->leftChild = *parent;
		*parent = grandChild;
		
	}
	(*parent)->bf = 0;
	*unbalanced = FALSE;
}

void levelOrder(FILE*fp, node* node, int level)
{
	if (node == NULL)
	{
		fprintf(fp, "- ");
		return;
	}
	if (level == 0)
		fprintf(fp, "%d ", node->data);  // Ű ���
	else if (level > 0)
	{
		levelOrder(fp, node->leftChild, level - 1);   // �ڽĵ� Ž��
		levelOrder(fp, node->rightChild, level - 1);
	}
}

int h(node* node)  // Ʈ���� ������ ����ϴ� �Լ�
{
	if (node == NULL)
		return 0;
	return MAX(h(node->leftChild), h(node->rightChild)) + 1;  // ���̰� ū���� ����
}