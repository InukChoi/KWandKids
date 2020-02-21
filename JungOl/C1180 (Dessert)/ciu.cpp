#include <cstdio>

using namespace std;

int N;
int permut[14];
int operators[3];
long long operands[3];
int result = 0;
char opss[4] = { ' ', '+', '-', '.' };

// '.' 연산. 앞 숫자와 뒷 숫자 붙이는 함수
long long make_behind(long long a, int b)
{
	int div = 10;
	int cp = b;
	while (cp / div != 0)
	{
		cp = cp / div;
		div *= 10;
	}
	return a * div + b;
}

//만들어진 연산자들 이용하여 계산
int calc()
{
	int opo_top = -1, opn_top = -1;
	operands[0] = -1;
	for (int i = 0; i < N - 1; i++)
	{
		if (permut[i] == 3)
		{
			if (!(i - 1 >= 0 && permut[i - 1] == 3))
				operands[++opn_top] = i + 1;
			operands[opn_top] = make_behind(operands[opn_top], i + 2);
		}
		else
		{
			if(!(i-1>=0&&permut[i-1]==3))
				operands[++opn_top] = i + 1;
			if (opo_top == 0)
			{
				switch (operators[opo_top])
				{
				case 1: operands[opn_top - 1] = operands[opn_top - 1] + operands[opn_top--]; break;
				case 2: operands[opn_top - 1] = operands[opn_top - 1] - operands[opn_top--]; break;
				default: printf("wrong operator\n");
				}
				operators[opo_top] = permut[i];
			}
			else
			{
				operators[++opo_top] = permut[i];
			}
		}
	}
	if (opo_top > -1)
	{
		if(permut[N-2]!=3)
			operands[++opn_top] = N;
		switch (operators[opo_top])
		{
		case 1: operands[opn_top - 1] = operands[opn_top - 1] + operands[opn_top--]; break;
		case 2: operands[opn_top - 1] = operands[opn_top - 1] - operands[opn_top--]; break;
		default: printf("wrong operator\n");
		}
	}
	return operands[0];
}

//연산자 순열 만드는 함수
void permu(int n, int k)
{
	if (n == k)
	{
		if (calc()==0)
		{
			if (result < 20)
			{
				for (int i = 0; i < N - 1; i++)
					printf("%d %c ", i + 1, opss[permut[i]]);
				printf("%d\n", N);
			}
			result++;
		}
	}
	else
	{
		for (int i = 1; i <= 3; i++)
		{
			permut[k] = i;
			permu(n, k + 1);
			permut[k] = 0;
		}
	}
}

int main()
{
	scanf("%d", &N);
	permu(N-1, 0);
	printf("%d", result);
}
