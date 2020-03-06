#include<iostream>
#include<queue>
#include<string.h>
using namespace std;
int T, N, M, isvis[2001][2001];
char c[2001][2001], res[5000];

struct info {
	int y, x;
	char c;
};

void init() {
	memset(isvis, 0, sizeof(isvis));
	for (int i = 1; i < N + M; i++)
		res[i] = 'z';
}

void bfs() {
	init();

	queue<info> q;
	info INFO;
	INFO.y = 1;
	INFO.x = 1;
	INFO.c = c[1][1];	

	q.push(INFO);
	res[1] = c[1][1]; //시작점
	isvis[1][1] = 1;

	info tmp_info;

	while (!q.empty()) {
		info tmp = q.front();
		q.pop();

		if (tmp.y == N && tmp.x == M)
			break;

		int idx = isvis[tmp.y][tmp.x]; //순서 인덱스, 이동할때마다 1씩 증가
		if (res[idx] < tmp.c)	continue; // 최종 저장된 글자보다 느린 순서는 가지치기

		if (tmp.y + 1 <= N && !isvis[tmp.y + 1][tmp.x]) { // 아래로 이동
			isvis[tmp.y + 1][tmp.x] = idx + 1;
			tmp_info.y = tmp.y + 1;
			tmp_info.x = tmp.x;
			tmp_info.c = c[tmp.y + 1][tmp.x];
			if (res[idx + 1] >= tmp_info.c) { //해당 위치 이름 값 계속 갱신
				res[idx + 1] = tmp_info.c;

				q.push(tmp_info);
			}
		}

		if (tmp.x + 1 <= M && !isvis[tmp.y][tmp.x + 1]) { // 오른쪽으로 이동
			isvis[tmp.y][tmp.x + 1] = idx + 1;
			tmp_info.y = tmp.y;
			tmp_info.x = tmp.x + 1;
			tmp_info.c = c[tmp.y][tmp.x + 1];
			if (res[idx + 1] >= tmp_info.c) {
				res[idx + 1] = tmp_info.c;

				q.push(tmp_info);
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N >> M;
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= M; j++)
				cin >> c[i][j];
			
		bfs();

		cout << "#" << tc << " ";
		for (int i = 1; i < N + M; i++)
			cout << res[i];
		cout << "\n";
	}
	return 0;
}
