#include <iostream>
#include <malloc.h>
#include <stdio.h>
#define MAX_VERTEX_NUM 20
#define MAX_ARCNUM_NUM 100
#define ERROR 0
#define OK 1
//ջ��Ԫ�صĸ���
#define SIZE 20
using namespace std;

//**********�����ڽӱ���Ϊͼ�Ĵ洢�ṹ**********
typedef struct ArcNode {  //�ߵĽ��ṹ
    int adjvex; //�ñ���ָ��Ķ���λ��
    int weight; //���ϵ�Ȩֵ
    struct  ArcNode* nextarc;//ָ����һ������ָ��
}ArcNode;

typedef struct {  //����Ľ��ṹ
    char vertex;    //������Ϣ
    ArcNode* firstarc; //ָ���һ�������ö���ı�
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {  //ͼ�Ľṹ���壨�ڽӱ�
    AdjList vertices;
    int vexnum, arcnum;  //ͼ�ĵ�ǰ�������ͱ���
}ALGraph;

void CreateGraph(ALGraph* G)
{
    int k, w, v, Kg; ArcNode* s;
    cout << "�����������Ŀ��AOE-���Ľ�����ͻ��(�ÿո����)��";
    cin >> G->vexnum >> G->arcnum;
    for (int i = 0; i < 20; i++)
    {
        G->vertices[i].firstarc = NULL;
    }
    for (int i = 0; i < G->vexnum; i++)
    {
        cout << "�����" << i + 1 << "��������ƣ�";
        cin >> G->vertices[i].vertex;
        G->vertices[i].firstarc = NULL;
    }
    //-------ǰ�巨
    for (k = 0; k < G->arcnum; k++)
    {
        cout << "�����" << k + 1 << "�������������(�ÿո�ָ�)��";
        cin >> w >> v;
        w -= 1; v -= 1;
        cout << "�û��Ȩֵ��";
        cin >> Kg;
        s = (ArcNode*)malloc(sizeof(ArcNode));
        s->adjvex = v; s->weight = Kg;
        s->nextarc = G->vertices[w].firstarc;
        G->vertices[w].firstarc = s;
    }
}

void DispGraph(ALGraph* G)
{
    cout << "ʹ���ڽӱ���Ϊͼ�Ĵ洢�ṹ��" << endl;
    ArcNode* p;
    for (int i = 0; i < G->arcnum; i++)
    {
        cout << G->vertices[i].vertex << "  -";
        p = G->vertices[i].firstarc;
        while (p != NULL)
        {
            cout << p->weight << "->  ";
            cout << p->adjvex + 1 << "  -";
            p = p->nextarc;
        }
        cout << "->  ^" << endl;
    }
}


//---------(����)ջ�Ļ�������------------------
struct SqStack {//(����)ջ������
    int sta[SIZE];
    int top;
};
void InitStack(SqStack* s)//ջ�ĳ�ʼ��
{
    for (int k = 0; k < SIZE; k++)
        s->sta[k] = -1;
    s->top = -1;  // 0
}
int InStack(SqStack* s, int data)//ѹջ
{
    if (s->top == SIZE - 1)
    {
        cout << "the Stack is full!" << endl;
        return 1;
    }
    (s->top)++;
    s->sta[s->top] = data;
    return 0;
}
int OutStack(SqStack* s)//��ջ
{
    int tmp;
    if (s->top < 0)
    {
        cout << "the Stack is empty!" << endl;
        return -1;
    }
    tmp = s->sta[s->top];
    (s->top)--;
    return tmp;
}
void destory(SqStack* s)//ջ��ɾ��
{
    s->top = -1;
    for (int k = 0; k < SIZE; k++)
        s->sta[k] = 0;
}

//----------����������֤�����޻�ͼ----------------
int ve[MAX_ARCNUM_NUM]; //���緢��ʱ��
int vl[MAX_ARCNUM_NUM]; //��ٷ���ʱ��

/*--���������---*/
int indegree[MAX_VERTEX_NUM];
int test1[MAX_VERTEX_NUM];
void FindInDegree(ALGraph* G)
{
    for (int k = 0; k < G->vexnum; k++)
        indegree[k] = test1[k] = 0;
    ArcNode* p;
    for (int i = 0; i < G->arcnum; i++)
    {
        p = G->vertices[i].firstarc;
        while (p != NULL)
        {
            indegree[p->adjvex]++;
            p = p->nextarc;
        }
    }
}
int TopologicalSort(ALGraph* G, SqStack* T)
{
    FindInDegree(G);
    SqStack* S; S = (SqStack*)malloc(sizeof(SqStack));
    InitStack(S);
    InitStack(T); int Cout = 0;
    for (int m = 0; m < G->arcnum; m++)
        ve[m] = 0;
    for (int i = 0; i < G->vexnum; i++)
        if (indegree[i] == 0)
        {
            InStack(S, i);
        }
    int i, k;
    ArcNode* p;
    while (S->top >= 0)    //ջ����
    {
        i = OutStack(S); InStack(T, i);/*test[i]=1;*/ Cout++;
        for (p = G->vertices[i].firstarc; p != NULL; p = p->nextarc)
        {
            k = p->adjvex;
            indegree[k]--;  //i�Ŷ���ÿһ���ڽӵ����-1
            if (indegree[k] == 0)
                InStack(S, k);
            if (ve[i] + p->weight > ve[k]) ve[k] = ve[i] + p->weight;
        }//for
    }//while
    if (Cout < G->vexnum)
        return ERROR; cout << endl;
    return 1;
}

//----------�ؼ�·��----------
int CriticalPath(ALGraph* G, SqStack* T)
{
    if (TopologicalSort(G, T) == 0) {
        cout << endl << "���������AOE-���д��ڻ��ṹ����" << endl;
        cout << "--****************************************--" << endl;
        return ERROR;//0
    }
    for (int n = 0; n < G->vexnum; n++)
        vl[n] = 1000; vl[G->vexnum - 1] = ve[G->vexnum - 1];
    ArcNode* p; int j, k, dut, ee, el;
    cout << endl << "------------------------------------------------------------------------------------";
    int b = 0, xx = T->top; cout << endl << "�������Ⱥ��ϵ���������У���" << endl;
    while (b <= xx)
    {
        cout << T->sta[b] + 1 << " "; b++;
    }
    cout << endl << "------------------------------------------------------------------------------------" << endl;
    while (T->top >= 0)
        for (j = OutStack(T), p = G->vertices[j].firstarc; p != NULL; p = p->nextarc)
        {
            k = p->adjvex; dut = p->weight;
            if (vl[k] - dut < vl[j]) vl[j] = vl[k] - dut;
        }//for
    printf("��� �յ� ���翪ʼʱ�� ��ٿ�ʼʱ�� Ȩֵ   ��ע\n");
    int sum = 0, c = 0;
    for (j = 0; j < G->vexnum; ++j)
        for (p = G->vertices[j].firstarc; p != NULL; p = p->nextarc) {
            k = p->adjvex; dut = p->weight;
            ee = ve[j]; el = vl[k] - dut;
            printf("%2d %4d %8d %12d %8d     ", j + 1, k + 1, ee, el, dut);
            if (ee == el)
            {
                cout << "�ؼ����";
                cout << "<" << j + 1 << " ," << k + 1 << " >  �û��Ҫʱ��=" << p->weight;

                if (test1[j] == 0 && c == 0 && test1[k] == 0)
                {
                    sum += dut; c++; cout << " *������ʱ��";
                    test1[j] = 2; test1[k] = 1;
                }
                if (test1[j] == 1)
                {
                    sum += dut; cout << " *������ʱ��";
                    test1[j] = 2; test1[k] = 1;
                }
            }
            cout << endl;
        }
    cout << "----------------------------------------------" << endl;
    cout << "��Ŀ���������ʱ��Ϊ��" << sum << "����λʱ�䣩" << endl;
    cout << "----------------------------------------------" << endl << endl;
    return 0;
}
int main()
{
    ALGraph* G = new ALGraph;
    cout << "***********���㹤����������Ŀ���������ʱ��***********" << endl << endl;
    CreateGraph(G);
    SqStack* T;
    T = (SqStack*)malloc(sizeof(SqStack));
    CriticalPath(G, T);
    return 0;
}
