#include <iostream>
#include <cmath>
using namespace std;

#define MAX(a,b)(a>b?a:b)

int maxV = 0;
int N, M;
int board[15][15];
int tmp[15][15];
int D;
int archers[3];
int dist[3]; //거리
int enemyI[3][2]; //죽일 적 인덱스 저장해두기
bool visited[15];
int tcnt = 0;

void killEnemy()
{
	for (int n = N - 1; n >= 0; n--)//점점 인덱스가 위로 올라옴(적들이 아래로 내려감)
	{
		enemyI[0][0] = enemyI[1][0] = enemyI[2][0] = -1; //초기화
		enemyI[0][1] = enemyI[1][1] = enemyI[2][1] = -1;
		dist[0] = dist[1] = dist[2] = 987654321;
		for (int j = 0; j < M; j++)
		{			
			for (int i = n; i >= 0; i--)
			{
				if (tmp[i][j])
				{
					for (int a = 0; a < 3; a++)
					{
						int cdist = (n + 1 - i) + abs(archers[a] - j);
						if (cdist > D)continue;
						if (cdist < dist[a])
						{
							dist[a] = cdist;							
							enemyI[a][0] = i;
							enemyI[a][1] = j;
						}
						
					}
				}
			}
		}
		//죽일 적을 골랐으니 죽여버리자!
		for (int a = 0; a < 3; a++)
		{
			int ai = enemyI[a][0];
			int aj = enemyI[a][1];
			if (ai == -1 || aj == -1)continue;
			if (tmp[ai][aj]) //이미 죽은 적을 죽일수는 없어요^^
			{
				tcnt++;
				tmp[ai][aj] = 0;
			}
		}

	}
}

void setArcher(int s, int cnt)
{
	if (cnt == 3)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)tmp[i][j] = board[i][j];
		}
		tcnt = 0;
		killEnemy();
		maxV = MAX(maxV, tcnt);
		return;
	}
	else
	{
		for (int i = s; i < M; i++)
		{
			if (visited[i])continue;
			visited[i] = true;
			archers[cnt] = i; //궁수가 있는 열의 위치
			setArcher(i + 1, cnt + 1);
			visited[i] = false;
		}
	}
}

int main()
{
	cin >> N >> M >> D;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> board[i][j];
			visited[i] = 0;
		}
	}
	setArcher(0, 0);
	cout << maxV << "\n";
	return 0;
}
