#include<stdio.h>
int R, C, isvis[20][20], dp[27], maxcnt, my[4] = { 0,0,1,-1 }, mx[4] = { 1,-1,0,0 };
char letter[20][20];

void dfs(int y, int x, int cnt) {
	if (maxcnt < cnt)
		maxcnt = cnt;

	for (int i = 0; i < 4; i++) {
		int next_y = y + my[i];
		int next_x = x + mx[i];

		if (next_y >= R || next_y < 0 || next_x >= C || next_x < 0)
			continue;
		if (!isvis[next_y][next_x] && !dp[letter[next_y][next_x] - 'A']) {
			isvis[next_y][next_x]++;
			dp[letter[next_y][next_x] - 'A']++;
			
			dfs(next_y, next_x, cnt + 1);

			isvis[next_y][next_x]--;
			dp[letter[next_y][next_x] - 'A']--;
		}	
	}
}

int main() {
	scanf("%d%d", &R, &C);
	for (int r = 0; r < R; r++)
		for (int c = 0; c < C; c++)
			scanf(" %c", &letter[r][c]);

	isvis[0][0]++;
	dp[letter[0][0] - 'A']++;
	dfs(0, 0, 1);

	printf("%d", maxcnt);
	return 0;
}
