#include <iostream>
#include <vector>
 
using namespace std;
 
#define INF 987654321
#define MIN(a,b)(a<b?a:b)
 
struct Info
{
    int dst;
    int cost;
};
 
int N, M;
vector<vector<Info>> graph;
vector<bool>visited;
int sV;
int minV = INF;
 
void DFS(int tCost, int cV)
{
    if (tCost >= minV)return;
    visited[cV] = true; //특이하게 방문 처리를 여기서 해준다... 거리가 더 짧을 때 갱신해주어야 해서 그런가?
    for (unsigned int i = 0; i < graph[cV].size(); i++)
    {
        int nV = graph[cV][i].dst;
        if(nV==sV) //가지를 뻗을때 이미 출발지가 있으면 리턴(안하면 시간초과남)
        {
            minV = MIN(minV, tCost + graph[cV][i].cost);
            return;
        }
        if (visited[nV])continue;
 
        DFS(tCost + graph[cV][i].cost, nV);
    }
}
 
int main()
{
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++)
    {
        cin >> N >> M;
        minV = INF;
        graph.clear();
        graph.resize(N + 1);
 
        for (int m = 0; m < M; m++)
        {
            int s, e, c;
            cin >> s >> e >> c;
            graph[s].push_back({ e,c });
        }
 
        for (int i = 1; i <= N; i++)
        {
            visited.clear();
            visited.resize(N + 1, false);
            sV = i;
            DFS(0, i);
        }
        if (minV == INF)minV = -1;
 
        cout << "#" << tc << " " << minV << "\n";
    }
    return 0;
}
