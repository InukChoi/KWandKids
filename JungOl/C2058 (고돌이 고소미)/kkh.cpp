#include<iostream>
#include<queue>
using namespace std;
int N, Map[26][26], isvis[26][26][26][26], gosm_st_ed[4][2], min_sec = INT32_MAX;
 
struct gosm {int godol_y, godol_x, goso_y, goso_x, sec;};
gosm input_point[2];
queue<gosm> q;
 
void init() {
    for (int i = 1; i <= N; i++) 
        for (int j = 1; j <= N; j++) 
            for (int k = 1; k <= N; k++) 
                for (int h = 1; h <= N; h++) 
                    isvis[i][j][k][h] = INT32_MAX; //두개의 위치를 동시에 움직여야 함으로 4차원 배열 선언
}
 
 
void bfs(gosm START) {      
    q.push(START);
    isvis[START.godol_y][START.godol_x][START.goso_y][START.goso_x] = 0; //시작값 지정
 
    while (!q.empty()) {
        gosm tmp = q.front();
        q.pop();
 
        for (int del_y_godol = -1; del_y_godol <= 1; del_y_godol++) { //8방향 이동
            for (int del_x_godol = -1; del_x_godol <= 1; del_x_godol++) {
                //if (del_y_godol == 0 && del_x_godol == 0) continue; //제자리에 있는 경우도 포함해야 돌아갑니다
 
                int next_y_godol = tmp.godol_y + del_y_godol;         //고돌이 다음 이동점
                int next_x_godol = tmp.godol_x + del_x_godol;
 
                if (next_y_godol > N || next_y_godol < 1) continue;
                if (next_x_godol > N || next_x_godol < 1) continue;
                if (Map[next_y_godol][next_x_godol] != 0)   continue;
                 
                for (int del_y_goso = -1; del_y_goso <= 1; del_y_goso++) { //8방향 이동
                    for (int del_x_goso = -1; del_x_goso <= 1; del_x_goso++) {
 
                        //if (del_y_goso == 0 && del_x_goso == 0)   continue; //마찬가리로 제자리 경우도 포함
 
                        int next_y_goso = tmp.goso_y + del_y_goso;      //고순이 이동점
                        int next_x_goso = tmp.goso_x + del_x_goso;
 
                        if (next_y_goso > N || next_y_goso < 1)   continue;
                        if (next_x_goso > N || next_x_goso < 1)   continue;
                        if (Map[next_y_goso][next_x_goso] != 0) continue;
 
                        if (abs(next_y_godol - next_y_goso) > 1 || abs(next_x_godol - next_x_goso) > 1) {  
                        //서로 위치 비교 일정 거리 유지
                        //isvis은 시간 의미 작은 시간일 때만 갱신
                            if (isvis[next_y_godol][next_x_godol][next_y_goso][next_x_goso] > isvis[tmp.godol_y][tmp.godol_x][tmp.goso_y][tmp.goso_x] + 1) {
                                isvis[next_y_godol][next_x_godol][next_y_goso][next_x_goso] = isvis[tmp.godol_y][tmp.godol_x][tmp.goso_y][tmp.goso_x] + 1;
                               
                               //도착 안했을 경우만 계속 진행
                                if(next_y_godol != gosm_st_ed[1][0] || next_x_godol != gosm_st_ed[1][1] || next_y_goso != gosm_st_ed[3][0] || next_x_goso != gosm_st_ed[3][1])                      
                                    q.push({ next_y_godol, next_x_godol, next_y_goso, next_x_goso, tmp.sec + 1});
                            }                         
                        }
                    }
                }
            }
        }
    }
}
 
int main() {
    cin >> N;
 
    for (int i = 0; i < 4; i++)
        cin >> gosm_st_ed[i][0] >> gosm_st_ed[i][1];
 
    for (int i = 1; i <= N; i++) 
        for (int j = 1; j <= N; j++) 
            cin >> Map[i][j];
         
    init(); //방문점 무한대로 초기화
    
    bfs({ gosm_st_ed[0][0], gosm_st_ed[0][1], gosm_st_ed[2][0],gosm_st_ed[2][1] }); //고돌이, 고순이 시작 위치 입력
 
    min_sec = isvis[gosm_st_ed[1][0]][gosm_st_ed[1][1]][gosm_st_ed[3][0]][gosm_st_ed[3][1]];
 
    cout << min_sec;
     
    return 0;
}
