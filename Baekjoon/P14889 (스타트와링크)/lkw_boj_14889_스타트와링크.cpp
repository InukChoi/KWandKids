#include<iostream>
using namespace std;

int arr[21][21]; // �ó���

int num[21]; // 1~20
int team1[10]; // �� 1. �� �ϳ��� �������� �������� �˾Ƽ� ������
bool team[21]; // 1�� 0���� ���� �����Ѵ�.
int MIN = 987654321;

void comb(int n, int r, int depth) {
	if (r == depth) {
		/*cout << "team1 : ";
		for (int i = 1; i <= n; i++)
			if (team[i])
				cout << num[i] << " ";
		cout << endl;
		cout << "team2 : ";
		for (int i = 1; i <= n; i++)
			if (!team[i])
				cout << num[i] << " ";
		cout << endl << endl;*/
		int t1sum = 0, t2sum = 0;
		for (int j = 1; j <= n; j++)
			for (int i = 1; i <= n; i++) {
				if (j == i) continue;
				if (team[j] == team[i] && team[j] == 1)
					t1sum += arr[j][i]; // 1�� ����
				if (team[j] == team[i] && team[j] == 0)
					t2sum += arr[j][i]; // 2�� ����
			}
		//cout << "t1 sum : " << t1sum << ", t2 sum :" << t2sum << endl;
		int diff = abs(t1sum - t2sum);
		if (MIN > diff)
			MIN = diff;

	}
	else {
		for (int i = team1[depth - 1]; i <= n; i++) { // �ߺ��� ���ϱ� ���� ������������ 
			if (!team[i]) {
				team[i] = 1;
				team1[depth] = num[i];
				comb(n, r, depth + 1);
				team[i] = 0;
			}
		}
	}
}

int main() {
	int N;
	cin >> N;

	for (int j = 1; j <= N; j++) {
		num[j] = j;
		team[j] = 0;
		for (int i = 1; i <= N; i++)
			cin >> arr[j][i];
	}
	team1[0] = 1; // 1�� ������ �� ���� ������Ų��.
	team[1] = 1;
	comb(N, N / 2, 1); // 1�� ������ ���� �� �� ���� ������ �����Ѵ�.

	cout << MIN << endl;

	return 0;
}
