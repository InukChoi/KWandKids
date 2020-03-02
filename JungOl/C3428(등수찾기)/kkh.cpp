#include<iostream>
#include<vector>
using namespace std;
int N, M, X, isvis_down[100001], isvis_up[100001], cnt_down, cnt_up;
vector<int> v_down[100001];
vector<int> v_up[100001];
  
void dfs_down(int idx) {
    for (int i = 0; i < v_down[idx].size(); i++) {
        int tmp = v_down[idx][i];
  
        if (isvis_down[tmp] == 0) {
            isvis_down[tmp] = 1;
            dfs_down(tmp);
        }
    }
}
  
void dfs_up(int idx) {
    for (int i = 0; i < v_up[idx].size(); i++) {
        int tmp = v_up[idx][i];
  
        if (isvis_up[tmp] == 0) {
            isvis_up[tmp] = 1;
            dfs_up(tmp);
        }
    }
}
  
int main() {
    cin >> N >> M >> X;
    int a, b;
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        v_down[a].push_back(b);
        v_up[b].push_back(a);
    }
  
    dfs_up(X);
    dfs_down(X);
  
    for (int i = 1; i <= 100000; i++) {
        if (isvis_down[i])
            cnt_down++;     
    
        if (isvis_up[i])
            cnt_up++;
    }
  
    cout << cnt_up + 1 << " " << N - cnt_down;
  
    return 0;
}
