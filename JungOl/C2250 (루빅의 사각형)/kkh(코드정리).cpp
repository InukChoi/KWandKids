#include<iostream>
using namespace std;
int input[4][4], min_depth = 7, ans[10][3], ans_tmp[10][3];
int origin[4][4] = { {1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16} };

void dfs(int arr[][4], int depth, int isrow_move, int idx_move) { 
    if (min_depth <= depth)  
        return;
 
    int next_arr[4][4];
    int row_arr[4] = { 0 };
    int col_arr[4] = { 0 };
    int summ = 0, row_4 = 0, col_4 = 0; 
 
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            next_arr[i][j] = arr[i][j];
            if (next_arr[i][j] == origin[i][j]) { 
                summ++;
                row_arr[i]++;
                col_arr[j]++;
 
                if (row_arr[i] == 4) 
                    row_4++;
                if (col_arr[j] == 4) 
                    col_4++;                
            }           
        }
    }
    
    if (summ < 12 && depth + 1 >= min_depth) 
        return;
    if (summ < 8 && depth + 2 >= min_depth)  
        return;  
     
    if (summ == 12 && (row_4 == 3 || col_4 == 3) ) {
        int idx_row = -1, idx_col = -1;
        for (int i = 0; i < 4; i++) {  
            if (row_arr[i] == 0) {
                idx_row = i;
                break;
            } 
            if (col_arr[i] == 0) {
                idx_col = i;
                break;
            }
        }
 
        for (int i = 0; i < depth; i++) { 
            ans[i][0] = ans_tmp[i][0];
            ans[i][1] = ans_tmp[i][1];
            ans[i][2] = ans_tmp[i][2];
        }
 
        if (idx_row != -1) { 
            int move_cnt = next_arr[idx_row][0] - origin[idx_row][0];            
            ans[depth][0] = 1;
            ans[depth][1] = idx_row;
            ans[depth][2] = move_cnt; 
        }
        else {
            int move_cnt = (next_arr[0][idx_col] - origin[0][idx_col]) / 4;  
            ans[depth][0] = 2;
            ans[depth][1] = idx_col;
            ans[depth][2] = move_cnt;
        } 
        min_depth = depth;
        return;
    }
   
    for (int nrow = 0; nrow <= 3; nrow++) {
        if (isrow_move == 1 && idx_move == nrow) 
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
     
        int ntmp = next_arr[nrow][3];                   
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
