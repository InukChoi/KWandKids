#include <iostream>
#include <string>
using namespace std;

int alpha[26] = { 0, };
int tCnt = 0;
int strLen = 0;

void DFS(int cnt,char prev)
{
	if(cnt>=strLen)
	{
		tCnt++;
	}
	else
	{
		for(int i=0;i<26;i++)
		{
			if (!alpha[i])continue;
			if (prev == i + 'a')continue;
			alpha[i]--;
			DFS(cnt + 1, i + 'a');
			alpha[i]++;
		}
	}
}

int main()
{
	string input;
	cin >> input;
	strLen = input.length();
	for(int s=0;s<strLen;s++)
	{
		alpha[input[s] - 'a']++;
	}
	DFS(0, '\0');
	cout << tCnt << "\n";
	return 0;
}
