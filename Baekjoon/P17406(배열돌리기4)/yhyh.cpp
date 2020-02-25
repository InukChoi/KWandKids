#include <iostream>
#include <vector>
using namespace std;

#define MIN(a,b)(a<b?a:b)

int N, M, K;
int A[50][50];
int copyA[50][50];
int seq[6];
bool visited[6];
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };

int minResult = 987654321;

struct rInfo
{
	int r;
	int c;
	int s;
};

rInfo rotateA[6];

int getMin()
{

	int minSum = 987654321;
	for(int i=0;i<N;i++)
	{
		int rowSum = 0;
		for(int j=0;j<M;j++)
		{
			rowSum += copyA[i][j];
		}
		minSum = MIN(minSum, rowSum);
	}
	return minSum;
}

void RotateAll()
{
	for(int i=0;i<N;i++)
	{
		for (int j = 0; j < M; j++)copyA[i][j] = A[i][j];//copy
	}

	int cmin = 987654321;
	for(int i=0;i<K;i++)
	{
		int mrow = rotateA[seq[i]].r - 1;
		int mcol = rotateA[seq[i]].c - 1;

		for(int s=1;s<=rotateA[seq[i]].s;s++)
		{
			//개수는 2*s+1
			int row = mrow - s;
			int col = mcol - s;
			int tmp = copyA[row][col]; //임시저장
			for(int d=0;d<4;d++)
			{
				int cnt = 2 * s;
				while(cnt--)
				{
					copyA[row][col] = copyA[row + dx[d]][col + dy[d]];
					row = row + dx[d];
					col = col + dy[d];
				}
			}
			copyA[row][col + 1] = tmp;
		}
	}
	cmin = getMin();
	minResult = MIN(minResult, cmin);
}

void makeSequence(int cnt)
{
	if(cnt>=K)
	{
		RotateAll();
	}
	else
	{
		for(int i=0;i<K;i++)
		{
			if (visited[i])continue;
			visited[i] = true;
			seq[cnt] = i;
			makeSequence(cnt + 1);
			visited[i] = false;
		}
	}
}

int main()
{
	cin >> N >> M >> K;
	for(int i=0;i<N;i++)
	{
		for (int j = 0; j < M; j++)cin >> A[i][j];
	}

	for(int i=0;i<K;i++)
	{
		visited[i] = false;
		cin>>rotateA[i].r>>rotateA[i].c>>rotateA[i].s;
	}
	makeSequence(0);

	cout << minResult << "\n";
	return 0;
}
