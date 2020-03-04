#include <iostream>
using namespace std;

#define MIN(a,b)(a<b?a:b)
#define INF 987654321
int minV = INF;
int board[10][10];
int comp[10][10];
int confe[6] = { 0,5,5,5,5,5 }; //색종이
void clearArr(int srow, int scol, int bSize)
{
	for (int i = srow; i < srow + bSize; i++)
	{
		for (int j = scol; j < scol + bSize; j++)
		{
			comp[i][j] = 0;
		}
	}
}

bool check(int srow, int scol, int bSize)
{
	for (int i = srow; i < srow + bSize; i++)
	{
		for (int j = scol; j < scol + bSize; j++)
		{
			if (i >= 10 || j >= 10)return false;
			if (!board[i][j] || comp[i][j])return false;
		}
	}

	for (int i = srow; i < srow + bSize; i++)
	{
		for (int j = scol; j < scol + bSize; j++)
		{
			comp[i][j] = 1;
		}
	}
	return true;
}

bool isSame()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (comp[i][j] != board[i][j])return false;
		}
	}
	return true;
}


void Recursion(int srow, int cnt)
{
	if (cnt >= minV)return;

	if (isSame()) //전부 같은지 확인
	{
		minV = MIN(minV, cnt);
		return;
	}

	for (int i = srow; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (board[i][j] && !comp[i][j])//board[i][j]==1이면(또는 이미 방문했다면)
			{
				for (int x = 5; x >= 1; x--)
				{
					if (confe[x] <= 0)continue;
					if (check(i, j, x))
					{
						confe[x]--;
						Recursion(i, cnt + 1);
						clearArr(i, j, x); //backtracking
						confe[x]++;
					}
				}
				return;//만약에 1x1 색종이도 안된다면 그 다음은 볼 필요가 없음
				//현재 칸에서 오른쪽,아래만 확인하기 때문에
				//이전에서 색종이가 붙지 않았다면 틀린 케이스
			}
		}
	}
}

int main()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cin >> board[i][j];
			comp[i][j] = 0;
		}
	}

	Recursion(0, 0);
	if (minV == INF)minV = -1;
	cout << minV << "\n";
	return 0;
}
