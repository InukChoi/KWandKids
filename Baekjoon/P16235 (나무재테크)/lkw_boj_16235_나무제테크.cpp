#include <time.h>
#include<iostream>
using namespace std;

int N, M, K; //�� ����, ���� ��, �� ��

struct tree {
	int y = 0, x = 0, age = 0;
	tree* next = NULL;
	tree* prev = NULL;
};
tree Tr[10000000]; // ������ �ʹ� ������. �������� ���ô�.
int Trd = 0;


struct trist { // ���Ḯ��Ʈ �ʹ��ʹ� �ȴ�
	tree* head = NULL;
	tree* tail = NULL;

	void insert(tree* a) { // ����Ʈ ����
		if (head == NULL) { // ù ������ ��
			head = a;
			tail = a;
			return;
		}
		else if (head == tail) { // ���� ����Ʈ�� �ϳ� �ۿ� ���� ��
			//cout << "chk 0";
			tree* tmp = head;
			if (cmp(a, tmp)) {
				head = a;
				a->next = tmp;
				tmp->prev = a;
			}
			else {
				tail = a;
				a->prev = tmp;
				tmp->next = a;
			}
			return;
		}
		else {
			//cout << "chk 1";
			tree* tmp = head;
			while (tmp->next != NULL) {
				//cout << "chk 2!";
				if (cmp(a, tmp) == 0) { // ���� ��ġ�� ã�Ƴ�����
					//cout << "chk 3!";
					tmp = tmp->next;
				}
				else {
					//cout << "chk 4!";
					if (tmp != head) { // �� �տ� ������ �ƴϴ�
						tmp->prev->next = a; // if tmp head, error
						a->prev = tmp->prev;
						tmp->prev = a;
						a->next = tmp;
						return;
					}
					else { // �밡���� �����ؾ��Ѵ�
						head = a;
						tmp->prev = a;
						a->next = tmp;
						a->prev = NULL;
						return;
					}
				}
				//cout << "chk !";
			}
			if (cmp(a, tmp)) { // ������ ����
				tmp->prev->next = a;
				a->prev = tmp->prev;
				a->next = tmp;
				tmp->prev = a;
				tmp->next = NULL;
				tail = tmp;
			}
			else { // ���� ����
				tmp->next = a;
				a->prev = tmp;
				tail = a;
			}
		}
	}
	void remove(tree* a) { // ���� �Ф�
		if (a->next == NULL && a->prev == NULL) {// ȥ�ھ�?
			head = NULL;
			tail = NULL;
			//delete a;
		}
		else if (a->prev == NULL) { // ����?
			head = a->next;
			head->prev = NULL;
			//delete a;
		}
		else if (a->next == NULL) { // ������?
			tail = a->prev;
			tail->next = NULL;
			//delete a;
		}
		else { // �߰��̱���
			a->prev->next = a->next;
			a->next->prev = a->prev;
			//delete a;
		}
	}
	bool cmp(tree* a, tree* b) { // 1 ���� �� ����
		if (a->age > b->age)
			return 0;
		else if (b->age >= a->age)
			return 1;

	}
	void prt() {
		tree* tmp = head;
		cout << "-tree info-\n";
		while (tmp != NULL) {
			cout << "r :" << tmp->y << ", c : " << tmp->x << ", age : " << tmp->age << endl;
			tmp = tmp->next;
		}
		cout << endl;
	}
};

int a[11][11]; // static���
int land[11][11];
int deadenergy[11][11];

int dy[8] = { -1,-1,0,1,1,1,0,-1 };
int dx[8] = { 0,1,1,1,0,-1,-1,-1 };

trist T[11][11];

void spring() {
	//������ �ڽ��� ���̸�ŭ ����� �԰�, ���̰� 1 �����Ѵ�. 
	//������ ������ ������ �ִ� 1��1 ũ���� ĭ�� �ִ� ��и� ���� �� �ִ�. 
	//	�ϳ��� ĭ�� ���� ���� ������ �ִٸ�, ���̰� � �������� ����� �Դ´�. 
	//����, ���� ����� ������ �ڽ��� ���̸�ŭ ����� ���� �� ���� ������ ����� ���� ���ϰ� ��� �״´�.
	for (int j = 1; j <= N; j++)
		for (int i = 1; i <= N; i++)
			deadenergy[j][i] = 0;

	for (int j = 1; j <= N; j++) {
		for (int i = 1; i <= N; i++) {
			tree* tmp = T[j][i].head;
			tree* tmp2;
			while (tmp != NULL) {
				if (land[j][i] < tmp->age) {
					tmp2 = tmp;
					tmp = tmp->next;
					deadenergy[j][i] += tmp2->age / 2;
					//cout << "r :" << tmp2->y << ", c : " << tmp2->x << ", age : " << tmp2->age << endl;
					T[j][i].remove(tmp2);
				}
				else {
					land[j][i] -= tmp->age;
					tmp->age++;
					tmp = tmp->next;
				}
			}
		}
	}
}
void summer() {
	// summer
			//�������� ���� ���� ������ ������� ���ϰ� �ȴ�.
			//������ ���� �������� ���̸� 2�� ���� ���� ������ �ִ� ĭ�� ������� �߰��ȴ�.�Ҽ��� �Ʒ��� ������.
	for (int j = 1; j <= N; j++)
		for (int i = 1; i <= N; i++)
			land[j][i] += deadenergy[j][i];
}
void autumn() {
	//�������� ������ �����Ѵ�.�����ϴ� ������ ���̰� 5�� ����̾�� �ϸ�, 
	//������ 8���� ĭ�� ���̰� 1�� ������ �����.
	//���� ���� ����� ĭ���� ������ ������ �ʴ´�.
	tree* auttmp[11][11];
	for (int j = 1; j <= N; j++)
		for (int i = 1; i <= N; i++)
			auttmp[j][i] = T[j][i].head;

	for (int j = 1; j <= N; j++) {
		for (int i = 1; i <= N; i++) {
			tree* tmp = auttmp[j][i];
			int y0, x0;
			while (tmp != NULL) {
				if (tmp->age % 5 == 0) {
					for (int i = 0; i < 8; i++) {
						y0 = tmp->y + dy[i];
						x0 = tmp->x + dx[i];
						if (y0 >= 1 && y0 <= N && x0 >= 1 && x0 <= N) {
							tree* nt = &Tr[Trd];//new tree;
							Trd++;
							nt->age = 1;
							nt->y = y0;
							nt->x = x0;
							//cout << "chk 4";
							T[y0][x0].insert(nt); // error
							//cout << "r :" << nt->y << ", c : " << nt->x << ", age : " << nt->age << endl;
						}
					}
				}
				tmp = tmp->next;
			}
		}
	}
}
void winter() {
	for (int j = 1; j <= N; j++)
		for (int i = 1; i <= N; i++)
			land[j][i] += a[j][i];
}
int main() {
	clock_t start, end; // ���� �Ҵ翡�� ���� �ð��� �䱸�Ǵ� ���� �˾Ұ�, �̸� �����ϰ��� �������� �̳��� �̸� ��Ƴ�

	cin >> N >> M >> K;

	for (int j = 1; j <= N; j++)
		for (int i = 1; i <= N; i++) {
			cin >> a[j][i];
			land[j][i] = 5;
		}
	int r, c, a;
	for (int i = 0; i < M; i++) {
		cin >> r >> c >> a;
		tree* tmp = &Tr[Trd];//new tree;
		Trd++;
		tmp->y = r;
		tmp->x = c;
		tmp->age = a;
		T[r][c].insert(tmp);
		//T.prt();
	}

	double tspr = 0, tsum = 0, taut = 0, twin = 0;

	for (int i = 1; i <= K; i++) {
		//cout << i << "��° ��" << endl;
		//start = clock();
		spring();
		//end = clock();
		//tspr += end - start;
		//cout << "��° ����" << endl;

		//start = clock();
		summer();
		//end = clock();
		//tsum += end - start;
		//T.prt();

		//cout << i << "��° ����" << endl;
		//start = clock();
		autumn();
		//end = clock();
		//t/aut += end - start;
		//T.prt();

		//cout << i << "��° �ܿ�" << endl;
		//start = clock();
		winter();
		//end = clock();
		//twin += end - start;
		//T.prt();
	}
	//T[1][1].prt();

	//cout << " ��  : " << tspr <<endl;
	//cout << "���� : " << tsum << endl;
	//cout << "���� : " << taut << endl;
	//c/out << "�ܿ� : " << twin << endl;

	int count = 0;

	for (int j = 1; j <= N; j++) {
		for (int i = 1; i <= N; i++) {
			tree* tmp = T[j][i].head;
			while (tmp != NULL)
			{
				count++;
				tmp = tmp->next;
			}
		}
	}
	cout << count;

	/*
	for (int j = 1; j <= N; j++) {
		for (int i = 1; i <= N; i++) {
			tree* rp = T[j][i].head;
			tree* rp2;
			while (rp != NULL) {
				rp2 = rp;
				rp = rp->next;
				delete rp2;
			}
		}
	}
	*/

	return 0;
}