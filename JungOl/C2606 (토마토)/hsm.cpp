#include<stdio.h>
#include<iostream>
#include<deque>
#include<cstring>

using namespace std;

struct Tomato
{
	int x, y, z, t;
};

int m, n, h;
int cnt;
int map[100][100][100];
int visited[100][100][100];
deque<Tomato> q;

int dx[] = { 1,-1,0,0,0,0 };
int dy[] = { 0,0,1,-1,0,0 };
int dz[] = { 0,0,0,0,1,-1 };

int main() {
	cnt = 0;
	scanf("%d %d %d", &m, &n, &h);
	memset(map, -1, sizeof(map));
	memset(visited, 0, sizeof(visited));

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < m; k++) {
				scanf(" %d", &map[k][j][i]);
				if (map[k][j][i] == 1) {
					q.push_back({ k,j,i,0 });
					visited[k][j][i] = 1;
				}
				if (map[k][j][i] == 0) {
					cnt++;
				}
			}
		}
	}

	int ans;
	if (cnt == 0) {
		printf("%d\n", cnt);
		//system("pause");
		return 0;
	}

	while (!q.empty()) {
		int x = q.front().x;
		int y = q.front().y;
		int z = q.front().z;
		int tt = q.front().t;
		q.pop_front();

		if (cnt <= 0) {
			ans = tt;
			break;
		}

		for (int i = 0; i < 6; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			int nz = z + dz[i];

			if (nx >= 0 && nx < m&& ny >= 0 && ny < n && nz >= 0 && nz < h) {
				if (visited[nx][ny][nz] == 1) {
					continue;
				}

				if (map[nx][ny][nz] == -1) {
					continue;
				}

				cnt--;
				visited[nx][ny][nz] = 1;
				q.push_back({ nx,ny,nz,tt + 1 });
			}
      
			if (cnt <= 0) {
				break;
			}
		}
    
		if (cnt <= 0) {
			ans = tt + 1;
			break;
		}
	}
  
	if (cnt != 0) {
		printf("%d\n", -1);
	}
	else {
		printf("%d\n", ans);
	}

	//system("pause");
	return 0;
}
