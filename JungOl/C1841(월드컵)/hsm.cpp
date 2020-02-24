#include<stdio.h>
#include<iostream>
#include<vector>

using namespace std;

int ans;
int team[6][3];
pair<int, int> game[15] = {
	{0,1},{0,2},{0,3},{0,4},{0,5},{1,2},{1,3},{1,4},{1,5},{2,3},{2,4},{2,5},{3,4},{3,5},{4,5}
};

void dfs(int cnt) {
	if (ans == 1) {
		return;
	}

	if (cnt == 15) {
		ans = 1;
		return;
	}

	int t1 = game[cnt].first;
	int t2 = game[cnt].second;

	if (team[t1][0] > 0 && team[t2][2] > 0) {
		team[t1][0]--;
		team[t2][2]--;
		dfs(cnt + 1);
		team[t1][0]++;
		team[t2][2]++;
	}
	if (team[t1][2] > 0 && team[t2][0] > 0) {
		team[t1][2]--;
		team[t2][0]--;
		dfs(cnt + 1);
		team[t1][2]++;
		team[t2][0]++;
	}
	if (team[t1][1] > 0 && team[t2][1] > 0) {
		team[t1][1]--;
		team[t2][1]--;
		dfs(cnt + 1);
		team[t1][1]++;
		team[t2][1]++;
	}
}

int main() {
	for (int i = 0; i < 4; i++) {
		int sum = 0;
		ans = 0;
		for (int j = 0; j < 6; j++) {
			scanf(" %d %d %d", &team[j][0], &team[j][1], &team[j][2]);
			sum = sum + team[j][0] + team[j][1] + team[j][2];
		}
		
		if (sum != 30) {
			ans = 0;
		}
		else {
			dfs(0);
		}
		printf("%d\n", ans);
	}

	//system("pause");
	return 0;
}
