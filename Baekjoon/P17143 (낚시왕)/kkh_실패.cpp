#include <iostream>
using namespace std;
int R, C, M, shark[10001][6], move_y[5] = { 0, -1, 1, 0, 0 }, move_x[5] = { 0, 0, 0, 1, -1 }, res;
int AA[101][101];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> R >> C >> M;
	for (int i = 1; i <= M; i++) {
		for (int j = 0; j < 5; j++)
			cin >> shark[i][j]; // y,x,�ӷ�, �̵�����, ũ��
		AA[shark[i][0]][shark[i][1]] = i;//��� ��ġ ��ǥ �ε����� ǥ��
	}

	for (int cnt = 1; cnt <= C; cnt++) {
		int minn = 101, idx = 0;
		for (int j = 1; j <= M; j++) {
			if (shark[j][1] == cnt) {//���� ���ÿ� ��ġ�� �ּ� y�� ���ϱ�
				if (minn > shark[j][0]) {
					minn = shark[j][0];
					idx = j;
				}
			}
		}

		if (minn < 101) {
			shark[idx][0] = 0; //���� ��� x, y�� 0���� ǥ��
			shark[idx][1] = 0;
			res += shark[idx][4]; //���� ��� ũ�� �߰�
		}

		for (int i = 1; i <= M; i++) {
			int tmp_y = shark[i][0], tmp_x = shark[i][1];
			if (!tmp_y)	continue; //��ų� ���� ����ϰ�� �ѱ��
			AA[tmp_y][tmp_x] = 0; //���� ��� ��ġ �ӽ÷� ����
			if (shark[i][3] == 1) { //���� �����϶�
				shark[i][0] += (move_y[shark[i][3]] * shark[i][2]);
				if (shark[i][0] < 1) {
					shark[i][0]--;
					int tmp_div = abs(shark[i][0]) / (R - 1);
					int tmp_mod = abs(shark[i][0]) % (R - 1);
					if (tmp_div & 1) {
						shark[i][0] = R - tmp_mod;
						if (!tmp_mod) //������ ĭ�� �ִ� ��� ������ �ٸ�
							shark[i][3] = 2;
					}
					else {
						shark[i][0] = 1 + tmp_mod;
						if (tmp_mod) //ù��° ĭ�� �ִ� ��� ������ �ٸ�
							shark[i][3] = 2;
					}
				}
			}
			else if (shark[i][3] == 2) {//�Ʒ��� �����϶�
				shark[i][0] += (move_y[shark[i][3]] * shark[i][2]);
				if (shark[i][0] > R) {
					shark[i][0] -= R;
					int tmp_div = shark[i][0] / (R - 1);
					int tmp_mod = shark[i][0] % (R - 1);
					if (tmp_div & 1) {
						shark[i][0] = 1 + tmp_mod;
						if (!tmp_mod)
							shark[i][3] = 1;
					}
					else {
						shark[i][0] = R - tmp_mod;
						if (tmp_mod)
							shark[i][3] = 1;
					}


				}
			}
			else if (shark[i][3] == 3) { //���������� �����϶�
				shark[i][1] += (move_x[shark[i][3]] * shark[i][2]);
				if (shark[i][1] > C) {
					shark[i][1] -= C;
					int tmp_div = shark[i][1] / (C - 1);
					int tmp_mod = shark[i][1] % (C - 1);
					if (tmp_div & 1) {
						shark[i][1] = 1 + tmp_mod;
						if (!tmp_mod)
							shark[i][3] = 4;
					}
					else {
						shark[i][1] = C - tmp_mod;
						if (tmp_mod)
							shark[i][3] = 4;
					}

				}
			}
			else if (shark[i][3] == 4) {//�������� �����϶�
				shark[i][1] += (move_x[shark[i][3]] * shark[i][2]);
				if (shark[i][1] < 1) {
					shark[i][1]--;
					int tmp_div = abs(shark[i][1]) / (C - 1);
					int tmp_mod = abs(shark[i][1]) % (C - 1);
					if (tmp_div & 1) {
						shark[i][1] = C - tmp_mod;
						if (!tmp_mod)
							shark[i][3] = 3;
					}
					else {
						shark[i][1] = 1 + tmp_mod;
						if (tmp_mod)
							shark[i][3] = 3;
					}

				}
			}

			if (AA[shark[i][0]][shark[i][1]] < i) { //�̵��� ��ġ�� �̹� �̵��� ��� �ִ��� Ȯ��
				int tmp_idx = AA[shark[i][0]][shark[i][1]];
				if (shark[tmp_idx][4] > shark[i][4]) {//ũ�� ���� ������� ��ǥ 0���� ����
					shark[i][0] = 0;
					shark[i][1] = 0;
				}
				else {
					shark[tmp_idx][0] = 0;
					shark[tmp_idx][1] = 0;
					AA[shark[i][0]][shark[i][1]] = i;
				}
			}
		}
		
	}

	cout << res;
	return 0;
}