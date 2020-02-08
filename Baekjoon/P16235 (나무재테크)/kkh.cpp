#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;
int N, M, K, tmp, ed, totcnt, land[11][11], Add[11][11], move_y[8] = { -1, -1, -1, 0, 1, 1, 1, 0 }, move_x[8] = { -1,0,1,1,1,0,-1,-1 };
deque<int> v[11][11];

int main() {
	scanf(" %d %d %d", &N, &M, &K);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++) {
			scanf(" %d", &Add[i][j]); //�ų� �߰��Ǵ� ��а�
			land[i][j] = 5; //���� ������ִ� ��а�
		}
	totcnt = M; //��ü �ɾ����ִ� ���� ��
	int y, x, z;
	for (int i = 0; i < M; i++) {
		scanf(" %d %d %d", &y, &x, &z);
		v[y][x].push_back(z);//��ǥ �� �������� ����
	}

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			sort(v[i][j].begin(), v[i][j].end()); //��ǥ �� ������������ ����, � ���� �켱
	for (int year = 1; year <= K; year++) {
		//��
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				tmp = 0, ed = v[i][j].size();
				for (int cnt = 0; cnt < ed; cnt++) {
					if (land[i][j] < v[i][j][cnt]) { //���� ��а� ���� ���� ��

						for (int kk = ed - 1; kk >= cnt; kk--) {
							tmp += v[i][j][kk] / 2; //������ �� Ŭ ��� �� �迭 ���� �ӽ� ���� �� pop
							v[i][j].pop_back();
						}
						totcnt -= ed - cnt; //���� ���� ��ŭ ī��Ʈ �ٿ�
						break;
					}
					else {
						land[i][j] -= v[i][j][cnt]; //���� ����� �� ���� ��� ���� ���̸�ŭ ����
						v[i][j][cnt]++; 
					}
				}
				land[i][j] += tmp; //���� ,  ���� ���� �ӽ����� �� ������ �߰�
			}
		}

		//���� + �ܿ�
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				land[i][j] += Add[i][j];
				tmp = v[i][j].size();
				for (int cnt = 0; cnt < tmp; cnt++) {
					if (!(v[i][j][cnt] % 5)) {
						for (int k = 0; k < 8; k++) { //�ֺ� 8�� ��ǥ Ȯ��
							int tmp_y = i + move_y[k];
							int tmp_x = j + move_x[k];
							if (tmp_y > 0 && tmp_y <= N && tmp_x > 0 && tmp_x <= N) {
								v[tmp_y][tmp_x].push_front(1); // 1�� �� ������ ����
								totcnt++; //ī��Ʈ �߰�
							}
						}
					}
				}
			}
		}

	}

	printf("%d", totcnt);
	return 0;
}