#include<stdio.h>
#include<string.h>
int T, K, IdxCnt, synergy[200][200], isvis[200];
int q[3000], nfront, nend;
char strIndex[200][51];
 
void init() {
    memset(synergy, 0, sizeof(synergy));    
    memset(isvis, 0, sizeof(isvis));
    IdxCnt = nfront = nend = 0;
}
 
void saveName(char* str1, char* str2) {
    int flag1 = 1, flag2 = 1, idx1, idx2;
    for (int i = 0; i < IdxCnt; i++) {
        if (flag1 && strcmp(strIndex[i], str1) == 0) {
            flag1 = 0;
            idx1 = i;
        }
        if (flag2 && strcmp(strIndex[i], str2) == 0) {
            flag2 = 0;
            idx2 = i;
        }
    }
    if (flag1) {
        strcpy(strIndex[IdxCnt], str1);
        idx1 = IdxCnt++;
    }
    if (flag2) {
        strcpy(strIndex[IdxCnt], str2);
        idx2 = IdxCnt++;
    }
 
    synergy[idx1][idx2] = 1;
    synergy[idx2][idx1] = 1;
}
 
void bfs() {
    q[nend++] = 0;
    isvis[0] = 1;
    register int tmp, otherteam;
    while (nfront != nend) {
        tmp = q[nfront++];
        otherteam = isvis[tmp] == 1 ? 2 : 1;
        for (register int i = 0; i < IdxCnt; i++) {
            if (isvis[i] == 0 && synergy[tmp][i]) {
                isvis[i] = otherteam;
                q[nend++] = i;
            }
        }
    }
}
 
int judge() {
    for (register int i = 0; i < IdxCnt; i++)
        for (register int k = 0; k < IdxCnt; k++)
            if (isvis[i] == isvis[k] && synergy[i][k]) 
                return 0;   
 
    return 1;
}
 
int main() {    
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {    
        init();
 
        scanf("%d", &K);
        char strInput_1[51], strInput_2[51];
        for (int k = 0; k < K; k++) {
            scanf(" %s %s", strInput_1, strInput_2);            
            saveName(strInput_1, strInput_2);
        }
        bfs();
 
        if (judge())
            printf("#%d Yes\n", tc);
        else
            printf("#%d No\n", tc);
    }
    return 0;
}
