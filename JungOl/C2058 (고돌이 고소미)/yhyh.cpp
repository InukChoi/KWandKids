#include <iostream>
#include <queue>
using namespace std;

#define MIN(a,b)(a<b?a:b)

int N;
int minV = 987654321;
int board[26][26];

int visited[26][26][26][26] = { 0, };//4차 배열..괜찮을까?
int smr, smc, sfr, sfc;
int emr, emc, efr, efc;

int dx[9] = { -1,-1,-1,0,0,0,1,1,1 };
int dy[9] = { -1,0,1,-1,0,1,-1,0,1 };

struct Info
{
	int dist;
	int mr; //고돌이
	int mc;
	int fr; //고소미
	int fc;
};

bool operator<(Info a,Info b)
{
	return a.dist > b.dist;
}

void BFS()
{
	priority_queue<Info> pq;
	pq.push({ 0,smr,smc,sfr,sfc });
	while(!pq.empty())
	{
		int cmr, cmc, cfr, cfc, cdist;
		cmr = pq.top().mr;
		cmc = pq.top().mc;
		cfr = pq.top().fr;
		cfc = pq.top().fc;
		cdist = pq.top().dist;

		pq.pop();
		if (cdist > minV)continue;
		if (cmr == emr && cmc == emc && cfr == efr && cfc == efc) //dist 기록
		{
			minV = MIN(minV, cdist);
		}
		else
		{
			int nmr = cmr, nmc = cmc, nfr = cfr, nfc = cfc;
			
			for (int md = 0; md < 9; md++)//8x8로 해야함
			{
				nmr = cmr + dx[md];
				nmc = cmc + dy[md];
				if (nmr <= 0 || nmr > N || nmc <= 0 || nmc > N)continue;
				if (board[nmr][nmc] == 1)continue;
					

				for(int fd = 0;fd<9;fd++)
				{
					nfr = cfr + dx[fd];
					nfc = cfc + dy[fd];
					if (nfr <= 0 || nfr > N || nfc <= 0 || nfc > N)continue;
					if (board[nfr][nfc] == 1)continue;
					if (visited[nmr][nmc][nfr][nfc])continue;
					if (abs(nfr - nmr) <= 1 && abs(nfc - nmc) <= 1)continue;//8방향에 서로가 있다면
					visited[nmr][nmc][nfr][nfc] = 1;
					pq.push({ cdist + 1,nmr,nmc,nfr,nfc });
				}
			}
			
		}
	}
}
int main()
{
	cin >> N;

	cin >> smr >> smc >> emr >> emc;
	cin >> sfr >> sfc >> efr >> efc;
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=N;j++)
		{
			cin >> board[i][j];
		}
	}
	BFS();
	cout << minV << "\n";
	return 0;
}
