#include<iostream>
using namespace std;
int nChar_cnt[26], char_size, ans_cnt;
char c[11];
 
void dfs(int cnt, int pastChar) {
    if (cnt == char_size) { //문자열 전부 사용했을 때만 카운트
        ans_cnt++;
        return;
    }
 
    for (int i = 0; i <= 25; i++) {
        if (pastChar == i)
            continue;
 
        if (nChar_cnt[i]) {
            nChar_cnt[i]--;
            dfs(cnt + 1, i);
            nChar_cnt[i]++;
        }
    }
}
 
int main() {
    scanf("%s", c);
     
    for (char_size = 0; c[char_size] != '\0'; char_size++) //문자열 입력 및 길이 확인
        nChar_cnt[c[char_size] - 'a']++;    
 
    dfs(0, -1);
    cout << ans_cnt;
 
    return 0;}
