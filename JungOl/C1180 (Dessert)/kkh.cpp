#include <iostream>
using namespace std;
int N, outputCnt, oper[20];
 
void dfs(int n) {
    if (n == N) {   
        int summ = 0;
        int num = 1;  //+,- 사이에 있는 숫자를 임시 저장
        int tmp = -5; // +,- 값을 임시 저장
 
        for (int i = 2; i <= N; i++) {  //N자리 합산 ,   sum (tmp) num (oper[i]) 형태 연산자 단위로 끈어서 계산  
            if (oper[i] == -1 || oper[i] == -2) { 
     
                if (tmp == -1) //이전 연산자가 -1( + ) 인 경우
                    summ += num; 
                else if (tmp == -2) //이전 연산자가 -2( - ) 인 경우
                    summ -= num;
                else
                    summ = num;  //초기값 때문에 추가
 
                tmp = oper[i], num = i; //임시저장 값들 교체
            }
            else { //연산자가 . 일 경우 숫자 합치기 num에 저장
                i >= 10 ? num = num * 100 + i : num = num * 10 + i;                              
            }
        }
 
        if (tmp == -1)
            summ += num;
        else if (tmp == -2)
            summ -= num;
        else
            summ = num;        
 
        if (summ == 0) {
            if (outputCnt < 20) { //출력
                cout << 1;
                for (int i = 2; i <= N; i++) {
                    if (oper[i] == -1)
                        cout << " + " << i;
                    else if (oper[i] == -2)
                        cout << " - " << i;
                    else if (oper[i] == -3)
                        cout << " . " << i;
                }
                cout << "\n";
            }
            outputCnt++;
        }
        return;
    }
     
    for (int i = -1; i >= -3; i--) {  //연산자 순열 구하기
        oper[n + 1] = i;
        dfs(n + 1);
    }
}
 
int main() {
    cin >> N;
    dfs(1);
    cout << outputCnt;    
    return 0;
}
