#include<iostream>
#include<vector>
using namespace std;
int isgame[6][3], output[4], input[4][6][3];
vector<pair<int, int> > v;
 
void LLscore(int idx_input) { // 스코어 맞았는지 확인 idx_input : 입력 값 인덱스
    int flag = 1;
    for (int team = 0; team < 6; team++) 
        for (int score = 0; score < 3; score++) 
            if (input[idx_input][team][score] != isgame[team][score]) { //하나 틀리면 바로 탈출
                flag = 0;
                goto Exit;
            }   
 
Exit:
    if (flag)     //플래그 찍어서 결과 기록
        output[idx_input] = 1; 
}
 
void dfs(int idx, int idx_input) {
    if (idx == 15) { // 6팀이 할수 있는 경기 조합은 15경기
        LLscore(idx_input); //15경기 조합 맞춘후 스코어 비교
        return;
    }
    // v 에 경기 조합이 저장되어있음
    // 승리 vs 패배, 왼쪽팀의 승리값, 오른쪽 패배값 비교, 입력값보다 적은 상태일때만 추가 탐색( 0 : 승리갯수 , 1 : 무승부 갯수, 2: 패배갯수 )
    if (input[idx_input][v[idx].first][0] > isgame[v[idx].first][0] && input[idx_input][v[idx].second][2] > isgame[v[idx].second][2]) {
        isgame[v[idx].first][0]++;
        isgame[v[idx].second][2]++;
 
        dfs(idx + 1, idx_input);
 
        isgame[v[idx].first][0]--;
        isgame[v[idx].second][2]--;
    }
    //패배 vs 승리, 마찬가지로 입력과 비교하여 가지치기
    if (input[idx_input][v[idx].first][2] > isgame[v[idx].first][2] && input[idx_input][v[idx].second][0] > isgame[v[idx].second][0]) {
        isgame[v[idx].first][2]++;
        isgame[v[idx].second][0]++;
 
        dfs(idx + 1, idx_input);
 
        isgame[v[idx].first][2]--;
        isgame[v[idx].second][0]--;
    }
    //무승부 vs 무승부 비교
    if (input[idx_input][v[idx].first][1] > isgame[v[idx].first][1] && input[idx_input][v[idx].second][1] > isgame[v[idx].second][1]) {
        isgame[v[idx].first][1]++;
        isgame[v[idx].second][1]++;
 
        dfs(idx + 1, idx_input);
 
        isgame[v[idx].first][1]--;
        isgame[v[idx].second][1]--;
    }
     
     
}
 
 
int main() {
    for (int i = 0; i < 4; i++) 
        for (int team = 0; team < 6; team++) 
            for (int score = 0; score < 3; score++)          
                cin >> input[i][team][score];
 
    for (int i = 0; i < 5; i++) 
        for (int j = i + 1; j < 6; j++) //조합 경우의 수 백터에 추가 15개
            v.push_back({ i, j });
 
    for(int i = 0; i < 4; i++)
        dfs(0, i);
 
    for (int i = 0; i < 4; i++)
        cout << output[i] << " ";   
 
    return 0;
}
