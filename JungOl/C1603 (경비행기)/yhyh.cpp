//https://beginthread.tistory.com/41 (참고해서 해결)

#include <iostream>
#include <cmath>
using namespace std;

#define MAX(a,b)(a>b?a:b)
#define MIN(a,b)(a<b?a:b)

bool visited[1001];

int N, K;
int refuels[1002][2];

int fuel; //전역변수로

int calc(int sI, int eI) //필요한 연료랑을 리턴
{
    double sX = refuels[sI][0];
    double sY = refuels[sI][1];
    double eX = refuels[eI][0];
    double eY = refuels[eI][1];

    double comp;
    comp = (sX - eX) * (sX - eX) + (sY - eY) * (sY - eY); //sqrt는 연산시간이 너무 많아서 생략
    return comp;
}

bool DFS(int i,int K)
{
    if (K < 1)return false;
    visited[i] = true; //방문했음을 표시
    for(int j=1;j<=N;j++)
    {
        if ((!visited[j]&&calc(i, j) <= fuel) && (calc(j, N + 1) <= fuel||DFS(j,K-1)))return true;
        //i부터 j까지가 연료통을 넘지 않는지 (1)
        //j부터 j+1, j+2, ..., N+1까지가 연료통을 넘지 않는지
    }
    return false;
}

int main()
{
    cin >> N >> K;
    for (int i = 1; i <= N; i++)
    {
        visited[i] = false;
        cin >> refuels[i][0] >> refuels[i][1];
    }
    refuels[0][0] = refuels[0][1] = 0;
    refuels[N + 1][0] = refuels[N + 1][1] = 10000;

    int left = 1;
    int right = 14414;//최대용량

    while(left<=right) //연료통을 binary Search로 지정해준 후, 가능한지를 판별하여 범위를 축소해나간다.
    {
        for (int i = 1; i <= N; i++)
        {
            visited[i] = false;
        }
        int mid = (left + right) / 2; //연료통을 미리 지정해둠
        fuel = mid * mid * 100; //연료통 지정
        if (DFS(0, K))right = mid - 1;//가능하다면 현재보다 작은값에서 찾아봄
        else left = mid + 1; //불가능하다면 현재보다 큰값에서 찾아봄
    }

    cout << left << "\n";
    return 0;
}
