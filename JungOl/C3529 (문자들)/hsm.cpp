#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<cstring>
using namespace std;

int r, c;
int max_num = -1;
char map[22][22];
bool visited[22][22];
bool alph[26];

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

void dfs(int x, int y) {
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
	
		if (nx >= 0 && nx < r && ny >= 0 && ny < c) {
			if (!visited[nx][ny]) {
				if (!alph[map[nx][ny] - 'A']) {
					visited[nx][ny] = true;
					alph[map[nx][ny] - 'A'] = true;
					dfs(nx, ny);
					visited[nx][ny] = false;
					alph[map[nx][ny] - 'A'] = false;
				}
			}
		}
	}

	int cnt = 0;
	for (int k = 0; k < 26; k++) {
		if (alph[k] == true) {
			cnt++;
		}
	}
	if (max_num < cnt) {
		max_num = cnt;
	}
}

int main() {
	scanf("%d %d", &r, &c);
	for (int i = 0; i < r; i++) {
		string t;
		cin >> t;

		for (int j = 0; j < c; j++) {
			map[i][j] = t[j];
		}
	}

	visited[0][0] = true;
	alph[map[0][0] - 'A'] = true;
	dfs(0, 0);
		
	printf("%d\n", max_num);
	//system("pause");
	return 0;
}
