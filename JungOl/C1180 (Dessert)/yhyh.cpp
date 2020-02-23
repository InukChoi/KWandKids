#include <iostream>
using namespace std;

int N;
char opr[3] = { '+','-','.' }; //총 3가지의 피연산자
int limit = 0; //20개 이상이면 출력 제한

int opn[16];//피연산자 스택
int ntop = 0; //피연산자 top

char ops[15]; //연산자 스택
int rtop = -1; //연산자 set top

char pop[15]; //출력 연산자

int calc(int fop, int sop, char op)//계산 함수
{
	switch (op)
	{
	case '+':
		return fop + sop;
		break;
	case '-':
		return fop - sop;
		break;

	default:
		break;
	}
	return 0;
}

void solve(int cnt)
{
	if (cnt >= N)
	{
		int fop = opn[0];
		int sop;
		char op;
		for (int i = 0; i <= rtop; i++)//스택에 있는 값을 계산함
		{
			op = ops[i];
			sop = opn[i + 1];
			fop = calc(fop, sop, op);

		}
		if (fop == 0) //0일 경우에
		{
			limit++;
			if(limit<=20)//출력 제한수를 넘기지 않았을 경우에만 출력함
			{
				for (int i = 1; i < N; i++)
				{
					cout << i << " " << pop[i] << " ";
				}
				cout << N << "\n";
			}
		}
		return;
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			pop[cnt] = opr[i]; //연산자 set
			if (i == 2) //.일때 숫자 두개를 붙임
			{
				if (cnt >= 9) //10 이상일 경우
				{
					opn[ntop] = opn[ntop] * 100 + (cnt + 1); //ex. 711, 1011
				}
				else opn[ntop] = opn[ntop] * 10 + (cnt + 1);

			}
			else
			{
				ntop++; //.이 아닌경우 그 다음 피연산자와 연산자를 스택에 입력
				rtop++;
				ops[rtop] = opr[i];
				opn[ntop] = cnt+1;
			}

			solve(cnt + 1);
			if (i != 2) //backtracking
			{
				ntop--;
				rtop--;
			}
		}
	}
}

int main()
{
	cin >> N;
	opn[0] = 1;
	solve(1); //첫번째 연산자 -> 첫번째 피연산자 (연산자) 두번째 피연산자
	cout << limit << "\n";
	return 0;
}
