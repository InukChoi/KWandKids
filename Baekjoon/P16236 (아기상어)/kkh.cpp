#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int N, see[20][20], my[4] = { 0,0,-1,1 }, mx[4] = { 1,-1,0,0 };
struct fish { int y, x, size, eat, sec; }; // y,x, ����� or ��� size, ���� Ƚ��, total time
vector<fish> v;//����üŸ���� ���� ����
fish shark;//��� ��ġ ����

bool bfs() {//���� ����� ��ġ�� ����� ã�� or ��ġ ����
	int isvis[20][20] = { 0 };//�湮�� �ʱ�ȭ
	bool b = false;
	queue<fish> q;
	q.push(shark);
	isvis[shark.y][shark.x] = 1;
	while (!q.empty()) {
		fish tmp = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int move_y = tmp.y + my[i];
			int move_x = tmp.x + mx[i];
			if (move_y >= N || move_y < 0 || move_x >= N || move_x < 0)	continue;
			if (!isvis[move_y][move_x] && see[move_y][move_x] <= shark.size ) {//������ ���ų� ������ Ȯ��
				isvis[move_y][move_x] = isvis[tmp.y][tmp.x] + 1;//�ð� ���ϱ� ���� 1�� �߰�
				q.push({ move_y , move_x, 0 });
			}
		}
	}

	int idx = 0, minn = 100000;
	for (int i = 0; i < v.size(); i++) {
		if (v[i].size >= shark.size)	continue;
		if (!isvis[v[i].y][v[i].x])		continue;
		if (minn > isvis[v[i].y][v[i].x]) {//���� ���� �ð��� ����� �ε��� ���ϱ�
			minn = isvis[v[i].y][v[i].x];
			idx = i;
			b = true; //����ߴٴ� ǥ��
		}
		else if (minn == isvis[v[i].y][v[i].x]) {
			if (v[idx].y > v[i].y) {//�Ÿ� ���� �� y�� ���� ��
				idx = i;
				b = true;
			}				
			else if (v[idx].y == v[i].y) {//x�� ��
				if (v[idx].x > v[i].x) {
					idx = i;
					b = true;
				}					
			}
		}
	}

	if (b) {//b == true ? ��ɼ��� : ��ɽ���
		shark.y = v[idx].y;//��� ��ġ ����
		shark.x = v[idx].x;
		shark.eat++; //���� Ƚ�� 1�߰�
		if (shark.eat == shark.size) { 
			shark.size++; 
			shark.eat = 0;	
		}			
		shark.sec += minn - 1; //total time ����		
		v.erase(v.begin() + idx);//���� ����� ����
	}
	return b;
}

int main() {
	scanf_s(" %d", &N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			scanf_s(" %d", &see[i][j]);
			if (see[i][j] >= 1 && see[i][j] <= 6)
				v.push_back({ i,j,see[i][j], 0 });
			else if (see[i][j] == 9)
				shark = { i , j, 2, 0, 0 };
		}
	see[shark.y][shark.x] = 0; //bfs�Ҷ� �Ž����� ����
	while (bfs());	//��� �����Ҷ����� �ݺ�
	printf("%d", shark.sec); 
	return 0;
}