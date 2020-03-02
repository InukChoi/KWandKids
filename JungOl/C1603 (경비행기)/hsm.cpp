#include<stdio.h>
#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int n, k;
int sx, sy, ex, ey; //시작지점, 끝지점
int ans = 987654321;

queue<pair<int, int>> q;

vector<pair<int, int>> v; //n개의 경유지들 좌표
vector<int> d; //data 0~n-1 저장되어서 v의 인덱스 표시하기 위해 만든 변수

/*
부분집합 구하는 함수로 k개이하일때 경로를 구해 작은 연료통 값을 ans에 대입하는 방식으로
생각했는데ㅠㅠㅠ..시간 초과가 뜨네요 8ㅡ8 우선 더 고민해볼게요...
*/

void make_answer(queue<int> q) {
	int oil = -1;
	while (!q.empty()) {
		//printf("q: %d\n", q.front());
		int x = v[q.front()].first;
		int y = v[q.front()].second;
		q.pop();
		//printf("x,y: %d %d\n", x, y);

		int tmp = floor(sqrt((sx - x)*(sx - x) + (sy - y)*(sy - y)));
		if (tmp % 10 != 0) {
			tmp = tmp / 10 + 1;
		}
		else {
			tmp /= 10;
		}

		//printf("tmp: %d\n", tmp);
		if (oil < tmp) {
			oil = tmp;
		}
		
		sx = x;
		sy = y;
	}

	int tmp = floor(sqrt((sx - ex)*(sx - ex) + (sy - ey)*(sy - ey)));
	if (tmp % 10 != 0) {
		tmp = tmp / 10 + 1;
	}
	else {
		tmp /= 10;
	}
	//printf("tmp: %d\n", tmp);
	if (oil < tmp) {
		oil = tmp;
	}

	//printf("\n%d\n---------------\n", oil);
	if (ans > oil) {
		ans = oil;
	}
}

void powerset(int n) {
	int max = 1 << n;
	for (int i = 0; i < max; i++) {
		queue<int> tmp;
		sx = 0, sy = 0, ex = 10000, ey = 10000;
		for (int j = 0; j < n; j++) {
			if (i&(1 << j)) {
				tmp.push(d[j]);
			}
		}
		if (tmp.size()<=k) {
			make_answer(tmp);
		}
	}
}

int main() {
	scanf("%d %d", &n, &k);
	int temp = 0;
	for (int i = 0; i < n; i++) {
		int t1, t2;
		scanf("%d %d", &t1, &t2);
		v.push_back({ t1,t2 });
		d.push_back(temp++);
		f.push_back(0);
	}
	
	powerset(d.size());
	
	printf("%d\n", ans);
	//system("pause");
	return 0;
}
