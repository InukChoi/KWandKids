#include <iostream>
#include <cstring>
using namespace std;
 
#define INF 987654321
#define MIN(a,b)(a<b?a:b)
int N, M;
 
int board[51][51];
int dp[51][51][51][51];
 
 
int Solve(int si, int sj, int ei, int ej)
{
    if (dp[si][sj][ei][ej] != -1)return dp[si][sj][ei][ej];
 
    if (si == ei && sj == ej)
    {
        dp[si][sj][ei][ej] = 0;
        return 0; //만약에 1x1이라면 0리턴
    }
    else
    {
 
        int csum = 0;
        //반복문으로 하면 시간초과
        //큰 사각형에서 작은 사각형을 빼주는 느낌
        csum = board[ei][ej] - board[si-1][ej] - board[ei][sj-1] + board[si-1][sj-1];
         
 
        //나눌 초콜릿의 크기 구하기
 
 
        int minSum = 987654321;
 
        if (si < ei) {
            for (int i = si; i < ei; i++) //i번째 행에서 나눈다
            {
                minSum = MIN(minSum, csum + Solve(si, sj, i, ej) + Solve(i + 1, sj, ei, ej));
            }
        }
 
        if (sj < ej) {
            for (int j = sj; j < ej; j++) { //j번째 행에서 나눈다
                minSum = MIN(minSum, csum + Solve(si, sj, ei, j) + Solve(si, j + 1, ei, ej));
            }
        }
 
        dp[si][sj][ei][ej] = minSum;
        return dp[si][sj][ei][ej];
    }
}
 
int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++)
    {
        cin >> N >> M;
        memset(board, 0, sizeof(board));
        memset(dp, -1, sizeof(dp));
        int csum = 0;
        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= M; j++)
            {
                cin >> board[i][j];
            }
        }
       //행의 누적합을 구한다
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M-1; j++) {
                board[i][j + 1] += board[i][j];
            }
        }
      //열의 누적합을 구한다
        for (int i = 1; i <= N-1; i++) {
            for (int j = 1; j <= M; j++) {
                board[i + 1][j] += board[i][j];
            }
        }
        csum = Solve(1, 1, N, M);
 
        cout << "#" << tc << " " << csum << "\n";
    }
    return 0;
}
