#include<iostream>
#include<queue>
#include<vector> 
#include<set>
#include<string.h>  //무기 장전... 

using namespace std;
int N, M, map[100][100], isvis[100][100], my[4] = { 0,0,-1,1 }, mx[4] = { 1,-1,0,0 }, nIndex, res_min = INT32_MAX, isgrid[10001], len_check[10001];
vector<vector<int> > v;
set<pair<int, int> > s;

void bfs(int idx, int y, int x) { //구역 나누기, 인덱스로 표시
	queue<pair<int, int> > q;
	q.push({ y,x });
	isvis[y][x] = idx;

	int color = map[y][x];

	while (!q.empty()) {
		pair<int, int> tmp = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {      //붙어있는 같은 색 점에 동일한 인덱스 표시
			int next_y = tmp.first + my[i];
			int next_x = tmp.second + mx[i];
			if (next_y >= N || next_y < 0 || next_x >= M || next_x < 0) continue;
			if (map[next_y][next_x] != color)   continue;
			if (isvis[next_y][next_x])          continue;

			isvis[next_y][next_x] = idx;
			q.push({ next_y, next_x });
		}
	}
}

void connection() { //서로 붙어 있는 구역 확인
	int tmp_min, tmp_max;
	int rsz = nIndex + 1; 
	v.resize(rsz);      //찾은 인덱스 싸이즈 만큼 리사이즈

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			for (int k = 0; k < 4; k++) {
				int next_y = i + my[k];
				int next_x = j + mx[k];
				if (next_y >= N || next_y < 0 || next_x >= M || next_x < 0) continue;
				if (isvis[i][j] == isvis[next_y][next_x])                   continue;

				if (isvis[i][j] < isvis[next_y][next_x]) { //set에 저장 하기 전 크기 비교 //set 메모리, 찾은 시간 줄이기 위해 추가
					tmp_min = isvis[i][j];                   
					tmp_max = isvis[next_y][next_x];
				}
				else {
					tmp_min = isvis[next_y][next_x];
					tmp_max = isvis[i][j];
				}


				if (s.find({ tmp_min, tmp_max }) != s.end())    continue; 
				s.insert({ tmp_min, tmp_max });

				v[isvis[i][j]].push_back(isvis[next_y][next_x]);  //구역 별 연결 양방향 표시 
				v[isvis[next_y][next_x]].push_back(isvis[i][j]);  
			}
}

int gridgame(int start_idx) { //최장 거리 찾기
	memset(isgrid, 0, sizeof(isgrid));
	queue<int> q;
	q.push(start_idx);
	isgrid[start_idx] = 1;

	int max_cnt = 0;

	while (!q.empty()) {
		int tmp = q.front();
		q.pop();

		if (max_cnt < isgrid[tmp])
			max_cnt = isgrid[tmp];		//최장 거리 저장

		for (int i = 0; i < v[tmp].size(); i++) { 
			int next_idx = v[tmp][i];
			if (isgrid[next_idx])
				continue;

			isgrid[next_idx] = isgrid[tmp] + 1; //거리 1씩 늘어남
			q.push(next_idx);
		}
	}
	return max_cnt - 1;
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> map[i][j];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (isvis[i][j] == 0)
				bfs(++nIndex, i, j);

	connection();
	
	for (int i = 1; i <= nIndex; i++) {
		if (len_check[i])	continue;

		int tmp = gridgame(i);
		if (res_min > tmp)
			res_min = tmp;

		for (int j = i + 1; j <= nIndex; j++)   //가장 마지막 구역 - 지나갔던 구역 -> 최소거리와 비교
   			 if (tmp - isgrid[j] + 1 >= res_min)     //탐색 전 가지치기 할 수 있음
				len_check[j] = 1;		
	}
	cout << res_min;
	return 0;
}
