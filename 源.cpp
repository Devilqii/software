#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include<ctime>
using namespace std;
class Solve
{
private:
	char* cst;
	float* fst;
	int cp, fp;
	static int table[7][7];  //算数优先符号表
protected:
	int compare(char a, char b);
	/* 在这里比较运算符的优先次序如a 为新输入操作符， b 为后输入操作符, 如果 a > b
	 返回 1， 如果 a = b 返回0; 如果 a < b, 返回 1 */
	void computer(char c);
	/* 从操作数栈里取出两数进行 c 运算，并把结果入栈*/
	int getodr(char c);  //获取操作符在table表中的下标;
public:
	Solve();
	void isolve();
	~Solve();
	void getNum(float c);     //获取相应长度
	void getCh(char c);		//获取相应字符压入栈
	float getRes();
};
int Solve::table[7][7] = {// +， -， *， /， （， ）， #，
	{ -1, -1, -1, -1, 1, 0, 1 },
	{ -1, -1, -1, -1, 1, 0, 1 },
	{ 1,  1, -1, -1, 1, 0, 1 },
	{ 1,  1, -1, -1, 1, 0, 1 },
	{ 1,  1, 1,  1, 1, 0, 1 },
	{ -1, -1, -1, -1, 0, 0 ,0 },
	{-1, -1, -1, -1, 0, 0, 0}
};
Solve::Solve()              // 完成初始化操作符操作数堆栈置0
{
	cst = new char[30];
	fst = new float[30];
}
Solve::~Solve() {}
void Solve::isolve()
{
	cp = 0;
	fp = 0;
}
void Solve::getNum(float c)
{
	fst[fp++] = c;
}
float Solve::getRes()
{
	return  fst[--fp];
}
void Solve::getCh(char c)			// c 为新得到的字符;
{
	if (cp == 0 && c == '#')		//接受第一个字符 '#'
	{
		cst[cp++] = c;
	}
	else							//若输入的是加减乘除'#'；
	{
		char u = cst[cp - 1];		// u 栈顶字符
		if (compare(c, u) == 1)		//新输入的优先级大于栈顶
		{
			cst[cp++] = c;
		}
		else if (compare(c, u) == 0) // 新输入优先级小于栈顶
		{
			if (u == '(' && c == ')' || u == '#' && c == '#')
			{
				cp--; //将左括号移出去;
			}
			else
			{
				printf("priority 0 error");
			}
		}
		else if (compare(c, u) == -1) //新输入优先级等于小于栈顶
		{
			do
			{
				cp--;
				computer(u);			//拿出栈顶符号去计算
				u = cst[cp - 1];	//新的栈顶符号
			} while (compare(c, u) == -1);
			//直到栈顶符号优先级不高于 最新输入的操作符优先级，跳出循环
			if (u == '(' && c == ')' || u == '#' && c == '#') //如果优先级相等，就拿出去;
			{
				cp--; //将左括号移出去;
			}
			else					 //如果新输入操作符优先级高，则放入;
			{
				cst[cp++] = c;
			}
		}
		else
		{
			printf("error\n");
		}
	}
}
int Solve::compare(char a, char b)
{
	return table[getodr(a)][getodr(b)];
}
void Solve::computer(char c)
{
	float a, b;
	float res;
	b = fst[--fp];
	a = fst[--fp];
	if (c == '*')
	{
		res = a * b;
	}
	else if (c == '/') //除数为0是不被允许的,这里当除数为时当1处理，防止程序崩溃;
	{
		if (b == 0)
		{
			res = a;
		}
		else
		{
			res = 1.0 * a / b;
		}
	}
	else if (c == '+')
	{
		res = a + b;
	}
	else if (c == '-')
	{
		res = a - b;
	}
	else
	{
		printf("computer error having excepted opr");
	}
	fst[fp++] = res; //将计算成功的结果返回堆栈；
}
int Solve::getodr(char c)
{
	if (c == '+') return 0;
	if (c == '-') return 1;
	if (c == '*') return 2;
	if (c == '/') return 3;
	if (c == '(') return 4;
	if (c == ')') return 5;
	if (c == '#') return 6;
}
int main()
{
	srand((unsigned)time(NULL));
	int num, max = 0;
	char op[20] = { '\0' };
	bool cld1, cld2; // cld1为1 表示可能含有括号， 为0表示不含括号， cld2 为1表示含有小数为2表示不含有小数;
	float  resArray[100] = { 0 };
	int respos = 0;
	// 输入操作

	printf("请输入生成题目的数量:\n");
	while (true)
	{
		cin >> num;
		if (num > 0) break;
		cout << "输入有误， 请重新输入题目数量:\n";
	}
	printf("========================================================\n");
	printf("请选择运算符， 例如：加减乘除  +  -  *  /  :\n ");
	cin >> op;
	printf("========================================================\n");
	printf("请输入数值的最大值:\n");
	while (true)
	{
		cin >> max;
		if (max > 0) break;
		cout << "输入有误， 请重新输入最大值:\n";
	}
	printf("========================================================\n");
	printf("请选择是否有括号 1or0（1代表有，0代表无）:\n");
	cin >> cld1;
	printf("========================================================\n");
	printf("请选择是否有小数 1or0（1代表有，0代表无）:\n");
	cin >> cld2;

	// **********************************************--------***********//
	 //生成操作
	int opnum = 0;    //统计op 并处理
	while (true)
	{
		if (op[opnum] != '\0')
		{
			opnum++;
		}
		else
		{
			break;
		}
	}  // 此时  opnum 记录着 op操作符的数量；
	/*****************************************************************/

	// 考虑到实际中不太会有 过于长的多项式， 这里 设置一个随机数把含有的符号数限制到7个以内；
	// opmax 为 + - * / 的最大个数， 限制了多项式的长度;
	int pos = 0;
	int opmax = 0;
	int kuohao = 0;
	int order = 1; //题目序号
	int flag = 0; // 排除一个操作数左右两边括号的情况:  (a) + b 
	Solve s1;  //创建计算器， 用于实时计算字符串的值；
	while (num--)
	{
		s1.isolve(); //清空计算器; 
		s1.getCh('#'); // 放入'#' 准备接受算式开始计算;
		float factor = 0;
		cout << order++ << ".     ";
		pos = 0;
		opmax = rand() % 6 + 1;
		kuohao = 0;
		while (opmax--)			//开始生成多项式
		{
			char vv = '\0';
			bool lf = false;	// 用于表示此次是否生成了左括号
			if (cld1 == 1 && rand() % 8 > 5) // 1/8 的概率出现括号;
			{
				flag = 0;
				cout << '(';
				kuohao++;
				lf = true;
			}
			if (lf)
			{
				s1.getCh('(');
			}
			factor = rand() % (max - 1) + 1 + ((rand() % 100) * 1.0 / 100) * cld2;
			cout << factor;
			//生成操作数 factor;
			s1.getNum(factor); //操作数放入计算器
			bool rf = false;  //用于表示是否生成了右括号;
			if (cld1 == 1 && kuohao > 0 && flag != 0)
			{
				if (rand() % 4 > 2)
				{
					cout << ')';
					kuohao--;
					rf = true;
				}
			}
			if (rf)
			{
				s1.getCh(')');
			}
			//生成操作符 
			pos = rand() % opnum;
			cout << op[pos];

			//将操作符放入计算器;
			s1.getCh(op[pos]);

			flag++;
		}
		factor = rand() % (max - 1) + 1 + ((rand() % 100) * 1.0 / 100) * cld2;
		cout << factor;
		//将最后一个操作数放入计算器
		s1.getNum(factor);
		while (kuohao--)
		{
			cout << ')';
			s1.getCh(')');
		}
		//将结尾符号'#'放入计算器;
		s1.getCh('#');
		printf("=?\n");
		//将最终的结果放入结果数组
		resArray[respos++] = s1.getRes();
	}
	printf("========================================================\n");
	printf("||****************************************************||\n");
	printf("计算结果如下：\n");
	// 输出答案 *************************************************//:
	for (int i = 0; i < respos; i++)
	{
		cout << i + 1 << ". " << resArray[i] << endl;
		if (i + 1 % 10 == 0)
		{
			cout << endl;
		}
	}
	printf("||****************************************************||\n");
	printf("========================================================\n");
	//******************************************************//

	return 0;
}