#include<iostream>
using namespace std;

int N = 0;
int sharksize = 2;
int eatcount = 0;
int sy = 0, sx = 0, fy = 0, fx = 0;
int time = 0;

int arr[20][20]; // 9 : ���, 0 : ��ĭ, 1~6 : �����ũ��
bool canmove[20][20]; // ������ �� �ִ� ��
int caneat[20][20];
bool visit[20][20];
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };

void findcanmove() { // ������ �� �ִ� �� ���ϴ� �Լ�
	for (int j = 0; j < N; j++)
		for (int i = 0; i < N; i++)
			if (sharksize >= arr[j][i] && arr[j][i] != 9)
				canmove[j][i] = 1;
			else canmove[j][i] = 0;
}
void search_init() { // visit �ʱ�ȭ
	for (int j = 0; j < N; j++)
		for (int i = 0; i < N; i++)
			visit[j][i] = 0;
}
void search(int y, int x) {// bfs�� �ؾ���, �Է� ���� ��ġ�� �������� �ʺ�켱 Ž��
	int qy[1001];
	int qx[1001];
	int dis[1001];
	int head = 0;
	int tail = 0;

	qy[tail] = y;
	qx[tail] = x;
	dis[tail] = 0;
	tail++;

	int y1, x1, d1;
	while (head < tail) {
		y1 = qy[head];
		x1 = qx[head];
		d1 = dis[head];
		head++;

		if (visit[y1][x1])
			continue;
		else
			visit[y1][x1] = 1;
		//cout << "y1 : " << y1 << ", x1 : " << x1 << endl;
		if (y1 == sy && x1 == sx) { // �ڽ��� ���� ����
			caneat[y1][x1] = 0;
		}
		else if (sharksize > arr[y1][x1] && arr[y1][x1] > 0) { // ���� �� �ִ� �� �Ÿ� ����
			caneat[y1][x1] = d1;
		}
		else caneat[y1][x1] = 0;

		int y0, x0;
		for (int i = 0; i < 4; i++) {
			y0 = y1 + dy[i];
			x0 = x1 + dx[i];
			if (y0 >= 0 && y0 < N && x0 >= 0 && x0 < N && visit[y0][x0] == 0 && canmove[y0][x0]) {
				qy[tail] = y0;
				qx[tail] = x0;
				dis[tail] = d1 + 1;
				tail++;
			}
		}
	}
}
bool eatfish() { // ���� �����
	int dis = 10000;
	bool flg = 0;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			if (caneat[j][i] > 0) { // ���� �� �ִ� �༮�ΰ�
				flg = 1; // ���� �� �ִ°� �ּ� �ϳ� �̻�
				int tmp = caneat[j][i];
				if (dis > tmp) { // ����� �༮�� ã�ƺ���
					dis = tmp;
					fy = j;
					fx = i;
				}
				else if (dis == tmp) { // ���� �Ÿ��� �켱������ ��������
					if (j < fy) {
						fy = j;
						fx = i;
					}
					else if (j == fy && i < fx) {
						fy = j;
						fx = i;
					}
				}
			}
		}
	}
	if (!flg) return flg; // ������ ��

	eatcount++; // ���� Ƚ�� ī��Ʈ
	time += dis; // �ɸ��ð�
	arr[sy][sx] = 0; // �����ġ ������Ʈ
	sy = fy;
	sx = fx;
	arr[sy][sx] = 9; // �����ġ ������Ʈ

	if (eatcount / sharksize > 0) { // ���� ����
		sharksize++;
		eatcount = 0;
	}

	return flg;
}
void prt() {
	cout << "arr" << endl;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++)
			cout << arr[j][i];
		cout << endl;
	}
	cout << "move" << endl;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++)
			cout << canmove[j][i];
		cout << endl;
	}
	cout << "eat" << endl;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++)
			cout << caneat[j][i];
		cout << endl;
	}
	cout << "sharksize : " << sharksize << ", eatcount : " << eatcount << ", time : " << time << endl;
}
int main() {
	cin >> N;

	for (int j = 0; j < N; j++)
		for (int i = 0; i < N; i++) {
			cin >> arr[j][i];
			if (arr[j][i] == 9) {
				sy = j;
				sx = i;
			}
		}
	sharksize = 2;
	time = 0;
	eatcount = 0;
	// ���� �� �ִ� ����� �ľ�
	// ������ �� �� �ִ� ����� �ľ�
	// ���� ����� ����� �Ծ� (�켱���� : 1. y ��ǥ ������ 2. x��ǥ ������)
	//prt();
	while (1) {

		findcanmove(); // ������ �� �ִ� �� üũ
		search_init(); // visit �ʱ�ȭ
		search(sy, sx); // ���� Ž��
		//prt();
		if (!eatfish()) // ���� �� ���� �� ����
			break;
	}
	cout << time;

	return 0;
}