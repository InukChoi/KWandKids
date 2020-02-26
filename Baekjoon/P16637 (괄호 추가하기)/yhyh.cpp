#include <iostream>
#include <string>
#include <set>
using namespace std;

#define MAX(a,b)(a>b?a:b)

int opns[11]; //피연산자 집합
char oprs[10] = "\0"; //연산자 집합
int strLen;

int maxV = -987654321;
int opnSize;

int calc(int fop, int sop,char opr)
{
	switch(opr)
	{
	case '+':
		return fop + sop;
	case '-':
		return fop - sop;
	default:
		return fop * sop;
	}
	return 0;
}


int ctoi(char num)
{
	return num - '0';
}


int main()
{
	cin >> strLen;
	cin >> opns[0];
	for(int i=0;i<strLen/2;i++)
	{
		char tmp;
		cin >> oprs[i] >> tmp;
		opns[i+1] = ctoi(tmp);
	}

	
	opnSize = strLen / 2;
	

	set<int> dp[10];
	dp[0].insert(opns[0]);
	dp[1].insert(calc(opns[0], opns[1], oprs[0]));

	set<int>::iterator iter;

	for (int i = 2; i <= opnSize; i++)
	{
		for (iter = dp[i - 2].begin(); iter != dp[i - 2].end(); ++iter)
		{
			int fop, sop;
			fop = calc((*iter), opns[i - 1], oprs[i - 2]);
			sop = opns[i];
			dp[i].insert(calc(fop, sop, oprs[i - 1]));

			fop = (*iter);
			sop = calc(opns[i - 1], opns[i], oprs[i - 1]);
			dp[i].insert(calc(fop, sop, oprs[i - 2]));
		}
		for (iter = dp[i - 1].begin(); iter != dp[i - 1].end(); ++iter)
		{
			dp[i].insert(calc((*iter), opns[i], oprs[i - 1]));
		}
	}


	int maxV = -987654321;
	for (iter = dp[opnSize].begin(); iter != dp[opnSize].end(); ++iter)
	{
		maxV = MAX(maxV, (*iter));
	}
	
	cout << maxV << "\n";
	return 0;
}
