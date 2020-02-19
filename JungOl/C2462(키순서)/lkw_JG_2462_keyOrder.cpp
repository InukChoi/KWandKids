#include<iostream>
using namespace std;

bool key[501][501] = { {0, }, }; // j �� i q���� �۾�
bool v[501] = { 0, }; // Ž�� �� �湮 Ȯ�ο�

void dfs(int idx, int N, int& cnt) { // ������ ū ��� Ž��
	v[idx] = 1;
	cnt++;
	for (int i = 1; i <= N; i++)
		if (key[idx][i] && !v[i])
			dfs(i, N, cnt);
}
void dfs_back(int idx, int N, int & cnt) { // ������ ���� ��� Ž��
	v[idx] = 1;
	cnt++;
	for (int i = 1; i <= N; i++)
		if (key[i][idx] && !v[i])
			dfs_back(i, N, cnt);
}
bool search(int idx, int N) { // Ű ���� Ȯ�� �����ϸ� 1, �ƴϸ� 0
	int cnt = 0;
	v[idx] = 1;
	for (int i = 1; i <= N; i++)
		if (key[idx][i] && !v[i]) // ������ ū ����̸� �� ������� ū ����� ������ Ŀ
			dfs(i, N, cnt);
	
	for (int i = 1; i <= N; i++)
		if (key[i][idx] && !v[i]) // ������ ���� ����̸� �� ������� ���� ����� ������ �۾�
			dfs_back(i, N, cnt);

	//cout << "idx : " << idx << ", cnt : " << cnt << endl;
	if (cnt == N - 1) // ������ ũ�ų� ���� ����� N-1�̸� ���� Ű ������ Ȯ���� �� �ִ�.
		return 1;
	else 
		return 0;
}


int main() {
	int N, M;
	cin >> N;
	cin >> M;
	for (int i = 0; i < M; i++) {
		int s, l;
		cin >> s >> l;
		key[s][l] = 1;
	}
	int ans = 0;
	for (int i = 1; i <= N; i++) { // �� ����� ����
		for (int i = 0; i <= N; i++)
			v[i] = 0;
		if(search(i, N)) // Ű ���� Ȯ�� �������� �˻�
			ans++;
	}

	cout << ans;

	return 0;
}