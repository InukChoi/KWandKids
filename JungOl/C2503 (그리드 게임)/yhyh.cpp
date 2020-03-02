//참고 : https://github.com/Rkda8071/PS/blob/4311899b51191f114226d223f882760a37750e1e/JUNGOL/2503/main.cpp
//문제 풀이 참고 : https://justicehui.github.io/koi/2020/01/25/BOJ2452/

#include <iostream>
#include <vector>
#include <set>
using namespace std;

#define INF 987654321

#define MIN(a,b)(a<b?a:b)
#define MAX(a,b)(a>b?a:b)

bool board[100][100];
int num[100][100];
int que[10001][2];


set<int> graph[10001];
int R, C;

int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };

int minV = INF;
int maxV = 0;

void BFS(int row, int col, bool color, int cnt) //칠할 색깔
{
    int f, r;
    f = r = 0;
    que[r][0] = row;
    que[r][1] = col;
    r++;

    num[row][col] = cnt;

    while (f < r)
    {
        int crow = que[f][0];
        int ccol = que[f][1];
        f++;
        for (int d = 0; d < 4; d++)
        {
            int nrow = crow + dx[d];
            int ncol = ccol + dy[d];
            if (nrow < 0 || nrow >= R || ncol < 0 || ncol >= C)continue;
            if (!num[nrow][ncol] && board[nrow][ncol] == color)
            {
                num[nrow][ncol] = cnt;
                que[r][0] = nrow;
                que[r][1] = ncol;
                r++;
            }
            if(num[nrow][ncol]!=0&&num[nrow][ncol]!=cnt)
            {
                graph[cnt].insert(num[nrow][ncol]);
                graph[num[nrow][ncol]].insert(cnt);
            }
        }
    }
}


void Solve()
{
    //make group & graph(인접리스트)
    //1. 색깔이 같은 인접한 값들을 묶어서 정점으로 만들고
    //2. 인접한 정점끼리 연결시킨다. (인접행렬은 메모리 초과가 발생하므로 set을 이용하여 인접리스트로 구현함)
    int cnt = 1;
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            if (num[i][j] != 0)continue;
            BFS(i, j, board[i][j], cnt);
            cnt++;
        }
    }
    
    int chk[10001] = { 0, };
    //각 정점들의 최장 경로를 찾는다.
    //플로이드-워셜 방법으로 해보았는데 시간 초과 발생함(더불어 메모리 초과도 ㅠㅠㅠ)
    //각 정점들의 최장경로를 각각 찾아줌
    for(int i=1;i<cnt;i++)
    {
        if (chk[i])continue;
        maxV = 0;
        int visited[10001] = { 0, };
        set<int>::iterator it;
        int f = 0, r = 0;

        que[r][0] = i;
        que[r][1] = 0;//depth
        visited[i] = 1;
        r++;
        while(f<r)
        {
            int ci = que[f][0];
            int cd = que[f][1];
            maxV = MAX(maxV, cd);

            f++;
            for(it=graph[ci].begin();it!=graph[ci].end();++it)
            {
                int ni = (*it);
                int nd = cd + 1;
                if (visited[ni]!=0)continue;
                visited[ni] = visited[ci]+1;
                que[r][0] = ni;
                que[r][1] = nd;
                
                r++;
            }
        }
        minV = MIN(minV, maxV);
        //가지치기
        //제일 depth값이 큰 정점은 현재 정점에서 가장 멀리있는 정점임을 의미한다.
        //즉 그래프의 양끝에 있으므로 이 부분의 최장경로를 볼 필요가 없음
        //(핵심은 그래프의 중간 정점을 찾아야 함)
        for (int j = i + 1; j < cnt; j++) {
            if (maxV - (visited[j] - 1) >= minV) chk[j] = 1; 
            //현재 그래프의 가장 멀리 있는 정점을 체크하고 다시 방문하지 않는다.
        }
    }
}




int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> R >> C;

    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            num[i][j] = 0;
            cin >> board[i][j];
        }
    }
    Solve();
    cout << minV << "\n";
    return 0;
}
