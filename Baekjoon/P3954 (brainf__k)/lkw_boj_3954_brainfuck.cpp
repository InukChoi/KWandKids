#include<iostream>
using namespace std;

int m[100001]; // �����Ͱ� �ٷ�� �޸�
char c[4097];	// ��ɾ���� ��� �迭
int pointer; // �޸��� �ּ�
char p[4097]; // �־��� �Է� ���ڿ� ����
int pdx = 0; // ���ڿ��� ����Ű�� ����. ������ó�� �ּ� �ϳ��� ������
int ls, le; // ������ ���۰� ��

int goto_idx[4097]; // ���� �߻��� �̵��� ��ɾ� �ε���

void init() { // ������ �ʱ�ȭ
	for (int i = 0; i <= 100000; i++)
		m[i] = 0;
	for (int i = 0; i <= 4096; i++)
	{
		c[i] = 0;
		p[i] = 0;
	}
	pointer = 0;
	pdx = 0;
	ls = 0, le = 0;
}

bool compute(int m_s, int c_s, int i_s) {// ���ѷ����� 0, ��������Ǹ� 1
	int pc = 0;
	//int count_pc = 0;
	for(int count_pc=0; count_pc < 50000000; count_pc++) { // ��õ���� ������ ����

		if (c[pc] == '-') {
			m[pointer] = (m[pointer] - 1 + 256) % 256; // 0���� �۾����� 255�� ������
			pc++;
			//cout << "- : " << m[pointer] << endl;
		}
		else if (c[pc] == '+') {
			m[pointer] = (m[pointer] + 1) % 256;
			pc++;
			//cout << "+ : " << m[pointer] << endl;
		}
		else if (c[pc] == '<') {
			pointer = (pointer + m_s - 1) % m_s; // 0���� �������� ���� ������ ������
			pc++;
			//cout << "< : " << pointer << endl;
		}
		else if (c[pc] == '>') {
			pointer = (pointer + 1) % m_s; // ������ ������ ������ ���� ���� ������
			pc++;
			//cout << "> : " << pointer << endl;
		}
		else if (c[pc] == '.') { // ����� ����
			//char t = m[pointer];
			//cout << t << "\n";
			pc++;
		}
		else if (c[pc] == ',') { // 
			if (pdx >= i_s)
				m[pointer] = 255;
			else m[pointer] = p[pdx++];
			pc++;
		}
		else if (c[pc] == '[') {
			if (m[pointer] == 0) {
				pc = goto_idx[pc];
				//pc--;
				//pc++;
			}
			pc++;
		}
		else if (c[pc] == ']') {
			if (m[pointer] != 0) {
				//cout << "] : " << m[pointer] << '\n';				
				pc = goto_idx[pc];
				//pc--;
				//pc++;
			}
			pc++;
		}
		//pc++;
		if (le < pc) // ���� �ٱ��� ���� ���ؾ� ����Ȱ� �ؼ�
			le = pc;
		//cout << "pc : " << pc << "\n";
		if (pc >= c_s)
			return 1;
	}
	return 0;
}

int main() {
	int T;
	int mem_size, code_size, input_size;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		init();
		cin >> mem_size >> code_size >> input_size;
		cin >> c; // ��ɾ�
		cin >> p; // ��¹�

		int ssnt = 0;
		int stack[2048];

		for (int i = 0; i < code_size; i++) {// ������ �����ؾ��� ��ɾ� �ε���
			goto_idx[i] = i + 1;
			if (c[i] == '[') {
				stack[ssnt] = i;
				ssnt++;
			}
			else if (c[i] == ']') {
				goto_idx[i] = stack[ssnt - 1]; // ¦�� �´� ���� ] -> [
				goto_idx[stack[ssnt - 1]] = i; // ¦�� �´� ���� [ -> ]
				ssnt--;
			}

		}
		//cout << "goto : ";
		//for(int i=0; i < code_size; i++)
		//	cout << goto_idx[i] << " ";
		//cout << endl;
		//cout << c << endl;
		//cout << p << endl;
		bool f = compute(mem_size, code_size, input_size);
		if (f)
			cout << "Terminates\n";
		else cout << "Loops " << goto_idx[le] << " " << le << endl;
	}

	return 0;
}