#include<iostream>
#include"Create.h"
using namespace std;

int main()
{
	cout << "================医院选址程序================" << endl;
	int HosAddr = 0;//选址点
	VGraph G;

	CreateVillage(G);//生成表示村庄的无向网
	ShowMatrix(G);
	ShortPath(G);//Floyed算法

	//cout << "=================== D[] ===================" << endl;
	//for (int i = 0; i < G.vexnum; i++) {
	//	for (int j = 0; j < G.vexnum; j++) {
	//		cout << D[i][j] << " ";
	//	}
	//	cout << endl;
	//}

	SumDestination(G);//计算偏心度并存放在顺序表中

	//cout << "================= D_Sum[] =================" << endl;
	//for (int i = 0; i < G.vexnum; i++) {
	//	cout << D_Sum[i] << " ";
	//}
	//cout << endl;

	LocateHospital(G, HosAddr);
	cout << "医院应该选址在第" << HosAddr+1 << "条村庄" << endl;

	ShowDestination(G,HosAddr);

	return 0;
}

/*
有一个乡镇，共有n个村庄，现在要建立一家医院，那么医院应该选址在哪个村庄合适呢？
设计算法，满足如下选址要求：使得所有村庄到达医院都最近。
(1)	随机生成一个有n个村庄和村庄间的路径及路径长度，并输出；
(2)	显示出各村庄到医院的路径和路径长度。
*/