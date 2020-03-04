//백준의 이분그래프 문제와 거의 동일!
//대신 내전 경기는 인접행렬로 구현해도 딱히 문제가 없음 (101x101이 최대...가 맞나..? 여서 메모리 초과가 안나는듯...)
#include <iostream>
#include <cstring>
#include <map>
#include <queue>
using namespace std;
 
int K;
map<string, int> pIndex;
string player[201];
int syn[201][201];
int chk[201];
 
int pSize;
 
bool check()
{
    for(int i=0;i<pSize;i++)
    {
        for(int j=i+1;j<pSize;j++)
        {
            //if (i == j)continue;
            if (syn[i][j] && (chk[i] == chk[j]))return false;
        }
    }
    return true;
}
void BFS(int sV)
{
    int visited[201] = { 0, };
    bool flag = true;
    queue<int> q;
    q.push(sV);
    chk[sV] = 1; //1번으로 칠함
 
    while(!q.empty())
    {
        int ci = q.front();
        visited[ci] = 1;
        q.pop();
        for(int ni=0;ni<pSize;ni++)
        {
            if (ci == ni)continue;
            //만약 조합으로 묶여있는데 같은색이면 return false
            if (visited[ni])continue;
            if(syn[ci][ni]) //시너지 효과 발생
            {
                if (chk[ni] == -1)chk[ni] = !chk[ci];//반대 색칠
                q.push(ni);
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
        cin >> K;
        int index = 0;
        pIndex.clear();
        memset(syn, 0, sizeof(syn));
        memset(chk, -1, sizeof(chk));
        for(int i=0;i<K;i++)
        {
            string f, s;
            cin >> f >> s;
            if (pIndex.insert({ f,index }).second)
            {
                player[index] = f;
                index++;
            }
            if (pIndex.insert({ s,index }).second)
            {
                player[index] = s;
                index++;
            }
            int fi = pIndex[f];
            int si = pIndex[s];
 
            syn[fi][si] = 1;
            syn[si][fi] = 1;
        }
        pSize = pIndex.size();
         
        for(int i=0;i<pSize;i++)
        {
            if (chk[i] == -1)BFS(i);
        }
 
        bool result = check();
 
        cout << "#" << tc << " ";
        if (result)cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}
