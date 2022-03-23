#include <iostream>
#include "Create.h"
using namespace std;

int main()
{
	cout << "================医院选址程序================" << endl;
	int HosAddr = 0; //选址点
	VGraph G;

	CreateVillage(G); //生成表示村庄的无向网
	ShowMatrix(G);
	ShortPath(G); // Floyed算法

	SumDestination(G); //计算偏心度并存放在顺序表中

	LocateHospital(G, HosAddr);
	cout << "医院应该选址在第" << HosAddr + 1 << "条村庄" << endl;

	ShowDestination(G, HosAddr);

	return 0;
}