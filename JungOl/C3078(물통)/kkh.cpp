#include <iostream>
#include <queue>
#include <set>
using namespace std;
int a, b, c, d;
struct bottle { int x, y, cnt;};
queue<bottle> q;
set<pair<int, int> > s;
int main() {
    cin >> a >> b >> c >> d;
 
    q.push({ 0,0,0 }); // 물, 물, 횟수
    set<pair<int, int> >::iterator iter;
    int flag = 1;
    while (!q.empty()) {
        bottle tmp = q.front();
        q.pop();
         
        if (tmp.x == c && tmp.y == d) { //목표에 도달하면 출력 후 횟수 출력 후 루프 탈출
            cout << tmp.cnt;
            flag = 0;
            break;
        }
 
        iter = s.find({ tmp.x, tmp.y }); // 현재 물의 비율이 기존에 나왔었는지 확인
        if (iter != s.end()) // 있었으면 패스
            continue;
 
        s.insert({ tmp.x, tmp.y }); //없으면 set에 추가
         
        if (tmp.x != 0 && tmp.x != a) { //첫번째 물통에 물 채우기 , 버리기
            q.push({ a, tmp.y, tmp.cnt + 1 });
            q.push({ 0, tmp.y, tmp.cnt + 1 });
        }
        else if(tmp.x == 0) //없을땐 채우고
            q.push({ a, tmp.y, tmp.cnt + 1 });
        else if(tmp.x == a) //꽉차있으면 버리기만
            q.push({ 0, tmp.y, tmp.cnt + 1 });
             
         
        if (tmp.y != 0 && tmp.y != b) { //두번째도 마찬가지
            q.push({ tmp.x, b, tmp.cnt + 1 });
            q.push({ tmp.x, 0, tmp.cnt + 1 });
        }
        else if (tmp.y == 0)
            q.push({ tmp.x, b, tmp.cnt + 1 });
        else if (tmp.y == b)
            q.push({ tmp.x, 0, tmp.cnt + 1 });
 
 
        if (tmp.y > 0 && tmp.x != a) { //두번째 물을 첫번째에
            if (a - tmp.x >= tmp.y)
                q.push({ tmp.x + tmp.y, 0, tmp.cnt + 1 });
            else
                q.push({ a, tmp.y - (a - tmp.x), tmp.cnt + 1 });
        }
 
        if (tmp.x > 0 && tmp.y != b) { //첫번째 물을 두번째에
            if (b - tmp.y >= tmp.x)
                q.push({ 0, tmp.y + tmp.x, tmp.cnt + 1 });
            else
                q.push({ tmp.x - (b - tmp.y), b, tmp.cnt + 1 });
        }       
    }
 
    if (flag) //못찾은 경우 플래그
        cout << -1;
 
    return 0;
}
