#include<iostream>
#include<string.h>
using namespace std;
int T, N, M, choco[51][51];
pair<int, int> dp[51][51][51][51]; //시작y, 시작x, 끝y, 끝x --> 영역에서 건포도 합, 아래 조각에서 건포도 합
pair<int, int> dfs(int st_y, int st_x, int ed_y, int ed_x) {
    if (st_y == ed_y && st_x == ed_x) //단일 영역일때 리턴
        return { choco[st_y][st_x], 0 };
 
    if (dp[st_y][st_x][ed_y][ed_x].second) //dp있으면 리턴
        return dp[st_y][st_x][ed_y][ed_x];
 
    int minn = INT32_MAX, summ = 0; 
    for (int mid = st_y; mid < ed_y; mid++) { //가로로 자르기 아래 조각에서 최소 건포도 수를 구한다.
        pair<int, int> tmp_1 = dfs(st_y, st_x, mid, ed_x);
        pair<int, int> tmp_2 = dfs(mid + 1, st_x, ed_y, ed_x);
         
        if (minn > tmp_1.second + tmp_2.second) {
            minn = tmp_1.second + tmp_2.second;
            summ = tmp_1.first + tmp_2.first;
        }
    }
    for (int mid = st_x; mid < ed_x; mid++) { //세로로 자르기
        pair<int, int> tmp_1 = dfs(st_y, st_x, ed_y, mid);
        pair<int, int> tmp_2 = dfs(st_y, mid + 1, ed_y, ed_x);
 
        if (minn > tmp_1.second + tmp_2.second) {
            minn = tmp_1.second + tmp_2.second;
            summ = tmp_1.first + tmp_2.first;
        }
    }       
    return dp[st_y][st_x][ed_y][ed_x] = { summ, minn + summ }; //아래 조각 +  현재 영역에서의 건포도 수를 합쳐서 저장
}
 
int main() {
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        scanf("%d%d", &N, &M);
        for (int r = 1; r <= N; r++) 
            for (int c = 1; c <= M; c++) 
                scanf("%d", &choco[r][c]);  
 
        memset(dp, 0, sizeof(dp));
        pair<int, int> res = dfs(1, 1, N, M);
        printf("#%d %d\n", tc, res.second);     //두번째만 출력
    }
    return 0;
}
