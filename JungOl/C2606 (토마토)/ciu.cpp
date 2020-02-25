#include <cstdio>
//koi 2013 초3
using namespace std;

#define MAX 200000 //큐 최대 크기

int N, M, H; //행, 열, 높이
int map[100][100][100]; //토마토 상자 맵
int qr[MAX]; //행에 대한 원형 큐
int qc[MAX]; //열에 대한 원형 큐
int qh[MAX]; //높이에 대한 원형 큐
int front, rear, qsize = 0; //큐 front, rear, 사이즈
int dR[6] = { -1, 0, 1, 0, 0, 0 }; //열 델타 배열
int dC[6] = { 0, 1, 0, -1, 0, 0 };
int dH[6] = { 0, 0, 0, 0, 1, -1 };
int remain = 0; //익지 않은 토마토 수

int bfs()
{
	int r, c, h, rr, cc, hh;
	int time = 0;
	int limit;
	while (front != rear) //큐 empty 아닌 경우 (front==rear면 empty상태)
	{
		if (remain <= 0) //익지 않은 토마토 없으면 break
			break;
		time++; //시간 증가
		int limit = qsize;
		for (int i = 0; i < limit; i++) //현재 큐 사이즈 만큼 탐색(이번 시간 동안 일어날 수 있는 일만 탐색)
		{
			front = (front + 1) % MAX; //q.front, q.pop
			r = qr[front]; c = qc[front]; h = qh[front];
			qsize--;
			for (int d = 0; d < 6; d++)
			{
				rr = r + dR[d]; cc = c + dC[d]; hh = h + dH[d];
				if (rr < 0 || rr >= N || cc < 0 || cc >= M || hh < 0 || hh >= H) continue;
				if (map[rr][cc][hh]) continue; //0이 아니면 탐색 continue
				map[rr][cc][hh] = 1;
				rear = (rear + 1) % MAX;
				qr[rear] = rr; qc[rear] = cc; qh[rear] = hh; //q.push
				qsize++;
				remain--; //익지 않은 토마토 수 - 1
			}
		}
	}
	if (remain > 0) //아직 익지 않은 토마토가 있으면
		time = -1; //전부 익을 수 없음을 표시
	return time;
}

int main()
{
	front = rear = -1;
	scanf("%d %d %d", &M, &N, &H);
	for(int i=0; i<H; i++)
		for(int j=0; j<N; j++)
			for (int k = 0; k < M; k++)
			{
				scanf("%d", &map[j][k][i]);
				if (map[j][k][i] == 1) //익은 토마토면 큐에 삽입
				{
					rear = (rear + 1) % MAX;
					qr[rear] = j; qc[rear] = k; qh[rear] = i;
					qsize++;
				}
				else if (!map[j][k][i]) //익지 않은 토마토 수 카운팅
					remain++;
			}
	int result = bfs();
	printf("%d", result);

	return 0;
}
