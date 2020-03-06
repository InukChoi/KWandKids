#include<iostream>
#include<string.h>
using namespace std;
int T, N, M, isvis[2001][2001];
char c[2001][2001], res[5000];
pair<int, int> st, st_tmp;

void init() {
	memset(isvis, 0, sizeof(isvis));
	for (int i = 1; i < N + M; i++)		
		res[i] = 'z';	
	
	isvis[1][1] = 1;
	res[1] = c[1][1];
	st = { 1, 1 };
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
		
		init();
		                                            
		for (int idx = 2; idx < N + M; idx++) {			//1,1 에서 오른쪽아래로 사선으로 스캔하면서 거리 탐색
			st.second == M ? st.first++ : st.second++; // 맨위 시작값 갱신

			st_tmp = st;
			while (st_tmp.first <= N && st_tmp.second > 0) { //사선으로 내려가면서 우선순위 확인한다
                                                       //최종 결정된 글자와 같은 이전 위치랑만 비교
				if (st_tmp.second > 1 && isvis[st_tmp.first][st_tmp.second - 1]) { //오른쪽방향,
					if (c[st_tmp.first][st_tmp.second - 1] == res[idx - 1] && c[st_tmp.first][st_tmp.second] <= res[idx]) {
						isvis[st_tmp.first][st_tmp.second] = 1;
						res[idx] = c[st_tmp.first][st_tmp.second];
					}
				}

				if (st_tmp.first > 1 && isvis[st_tmp.first - 1][st_tmp.second]) { //아래쪽방향
					if (c[st_tmp.first - 1][st_tmp.second] == res[idx - 1] && c[st_tmp.first][st_tmp.second] <= res[idx]) {
						isvis[st_tmp.first][st_tmp.second] = 1;
						res[idx] = c[st_tmp.first][st_tmp.second];
					}
				}

				st_tmp.first++; //왼쪽 아래로 한칸씩 이동
				st_tmp.second--;
			}					
		}
		cout << "#" << tc << " ";
		for (int i = 1; i < N + M; i++) 
			cout << res[i];
		cout << "\n";		
	}
	return 0;
}
