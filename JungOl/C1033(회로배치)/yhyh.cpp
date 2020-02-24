#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define INF 987654321
#define MIN(a,b)(a<b?a:b)

int N; //격자판 크기
int K; //회로 위를 지나가는 비용
int M; //이미 배치된 회로 개수

int board[51][51];
int dp[51][51];
int prevN[51][51]; //treeSet 방향 저장
bool visited[51][51]; //treeSet에 visit 표시

int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };

int startX, startY; //시작점
int endX, endY; //끝점


struct circuit
{
	int row;
	int col;
	int dist;
	int dir;
};

bool operator<(circuit a, circuit b)
{
	return a.dist > b.dist; //greater부분이 항상 헷갈림 ㅠ
}

int revDir[4] = { 1,0,3,2 };//상하좌우의 반대방향 리턴

int main()
{
	cin >> N;
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=N;j++)
		{
			board[i][j] = 0; //초기화
			dp[i][j] = INF;
			prevN[i][j] = -1;
		}
	}
	cin >> startX >> startY >> endX >> endY;
	cin >> K;
	cin >> M;
	for(int m=0;m<M;m++) //1.설치된 회로를 표시해두자.
	{
		int tSize;//회로 격자 개수
		cin >> tSize;

		int tmpSX, tmpSY, tmpEX, tmpEY; //임시 시작점과 끝점
		cin >> tmpSX >> tmpSY;
		
		for(int t=1;t<tSize;t++)
		{
			cin >> tmpEX >> tmpEY;
			if(tmpSX==tmpEX) //열이 달라짐
			{
				if (tmpSY > tmpEY) 
				{
					for (int j = tmpEY; j <= tmpSY; j++)
					{
						board[tmpSX][j] = 1; //이미 설치된 회로 표시
					}
				}
				else 
				{
					for (int j = tmpSY; j <= tmpEY;j++)
					{
						board[tmpSX][j] = 1; //이미 설치된 회로 표시
					}
				}

				
			}
			else //행이 달라짐
			{
				if (tmpSX > tmpEX)
				{
					for (int i = tmpEX; i <= tmpSX; i++)
					{
						board[i][tmpSY] = 1; //이미 설치된 회로 표시
					}
				}
				else
				{
					for (int i = tmpSX; i <= tmpEX;i++)
					{
						board[i][tmpSY] = 1; //이미 설치된 회로 표시
					}
				}
			}
			tmpSX = tmpEX;
			tmpSY = tmpEY;
		}
	}
	//2.최단 경로를 찾자(다익스트라)

	priority_queue<circuit>pq;
	int cdist = 1;
	if (board[startX][startY] == 1)cdist = K;
	pq.push({ startX,startY,cdist,-1 });
	int crow, ccol;
	int nrow, ncol;
	int ndist = 1;
	while(!pq.empty())
	{
		crow = pq.top().row;
		ccol = pq.top().col;
		cdist = pq.top().dist;
		//이전 부모 방향 저장
		pq.pop();
		if (visited[crow][ccol])continue;
		visited[crow][ccol] = true;
		for(int d=0;d<4;d++)
		{
			nrow = crow + dx[d];
			ncol = ccol + dy[d];
			if (nrow <= 0 || nrow > N || ncol <= 0 || ncol > N)continue;
			if (visited[nrow][ncol])continue; //이미 treeSet이면
			if (board[nrow][ncol])ndist = K;
			else ndist = 1;
			if(cdist+ndist<=dp[nrow][ncol])//이미 저장되어있는 경우보다 작을 경우에만 pq에 넣는다.
			{
				dp[nrow][ncol] = cdist + ndist;
				prevN[nrow][ncol] = revDir[d];
				pq.push({ nrow,ncol,cdist + ndist,revDir[d] });
			}
		}

	}
	cout << dp[endX][endY] << "\n";
	stack<pair<int, int>> prevSet;
	prevSet.push({ endX,endY });
	crow = endX;
	ccol = endY;
	int cdir = prevN[endX][endY]; //이전 부모 방향
	while(true)//prev을 이용해서 스택에 집어넣자
	{
		int nrow = crow + dx[cdir];
		int ncol = ccol + dy[cdir];
		int ndir = prevN[nrow][ncol];
		if (ndir != cdir)prevSet.push({ nrow,ncol });
		if (ndir == -1)break;//시작 노드
		crow = nrow;
		ccol = ncol;
		cdir = ndir;
	}
	cout << prevSet.size() << " ";

	while(!prevSet.empty())
	{
		cout << prevSet.top().first << " " << prevSet.top().second << " ";
		prevSet.pop();
	}
}
