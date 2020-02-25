#include <iostream>
#include <queue>
using namespace std;

#define MAX(a,b)(a>b?a:b)

int tomato[100][100][100];
int visited[100][100][100];

int dx[6] = {-1,1,0,0,0,0};
int dy[6] = {0,0,-1,1,0,0};
int dh[6] = {0,0,0,0,-1,1};

struct tInfo
{
	int row;
	int col;
	int height;
};
int main()
{
	int N, M, H;
	cin >> M >> N >> H;
	queue<tInfo> q;
	for (int h = 0; h < H; h++)
	{
		for (int n = 0; n < N; n++)
		{
			for (int m = 0; m < M; m++)
			{
				cin >> tomato[n][m][h];
				if (tomato[n][m][h] == 1)
				{
					q.push({ n,m,h });
					visited[n][m][h] = 1; //나중에 1 빼야함!
				}
			}
		}
	}

	int crow;
	int ccol;
	int chei;


	while(!q.empty())
	{
		crow = q.front().row;
		ccol = q.front().col;
		chei = q.front().height;

		q.pop();
		int nrow, ncol, nhei;
		for(int d=0;d<6;d++)
		{
			nrow = crow + dx[d];
			ncol = ccol + dy[d];
			nhei = chei + dh[d];
			if (nrow < 0 || nrow >= N || ncol < 0 || ncol >= M || nhei < 0 || nhei >= H)continue;
			if (visited[nrow][ncol][nhei] > 0)continue;
			if (tomato[nrow][ncol][nhei] == -1)continue;
			visited[nrow][ncol][nhei] = visited[crow][ccol][chei] + 1;
			q.push({ nrow,ncol,nhei });
		}
	}

	int maxV = 0;
	for (int h = 0; h < H; h++)
	{
		for (int n = 0; n < N; n++)
		{
			for (int m = 0; m < M; m++)
			{
				if (visited[n][m][h] == 0&&tomato[n][m][h]!=-1)
				{
					cout << -1 << "\n";
					return 0;
				}
				maxV = MAX(maxV, visited[n][m][h]);
			}
		}
	}
	cout << maxV - 1 << "\n";
	return 0;
}
