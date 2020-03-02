#include<iostream>
#include<vector>
using namespace std;
int N, M, star_cnt, star_row_cnt[6], totcnt = 20, isvis_row[6][11], isvis_col[6][11], check_col_idx[11];
char map[6][11], backup_map[6][11];
vector<int> v_row[6];
 
void checkstar_col(int y, int x) { //세로줄 막대 가능한 위치 전부 확인
    int tmp_cnt = 0;
    while (tmp_cnt < 5 && map[y + tmp_cnt][x] == '*') //별개수 카운트
        tmp_cnt++;
     
    if (tmp_cnt == 5)   //5개일경우만 체크
        for (int k = 0; k < 5; k++)          
            isvis_col[y + k][x] = 1;        
}
 
void checkstar_row(int y, int x) {  //가로줄 막대 가능한 위치 전부 확인
    int tmp_cnt = 0;
    while (x + tmp_cnt <= M && map[y][x + tmp_cnt] == '*') //별 카운트
        tmp_cnt++;      
 
    if (tmp_cnt >= 5) { //5개 이상일경우 체크 
        v_row[y].push_back(x); //백터에 시작점만 저장
        for (int i = 0; i < tmp_cnt; i++) 
            isvis_row[y][x + i] = 1;  //위치 체크
    }
}
 
int counter_rowbar() { // 가로 막대 개수 구하기
    int res = 0;
    for (int r = 1; r <= N; r++) {
        if (v_row[r].empty())       continue;   //해당 행에 가로 막대를 놓을 위치가 없는경우
        if (star_row_cnt[r] == 0)   continue;   //별이 이미 다 지워진 경우
         
        int tmp_cnt = 0;
        for (int k = 0; k < v_row[r].size(); k++) {
 
            int cnt = 0;
            int tmp = v_row[r][k];
 
            for (int i = 0; i < 5; i++) 
                if (backup_map[r][tmp + i] == '*') //해당 막대로 가려지는 별 개수 체크
                    cnt++;          
 
            if (cnt == star_row_cnt[r]) { //하나의 막대로 다 가려지면 막대개수 1추가
                tmp_cnt = 1;
                break;
            }
        }
 
        if (tmp_cnt == 0) //하나로 안가려지면 막대 개수 2추가 (가로가 길이가 10이라 최대 개수 2개이다)
            tmp_cnt = 2;
 
        res += tmp_cnt;   //행 별 전부 합산
    }
 
    return res;
}
 
void dfs(int idx, int cnt) { //세로 막대 조합으로 선별
    if (cnt >= totcnt) //가지치기
        return;
 
    if (idx > M) { 
        for (int r = 1; r <= N; r++) {
            star_row_cnt[r] = 0;
            for (int c = 1; c <= M; c++) {
                if (check_col_idx[c] == 0 && map[r][c] == '*') { //선택한 세로 막대로 가려지고 남은 별들만 복사
                    backup_map[r][c] = '*';
                    star_row_cnt[r]++;          //행 별 별 개수 카운트
                }
                else
                    backup_map[r][c] = '.';
            }
        }
             
        int row_bar = counter_rowbar(); //가로 막대 개수 구하기
 
        if (cnt + row_bar < totcnt)  //최소값 출력
            totcnt = cnt + row_bar;
 
        return;
    }
 
    if (check_col_idx[idx])       //세로막대가 필수인 위치는 조합해서 패스
        dfs(idx + 1, cnt + 1);
    else if(isvis_col[1][idx]) {  //세로막대가 가능하나 위치인지 확인
        check_col_idx[idx] = 1;
        dfs(idx + 1, cnt +1);
        check_col_idx[idx] = 0;
        dfs(idx + 1, cnt);
    }
    else {                        //세로막대가 불가능한 위치는 선택 x
        check_col_idx[idx] = 0;
        dfs(idx + 1, cnt);
    }
}
 
 
int main() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) 
        for (int j = 1; j <= M; j++) {
            cin >> map[i][j];
            if (map[i][j] == '*') {
                star_cnt++;
                star_row_cnt[i]++;    //입력 값 별 카운트
            }
        }   
         
    for (int i = 1; i <= N; i++) 
        for (int j = 1; j <= M - 4; j++) //가로막대 가능한 위치 체크
            checkstar_row(i, j);    
         
    if(N == 5)
        for(int i = 1; i <= M; i++)      //세로막대 가능한 위치 체크
            checkstar_col(1, i);
 
    int judge = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (isvis_col[i][j] && !isvis_row[i][j])    //세로막대 가능 && 가로 막대 불가능 한 위치에 세로막대 조합 미리 선택
                check_col_idx[j] = 1;
 
            if (isvis_col[i][j] || isvis_row[i][j])     //세로,가로 막대로 가려지는 별 개수 카운트
                judge++;
        }
    }
 
    if (judge != star_cnt) {  //전부 다 안가려지면 -1 바로 출력
        cout << -1;
        return 0;
    }
                 
    if (N == 5)           //행이 5일경우 세로 막대 가로 막대 같이 계산
        dfs(1, 0);  
    else                  //행이 5미만일 경우 가로 막대만 계산
        totcnt = counter_rowbar();  
             
             
    cout << totcnt;   
    return 0;
}
