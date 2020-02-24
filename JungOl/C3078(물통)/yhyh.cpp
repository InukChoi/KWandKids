#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define INF 987654321

int N, M, eX, eY;

vector<vector<int>> watersR;
vector<vector<int>> watersC;

int getDist(int crow, int ccol)
{
    int ndist = INF;

    if (crow == 0||crow==N)
    {
        ndist = watersR[crow/N][ccol] + 1;
    }
    
    else if (ccol == 0||ccol==M)
    {
        ndist = watersC[ccol/M][crow] + 1;
    }
    return ndist;
}

int main()
{
    cin >> N >> M;
    watersR.resize(2, vector<int>(M + 1, INF)); //행 우선
    watersC.resize(2, vector<int>(N + 1, INF)); //열 우선

    cin >> eX >> eY;

    queue<pair<int, int>> pq;
    pq.push({ 0,0 });
    watersR[0][0] = 0;
    watersC[0][0] = 0;

    while (!pq.empty())
    {
        int crow = pq.front().first;
        int ccol = pq.front().second;

        pq.pop();

        int ndist = getDist(crow, ccol); //그다음 거리 구하기
        int nrow, ncol;
        for (int i = 0; i < 6; i++)
        {
            nrow = crow;
            ncol = ccol;
            switch (i)
            {
            case 0://FillA
                nrow = N;
                break;
            case 1://FillB
                ncol = M;
                break;
            case 2://EmptyA
                nrow = 0;
                break;
            case 3://EmptyB
                ncol = 0;
                break;
            case 4://Move(A,B)
                if (nrow <= M - ncol)
                {
                    ncol += nrow;
                    nrow = 0;
                }
                else
                {
                    nrow -= (M - ncol);
                    ncol = M;
                }
                break;
            case 5://Move(B,A)
                if (ncol <= N - nrow)
                {
                    nrow += ncol;
                    ncol = 0;
                }
                else
                {
                    ncol -= (N - nrow);
                    nrow = N;
                }
                break;
            }

            if(nrow==0||nrow==N)
            {
                if (ndist < watersR[nrow/N][ncol])
                {
                    watersR[nrow/N][ncol] = ndist;
                    pq.push({ nrow,ncol });
                }
            }

            if(ncol==0||ncol==M)
            {
                if (ndist < watersC[ncol/M][nrow])
                {
                    watersC[ncol/M][nrow] = ndist;
                    pq.push({ nrow,ncol });
                }
            }

        }
    }
    int result = INF;
    if (eX == 0)
    {
        result = watersR[0][eY];
    }
    if (eX == N)
    {
        result = watersR[1][eY];
    }
    if (eY == 0)
    {
        result = watersC[0][eX];
    }
    if (eY == M)
    {
        result = watersC[1][eX];
    }
    if (result == INF)result = -1;
    cout << result << "\n";
    return 0;
}
