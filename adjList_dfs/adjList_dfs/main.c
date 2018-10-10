//2014105076 이찬영 4주차 실습
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct
{
	char num;
	struct node* next;
} node;

node * hnode;

char stack[26] = {0,};  // 스텍으로 사용할 배열
int top=0; // 스텍의 인덱스 
int* color[26] = {0,}; // 들린곳인지 아닌지 확인
int cnt = 0; // 패스의 겟수를 세는  카운터


void push(char _input);  // 스텍에 푸시 
char pop(); //스텍의 팝
void insertNode(int headNode, node * inputNode);  //adj 리스트에  새노드를 추가 하는 함수 
node * makeNode(char _node); // 노드 를 만드는함수
int serchhead( int nodeNum, char head); // 해당문자열의 adj리스트 열 번호를 찾아 주는함수
void printNode(int nodeNum); // adj 리스트를 화면에 출력
void dfs(FILE *f,int nodeNum, char start, char end);  // dfs를 사용해서 모든 simple path를 찾는 함수


int main(int args, char* argv[])
{
	FILE * f;  // 입력용 파일 
	FILE * of;  // 출력용 파일
	int nodeNum, edgeNum;  // 노드의 갯수와 엣지의 갯수
	char startNode, endNode;  //시작 노드와 끝 노드
	char temp1, temp2;   // 입력값을 잠시 저장할 공간

	f = fopen(argv[1], "r"); 
	of = fopen(argv[2], "w");

	fscanf(f,"%d %d %c %c", &nodeNum, &edgeNum, &startNode, &endNode);   // 파일에서 변수들을 입력 받는다.

	hnode = malloc(sizeof(node)*nodeNum);  //adj 노드의 열을 노드의 갯수만큼 동적 할당
	for (int i = 0; i < nodeNum; i++) //adj 노드의 열을 초기화
	{
		hnode[i].next = NULL;
		hnode[i].num = '0';
	}



	for(int i =0;i<edgeNum;i++)  // 엣지의 갯수만큼 파일을 읽어서 adj리스트에 노드를 추가합니다.
	{
		int headNum;
		fscanf(f,"\n%c %c", &temp1, &temp2);
		headNum = serchhead(nodeNum,temp1);  // temp1에 해당하는 리스트 열번호를 리턴; 
		
		if (headNum == -1)
		{
			printf("error");
			exit(1);
		}
		insertNode(headNum,makeNode(temp2)); // adj 리스트에 노드를 추가 합니다.
	}

	
	printNode(nodeNum);  
	
	
	dfs(of,nodeNum, startNode,endNode);  // 심플패스를 찾습니다.
	
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
		if (hnode[i].num == head) // 해당 열을 찾으면 열번호를 리턴한다.
		{
			return i;
		}
	}

	for (int i = 0; i < nodeNum; i++)  // 존재하지 않을경우 빈 열번호를 해당 노드의 열로 만들어준다
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
	int currentNode = serchhead(nodeNum, start);  //현재 노드의 위치
	int nextNode;  // 다음 노드의 위치

	color[currentNode] = 1;  // 현재위치를 들렸다고 표시
	push(start); // 시작위치를 스텍에 푸쉬 한다.

	if(start == end) // 리커시브 함수 탈출 조건  현재위치가 끝이면 스텍을 pop하고 리턴
	{
		
		for (int i = 0; i < top; i++)
		{
			printf("%c", stack[i]);  // 스텍을 전체 출력
			fprintf(f, "%c",stack[i]);
			if (i != top - 1)
			{
				printf("->");
				fprintf(f, "->");
				
			}
		}
		cnt++;  // 패스 카운터 증가
		printf("\n");
		fprintf(f, "\n");
		pop();
		return;
	}


	currentNode = serchhead(nodeNum, start);  // 현재 노드 
	node* head = hnode[currentNode].next; //노드에 인접해있는 노드를 찾는다.
	while (head != NULL)			      //노드에 인접해있는 노드를 찾는다.
	{
		nextNode = serchhead(nodeNum, head->num); 

		if (color[nextNode] == 0)
		{
			dfs(f,nodeNum, hnode[nextNode].num, end); // 리커시브로 dfs를 찾습니다. 
			color[nextNode] = 0; //탈출조건으로 돌아올경우 해당 노드를 방문 하지 않을걸로 바꾼다.
		}

		head = head->next;
	}

	pop();  // 탈출시 pop
}

