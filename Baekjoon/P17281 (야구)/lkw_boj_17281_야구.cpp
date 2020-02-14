#include<iostream>
using namespace std;

int arr[50][9];
int p[9] = { 1,2,3,4,5,6,7,8,0 };
int player[9]; // ���� �ϳ� �����ϰ�, �������� ������ ���� ���� Ÿ�� ����
int pcopy[9]; // �� ���� ���� �ڸ��� ����
bool v[8] = { 0, };

bool base[5]; // Ȩ�� ���� ��, ���� �� �����Ͽ���. Ȩ 1 2 3 Ȩ
int MAX = 0;

bool hit(int h, int &score) { // if 1, out
	if (h == 0) // �ƿ�
		return 1;
	else {
		base[0] = 1; // Ȩ���� ���� ��� 
		for (int j = 0; j < h; j++) { // h��Ÿ, hĭ ����
			for (int i = 4; i > 0; i--)
				base[i] = base[i - 1]; // �� ĭ�� �����Ѵ�.
			base[0] = 0; // ���� ������ �ٽ� 0����
			if (base[4]) { // Ȩ�� ���� ����� ������
				score++; //���� ��
				base[4] = 0;
			}

		}
		return 0;
	}
}

int baseball(int inn) { // 1 ������ �ùķ��̼� �Ѵ�.
	bool of = 0; // �ƿ� Ȯ�ο� �÷���
	int order = 0, out=0, score=0; // ���� ���� ,�ƿ� ī��Ʈ, ����
	for (int j = 0; j < inn; j++) {
		for (int i = 0; i < 5; i++) // ���̽� �ʱ�ȭ
			base[i] = 0;
		while (1) {
			of = hit(arr[j][pcopy[order++]], score); // ������� �÷���. �ƿ��̸� 1 ����
			order %= 9; // 9���̼� ���ư��鼭. �����̴׿��� �̾�����.
			if (of)
				out++;
			if (out == 3) { // 3�ƿ� �� �̴� ��.
				out = 0;
				break;
			}
		}
	}
	return score;
}

void perm(int N, int depth, int inn){
	if (N == depth) {
		for (int i = 0; i < 3; i++) 
			pcopy[i] = player[i];
		for (int i = 8; i > 3; i--)
			pcopy[i] = player[i - 1];
		pcopy[3] = 0; // ���� ������ ���� �ڸ��� �������ν� ���� �ϼ�
		
		int tmp = baseball(inn); // �ϼ��� ������ �÷���. ��� ���� ����
		if (MAX < tmp) {
			MAX = tmp;
			
			//cout << "P : ";
			//for (int i = 0; i < 9; i++)
			//	cout << pcopy[i] << " ";
			//cout << " - score : " << MAX << endl;
		
		}
		

	}
	else {
		for (int i = 0; i < N; i++) {
			if (!v[i]) {
				v[i] = 1;
				player[depth] = p[i];
				perm(N, depth + 1, inn);
				v[i] = 0;
			}
		}
	}

}

int main() {
	int inn; // 2~50

	cin >> inn;

	for (int j = 0; j < inn; j++)
		for (int i = 0; i < 9; i++)
			cin >> arr[j][i];

	perm(8, 0, inn);

	cout << MAX;

	return 0;
}