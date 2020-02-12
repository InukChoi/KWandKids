#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int *chickenAddr;
int **city;
int N, M;
int Distance = 1000000;
int cntC = 0;    // �ʱ� ġŲ�� ��

vector<pair<int, int>> pos, fin; // <y, x>

void swap2(int *arr, int i, int j);
void perm(int *arr, int depth, int n, int k);
int get_chicken_distance(int **arr, int r, int c, int N);
int get_city_chicken_distance(int **arr, int N);
void comb(vector<pair<int, int>> &fin, int n, int k, int index);

int main() {
	int CCD = 0; // ġŲ�Ÿ�

	cin >> N;
	cin >> M;

	city = new int*[N];
	for (int i = 0; i < N; ++i)
		city[i] = new int[N];

	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			cin >> city[j][i];
			if (city[j][i] == 2) {
				cntC++;
				pos.push_back(make_pair(j, i)); // ġŲ �� �߰���
			}
		}
	}
	if (cntC == M) { // �ʱ��� ġŲ���� �ִ� ��� ġŲ���� ��
		for (int j = 0; j < N; j++)
			for (int i = 0; i < N; i++)
				if (city[j][i] == 1)
					CCD = CCD + get_chicken_distance(city, j, i, N);
		cout << CCD;
	}
	else if (cntC > M) {// ġŲ���� ���־� �ϴ� ��� n C m
		comb(fin, cntC, M, 0);

		cout << Distance;

		//delete[] arr;
	}
	else cout << "error!";

	//////////////////////////////////////////////
	for (int i = 0; i < N; ++i)
	{
		delete[] city[i];
	}
	delete[] city;


	return 0;
}
void comb(vector<pair<int, int>> &fin, int n, int k, int index) {
	if (k == 0) {
		for (int i = 0; i < pos.size(); i++)
			city[pos.at(i).first][pos.at(i).second] = 0;
		for (int i = 0; i < fin.size(); i++)
			city[fin.at(i).first][fin.at(i).second] = 2;

		if (Distance > get_city_chicken_distance(city, N))
			Distance = get_city_chicken_distance(city, N);
	}
	else if (index == n)
		return;
	else {
		fin.push_back(pos.at(index));
		comb(fin, n, k - 1, index + 1);
		//cout << pos.at(index).first << " " << pos.at(index).second << " ";
		fin.pop_back();
		comb(fin, n, k, index + 1);
	}
}
int get_distance(int r1, int c1, int r2, int c2) {
	int R = abs(r1 - r2);
	int C = abs(c1 - c2);
	return R + C;
}
int get_chicken_distance(int **arr, int r, int c, int N) {	//r,c ���� ��ǥ
	int temp = 0;
	int d = 100;

	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			if (arr[j][i] == 2) {
				temp = get_distance(r, c, j, i);
				if (temp < d)
					d = temp;    //������ ���� ����� ġŲ������ �Ÿ�
			}
		}
	}

	return d;
}

int get_city_chicken_distance(int **arr, int N) {
	int CCD = 0;

	for (int j = 0; j < N; j++)
		for (int i = 0; i < N; i++)
			if (arr[j][i] == 1)
				CCD = CCD + get_chicken_distance(arr, j, i, N);

	return CCD;
}
void swap(vector<pair<int, int>> &a, vector<pair<int, int>> &b) {
	vector<pair<int, int>> tmp = a;
	a = b;
	b = tmp;
}
void swap2(int *arr, int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}
void perm(int *arr, int depth, int n, int k) { // n���� k��	
	if (depth == k) { // �ѹ� depth �� k�� �����ϸ� ����Ŭ�� ������. �����.		
		int *temp = new int[cntC];
		for (int index = 0; index < cntC; index++) {
			if (arr[index] != 0) {
				temp[index] = chickenAddr[index];
			}
			else temp[index] = -1;
		}

		for (int i = 0; i < cntC; i++) {
			if (temp[i] != -1)
				city[temp[i] / N][temp[i] % N] = 2;
			else city[chickenAddr[i] / N][chickenAddr[i] % N] = 0;
		}

		if (Distance > get_city_chicken_distance(city, N))
			Distance = get_city_chicken_distance(city, N);

		return;
	}

	for (int i = depth; i < n; i++) {
		swap2(arr, i, depth);
		perm(arr, depth + 1, n, k);
		swap2(arr, i, depth);
	}
}