#include <iostream>
#include <cmath>
using namespace std;
int n,v,c[1000],w[1000],s[1000],d[10000];
int main()
{
	cin >>n >>v;
	for (int i=1;i<=n;i++)
		cin >>w[i] >>c[i] >>s[i];   //输入
	for (int i=1;i<=n;i++)
		for (int j=v;j>=0;j--)
                //由于我们不知道当前物品要拿几个，所以我们要将判断移动到枚举个数之后。
			for (int k=1;k<=s[i];k++)   //用来枚举每个物品的个数
				if (j>=w[i]*k)  //判断能不能装得下
					d[j]=max(d[j],d[j-w[i]*k]+c[i]*k);
                    //公式中需要加入物品个数的因素，物品的价格就是单价*个数，价值同理。
	cout <<d[v];
	return 0;
}