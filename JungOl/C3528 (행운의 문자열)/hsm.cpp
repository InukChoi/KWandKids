#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

int cnt, ans;
string s;
vector<int> alph(26);
vector<int> v;

void dfs(int x) {
	if (cnt == s.size()) {
		ans++;
		return;
	}
	
	for (int i = 0; i < 26; i++) {
		if (alph[i] != 0) {
			if (x != i) {
				alph[i]--;
				cnt++;
				dfs(i);
				alph[i]++;
				cnt--;
			}
		}
	}
	return;
}
int main() {
	cin >> s;
	
	for (int i = 0; i < s.size(); i++) {
		alph[s[i] - 'a']++;
	}

	ans = 0;
	for (int i = 0; i < 26; i++) {
		cnt = 1;
		if (alph[i] != 0) {
			alph[i]--;
			dfs(i);
			alph[i]++;
		}
	}
	
	printf("%d\n", ans);
	//system("pause");
	return 0;
}
