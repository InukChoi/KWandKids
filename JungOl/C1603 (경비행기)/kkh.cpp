#include<iostream>
#include<queue>
#include<math.h>
using namespace std;
int N, K, land[1002][2], dp[1002], _MIN = 10000 * 10000 + 10000 * 10000;
int len_last[1001];
queue<pair<int, int> > q; // idx, cnt
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> K;
 
    int len_y, len_x, len[2];
 
    for (int i = 1; i <= N; i++) {
        cin >> land[i][1] >> land[i][0]; //x값 y값
 
        len_y = 10000 - land[i][0];
        len_x = 10000 - land[i][1];
        len_last[i] = len_y * len_y + len_x * len_x;    //각 섬에서 10000, 10000 까지의 거리 미리계산
 
        dp[i] = _MIN;
    }
             
    //현재까지 이동한거리 중 최장 거리를 저장(누적X)
    dp[N + 1] = _MIN;
 
    q.push({0, 0});
 
    len_last[0] = _MIN;
    land[N + 1][0] = 10000;
    land[N + 1][1] = 10000;
 
    while (!q.empty()) {
        int idx = q.front().first;
        int cnt = q.front().second;
         
        q.pop();
                                 
        if (dp[idx] >= dp[N + 1]) // 최소값보다 같거나 큰경우 패스
            continue;
 
        if (cnt == K) {           //K번째 섬에 도착한경우 무조건 10000, 10000으로 이동
            int max_len = dp[idx] > len_last[idx] ? dp[idx] : len_last[idx]; //현재까지의 이동 중 가장 큰 값
            if (dp[N + 1] > max_len) //가장 큰값이 dp보다 작으면 갱신
                dp[N + 1] = max_len;
        }
        else if (cnt < K) {
            for (int i = 1; i <= N; i++) {               
                if (dp[idx] >= dp[i]) //이동하려는 섬의 dp(최장 이동거리)가 더 작으면 이동 하지 않음
                    continue;
 
                int len_y = abs(land[idx][0] - land[i][0]);
                int len_x = abs(land[idx][1] - land[i][1]);
                int length = len_y * len_y + len_x * len_x;
 
                int max_len = length > dp[idx] ? length : dp[idx]; // 최장 이동거리 구하기
 
                if (dp[i] > max_len && dp[N + 1] > max_len) { //최장 이동거리가 더 작을 경우만 갱신
                    dp[i] = max_len;
                    q.push({ i, cnt+1 });
                }
            }
 
            int max_len = dp[idx] > len_last[idx] ? dp[idx] : len_last[idx]; //K번째 전에 바로 목적지로 가는 거리도 항상 계산
            if (dp[N + 1] > max_len)
                dp[N + 1] = max_len;
        }   
    }
     
    double ans = sqrt(dp[N + 1]) / 10; //최장거리를 연료 용량으로 환산
    cout << ceil(ans);                 //환산값 올림으로 출력
        
    return 0;
}
