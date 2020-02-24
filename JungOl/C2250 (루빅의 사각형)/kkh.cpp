#include<iostream>
using namespace std;
int input[4][4], min_depth = 7, ans[10][3], ans_tmp[10][3];
int origin[4][4] = { {1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16} };
//int test_sum[2][4] = { {10,26,42,58},{28,32,36,40} };
 

// 복잡도 계산 = 4개의 행, 열 1,2,3 칸 옮기기  = 2 * 4 * 3 = 24 최대 7번 ->> 24 ^ 7
// 맞은 원소 갯수를 통해 마지막 움직임과 마지막에서 두번째까지는 알수 있음 ->> 24 ^(7-2)
// 바로 이전 중복 위치 피하면 3가지 경우 피해서 21로 줄어둠


void dfs(int arr[][4], int depth, int isrow_move, int idx_move) { //(이전 배열, 뎁스, 이전에 행을 움직였는지, 어느 인덱스 움직였는지)
    if (min_depth <= depth)  // 최대 댑스 값으로 가지치기 
        return;
 
    int next_arr[4][4];
    int row_arr[4] = { 0 };
    int col_arr[4] = { 0 };
    int summ = 0, row_4 = 0, col_4 = 0; 
 
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            next_arr[i][j] = arr[i][j];
            if (next_arr[i][j] == origin[i][j]) { // 배열 백업 및 맞은 개수 카운트
                summ++;
                row_arr[i]++;
                col_arr[j]++;
 
                if (row_arr[i] == 4) // 원소 4개가 다 맞은 행 카운트
                    row_4++;
                if (col_arr[j] == 4) // 원소 4개가 다 맞은 열 카운트
                    col_4++;                
            }           
        }
    }
    
    if (summ < 12 && depth + 1 >= min_depth) //한번 회전으로 전부 맞출려면 한 줄을 뺀 12개 원소가 맞아야됨
        return;                              //12개 미만은 무조건 2번이상 회전을 해야됨 최대 댑스값과 비교하여 가지치기
 
    if (summ < 8 && depth + 2 >= min_depth)  //두번 회전으로 전부 맞추기 위해선 행,열을 회전 하는 9개
        return;                              //행행, 열열을 회전하는 8개가 필요 그아래로는 최소 3번이상 회전필요
     
     
     
    if (summ == 12 && (row_4 == 3 || col_4 == 3) ) { //12개가 맞고 3줄이 같은 경우, 한번의 회전만 남음, 뎁스 한층을 줄일 수 있음
        int idx_row = -1, idx_col = -1;
        for (int i = 0; i < 4; i++) {  //회전해야될 행,열 인덱스 탐색
            if (row_arr[i] == 0) {
                idx_row = i;
                break;
            }
 
            if (col_arr[i] == 0) {
                idx_col = i;
                break;
            }
        }
 
        for (int i = 0; i < depth; i++) { //뎁스 따라 저장 했던 회전 값들 최종 출력값에 저장
            ans[i][0] = ans_tmp[i][0];
            ans[i][1] = ans_tmp[i][1];
            ans[i][2] = ans_tmp[i][2];
        }
 
        if (idx_row != -1) { // 행을 회전할경우
            int move_cnt = next_arr[idx_row][0] - origin[idx_row][0]; //1열 위치를 빼면 회전값이 나옴
 
            ans[depth][0] = 1;
            ans[depth][1] = idx_row;
            ans[depth][2] = move_cnt; //최종 출력 값에 추가로 저장
        }
        else {
            int move_cnt = (next_arr[0][idx_col] - origin[0][idx_col]) / 4; //열은 4로 나눠야 됨
 
            ans[depth][0] = 2;
            ans[depth][1] = idx_col;
            ans[depth][2] = move_cnt;
        }
 
        min_depth = depth;
        return;
    }                                                           // 마지막 2번의 행열을 회전해야되는 경우 
    else if (summ == 9 && row_4 == 3 && col_4 == 3) {           // 복잡도 줄일려고 짠건데 위 가지치기로도 다 되는거 같다
        int idx_row = -1, idx_col = -1;                         // 아마 없어도 잘돌아갈듯?
        for (int i = 0; i < 4; i++) { //회전해야될 행열 찾기
            if (row_arr[i] == 0)
                idx_row = i;
            if (col_arr[i] == 0)
                idx_col = i;
        }
 
        for (int i = 0; i < depth; i++) {
            ans[i][0] = ans_tmp[i][0];
            ans[i][1] = ans_tmp[i][1];
            ans[i][2] = ans_tmp[i][2];
        }
        //먼저 회전해야될 행 or 열 찾기, 겹쳐진 부분 원소값을 비교해서 찾을 수 있음
        if (next_arr[idx_row][idx_col] >= idx_row * 4 + 1 && next_arr[idx_row][idx_col] < (idx_row + 1) * 4 + 1) {
      
      //행먼저 회전, 겹치는 원소값 비교로 회전값 구하기
            int move_cnt = next_arr[idx_row][idx_col] - origin[idx_row][idx_col];
            if (move_cnt < 0)
                move_cnt += 4;
 
            ans[depth][0] = 1;
            ans[depth][1] = idx_row;
            ans[depth][2] = move_cnt;
 
            for (int i = 0; i < 4; i++) {
                int ntmp = i + move_cnt;
                if (ntmp > 3)
                    ntmp -= 4;
 
                next_arr[idx_row][ntmp] = arr[idx_row][i]; //행 회전값 반영
            }
            
      //열 부분 회전 
            move_cnt = (next_arr[0][idx_col] - origin[0][idx_col]) / 4;
 
            ans[depth + 1][0] = 2;
            ans[depth + 1][1] = idx_col;
            ans[depth + 1][2] = move_cnt;
        }
           
    // 열먼저 회전 하는 경우 열행
        else {
            int move_cnt = (next_arr[idx_row][idx_col] - origin[idx_row][idx_col]) / 4;
            if (move_cnt < 0)
                move_cnt += 4;
 
            ans[depth][0] = 2;
            ans[depth][1] = idx_col;
            ans[depth][2] = move_cnt;
 
            for (int i = 0; i < 4; i++) {
                int ntmp = i + move_cnt;
                if (ntmp > 3)
                    ntmp -= 4;
 
                next_arr[ntmp][idx_col] = arr[i][idx_col];
            }
 
            move_cnt = next_arr[idx_row][0] - origin[idx_row][0];
 
            ans[depth + 1][0] = 1;
            ans[depth + 1][1] = idx_row;
            ans[depth + 1][2] = move_cnt;
        }
 
        min_depth = depth + 1;
        return;
    }
 
    /*  행행, 열열 회전하는 부분이지만 조건이 까다로워서 시간이 별루 안줄어듬
        주석 처리해도 잘 돌아감 
    else if (summ == 8 && (row_4 == 2 || col_4 == 2)) {
        int test_count = 0;
 
        if (row_4 == 2) { 
            for (int i = 0; i < 4; i++) {
                int ssss = 0;
                for (int j = 0; j < 4; j++) 
                    ssss += next_arr[i][j];
                 
                if (test_sum[0][i] == ssss)
                    test_count++;
            }
         
            if (test_count != 4)
                goto Pass;
        }
        else {
            for (int i = 0; i < 4; i++) {
                int ssss = 0;
                for (int j = 0; j < 4; j++)
                    ssss += next_arr[j][i];
 
                if (test_sum[1][i] == ssss)
                    test_count++;
            }
 
            if (test_count != 4)
                goto Pass;
        }   
     
        if (min_depth <= depth + 1)
            return;
 
        for (int i = 0; i < depth; i++) {
            ans[i][0] = ans_tmp[i][0];
            ans[i][1] = ans_tmp[i][1];
            ans[i][2] = ans_tmp[i][2];
        }
 
        int add_cnt = 0;
 
        for (int i = 0; i < 4; i++) {        
 
            if (row_arr[i] == 4) {
 
                int move_cnt = next_arr[i][0] - origin[i][0];
 
                ans[depth + add_cnt][0] = 1;
                ans[depth + add_cnt][1] = i;
                ans[depth + add_cnt][2] = move_cnt;
                add_cnt++;
 
            }
 
            if (col_arr[i] == 4) {
 
                int move_cnt = (next_arr[0][i] - origin[0][i]) / 4;
 
                ans[depth + add_cnt][0] = 2;
                ans[depth + add_cnt][1] = i;
                ans[depth + add_cnt][2] = move_cnt;
                add_cnt++;
 
            }
        }
 
        min_depth = depth + 1;
        return;
    }
 
    */
     
    //한칸씩 옮기면서 dfs로 배열 넣기 
    for (int nrow = 0; nrow <= 3; nrow++) {
        if (isrow_move == 1 && idx_move == nrow) //바로 이전에 움직였던 부분은 패스
            continue;
 
        for (int nsize = 1; nsize <= 3; nsize++) {
 
            int ntemp = next_arr[nrow][3];
            next_arr[nrow][3] = next_arr[nrow][2];
            next_arr[nrow][2] = next_arr[nrow][1];
            next_arr[nrow][1] = next_arr[nrow][0];
            next_arr[nrow][0] = ntemp;
            ans_tmp[depth][0] = 1;
            ans_tmp[depth][1] = nrow;
            ans_tmp[depth][2] = nsize;
            dfs(next_arr, depth + 1, 1, nrow);
        }
     
        int ntmp = next_arr[nrow][3];                   //4번 움직이면 원상복귀, 다음 행 그대로 회전
        next_arr[nrow][3] = next_arr[nrow][2];
        next_arr[nrow][2] = next_arr[nrow][1];
        next_arr[nrow][1] = next_arr[nrow][0];
        next_arr[nrow][0] = ntmp;
    }
 
    for (int ncol = 0; ncol <= 3; ncol++) {
        if (isrow_move == 0 && idx_move == ncol)
            continue;
 
        for (int nsize = 1; nsize <= 3; nsize++) {
 
            int ntemp = next_arr[3][ncol];
            next_arr[3][ncol] = next_arr[2][ncol];
            next_arr[2][ncol] = next_arr[1][ncol];
            next_arr[1][ncol] = next_arr[0][ncol];
            next_arr[0][ncol] = ntemp;
            ans_tmp[depth][0] = 2;
            ans_tmp[depth][1] = ncol;
            ans_tmp[depth][2] = nsize;
            dfs(next_arr, depth + 1, 0, ncol);
        }
 
        int ntmp = next_arr[3][ncol];
        next_arr[3][ncol] = next_arr[2][ncol];
        next_arr[2][ncol] = next_arr[1][ncol];
        next_arr[1][ncol] = next_arr[0][ncol];
        next_arr[0][ncol] = ntmp;
    }
}
 
 
int main() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            cin >> input[i][j];
    dfs(input, 0, -1, -1);
 
    cout << min_depth + 1 <<"\n";
 
    for (int i = 0; i <= min_depth; i++) 
        cout << ans[i][0] << " " << ans[i][1] + 1 << " " << ans[i][2] << "\n";
 
    return 0;
}
