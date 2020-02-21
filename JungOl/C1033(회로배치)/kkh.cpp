#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int N, K, ncir_cnt, st[2], ed[2], Map[51][51], dp[51][51], my[4] = { 0,0,1,-1 }, mx[4] = { -1,1,0,0 };
queue<pair<int, int>> q;
struct parent {int y, x, dir;};
parent pp[51][51];
 
int main() {
    cin >> N;           //판 크기 N*N
    cin >> st[0] >> st[1] >> ed[0] >> ed[1];  //시작점 끝점
    cin >> K;     //비용
    cin >> ncir_cnt;  //기존 회로 개수
 
    for (int i = 0; i < ncir_cnt; i++) {
        int tmp_cnt, tmp_st[2], tmp_ed[2];
        cin >> tmp_cnt;
        cin >> tmp_st[0] >> tmp_st[1];    
 
        for (int j = 0; j < tmp_cnt - 1; j++) {
            cin >> tmp_ed[0] >> tmp_ed[1];
 
            if (tmp_st[0] == tmp_ed[0]) {
                int del = tmp_st[1] < tmp_ed[1] ? 1 : -1;                
 
                for (int k = tmp_st[1]; k != tmp_ed[1]; k+= del) { // 기존 회로 위치를 지도에 K(비용)으로 표시
                    if (Map[tmp_st[0]][k] == 0)
                        Map[tmp_st[0]][k] = K;
                    else
                        Map[tmp_st[0]][k] += K;
                }
            }
            else {
                int del = tmp_st[0] < tmp_ed[0] ? 1 : -1;
 
                for (int k = tmp_st[0]; k != tmp_ed[0]; k += del) {
                    if (Map[k][tmp_st[1]] == 0)
                        Map[k][tmp_st[1]] = K;
                    else
                        Map[k][tmp_st[1]] += K;
                }
            }
 
            tmp_st[0] = tmp_ed[0], tmp_st[1] = tmp_ed[1];
        }
 
        if (Map[tmp_ed[0]][tmp_ed[1]] == 0)
            Map[tmp_ed[0]][tmp_ed[1]] = K;
        else
            Map[tmp_ed[0]][tmp_ed[1]] += K;
    }
        
    for (int i = 1; i <= N; i++) 
        for (int j = 1; j <= N; j++)   //최소 거리를 위해 무한값으로 초기화
            dp[i][j] = INT32_MAX;
         
    q.push(make_pair(st[0], st[1]));
    dp[st[0]][st[1]] = 1;
     
    pp[st[0]][st[1]].y = st[0];
    pp[st[0]][st[1]].x = st[1];
    pp[st[0]][st[1]].dir = -1;
 
    while (!q.empty()) {        //최소거리 구하는 bfs 비용합산하여 가장 적은 비용의 루트 탐색
        pair<int, int> tmp = q.front();
        q.pop();
 
        for (int i = 0; i < 4; i++) {
            int yy = tmp.first + my[i];
            int xx = tmp.second + mx[i];
            if (yy <= N && yy > 0 && xx <= N && xx > 0) {
                if (Map[yy][xx] && dp[yy][xx] > dp[tmp.first][tmp.second] + Map[yy][xx]) {
                    dp[yy][xx] = dp[tmp.first][tmp.second] + Map[yy][xx];
                    q.push(make_pair(yy, xx));
 
                    pp[yy][xx].y = tmp.first;     //이동한 좌표점에 어디서부터 온건지 표시 (이전 좌표 및 방향)
                    pp[yy][xx].x = tmp.second;
                    pp[yy][xx].dir = i;
 
                }
                else if(Map[yy][xx] == 0 && dp[yy][xx] > dp[tmp.first][tmp.second] + 1) {
                    dp[yy][xx] = dp[tmp.first][tmp.second] + 1;
                    q.push(make_pair(yy, xx));
 
                    pp[yy][xx].y = tmp.first;
                    pp[yy][xx].x = tmp.second;
                    pp[yy][xx].dir = i;
                }
            }
        }
    }
 
    parent test;
    test.y = pp[ed[0]][ed[1]].y;
    test.x = pp[ed[0]][ed[1]].x;
    test.dir = pp[ed[0]][ed[1]].dir;  //저장했던 루트를 통해 끝점에서 부터 역으로 탐색
     
    vector <pair<int, int> > v;
    while (1) {
        if (test.y == st[0] && test.x == st[1])
            break;
 
        int tmpy = pp[test.y][test.x].y;
        int tmpx = pp[test.y][test.x].x;
        int tmpdir = pp[test.y][test.x].dir;
 
        if (test.dir != tmpdir) { //방향이 바뀌는 부분은 백터에 저장
            v.push_back({ test.y, test.x });
        }
 
        test.y = tmpy;
        test.x = tmpx;
        test.dir = tmpdir;
    }
 
    cout << dp[ed[0]][ed[1]] << "\n";
    cout << v.size() + 2 << " ";
    cout << st[0] << " " << st[1] << " ";
 
    int tmpcnt = v.size();
 
    for (int i = tmpcnt - 1; i >= 0; i--) { //시작점 부터 출력해야되기 때문에 뒤집어서 출력
        cout << v[i].first << " " << v[i].second << " ";
    }
    cout << ed[0] << " " << ed[1];
 
 
 
    return 0;
}
