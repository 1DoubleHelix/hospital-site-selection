#pragma once
#include <iostream>
#include <time.h>
using namespace std;

#define MaxInt 32767 //极大值
#define MVNum 20	 //最大顶点数
#define AMin 10		 //最小路径长度
#define AMax 90		 //最大路径长度
#define OK 1
#define ERROR 0;

typedef int VexType;	//顶点数据类型
typedef int ArcType;	//边的权值类型
int Path[MVNum][MVNum]; //最短路径上顶点vj的前一顶点的序号
int D[MVNum][MVNum];	//记录顶点vi和vj之间的最短路径长度
int D_Sum[MVNum];		//保存各顶点的偏心度

typedef struct
{
	VexType vexs[MVNum];		//顶点表
	ArcType arcs[MVNum][MVNum]; //邻接矩阵
	int vexnum, arcnum;			//图的点数和边数
} VGraph;

int LocateVex(VGraph G, VexType v)
{ //确定点v在G中的位置
	for (int i = 0; i < G.vexnum; ++i)
		if (G.vexs[i] == v)
			return i;
	return -1;
} // LocateVex

void ShowMatrix(VGraph G)
{ //显示对称矩阵
	cout << "============生成路径的邻接矩阵为============" << endl;
	for (int i = 0; i < G.vexnum; i++)
	{
		for (int j = 0; j < G.vexnum; j++)
		{
			cout << G.arcs[i][j] << " ";
		}
		cout << endl;
	}
} // ShowMatrix

int CreateMatrix(VGraph &G)
{ //用随机数填充一个对称矩阵

	srand(unsigned(time(0)));
	for (int i = 0; i < G.vexnum; ++i)
	{
		for (int j = 0; j < G.vexnum; ++j)
		{
			G.arcs[i][j] = rand() % (AMax - AMin + 1) + AMin;
			G.arcs[j][i] = G.arcs[i][j];
		}
	}

	//随机删除n-2条边
	srand((unsigned)time(NULL)); //每次循环都生成不同的随机数
	for (int i = 0; i < G.vexnum - 2; i++)
	{
		int Delx = rand() % (G.vexnum);
		int Dely = rand() % (G.vexnum);
		G.arcs[Delx][Dely] = MaxInt;
		G.arcs[Dely][Delx] = MaxInt;
	}

	for (int i = 0; i < G.vexnum; i++)
	{
		G.arcs[i][i] = 0; //给对角线赋0值
	}

	return OK;
} // CreateMatrix

int CreateVillage(VGraph &G)
{ //采用邻接矩阵表示法，创建有向网G
	int i, j;

	bool k = true;
	while (k)
	{
		cout << "输入村庄个数，将随机生成路径长度" << endl;
		cout << "取值范围为3到20：" << endl;
		cin >> G.vexnum;
		if (G.vexnum >= 3 && G.vexnum <= 20)
			k = false;
		else
			cout << "输入有误！" << endl
				 << "============================================" << endl;
	}
	G.arcnum = G.vexnum * (G.vexnum - 1) / 2; //将路径设为最大值

	//填充村庄名称
	for (i = 0; i < G.vexnum; ++i)
	{
		G.vexs[i] = i; //按顺序赋予名称，从0开始
	}
	CreateMatrix(G); //随机生成路径长度
	return OK;
} // CreateVillage

void ShortPath(VGraph G)
{ //用Floyd算法求有向网G中各对顶点i和j之间的最短路径
	int i, j, k;
	for (i = 0; i < G.vexnum; ++i) //各对结点之间初始已知路径及距离
		for (j = 0; j < G.vexnum; ++j)
		{
			D[i][j] = G.arcs[i][j];
			if (D[i][j] < MaxInt && i != j)
				Path[i][j] = i; //如果i和j之间有弧，则将j的前驱置为i
			else
				Path[i][j] = -1; //如果i和j之间无弧，则将j的前驱置为-1
		}

	for (k = 0; k < G.vexnum; ++k)
		for (i = 0; i < G.vexnum; ++i)
			for (j = 0; j < G.vexnum; ++j)
				if (D[i][k] + D[k][j] < D[i][j])
				{								 //从i经k到j的一条路径更短
					D[i][j] = D[i][k] + D[k][j]; //更新D[i][j]
					Path[i][j] = Path[k][j];	 //更改j的前驱为k
				}
} // ShorPath

void DisplayPath(VGraph G, int begin, int end)
{ //显示最短路径

	if (Path[begin][end] != -1)
	{
		DisplayPath(G, begin, Path[begin][end]);
		cout << G.vexs[Path[begin][end]] + 1 << "-->"; //+1对应村庄序号
	}
} // DisplayPath

void SumDestination(VGraph G)
{ //计算并保存各顶点的偏心度到顺序表
	//初始化偏心度矩阵
	for (int i = 0; i < MVNum; i++)
	{
		D_Sum[i] = MaxInt;
	}
	//累加长度并赋值
	for (int i = 0; i < G.vexnum; i++)
	{
		int tmp = 0;
		for (int j = 0; j < G.vexnum; j++)
		{
			tmp += D[i][j];
		}
		D_Sum[i] = tmp;
	}
} // SumDestination

void LocateHospital(VGraph G, int &Hospital)
{						  //找到中心点
	Hospital = 0;		  //记录选址下标
	int Distant = MaxInt; //记录最短长度，赋最大值
	for (int i = 0; i < G.vexnum; i++)
	{
		if (D_Sum[i] < Distant)
		{
			Hospital = i;		//更新下标
			Distant = D_Sum[i]; //更新距离
		}
	}
} // LocateHospital

void ShowDestination(VGraph G, int Hos)
{ //显示路径和长度

	for (int i = 0; i < G.vexnum; i++)
	{

		cout << "第" << i + 1 << "个村庄到医院的路径";
		DisplayPath(G, i, Hos);
		cout << Hos + 1 << " ";
		cout << "距离为" << D[Hos][i] << endl;
		cout << endl;
	}
} // ShowDestination