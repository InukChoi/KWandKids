#include<iostream>
using namespace std;

int num[15] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
int n_t[15];
char a[3] = { '+', '-', '.' };
char b[14];
char b_t[14];

int cnt = 0;

int calc(int N) {	// '.' 연산을 우선 실행한 후에, 나머지 연산을 진행하여 결과를 반환
	int dot=1, end = N, idx=0;
	for (int i = 0; i < N - 1; i++) {
		n_t[i] = num[i];
		b_t[i] = b[i];
	}n_t[N - 1] = num[N - 1];

	while (dot!=0) {
		dot = 0;
		for (int i = idx; i < end - 1; i++) {
			if (b_t[i] == '.') {
				dot++;
				if(n_t[i+1] < 10)
					n_t[i] = n_t[i] * 10 + n_t[i + 1];
				else n_t[i] = n_t[i] * 100 + n_t[i + 1];
				for (int j = i + 1; j < end-1; j++)
					n_t[j] = n_t[j + 1];
				for (int j = i; j < end - 2; j++)
					b_t[j] = b_t[j + 1];
				end--;
				idx = i;
				break;
			}
		}
	}

	//cout << "  [  num : ";
	//for (int i = 0; i < end; i++)
	//	cout << n_t[i] << " ";
	//cout << "   ";
	//cout << "  [  op : ";
	//for (int i = 0; i < end -1; i++)
	//	cout << b_t[i] << " ";

	int res = n_t[0];
	for (int i = 0; i < end - 1; i++)
	{
		if (b_t[i] == '+')
			res = res + n_t[i + 1];
		else res = res - n_t[i + 1];
	}
	//cout << ", res : " << res;
	return res;
}

void dfs(int N, int depth) {	
	if (depth == N - 1) {
		if (calc(N) == 0) {
			if (cnt < 20) {
				for (int i = 0; i < N - 1; i++)
					cout << num[i] << " " << b[i] << " ";
				cout << num[N - 1];
				cout << endl;
			}
			cnt++;			
		}
	}
	else {
		for (int i = 0; i < 3; i++) {
			b[depth] = a[i];
			dfs(N, depth + 1);
		}
	}
}

int main() {

	int N;
	cin >> N;

	dfs(N, 0);
	cout << cnt << endl;
	return 0;
}
