#include <iostream>
#include <cmath>
using namespace std;
int n,v,c[1000],w[1000],s[1000],d[10000];
int main()
{
	cin >>n >>v;
	for (int i=1;i<=n;i++)
		cin >>w[i] >>c[i] >>s[i];   //����
	for (int i=1;i<=n;i++)
		for (int j=v;j>=0;j--)
                //�������ǲ�֪����ǰ��ƷҪ�ü�������������Ҫ���ж��ƶ���ö�ٸ���֮��
			for (int k=1;k<=s[i];k++)   //����ö��ÿ����Ʒ�ĸ���
				if (j>=w[i]*k)  //�ж��ܲ���װ����
					d[j]=max(d[j],d[j-w[i]*k]+c[i]*k);
                    //��ʽ����Ҫ������Ʒ���������أ���Ʒ�ļ۸���ǵ���*��������ֵͬ��
	cout <<d[v];
	return 0;
}