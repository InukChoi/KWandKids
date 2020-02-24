#include <iostream>
#include <queue>
using namespace std;
int M, N, H, tomoto[100][100][100], isvis[100][100][100], zero_cnt, max_Day;
int del_m[6] = { 1, 0, -1, 0, 0, 0 }, del_n[6] = { 0, 1, 0, -1, 0, 0 }, del_h[6] = { 0, 0, 0, 0, -1, 1 };
struct tmt{ int m, n, h;};
queue<tmt> q;
int main() {
    cin >> M >> N >> H;
 
    for (int h = 0; h < H; h++) 
        for (int n = 0; n < N; n++) 
            for (int m = 0; m < M; m++) {
                cin >> tomoto[m][n][h];
                if (tomoto[m][n][h] == 1) {
                    q.push({ m,n,h });
                    isvis[m][n][h] = 1; //토마토 위치 미리 방문점으로 표시  
                }
                else if (tomoto[m][n][h] == 0)
                    zero_cnt++;         // 제로 점 카운트
            }
     
    if (zero_cnt == 0) { //안익은 토마토 없으면 바로 출력
        cout << 0;
        return 0;
    }
 
    while (!q.empty()) {
        tmt TMT = q.front();
        q.pop();        
 
        for (int i = 0; i < 6; i++) { //상하앞뒤좌우 탐색
            int next_m = TMT.m + del_m[i];
            int next_n = TMT.n + del_n[i];
            int next_h = TMT.h + del_h[i];
 
            if (next_m >= 0 && next_m < M && next_n >= 0 && next_n < N && next_h >= 0 && next_h < H) {
                if (isvis[next_m][next_n][next_h] == 0 && tomoto[next_m][next_n][next_h] == 0) {
                    isvis[next_m][next_n][next_h] = isvis[TMT.m][TMT.n][TMT.h] + 1; //방문점에 1씩 추가해서 저장
                    tomoto[next_m][next_n][next_h] = 1;
 
                    zero_cnt--;         
                    if (max_Day < isvis[next_m][next_n][next_h])
                        max_Day = isvis[next_m][next_n][next_h];
 
                    q.push({ next_m, next_n, next_h });
                }
            }
        }
    }
 
    if (zero_cnt) //제로 갯수를 통해 완탐 됬는지 확인
        cout << - 1;
    else
        cout << max_Day - 1;
 
 
    return 0;
}
