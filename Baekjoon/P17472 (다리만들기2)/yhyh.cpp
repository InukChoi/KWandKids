//그리드 게임의 아이디어를 이용해서 해결!
//정점을 만들고, 간선(weight 있음) 이어서 그래프 만든 후 prim 알고리즘으로 해결
#include <iostream>
#include <queue>
using namespace std;

#define INF 987654321
#define MIN(a,b)(a<b?a:b)

int board[10][10];
int graph[7][7]; //그래프 인접 행렬로 만들어줌 (최대 6x6)

int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };

int que[200][2]; //어차피 priority queue stl 쓸거 왜 배열로 큐 했는지 모르겠음... ㅇ<-<
int vertex[10][10]; //정점 표시(겸 visited 체크)
int f, r;
int vSize = 0;
int N, M;

void makeGraph(int row, int col, int num)
{
	f = r = 0;
	vertex[row][col] = num;
	que[r][0] = row;
	que[r][1] = col;
	r++;
	while(f<r)
	{
		int cr = que[f][0];
		int cc = que[f][1];
		f++;
		for(int d=0;d<4;d++)
		{
			int nr = cr + dx[d];
			int nc = cc + dy[d];
			if (nr < 0 || nr >= N || nc < 0 || nc >= M)continue;
			if (board[nr][nc]&&!vertex[nr][nc]) //같은 섬이라면 정점 이름 표시
			{
				vertex[nr][nc] = num;
				que[r][0] = nr;
				que[r][1] = nc;
				r++;
			}
			else if(!board[nr][nc])//만약 주변이 바다라면? (계속 뻗어나가서 정점간 간선 이어줌)
			{
				int tcnt = 1;
				nr = nr + dx[d];
				nc = nc + dy[d];
				int res = -1;
				while(nr>=0&&nr<N&&nc>=0&&nc<M)
				{
					if (board[nr][nc])
					{
						res = tcnt;
						break;
					}
					nr = nr + dx[d];
					nc = nc + dy[d];
					tcnt++;
				}

				if(res>1&&vertex[nr][nc]) //1이하라면 넘어감(이렇게 하니 이부분에 2V 만큼의 시간이 들긴 하는데 어차피 6x6이라서..)
				{
					int nV = vertex[nr][nc];
					graph[num][nV] = MIN(graph[num][nV],res);
					graph[nV][num] = MIN(graph[num][nV],res);
				}
			}
			
		}
	}
}

int Prim()
{
	int sV = 1; //시작정점을 1로 하자
	int visited[7] = { 0, };
	int dist[7]; //거리
	for (int i = 1; i <= vSize; i++)dist[i] = INF;

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push({ 0,1 });
	int val = 0;
	while(!pq.empty())
	{
		int cV = pq.top().second;
		pq.pop();
		if (!visited[cV]) 
		{
			visited[cV] = 1;
			for (int i = 1; i <= vSize; i++)
			{
				if (graph[cV][i] < dist[i]&&!visited[i])
				{
					dist[i] = graph[cV][i];
					pq.push({ graph[cV][i],i });
				}
			}
		}
	}
	for(int i=1;i<=vSize;i++)
	{
		if (!visited[i])return 0; //만약 이어지지 못한 섬이 있다면 바로 0 리턴
		if(dist[i]!=INF) //dist 값 전부 더해줌
			val += dist[i];
	}
	return val;
}

int main()
{

	cin >> N >> M;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<M;j++)
		{
			cin >> board[i][j];
			vertex[i][j] = 0;
		}
	}
	for(int i=0;i<=6;i++)
	{
		for (int j = 0; j <= 6; j++)graph[i][j] = INF; //최댓값으로 초기화
	}
	int cnt = 1;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (board[i][j] && !vertex[i][j])
			{
				makeGraph(i, j, cnt); //그래프 만들어주기
				cnt++;
			}
		}
	}
	vSize = cnt - 1; //정점 사이즈
	int rVal = Prim();
	if (rVal == 0)rVal = -1; //0이 리턴되면 -1을 출력한다 (값이 0인 다리는 존재하지 않음)
	cout<<rVal<<"\n";
	
	return 0;
}
