#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
int  Max(int n, int a[])
{
	int i;
	int sum = 0;
	int max = 0;
	for (i = 0; i < n; i++)
	{
		sum += a[i];
		if (sum < 0)
			sum = 0;
		else
		{
			if (max < sum)
				max = sum;
		}
	}
	return max;
}
int main()
{
	int n, a[1000], max = 0, i;
	cin>>n;
	if (n <= 0)
		cout<<"error!";
	else
	{
		for (i = 0; i < n; i++)
			cin>>a[i];
		max = Max(n, a);
		cout<<max<<endl;
	}
	return 0;
}