#include <iostream>
#include <malloc.h>
#include <stdio.h>
#define MAX_VERTEX_NUM 20
#define MAX_ARCNUM_NUM 100
#define ERROR 0
#define OK 1
//栈里元素的个数
#define SIZE 20
using namespace std;

//**********创建邻接表作为图的存储结构**********
typedef struct ArcNode {  //边的结点结构
    int adjvex; //该边所指向的顶点位置
    int weight; //边上的权值
    struct  ArcNode* nextarc;//指向下一条弧的指针
}ArcNode;

typedef struct {  //顶点的结点结构
    char vertex;    //顶点信息
    ArcNode* firstarc; //指向第一条依附该顶点的边
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {  //图的结构定义（邻接表）
    AdjList vertices;
    int vexnum, arcnum;  //图的当前顶点数和边数
}ALGraph;

void CreateGraph(ALGraph* G)
{
    int k, w, v, Kg; ArcNode* s;
    cout << "请输入这个项目中AOE-网的结点数和活动数(用空格隔开)：";
    cin >> G->vexnum >> G->arcnum;
    for (int i = 0; i < 20; i++)
    {
        G->vertices[i].firstarc = NULL;
    }
    for (int i = 0; i < G->vexnum; i++)
    {
        cout << "输入第" << i + 1 << "个结点名称：";
        cin >> G->vertices[i].vertex;
        G->vertices[i].firstarc = NULL;
    }
    //-------前插法
    for (k = 0; k < G->arcnum; k++)
    {
        cout << "输入第" << k + 1 << "个活动的两个顶点(用空格分隔)：";
        cin >> w >> v;
        w -= 1; v -= 1;
        cout << "该活动的权值：";
        cin >> Kg;
        s = (ArcNode*)malloc(sizeof(ArcNode));
        s->adjvex = v; s->weight = Kg;
        s->nextarc = G->vertices[w].firstarc;
        G->vertices[w].firstarc = s;
    }
}

void DispGraph(ALGraph* G)
{
    cout << "使用邻接表作为图的存储结构：" << endl;
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


//---------(数组)栈的基本操作------------------
struct SqStack {//(数组)栈的声明
    int sta[SIZE];
    int top;
};
void InitStack(SqStack* s)//栈的初始化
{
    for (int k = 0; k < SIZE; k++)
        s->sta[k] = -1;
    s->top = -1;  // 0
}
int InStack(SqStack* s, int data)//压栈
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
int OutStack(SqStack* s)//出栈
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
void destory(SqStack* s)//栈的删除
{
    s->top = -1;
    for (int k = 0; k < SIZE; k++)
        s->sta[k] = 0;
}

//----------拓扑排序验证有向无环图----------------
int ve[MAX_ARCNUM_NUM]; //最早发生时间
int vl[MAX_ARCNUM_NUM]; //最迟发生时间

/*--各顶点入度---*/
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
    while (S->top >= 0)    //栈不空
    {
        i = OutStack(S); InStack(T, i);/*test[i]=1;*/ Cout++;
        for (p = G->vertices[i].firstarc; p != NULL; p = p->nextarc)
        {
            k = p->adjvex;
            indegree[k]--;  //i号顶点每一个邻接点入度-1
            if (indegree[k] == 0)
                InStack(S, k);
            if (ve[i] + p->weight > ve[k]) ve[k] = ve[i] + p->weight;
        }//for
    }//while
    if (Cout < G->vexnum)
        return ERROR; cout << endl;
    return 1;
}

//----------关键路径----------
int CriticalPath(ALGraph* G, SqStack* T)
{
    if (TopologicalSort(G, T) == 0) {
        cout << endl << "！！输入的AOE-网中存在环结构！！" << endl;
        cout << "--****************************************--" << endl;
        return ERROR;//0
    }
    for (int n = 0; n < G->vexnum; n++)
        vl[n] = 1000; vl[G->vexnum - 1] = ve[G->vexnum - 1];
    ArcNode* p; int j, k, dut, ee, el;
    cout << endl << "------------------------------------------------------------------------------------";
    int b = 0, xx = T->top; cout << endl << "工序间的先后关系（拓扑序列）：" << endl;
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
    printf("起点 终点 最早开始时间 最迟开始时间 权值   备注\n");
    int sum = 0, c = 0;
    for (j = 0; j < G->vexnum; ++j)
        for (p = G->vertices[j].firstarc; p != NULL; p = p->nextarc) {
            k = p->adjvex; dut = p->weight;
            ee = ve[j]; el = vl[k] - dut;
            printf("%2d %4d %8d %12d %8d     ", j + 1, k + 1, ee, el, dut);
            if (ee == el)
            {
                cout << "关键活动：";
                cout << "<" << j + 1 << " ," << k + 1 << " >  该活动需要时间=" << p->weight;

                if (test1[j] == 0 && c == 0 && test1[k] == 0)
                {
                    sum += dut; c++; cout << " *计入总时间";
                    test1[j] = 2; test1[k] = 1;
                }
                if (test1[j] == 1)
                {
                    sum += dut; cout << " *计入总时间";
                    test1[j] = 2; test1[k] = 1;
                }
            }
            cout << endl;
        }
    cout << "----------------------------------------------" << endl;
    cout << "项目的最早完成时间为：" << sum << "（单位时间）" << endl;
    cout << "----------------------------------------------" << endl << endl;
    return 0;
}
int main()
{
    ALGraph* G = new ALGraph;
    cout << "***********估算工程领域中项目的最早完成时间***********" << endl << endl;
    CreateGraph(G);
    SqStack* T;
    T = (SqStack*)malloc(sizeof(SqStack));
    CriticalPath(G, T);
    return 0;
}
