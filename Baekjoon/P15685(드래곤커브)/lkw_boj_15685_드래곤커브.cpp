#include<iostream>
using namespace std;

int arr[101][101];
int N;
int dy[4] = { 0, -1, 0, 1 };
int dx[4] = { 1, 0, -1, 0 };

struct dragon {
	int x, y, d, g;
};
dragon d[20];

void prt(int n) {
	cout << "\narr\n";
	for (int j = 0; j <= n; j++) {
		for (int i = 0; i <= n; i++)
			cout << arr[j][i];
		cout << endl;
	}cout << endl;
}
void rotate90(int X, int Y, int x[], int y[], int &idx) {
	int a, b;
	for (int i = idx - 2; i >= 0; i--) { // (Y, X)�� �������� 90�� ���ư� ��ǥ�� �߰�
		a = x[i] - X; 
		b = y[i] - Y;

		x[2 * (idx - 1) - i] = X - b;
		y[2 * (idx - 1) - i] = Y + a;
	}
	idx += idx - 1; // ���� ������ ������ �����ϰ� �� �谡 �ȴ�.
}
int countSquare() {
	int cnt = 0;
	for (int j = 0; j < 100; j++)
		for (int i = 0; i < 100; i++)
			if (arr[j][i] == 1 && arr[j][i + 1] == 1 && arr[j + 1][i] == 1 && arr[j + 1][i + 1] == 1)
				cnt++;

	return cnt;
}
void makecurve(dragon a) { // Ŀ�긦 ������
	int y[1050];
	int x[1050];
	int idx = 0;
	int lastY, lastX;

	x[idx] = a.x;
	y[idx] = a.y;
	idx++;
	x[idx] = a.x + dx[a.d];
	y[idx] = a.y + dy[a.d];
	idx++;
	lastX = x[idx - 1];
	lastY = y[idx - 1];

	for (int i = 0; i < a.g; i++) { // �ش� ���� �� ��ŭ
		rotate90(lastX, lastY, x, y, idx);
		lastX = x[idx - 1];
		lastY = y[idx - 1];
	}

	for (int i = 0; i < idx; i++) {
		arr[y[i]][x[i]] = 1; // Ŀ�� �������� ��
	}
	//prt(10);
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> d[i].x >> d[i].y >> d[i].d >> d[i].g;

	for (int j = 0; j <= 100; j++)
		for (int i = 0; i <= 100; i++) 
			arr[j][i] = 0; // 1�̸� Ŀ�� �������� ����

	//prt( 10);
	for (int i = 0; i < N; i++)
		makecurve(d[i]); // Ŀ�긦 �����

	cout << countSquare();

	return 0;
}