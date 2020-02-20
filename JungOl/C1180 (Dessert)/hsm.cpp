#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;

int n, sum, ans, cnt;
vector<int> v;
int operate[17]; //0:+, 1:-, 2:.

void dfs(int x) {
	operate[cnt] = x;

	//cnt: 연산자 후보군
	//sum: 후보군에서 주어진 수식 결과값
	if (cnt == n - 2) {
		sum = v[0];
		for (int i = 1; i < n; i++) {
			if (operate[i - 1] == 0) {
				int t1 = i;
				if(operate[t1] == 2) {
					int temp = v[t1];
					while (1) {
						temp *= 10;
						if (v[t1+1] >= 10) {
							temp *= 10;
						}	
						temp += v[t1 + 1];
						if (operate[t1 + 1] != 2) {
							break;
						}
						t1++;
					}
					sum += temp;
					i = t1 + 1;
					continue;
				}
				sum += v[i];
			}
			else if (operate[i - 1] == 1) {
				int t1 = i;
				if (operate[t1] == 2) {
					int temp = v[t1];
					while (1) {
						temp *= 10;
						if (v[t1 + 1] >= 10) {
							temp *= 10;
						}
						temp += v[t1 + 1];
						if (operate[t1 + 1] != 2) {
							break;
						}
						t1++;
					}
					sum -= temp;
					i = t1 + 1;
					continue;
				}
				sum -= v[i];
			}
			else if (operate[i - 1] == 2) {
				sum *= 10;
				if (v[i] >= 10) {
					sum *= 10;
				}
				sum += v[i];
			}
		}

		//수식 출력
		if (sum == 0) {
			ans++;
			if(ans>20){
				return;
			}
			printf("%d ", v[0]);
			for (int i = 1; i < n; i++) {
				if (operate[i - 1] == 0) {
					printf("+ %d ",v[i]);
				}
				else if (operate[i - 1] == 1) {
					printf("- %d ", v[i]);
				}
				else if (operate[i - 1] == 2) {
					printf(". %d ", v[i]);
				}
			}
			printf("\n");
		}
		return;
	}

	//다음 dfs()
	for (int i = 0; i < 3; i++) {
		if (cnt <= n - 2) {
			cnt++; 
			operate[cnt] = i;
			dfs(i);
			cnt--;
		}
	}
}
int main() {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		v.push_back(i);
	}

	memset(operate, -1, sizeof(operate));
	ans = 0;

	//dfs(첫번째 연산자(+,-,.))
	//문제에서는 소가 순차적으로 줄을 섰지만 
	//랜덤으로 줄 세우는 문제가 있을 수도 있어서 순열 썼음 (현재는 break해 놓음)
	do {
		cnt = 0;
		for (int i = 0; i < 3; i++) {
			dfs(i);
		}
		break;
	} while (next_permutation(v.begin(), v.end()));

	printf("%d\n", ans);
	return 0;
}
