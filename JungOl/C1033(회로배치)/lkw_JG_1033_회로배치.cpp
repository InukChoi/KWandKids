#include<iostream>
using namespace std;

int map[51][51]={ {0,}, }; // 지나갈 때 비용 ( 1 or k)
int cost[51][51]={ {0,}, }; // 시작점으로 부터 최소 비용

int dy[4] = { 0, 0, -1, 1 }; // 4방향 탐색
int dx[4] = { 1, -1, 0, 0 };

int qy[100000]; // BFS에 사용할 큐
int qx[100000];

int y_b[51][51]; // 이동해온 y좌표 저장
int x_b[51][51]; // 이동해온 x좌표 저장

void search(int N, int k, int y, int x) {	
	int head = 0, tail = 0;
	
	qy[tail] = y; // 처음은 시작 y 좌표
	qx[tail++] = x; // x 좌표	
	y_b[y][x] = 0;
	x_b[y][x] = 0;
	cost[y][x] = 1;

	while (head < tail) {
		int y_f = qy[head]; // 맨 앞에 것을 가져온다
		int x_f = qx[head++];

		for (int i = 0; i < 4; i++) {  // 4 방향
			int yt = y_f + dy[i]; // 이동할 4 방향 좌표
			int xt = x_f + dx[i];

			if (yt >= 1 && yt <= N && xt >= 1 && xt <= N)		// 범위를 벗어 나지 않고		
				if (cost[yt][xt] > map[yt][xt] + cost[y_f][x_f]) {
					// 현재까지의 탐색 결과보다 짧은 길을 발견하면
					cost[yt][xt] = map[yt][xt] + cost[y_f][x_f]; // 값을 갱신 후
					y_b[yt][xt] = y_f; // 건너온 좌표도 저장
					x_b[yt][xt] = x_f;
					qy[tail] = yt; // 그리고 큐에 삽입
					qx[tail++] = xt;
				}
		}
	}
}
int max(int a, int b) {
	if (a >= b) return a;
	else return b;
}
int min(int a, int b) {
	if (a < b) return a;
	else return b;
}
int main() {
	int N, ans, k, circuit; // 맵 크기, 정답, 회로가중치, 회로 수
	int y[2], x[2]; // index] 0 : start, 1 : end

	cin >> N; // map size
	for (int j = 1; j <= N; j++)
		for (int i = 1; i <= N; i++) {			
			map[j][i] = 1; // 우선 1로 초기화
			cost[j][i] = 987654321; // 기본 최대값
		}

	for (int i = 0; i < 2; i++)
		cin >> y[i] >> x[i]; // start, end coordi

		
	cin >> k;
	cin >> circuit;

	for (int i = 0; i < circuit; i++) {
		int corner, ys, xs, ye, xe;
		cin >> corner;
		cin >> ys >> xs; // 직선의 시작
		map[ys][xs] = k;
		for (int c = 1; c < corner; c++) {
			cin >> ye >> xe;		 // 직선의 끝	
			if (xs == xe) {
				for (int y0 = min(ys, ye); y0 <= max(ys, ye); y0++)
					map[y0][xs] = k;
			}
			else if (ys == ye) {
				for (int x0 = min(xs, xe); x0 <= max(xs, xe); x0++)
					map[ys][x0] = k;
			}			
			ys = ye; // 끝이 다음 직선의 시작
			xs = xe;
		}
	}	

	search(N, k, y[0], x[0]);
	
	/*cout << endl;
	for (int j = 1; j <= N; j++) {
		for (int i = 1; i <= N; i++) {
			printf("%2d ", cost[j][i]);
		}cout << endl;
	}
	cout << endl << "before\n";
	for (int j = 1; j <= N; j++) {
		for (int i = 1; i <= N; i++) {
			printf("(%2d,%2d) ", y_b[j][i], x_b[j][i]);
		}cout << endl;
	}*/

	ans = cost[y[1]][x[1]]; // 최소 거리
	cout << ans << endl; 

	int yy1 = y[1], xx1 = x[1], yy2, xx2; // 끝에서 부터 처음으로 거슬러간다.
	// y[1], x[1]은 도착점. yy1,xx1은 이전 점, yy2,xx2는 지금 점
	int ylist[2000], xlist[2000]; // 0번부터 끝, 코너들, 시작 순으로 저장
	int ldx = 0; 
	ylist[ldx] = yy1; // 처음엔 끝점
	xlist[ldx++] = xx1;

	int y_d1 = y_b[yy1][xx1] - yy1; // 이전점 - 지금점 으로 방향을 구한다.
	int x_d1 = x_b[yy1][xx1] - xx1;
	//cout << "yy1: " << yy1 << ", xx1 : " << xx1 << endl;
	while (1) {		
		yy2 = y_b[yy1][xx1]; // yy2 : [yy1][xx1] 방문 직전 점의 y 좌표
		xx2 = x_b[yy1][xx1];
		//cout << "yy2: " << yy2 << ", xx2 : " << xx2 << endl;
		
		int y_d2 = yy2 - yy1; // 이전 점으로 돌아가는 방향
		int x_d2 = xx2 - xx1;

		if (y_d1 != y_d2 || x_d1 != x_d2) { // 직전의 방향과 달라졌다면
			ylist[ldx] = yy1; // 코너입니다.
			xlist[ldx++] = xx1;			
		}
		if (yy2 == y[0] && xx2 == x[0]) { // 시작점으로 돌아갔다면
			ylist[ldx] = yy2;
			xlist[ldx++] = xx2;
			break;
		}
		yy1 = yy2; // 현재의 정보가 다음 반복의 이전 정보가 된다.
		xx1 = xx2;
		y_d1 = y_d2;
		x_d1 = x_d2;
	}
	
	cout << ldx;
	for (int i = ldx - 1; i >= 0; i--)
		cout << " " << ylist[i] << " " << xlist[i];

	return 0;
}