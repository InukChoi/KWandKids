#include<stdio.h>
#include<iostream>
#include<queue>
#include<algorithm>
#include<cmath>

using namespace std;

int n, k;
int visited[1010];
pair<int, int> a_list[1010];
int ans;

/*
인터넷 참고해서 이분탐색 아이디어 얻어서 풀었습니다.
정올마지막테케 수정완료^ㅡ^
*/

int main() {
	scanf("%d %d", &n, &k);
	int temp = 0;
	for (int i = 1; i <= n; i++) {
		int t1, t2;
		scanf("%d %d", &t1, &t2);
		a_list[i]={ t1,t2 };
	}
	a_list[n + 1] = { 10000,10000 };

	int l = 1, r = 14144;
	
	while (l <= r) {
		queue<int> q1;
		queue<int> q2;
		int flag = 0, mid = (l + r) / 2;
		for (int i = 1; i <= n + 1; i++) {
			visited[i] = 0;
		}
		q1.push(0); q2.push(0);
		visited[0] = 1;

		while (!q1.empty()) {
			int cur = q1.front();
			int cnt = q2.front();
			q1.pop(); q2.pop();

			if (cur == n + 1) {
				flag = 1;
				break;
			}

			if (cnt == k + 1) {
				continue;
			}

			for (int i = 1; i <= n + 1; i++) {
				if (!visited[i] && mid*mid >= (a_list[cur].first - a_list[i].first)*(a_list[cur].first - a_list[i].first) + (a_list[cur].second - a_list[i].second)*(a_list[cur].second - a_list[i].second)) {
					visited[i] = 1;
					q1.push(i);
					q2.push(cnt + 1);
				}
			}
		}
		if (flag) {
			r = mid - 1;
		}
		else {
			l = mid + 1;
		}
	}

	if (l % 10 != 0) {
		ans = l / 10 + 1;
	}
	else {
		ans = l / 10;
	}

	printf("%d\n", ans);
	//system("pause");
	return 0;
}

