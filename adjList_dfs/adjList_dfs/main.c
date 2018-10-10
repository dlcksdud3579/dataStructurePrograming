//2014105076 ������ 4���� �ǽ�
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct
{
	char num;
	struct node* next;
} node;

node * hnode;

char stack[26] = {0,};  // �������� ����� �迭
int top=0; // ������ �ε��� 
int* color[26] = {0,}; // �鸰������ �ƴ��� Ȯ��
int cnt = 0; // �н��� �ټ��� ����  ī����


void push(char _input);  // ���ؿ� Ǫ�� 
char pop(); //������ ��
void insertNode(int headNode, node * inputNode);  //adj ����Ʈ��  ����带 �߰� �ϴ� �Լ� 
node * makeNode(char _node); // ��� �� ������Լ�
int serchhead( int nodeNum, char head); // �ش繮�ڿ��� adj����Ʈ �� ��ȣ�� ã�� �ִ��Լ�
void printNode(int nodeNum); // adj ����Ʈ�� ȭ�鿡 ���
void dfs(FILE *f,int nodeNum, char start, char end);  // dfs�� ����ؼ� ��� simple path�� ã�� �Լ�


int main(int args, char* argv[])
{
	FILE * f;  // �Է¿� ���� 
	FILE * of;  // ��¿� ����
	int nodeNum, edgeNum;  // ����� ������ ������ ����
	char startNode, endNode;  //���� ���� �� ���
	char temp1, temp2;   // �Է°��� ��� ������ ����

	f = fopen(argv[1], "r"); 
	of = fopen(argv[2], "w");

	fscanf(f,"%d %d %c %c", &nodeNum, &edgeNum, &startNode, &endNode);   // ���Ͽ��� �������� �Է� �޴´�.

	hnode = malloc(sizeof(node)*nodeNum);  //adj ����� ���� ����� ������ŭ ���� �Ҵ�
	for (int i = 0; i < nodeNum; i++) //adj ����� ���� �ʱ�ȭ
	{
		hnode[i].next = NULL;
		hnode[i].num = '0';
	}



	for(int i =0;i<edgeNum;i++)  // ������ ������ŭ ������ �о adj����Ʈ�� ��带 �߰��մϴ�.
	{
		int headNum;
		fscanf(f,"\n%c %c", &temp1, &temp2);
		headNum = serchhead(nodeNum,temp1);  // temp1�� �ش��ϴ� ����Ʈ ����ȣ�� ����; 
		
		if (headNum == -1)
		{
			printf("error");
			exit(1);
		}
		insertNode(headNum,makeNode(temp2)); // adj ����Ʈ�� ��带 �߰� �մϴ�.
	}

	
	printNode(nodeNum);  
	
	
	dfs(of,nodeNum, startNode,endNode);  // �����н��� ã���ϴ�.
	
	printf("%d", cnt);
	fprintf(of, "%d", cnt);
	fclose(f);
	fclose(of);
	return 0;

}

void push(char _input)
{
	if (top >= 99)
		exit(1);
	stack[top] = _input;
	top++;
}

char pop()
{
	if (top <= 0)
		exit(1);
	stack[top-1] = 0;
	return stack[--top];
}


void insertNode(int headNode,node * inputNode)
{
	if (hnode[headNode].next == NULL)
	{
		hnode[headNode].next = inputNode;
	}
	else
	{
		node * head = hnode[headNode].next;
		while (head->next != NULL)
		{
			head = head->next;
		}
		head->next = inputNode;
	}
}

node * makeNode(char _node)
{
	node * resultNode = (node*)malloc(sizeof(node));

	resultNode->next = NULL;
	resultNode->num = _node;
	return resultNode;
}

int serchhead( int nodeNum, char head)
{
	for (int i = 0; i < nodeNum; i++)
	{
		if (hnode[i].num == head) // �ش� ���� ã���� ����ȣ�� �����Ѵ�.
		{
			return i;
		}
	}

	for (int i = 0; i < nodeNum; i++)  // �������� ������� �� ����ȣ�� �ش� ����� ���� ������ش�
	{ 
		if (hnode[i].num == '0')
		{
			hnode[i].num = head;
			hnode[i].next = NULL;
			
			return i;
		}
	}
	return -1;
}

void printNode(int nodeNum)
{
	for (int i = 0; i < nodeNum; i++)
	{
		node * head = hnode[i].next;
		printf("%c: ", hnode[i].num);

		while (head != NULL)
		{
			printf("%c ", head->num);
			head = head->next;
		}
		printf("\n");
	}
}


void dfs(FILE *f,int nodeNum, char start, char end)
{
	int currentNode = serchhead(nodeNum, start);  //���� ����� ��ġ
	int nextNode;  // ���� ����� ��ġ

	color[currentNode] = 1;  // ������ġ�� ��ȴٰ� ǥ��
	push(start); // ������ġ�� ���ؿ� Ǫ�� �Ѵ�.

	if(start == end) // ��Ŀ�ú� �Լ� Ż�� ����  ������ġ�� ���̸� ������ pop�ϰ� ����
	{
		
		for (int i = 0; i < top; i++)
		{
			printf("%c", stack[i]);  // ������ ��ü ���
			fprintf(f, "%c",stack[i]);
			if (i != top - 1)
			{
				printf("->");
				fprintf(f, "->");
				
			}
		}
		cnt++;  // �н� ī���� ����
		printf("\n");
		fprintf(f, "\n");
		pop();
		return;
	}


	currentNode = serchhead(nodeNum, start);  // ���� ��� 
	node* head = hnode[currentNode].next; //��忡 �������ִ� ��带 ã�´�.
	while (head != NULL)			      //��忡 �������ִ� ��带 ã�´�.
	{
		nextNode = serchhead(nodeNum, head->num); 

		if (color[nextNode] == 0)
		{
			dfs(f,nodeNum, hnode[nextNode].num, end); // ��Ŀ�ú�� dfs�� ã���ϴ�. 
			color[nextNode] = 0; //Ż���������� ���ƿð�� �ش� ��带 �湮 ���� �����ɷ� �ٲ۴�.
		}

		head = head->next;
	}

	pop();  // Ż��� pop
}

