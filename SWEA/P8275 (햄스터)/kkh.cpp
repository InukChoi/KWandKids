#include<stdio.h>
int T, N, X, M, report[10][3], ham[8];
int main() {
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        scanf("%d%d%d", &N,&X,&M);
        for (int i = 0; i < M; i++) 
            scanf("%d%d%d", &report[i][0], &report[i][1], &report[i][2]);
 
        ham[N + 1] = 1;
        for (int i = 1; i <= N; i++)
            ham[i] = X;
         
        int tmp[3], tmp_sum, flag = 1;
        while (ham[N + 1]) {
            flag = 1;
 
            for (int i = 0; i < M; i++) {
                tmp[0] = report[i][0];
                tmp[1] = report[i][1];
                tmp[2] = report[i][2];
 
                tmp_sum = 0;
 
                for (int idx = tmp[0]; idx <= tmp[1]; idx++) 
                    tmp_sum += ham[idx];
                 
                if (tmp_sum != tmp[2]) {
                    flag = 0;
                    break;
                }
            }
            if (flag) 
                break;
             
            ham[1]--;
            for (int idx = 1; idx <= N; idx++) {
                if (ham[idx] < 0) {
                    ham[idx] = X;
                    ham[idx + 1]--;
                }
            }
        }
        printf("#%d ",tc);
 
        if (flag) {
            for (int i = 1; i <= N; i++)
                printf("%d ", ham[i]);
        }
        else
            printf("-1");
         
        printf("\n");
    }
    return 0;
}

