#include <cstdio>
#include <set>
#include <utility>
//koi 2017 고1
using namespace std;

int A, B; //물통 A, B 총 용량
int t_a, t_b; //물통 A, B의 원하는 최종 상태
pair<int, int> queue[100000]; //물통 상태 원형 큐
set<pair<int, int>> s; //존재했던 물통 상태 set

//물통 A(sel=0), B(sel=1)에 물 가득 채우는 함수
void fill(int *a, int *b, int sel)
{
	if (!sel) *a = A;
	else *b = B;
}

//물통 A(sel=0), B(sel=1)에서 물 전부 버리는 함수
void empty(int* a, int* b, int sel)
{
	if (!sel) *a = 0;
	else *b = 0;
}

//물통 A에서 B(sel=0), 혹은 B에서 A(sel=1)로 물 붓는 함수
void move(int *a, int *b, int sel)
{
	if (!sel) //A에서 B로 물 붓는 경우
	{
		if (*a <= B - *b) { *b += *a; *a = 0; } //B에 남은 공간이 A에 남은 공간 보다 큰 경우
		else { *a -= B - *b; *b = B; }
	}
	else
	{
		if (*b <= A - *a) { *a += *b; *b = 0; }
		else { *b -= A - *a; *a = A; }
	}
}

//물통 작업 나누는 함수
void work(int *a, int *b, int sel)
{
	if (sel / 2 == 0)
		fill(a, b, sel % 2);
	else if (sel / 2 == 1)
		empty(a, b, sel % 2);
	else if (sel / 2 == 2)
		move(a, b, sel % 2);
}

int bfs()
{
	int f = -1, r = -1;
	int aa, bb; //물통 다음 상태
	int qsize = 0, time = 0; //큐 사이즈, 현재까지 걸린 작업 수
	int limit;
	if (t_a == 0 && t_b == 0) //0, 0인 상황은 바로 0 반환
		return 0;
	queue[++r] = make_pair(A, 0); s.insert(make_pair(A, 0));
	queue[++r] = make_pair(0, B); s.insert(make_pair(0, B));
	pair<int, int> p, pp;
	qsize += 2;
	set<pair<int, int>>::iterator iter;
	while (f != r)
	{
		time++; //작업 시간 증가
		limit = qsize; //현재 큐 사이즈 기억
		for (int i = 0; i < limit; i++) //현재 큐 사이즈 만큼 진행
		{
			f = (f + 1) % 100000;
			p = queue[f]; qsize--;
			if (p.first == t_a && p.second == t_b) return time; //원하는 상태 도달하면 현재 시간 반환
			for (int j = 0; j < 6; j++)
			{
				aa = p.first; bb = p.second;
				work(&aa, &bb, j); //작업을 통한 다음 상태 반환 받음
				pp = make_pair(aa, bb);
				iter = s.find(pp);
				if (iter == s.end()) //이때까지 없었던 상태만
				{
					s.insert(pp); //물통 상태 set에 추가
					r = (r + 1) % 100000;
					queue[r] = pp;
					qsize++;
				}
			}
		}
	}
	return -1;
}

int main()
{
	scanf("%d %d %d %d", &A, &B, &t_a, &t_b);
	int result = bfs();
	printf("%d", result);
}
