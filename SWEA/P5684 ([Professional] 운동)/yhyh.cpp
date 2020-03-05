#include <iostream>
using namespace std;

#define INF 987654321
#define MIN(a,b)(a<b?a:b)

int N, M;
int graph[401][401]; //똑같은 코드에서 graph 를 이차 벡터로 선언하면 제한시간 초과남 (왜...?)

int Solve()
{
	for (int k = 1; k <= N; k++)
	{
		for (int i = 1; i <= N; i++)
		{
			if (graph[i][k] == INF)continue;
			for (int j = 1; j <= N; j++)
			{
				graph[i][j] = MIN(graph[i][j], graph[i][k] + graph[k][j]);
			}
		}
	}

	int retV = INF;
	for (int i = 1; i <= N; i++)
	{
		retV = MIN(retV, graph[i][i]);
	}
	return retV;
}

int main()
{
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N >> M;
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)graph[i][j] = INF;
		}

		for (int m = 0; m < M; m++)
		{
			int s, e, c;
			cin >> s >> e >> c;
			graph[s][e] = c;
		}

		int minV = INF;

		minV = Solve();
		if (minV == INF)minV = -1;
		cout <<"#"<<tc<<" "<< minV << "\n";
	}
	return 0;
}
