#include <iostream>
#include <cstring>
using namespace std;
 
int N, X, M;
 
int ham[7];
int result[7];
int chk[10][3];
int countA[7];
 
bool flag = false;
 
int getSum(int s, int e, bool tmp)
{
    int csum = 0;
     
    if (tmp) {
        for (int i = s; i <= e; i++)
        {
            csum += ham[i];
 
        }
    }
    else
    {
        for (int i = s; i <= e; i++)
        {
            csum += result[i];
 
        }
    }
    return csum;
}
 
void setHam(int cnt)
{
    if (cnt > N)
    {
        for (int i = 0; i < M; i++)
        {
            int s = chk[i][0];
            int e = chk[i][1];
            int comp = chk[i][2];
            if (comp != getSum(s, e,true)) return;
        }
        flag = true;//결과값이 더 클 경우에만 새로 갱신
        if (getSum(1, N, false) <= getSum(1, N, true)) { //<=로 한 이유는, 같은 경우가 있다면 사전 빠른순(오름차순?)으로 갱신.. 
            for (int i = 1; i <= N; i++)
            {
                result[i] = ham[i];
            }
        }
    }
    else
    {
        if (countA[cnt]==0)setHam(cnt + 1); //제약조건에 해당되지 않는 우리는 최댓값으로 초기화된 상태에서 바로 다음 depth로 넘어감
        else {
            for (int i = X; i >= 0; i--)
            {
                ham[cnt] = i;
                setHam(cnt + 1);
            }
        }
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
        cin >> N >> X >> M;
        flag = false;
         
        for (int i = 1; i <= N; i++)ham[i] = X;
        memset(result, 0, sizeof(result));
        for (int i = 0; i < M; i++)
        {
            cin >> chk[i][0] >> chk[i][1] >> chk[i][2];
            countA[chk[i][0]] = 1;
            countA[chk[i][1]] = 1;
        }
        setHam(1);
        cout << "#" << tc << " ";
        if(!flag)
            cout<<-1<<"\n";
        else
        {
            for (int i = 1; i <= N; i++)cout << result[i] << " ";
            cout << "\n";
        }
    }
    return 0;
}
