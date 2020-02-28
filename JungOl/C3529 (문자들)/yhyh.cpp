#include <iostream>
using namespace std;

#define MIN(a,b)(a<b?a:b)
#define MAX(a,b)(a>b?a:b)

bool visited[21][21] = { 0, };
char board[21][21];

int R, C;
int alpha[26] = { 0, };
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };
int maxV = 0;

void DFS(int row,int col,int cnt)
{
	maxV = MAX(maxV, cnt);
	for(int d=0;d<4;d++)
	{
		int nr = row + dx[d];
		int nc = col + dy[d];
		if (nr < 0 || nr >= R || nc < 0 || nc >= C)continue;
		if (visited[nr][nc])continue;
		if (alpha[board[nr][nc]-'A'])continue;
		visited[nr][nc] = 1;
		alpha[board[nr][nc]-'A'] = 1;
		DFS(nr, nc, cnt + 1);
		alpha[board[nr][nc]-'A'] = 0;
		visited[nr][nc] = 0;
	}
}

int main()
{
	cin >> R>>C;

	
	for(int i=0;i<R;i++)
	{
		for(int j=0;j<C;j++)
		{
			cin >> board[i][j];
		}
	}

	visited[0][0] = 1;
	alpha[board[0][0]-'A'] = 1;
	DFS(0, 0, 1);

	cout << maxV << "\n";
	return 0;
}
