#include <cstdio>
//Koi 1999 - 중등부 2번
using namespace std;

int N, K;				//격자 판 크기, 회로 위 비용
int map[50][50];		//시작점, 끝점, 설치되어 있는 회로 나타내는 맵
int visited[50][50];	//방문 표시와 최소 비용 동시에 나타낼 맵
int parent[50][50];		//현재 칸의 부모(이전) 칸 나타내는 맵
int st[2501];			//설치할 경로의 전체 경로를 나타낼 스택
int result[100];		//결과 좌표
int s_r, s_c, d_r, d_c; //시작점, 끝점
int dR[4] = { -1, 0, 1, 0 }; //bfs 할 때 사용할 델타 배열
int dC[4] = { 0, 1, 0, -1 };
int queue[10000];		//bfs 할 때 사용할 큐

void bfs(int r, int c)
{
	int f = -1, rear = -1; //큐 front, rear
	int rr, cc;
	queue[++rear] = r * N + c; //현재 위치 1차원으로 변환하여 삽입
	int pos;
	int cost;
	if (map[r][c] == 1)	cost = K; //현재 위치가 회로 위라면 해당 비용
	else cost = 1; //회로가 아닌 빈 칸이면 1
	visited[r][c] = cost;
	parent[r][c] = -1; //첫 시작점의 부모는 -1로 설정
	while (f != rear)
	{
		pos = queue[++f];
		r = pos / N;
		c = pos % N;
		for (int i = 0; i < 4; i++)
		{
			rr = r + dR[i]; cc = c + dC[i];
			if (rr < 0 || rr >= N || cc < 0 || cc >= N) continue;
			if (map[rr][cc] == 1)	cost = K; //회로 위면 해당 비용
			else cost = 1;
			if (!visited[rr][cc]) //빈 칸인 경우
			{
				visited[rr][cc] = visited[r][c] + cost;
				queue[++rear] = rr * N + cc;
				parent[rr][cc] = r * N + c;
			}
			else if (visited[rr][cc] > visited[r][c] + cost) //빈 칸이 아니고 기존 최소비용보다 더 적은 비용인 경우
			{
				visited[rr][cc] = visited[r][c] + cost;
				queue[++rear] = rr * N + cc;
				parent[rr][cc] = r * N + c;
			}				
		}
	}
}

//전체 경로를 스택에 쌓는 함수 (도착점 -> 시작점)
int find_path()
{
	int r = d_r, c = d_c;
	int top = -1;
	int pos;
	st[++top] = r * N + c; //도착점부터 스택에 쌓음
	while (parent[r][c] > -1)
	{
		pos = parent[r][c];
		st[++top] = pos;
		r = pos / N; c = pos % N;
	}
	return top;
}

//전체 경로를 이용하여 시작점, 꺾이는 지점, 끝점 result 배열에 삽입
int make_result(int top)
{
	int cnt = 0;
	int pos, r, c, rr, cc;
	int c_flag = 0, r_flag = 0; //열이 바뀌고 있음을 나타내는 flag, 행이 바뀌고 있음을 나타내는 flag
	pos = st[top--];
	r = pos / N;
	c = pos % N;
	pos = st[top--];
	rr = pos / N;
	cc = pos % N;
	if (rr == r) //첫 지점과 다음 지점을 비교하여 r이 같으면 c가 변하고 있음을 나타내는 c_flag를 1로 기록
		c_flag = 1;
	else
		r_flag = 1;
	result[cnt++] = r * N + c; //시작점 삽입
	r = rr; c = cc;
	while (top > -1)
	{
		pos = st[top--];
		rr = pos / N;
		cc = pos % N;
		if (c_flag&&rr != r) //c가 변하고 있는데 r이 변하면 꺾이는 지점으로 생각
		{
			r_flag = 1; c_flag = 0;
			result[cnt++] = r*N+c;
		}
		else if (r_flag&&cc != c)
		{
			c_flag = 1; r_flag = 0;
			result[cnt++] = r*N+c;
		}			
		r = rr; c = cc;
	}
	result[cnt++] = d_r * N + d_c; //마지막 점 삽입
	return cnt;
}

int main()
{
	scanf("%d", &N);
	scanf("%d %d %d %d", &s_r, &s_c, &d_r, &d_c);
	s_r--; s_c--; d_r--; d_c--;
	map[s_r][s_c] = map[d_r][d_c] = 2;
	scanf("%d", &K);
	int L; //회로 수
	scanf("%d", &L);
	
	//맵에 설치되어 있던 회로 기록
	for (int i = 0; i < L; i++)
	{
		int J;
		int r, c, rr, cc;
		scanf("%d", &J);
		scanf("%d %d", &r, &c); r--; c--;
		map[r][c] = 1;
		for (int j = 1; j < J; j++)
		{
			scanf("%d %d", &rr, &cc); rr--; cc--;
			while (rr != r || cc != c)
			{
				if (rr > r)
					r++;
				else if (rr < r)
					r--;
				if (cc > c)
					c++;
				else if (cc < c)
					c--;
				map[r][c] = 1;
			}
			map[r][c] = 1;
		}
	}
	bfs(s_r, s_c); //최소비용 탐색
	int top = find_path(); //전체 경로 만들기
	int cnt = make_result(top); //전체 경로로 부터 시작점, 꺾이는 점, 끝점 구하기
	printf("%d\n%d", visited[d_r][d_c], cnt);
	for (int i = 0; i < cnt; i++)
	{
		printf("% d %d", result[i] / N+1, result[i] % N+1);
	}
}
