#include <iostream>
#include <queue>
using namespace std;

struct pipe
{
	int row;
	int col;
	int dir;
};

int dx[3] = { 0,1,1 }; //오른쪽, 아래, 오른쪽 대각선
int dy[3] = { 1,0,1 };

int invalid[3] = { 1,0,-1 }; //오른쪽->아래x, 아래->오른쪽x
int board[17][17];
bool valid[3] = { 0,0,0 }; //3방향 가능한지 체크

int main()
{
	int N;
	cin >> N;

	for(int i=1;i<=N;i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cin >> board[i][j]; //입력받기
		}
	}

	queue<pipe> move;
	move.push({ 1,2,0 }); //파이프 다음 시작점
	int cnt = 0;
	while(!move.empty())
	{
		int cr = move.front().row;
		int cc = move.front().col;
		int cd = move.front().dir;

		move.pop();
		
		if (cr == N && cc == N)
		{
			cnt++;
			continue;
		}

		valid[0] = valid[1] = valid[2] = 0;

		for(int d=0;d<3;d++)
		{
			int nr = cr + dx[d];
			int nc = cc + dy[d];
			int nd = d;
			if (nr <= 0 || nr > N || nc <= 0 || nc > N)continue;
			if (board[nr][nc])continue; //벽인 경우에 체크

			if(d==2) //대각선일때는 전부 체크해주어야 함
			{
				if (!valid[0] || !valid[1])continue; //오른쪽이나 아래가 벽인 경우
			}
			valid[d] = 1;
			
			if(invalid[cd]!=d)
			{
				move.push({ nr,nc,nd });
			}
				
		}
	}

	cout << cnt << '\n';
	return 0;
}
