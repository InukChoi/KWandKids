#include<iostream>
using namespace std;

int map[51][51]={ {0,}, }; // ������ �� ��� ( 1 or k)
int cost[51][51]={ {0,}, }; // ���������� ���� �ּ� ���

int dy[4] = { 0, 0, -1, 1 }; // 4���� Ž��
int dx[4] = { 1, -1, 0, 0 };

int qy[100000]; // BFS�� ����� ť
int qx[100000];

int y_b[51][51]; // �̵��ؿ� y��ǥ ����
int x_b[51][51]; // �̵��ؿ� x��ǥ ����

void search(int N, int k, int y, int x) {	
	int head = 0, tail = 0;
	
	qy[tail] = y; // ó���� ���� y ��ǥ
	qx[tail++] = x; // x ��ǥ	
	y_b[y][x] = 0;
	x_b[y][x] = 0;
	cost[y][x] = 1;

	while (head < tail) {
		int y_f = qy[head]; // �� �տ� ���� �����´�
		int x_f = qx[head++];

		for (int i = 0; i < 4; i++) {  // 4 ����
			int yt = y_f + dy[i]; // �̵��� 4 ���� ��ǥ
			int xt = x_f + dx[i];

			if (yt >= 1 && yt <= N && xt >= 1 && xt <= N)		// ������ ���� ���� �ʰ�		
				if (cost[yt][xt] > map[yt][xt] + cost[y_f][x_f]) {
					// ��������� Ž�� ������� ª�� ���� �߰��ϸ�
					cost[yt][xt] = map[yt][xt] + cost[y_f][x_f]; // ���� ���� ��
					y_b[yt][xt] = y_f; // �ǳʿ� ��ǥ�� ����
					x_b[yt][xt] = x_f;
					qy[tail] = yt; // �׸��� ť�� ����
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
	int N, ans, k, circuit; // �� ũ��, ����, ȸ�ΰ���ġ, ȸ�� ��
	int y[2], x[2]; // index] 0 : start, 1 : end

	cin >> N; // map size
	for (int j = 1; j <= N; j++)
		for (int i = 1; i <= N; i++) {			
			map[j][i] = 1; // �켱 1�� �ʱ�ȭ
			cost[j][i] = 987654321; // �⺻ �ִ밪
		}

	for (int i = 0; i < 2; i++)
		cin >> y[i] >> x[i]; // start, end coordi

		
	cin >> k;
	cin >> circuit;

	for (int i = 0; i < circuit; i++) {
		int corner, ys, xs, ye, xe;
		cin >> corner;
		cin >> ys >> xs; // ������ ����
		map[ys][xs] = k;
		for (int c = 1; c < corner; c++) {
			cin >> ye >> xe;		 // ������ ��	
			if (xs == xe) {
				for (int y0 = min(ys, ye); y0 <= max(ys, ye); y0++)
					map[y0][xs] = k;
			}
			else if (ys == ye) {
				for (int x0 = min(xs, xe); x0 <= max(xs, xe); x0++)
					map[ys][x0] = k;
			}			
			ys = ye; // ���� ���� ������ ����
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

	ans = cost[y[1]][x[1]]; // �ּ� �Ÿ�
	cout << ans << endl; 

	int yy1 = y[1], xx1 = x[1], yy2, xx2; // ������ ���� ó������ �Ž�������.
	// y[1], x[1]�� ������. yy1,xx1�� ���� ��, yy2,xx2�� ���� ��
	int ylist[2000], xlist[2000]; // 0������ ��, �ڳʵ�, ���� ������ ����
	int ldx = 0; 
	ylist[ldx] = yy1; // ó���� ����
	xlist[ldx++] = xx1;

	int y_d1 = y_b[yy1][xx1] - yy1; // ������ - ������ ���� ������ ���Ѵ�.
	int x_d1 = x_b[yy1][xx1] - xx1;
	//cout << "yy1: " << yy1 << ", xx1 : " << xx1 << endl;
	while (1) {		
		yy2 = y_b[yy1][xx1]; // yy2 : [yy1][xx1] �湮 ���� ���� y ��ǥ
		xx2 = x_b[yy1][xx1];
		//cout << "yy2: " << yy2 << ", xx2 : " << xx2 << endl;
		
		int y_d2 = yy2 - yy1; // ���� ������ ���ư��� ����
		int x_d2 = xx2 - xx1;

		if (y_d1 != y_d2 || x_d1 != x_d2) { // ������ ����� �޶����ٸ�
			ylist[ldx] = yy1; // �ڳ��Դϴ�.
			xlist[ldx++] = xx1;			
		}
		if (yy2 == y[0] && xx2 == x[0]) { // ���������� ���ư��ٸ�
			ylist[ldx] = yy2;
			xlist[ldx++] = xx2;
			break;
		}
		yy1 = yy2; // ������ ������ ���� �ݺ��� ���� ������ �ȴ�.
		xx1 = xx2;
		y_d1 = y_d2;
		x_d1 = x_d2;
	}
	
	cout << ldx;
	for (int i = ldx - 1; i >= 0; i--)
		cout << " " << ylist[i] << " " << xlist[i];

	return 0;
}