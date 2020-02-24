#include <iostream>
using namespace std;

int team1[] = { 0,0,0,0,0,1,1,1,1,2,2,2,3,3,4 };
int team2[] = { 1,2,3,4,5,2,3,4,5,3,4,5,4,5,5 };
int world[6][3];
int result[6][3];

int ans[4] = { 0,0,0,0 };//결과 테이블

void DFS(int tc,int cnt) //총 15경기
{
	if(cnt>=15)
	{
		for (int i = 0; i < 6; i++) 
		{
			for(int j=0;j<3;j++)
			{
				if (result[i][j] != world[i][j])
				{
					return;
				}
			}
		}
		ans[tc] = 1;
		return;
	}
	if (ans[tc])return;
	else
	{
		//team1이 승리
		if(result[team1[cnt]][0]+1<=world[team1[cnt]][0]
			&& result[team2[cnt]][2] + 1 <= world[team2[cnt]][2])
		{
			result[team1[cnt]][0]++;
			result[team2[cnt]][2]++;//패배
			DFS(tc, cnt + 1);
			result[team1[cnt]][0]--;
			result[team2[cnt]][2]--;
		}
		
		
		//비김
		if (result[team1[cnt]][1] + 1 <= world[team1[cnt]][1]
			&& result[team2[cnt]][1] + 1 <= world[team2[cnt]][1])
		{
			result[team1[cnt]][1]++;
			result[team2[cnt]][1]++;
			DFS(tc, cnt + 1);
			result[team1[cnt]][1]--;
			result[team2[cnt]][1]--;
		}
	
		//team2가 승리
		if (result[team1[cnt]][2] + 1 <= world[team1[cnt]][2]
			&& result[team2[cnt]][0] + 1 <= world[team2[cnt]][0])
		{
			result[team1[cnt]][2]++;
			result[team2[cnt]][0]++;
			DFS(tc, cnt + 1);
			result[team1[cnt]][2]--;
			result[team2[cnt]][0]--;
		}
		
	}
}


int main()
{
	for(int i=0;i<4;i++)
	{
		for(int r=0;r<6;r++)
		{
			cin >> world[r][0] >> world[r][1] >> world[r][2];
			result[r][0] = result[r][1] = result[r][2] = 0;
		}
		DFS(i,0);
	}
	for (int i = 0; i < 4; i++)cout << ans[i] << " ";
	cout << "\n";
	return 0;
}
