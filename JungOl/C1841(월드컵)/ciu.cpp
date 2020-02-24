#include <cstdio>

using namespace std;

const int L = 15;
int selected[18]; //6개팀의 결과 3^15개를 차례차례 담을 배열
int selected_comb[2]; //조합 만들 때 사용할 배열
int comb_set[15][2]; //6개 팀 중 2개 뽑는 경우=>15개 팀 페어(왼족팀, 오르쪽팀)
int results[4] = { 0 }; //가능한지 나타낼 최종 결과 배열
int quests[4][18]; //주어지는 입력
int comb_cnt = 0; //조합 만들 때 사용
int find_cnt = 0; //모두 찾았을 때 끊기 위해 사용

//몇번째 승,무.패에 저장할 지 인덱스 찾는 함수
void findIndex(int k, int i, int *left, int *right)
{
	*left = comb_set[k][0] * 3 + i; //왼쪽 팀 인덱스*3 + i (0:승, 1:무, 2:패)
	switch (i)
	{
	case 0: *right = comb_set[k][1] * 3 + 2; break; //오른쪽 팀은 왼쪽 팀이 승일 경우 패
	case 1: *right = comb_set[k][1] * 3 + 1; break;
	case 2: *right = comb_set[k][1] * 3 + 0; break;
	}
}

//15개 팀 페어에 대해 승,무,패 순열 만드는 함수
void permu(int n, int k)
{
	if (find_cnt > 3) //모두 찾았을 경우 종료
		return;
	if (n == k)
	{
		int valid_flag; //가능한 결과임을 나타내는 flag
		for (int i = 0; i < 4; i++)
		{
			if (!results[i]) //아직 가능한지 확인 안 된 것들만
			{
				valid_flag = 1;
				for (int j = 0; j < 18; j++)
					if (selected[j] != quests[i][j]) //찾은 결과와 주어진 입력이 안맞으면
					{
						valid_flag = 0; //아직은 확인 불가함을 표시
						break;
					}
				if (valid_flag) //가능한 결과인 경우
				{
					results[i] = 1; //결과를 1로 갱신
					find_cnt++;
				}
			}
		}
	}
	else
	{
		int left, right;
		for (int i = 0; i < 3; i++) //승,무,패
		{
			findIndex(k, i, &left, &right); //경기 결과 담을 인덱스 찾기
			selected[left]++; //왼쪽팀 승,무,패 +1
			selected[right]++; //오른쪽 팀 승,무,패 +1
			permu(n, k + 1);
			selected[left]--;
			selected[right]--;
		}
	}
}

//6개팀 중 2팀 뽑아 팀 페어 만드는 함수
void comb(int n, int k, int idx)
{
	if (n == k)
	{
		comb_set[comb_cnt][0] = selected_comb[0]; //왼쪽 팀
		comb_set[comb_cnt][1] = selected_comb[1]; //오른쪽 팀
		comb_cnt++;
	}
	else
	{
		for (int i = idx; i < 6; i++)
		{
			selected_comb[k] = i;
			comb(n, k + 1, i + 1);
			selected_comb[k] = 0;
		}
	}
}

int main()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 18; j++)
			scanf("%d", &quests[i][j]);
	comb(2, 0, 0); //팀 조합 만들기
	permu(L, 0); //승,무,패 순열 만들기
	for (int i = 0; i < 4; i++)
		printf("%d ", results[i]);
}
