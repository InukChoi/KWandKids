#include<stdio.h>
#include<iostream>
#include<queue>
#include<vector>
#include<cstring>
#include<map>

using namespace std;

struct Bottle
{
	int a_state, b_state, cnt;
};
int a, b, c, d;
int ans = -1;
//int visited[100001][100001]; -> Can't use 2-D array
map<pair<int, int>, int> visited;
queue<Bottle> q;

int main() {
	scanf("%d %d %d %d", &a, &b, &c, &d);

	q.push({ 0,0,0 });

	while (!q.empty()) {
		int t1 = q.front().a_state;
		int t2 = q.front().b_state;
		int t3 = q.front().cnt;
		visited[{t1, t2}] = t3;
		q.pop();

		if (t1 == c && t2 == d) {
			ans = t3;
			break;
		}

		for (int i = 0; i < 6; i++) {
			//fill A
			if (i == 0) {
				if (visited.count({ a,t2 }) == 0) {
					q.push({ a,t2,t3 + 1 });
				}
			}
			//fill B
			if (i == 1) {
				if (visited.count({ t1,b }) == 0) {
					q.push({ t1,b,t3 + 1 });
				}
			}
			//Empty A
			if (i == 2) {
				if (visited.count({ 0,t2 }) == 0) {
					q.push({ 0,t2,t3 + 1 });
				}
			}
			//Empty B
			if (i == 3) {
				if (visited.count({ t1,0 }) == 0) {
					q.push({ t1,0,t3 + 1 });
				}
			}
			//Move water A -> B
			if (i == 4) {
				int temp = b - t2; //empty space
				int temp1 = t1;
				int temp2 = t2;
				if (temp1 > temp) {
					temp1 -= temp;
					temp2 = b;
				}
				else {
					temp2 += temp1;
					temp1 = 0;
				}
				if (visited.count({ temp1,temp2 }) == 0) {
					q.push({ temp1,temp2,t3 + 1 });
				}
			}
			//Move water B -> A
			if (i == 5) {
				int temp = a - t1; //empty space
				int temp1 = t1;
				int temp2 = t2;
				if (temp2 > temp) {
					temp2 -= temp;
					temp1 = a;
				}
				else {
					temp1 += temp2;
					temp2 = 0;
				}
				if (visited.count({ temp1,temp2 }) == 0) {
					q.push({ temp1,temp2,t3 + 1 });
				}
			}
		}
	}

	printf("%d\n", ans);
	//system("pause");
	return 0;
}
