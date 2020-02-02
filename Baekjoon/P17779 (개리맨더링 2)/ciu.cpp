#include <iostream>

using namespace std;

static int map[20][20] = { { 0, }, }; //�ִ� 20x20 ��
static int N; //���ڸ� ũ��
static int diff_min = 0; //�ּ� ��
static int sum_all = 0; //��� �α��� �� 

//x,y,d1,d2�� ���� ���ű��� ���� �ּ� ���� ���ϴ� �Լ�
void search(int x, int y, int d1, int d2)
{
	int max = 0; //�α� ���� ���� ū ���ű��� �α� ��
	int min = sum_all; //�α� ���� ���� ���� ���ű��� �α� ��
	int sum = 0; //�� ���ű��� �α� ��
	int sum_sum = 0; //5�� ���ű� ��� ���� 1~4�� ���ű� �α� ��

	//1�� ���ű� �α� ��
	for (int i = 0, k = 0; i < x + d1; i++)
	{
		k += i < x ? 0 : 1;
		for (int j = 0; j <= y - k; j++)
			sum += map[i][j];
	}
	sum_sum += sum;
	min = min > sum ? sum : min; //�ּ� �α� �� ���� ������ �ּ� �α� �� ����
	max = max < sum ? sum : max; //�ִ� �α� �� ���� ũ�� �ִ� �α� �� ����
	sum = 0;
	//2�� ���ű� �α� ��
	for (int i = 0, k=0; i <= x + d2; i++)
	{
		if (i > x)
			k++;
		for (int j = y + 1 + k; j < N; j++)
			sum += map[i][j];
	}
	sum_sum += sum;
	min = min > sum ? sum : min;
	max = max < sum ? sum : max;
	sum = 0;
	//3�� ���ű� �α� ��
	for (int i = x + d1, k = y-d1-1; i < N; i++)
	{
		if (i <= x + d1 + d2)
			k++;
		for (int j = 0; j < k; j++)
			sum += map[i][j];
		
	}
	sum_sum += sum;
	min = min > sum ? sum : min;
	max = max < sum ? sum : max;
	sum = 0;
	//4�� ���ű� �α� ��
	for (int i = x + d2 + 1, k = 0; i < N; i++)
	{
		for (int j = y + d2 - k; j < N; j++)
			sum += map[i][j];
		k += i < x + d1 + d2 + 1 ? 1 : 0;
	}
	sum_sum += sum;
	min = min > sum ? sum : min;
	max = max < sum ? sum : max;
	sum = 0;

	sum = sum_all - sum_sum; // 5�� ���ű� �α� ��
	min = min > sum ? sum : min;
	max = max < sum ? sum : max;
	//�ִ� �α� ���ű��� �ּ� �α� ���ű� ���� ������ �ּ� �� ���� ������ ����
	if (max - min < diff_min)
		diff_min = max - min;
}

int main() 
{
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			scanf("%d", &map[i][j]);
			diff_min += map[i][j]; //�ּ� ���� ���� �ϴ� �� �α����� ����
		}
	sum_all = diff_min; //�� �α��� ���

	//0<x<N, 1<y<N-1, 1<d1<=y, 1<d2<N-y �� ���� ���� Ž��
	for (int x = 0; x < N; x++)
		for (int y = 1; y < N-1; y++)
			for (int d1 = 1; d1 <= y; d1++)
				for (int d2 = 1; d2 < N - y; d2++)
					search(x, y, d1, d2);
	cout << diff_min;
}