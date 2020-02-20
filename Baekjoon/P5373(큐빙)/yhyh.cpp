#include <iostream>
using namespace std;

char cubing[6][3][3]; //총 6면 3x3

void rotate(char board)
{
	char ftmp[3];
	/*
	// 윗 면은 흰색(0), 아랫 면은 노란색(1), 앞 면은 빨간색(2), 뒷 면은 오렌지색(3), 왼쪽 면은 초록색(4), 오른쪽 면은 파란색(5)
	U: 윗 면, D: 아랫 면, F: 앞 면, B: 뒷 면, L: 왼쪽 면, R: 오른쪽 면이다.
	두 번째 문자는 돌린 방향이다. +인 경우에는 시계 방향 (그 면을 바라봤을 때가 기준), -인 경우에는 반시계 방향이다.
	*/
	
	int cBoard = 0;//현재 면
	int sequence[4];
	switch (board)
	{
	case 'U'://위
		sequence[0] = 4;
		sequence[1] = 2;
		sequence[2] = 5;
		sequence[3] = 3;

		for (int i = 0; i < 3; i++)
		{
			ftmp[i] = cubing[sequence[0]][0][i];// 뒷면 <- 왼쪽면 (열 순서 그대로)
		}
		for (int i = 0; i < 3; i++)
		{
			cubing[sequence[0]][0][i] = cubing[sequence[1]][0][i]; //왼쪽면 <- 앞면(열 순서 그대로)
		}
		for (int i = 0; i < 3; i++)
		{
			cubing[sequence[1]][0][i] = cubing[sequence[2]][0][i]; //앞면 <- 오른쪽면(열 순서 그대로)
		}
		for (int i = 0; i < 3; i++)
		{
			cubing[sequence[2]][0][i] = cubing[sequence[3]][0][i]; //오른쪽면 <- 뒷면(열 순서 그대로)
		}
		for (int i = 0; i < 3; i++)
		{
			cubing[sequence[3]][0][i] = ftmp[i];//왼쪽 <- 뒷면(임시 저장했던 것 다시 옮기기)
		}


		break;
	case 'D':
		cBoard = 1;

		sequence[0] = 3; //뒷면
		sequence[1] = 5; //오른쪽면
		sequence[2] = 2; //앞면
		sequence[3] = 4; //왼쪽면

		for (int i = 0; i < 3; i++)
		{
			ftmp[i] = cubing[sequence[0]][2][i];// 왼쪽면 <- 뒷면 (열 순서가 그대로)
		}
		for (int i = 0; i < 3; i++)
		{
			cubing[sequence[0]][2][i] = cubing[sequence[1]][2][i]; //뒷면 <- 오른쪽면(열 순서 그대로)
		}
		for (int i = 0; i < 3; i++)
		{
			cubing[sequence[1]][2][i] = cubing[sequence[2]][2][i]; //오른쪽면 <- 앞면(열 순서 그댏)
		}
		for (int i = 0; i < 3; i++)
		{
			cubing[sequence[2]][2][i] = cubing[sequence[3]][2][i]; //앞면 <- 왼쪽면(열 순서 그대로)
		}
		for (int i = 0; i < 3; i++)
		{
			cubing[sequence[3]][2][i] = ftmp[i];//왼쪽 <- 뒷면(열 순서 그대로)
		}
		break;
	case 'F':
		cBoard = 2;
		//0 5 1 4
		sequence[0] = 4; //왼
		sequence[1] = 1; //아래
		sequence[2] = 5; //오
		sequence[3] = 0; //위

		//여기서는 행<-> 열 이렇게 바뀌기도 함.. ㅎㅎ ^_ㅠ
		for (int i = 0; i < 3; i++)
		{
			ftmp[2 - i] = cubing[sequence[0]][i][2];// 윗면(아래 행) <- 왼쪽(오른쪽 열)면 (순서가 뒤집힘)
		}
		for (int i = 0; i < 3; i++)
		{
			cubing[sequence[0]][i][2] = cubing[sequence[1]][0][i]; //왼쪽면(오른쪽 열) <- 아랫면(윗 행)(순서 그대로)
		}
		for (int i = 0; i < 3; i++)
		{
			cubing[sequence[1]][0][2 - i] = cubing[sequence[2]][i][0]; //아랫면(윗 행) <- 오른쪽면(왼쪽 열)(순서 바뀜)
		}
		for (int i = 0; i < 3; i++)
		{
			cubing[sequence[2]][i][0] = cubing[sequence[3]][2][i]; //오른쪽(왼쪽 열)면 <- 윗면(아래 행)(열 순서 그대로)
		}
		for (int i = 0; i < 3; i++)
		{
			cubing[sequence[3]][2][i] = ftmp[i];//윗면(아래 행) <- 왼쪽면(임시 저장했던 것 다시 옮기기)
		}
		break;
	case 'B':
		cBoard = 3;
		sequence[0] = 0; //위
		sequence[1] = 5; //오
		sequence[2] = 1; //아래
		sequence[3] = 4; //왼

		for (int i = 0; i < 3; i++)
		{
			ftmp[2 - i] = cubing[sequence[0]][0][i];// 왼쪽면(왼쪽 열) <- 윗(윗 행)면 (순서가 뒤집힘)
		}
		for (int i = 0; i < 3; i++)
		{
			cubing[sequence[0]][0][i] = cubing[sequence[1]][i][2]; //윗면(윗 행) <- 오른쪽면(오른쪽 열)(순서 그대로)
		}
		for (int i = 0; i < 3; i++)
		{
			cubing[sequence[1]][2 - i][2] = cubing[sequence[2]][2][i]; //오른쪽면(오른쪽 열) <- 아랫면(아래 행)(순서 바뀜)
		}
		for (int i = 0; i < 3; i++)
		{
			cubing[sequence[2]][2][i] = cubing[sequence[3]][i][0]; //아랫(아래 행)면 <- 왼쪽면(왼쪽 열)(순서 그대로)
		}
		for (int i = 0; i < 3; i++)
		{
			cubing[sequence[3]][i][0] = ftmp[i];//왼쪽면(왼쪽 열) <- 윗면(임시 저장했던 것 다시 옮기기)
		}
		break;
	case 'L':
		cBoard = 4;
		//0 3 1 2
		sequence[0] = 0; //위
		sequence[1] = 3; //뒷면
		sequence[2] = 1; //아래
		sequence[3] = 2; //앞면

		for (int i = 0; i < 3; i++)
		{
			ftmp[i] = cubing[sequence[0]][i][0];// 앞면(왼쪽 열) <- 윗(왼쪽 열)면 (순서 그대로)
		}
		for (int i = 0; i < 3; i++)
		{
			cubing[sequence[0]][2 - i][0] = cubing[sequence[1]][i][2]; //윗면(왼쪽 열) <- 뒷면(오른쪽 열)(순서 바뀜)
		}
		for (int i = 0; i < 3; i++)
		{
			cubing[sequence[1]][2-i][2] = cubing[sequence[2]][i][0]; //뒷면() <- 아랫면()(순서 바뀜)
		}
		for (int i = 0; i < 3; i++)
		{
			cubing[sequence[2]][i][0] = cubing[sequence[3]][i][0]; //아랫()면 <- 앞면()(순서 그대로)
		}
		for (int i = 0; i < 3; i++)
		{
			cubing[sequence[3]][i][0] = ftmp[i];//앞면() <- 윗면(임시 저장했던 것 다시 옮기기)
		}
		break;
	case 'R':
		cBoard = 5;
		//0 3 1 2
		sequence[0] = 2; //앞면
		sequence[1] = 1; //아래
		sequence[2] = 3; //뒤
		sequence[3] = 0; //윗

		for (int i = 0; i < 3; i++)
		{
			ftmp[i] = cubing[sequence[0]][i][2];// 윗면(오른쪽 열) <- 앞(오른쪽 열)면 (순서 그대로)
		}
		for (int i = 0; i < 3; i++)
		{
			cubing[sequence[0]][i][2] = cubing[sequence[1]][i][2]; //앞면() <- 아래면()(순서 그대로)
		}
		for (int i = 0; i < 3; i++)
		{
			cubing[sequence[1]][2-i][2] = cubing[sequence[2]][i][0]; //아래면() <- 뒷면()(순서 바뀜)
		}
		for (int i = 0; i < 3; i++)
		{
			cubing[sequence[2]][2 - i][0] = cubing[sequence[3]][i][2]; //뒷()면 <- 윗면()(순서 바뀜)
		}
		for (int i = 0; i < 3; i++)
		{
			cubing[sequence[3]][i][2] = ftmp[i];//윗면() <- 앞면(임시 저장했던 것 다시 옮기기)
		}
		break;
	}
	//해당 면 회전

	char tmp[3][3];
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)tmp[r][c] = cubing[cBoard][2 - c][r];
	}
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)cubing[cBoard][r][c] = tmp[r][c];
	}
	//인접한 면들 회전

	
	
}

int main()
{
	int T;
	cin >> T;
	for (int t = 0; t < T; t++)
	{
		//큐빙 초기화
		for (int i = 0; i < 6; i++)
		{
			// 윗 면은 흰색, 아랫 면은 노란색, 앞 면은 빨간색, 뒷 면은 오렌지색, 왼쪽 면은 초록색, 오른쪽 면은 파란색
			//흰색은 w, 노란색은 y, 빨간색은 r, 오렌지색은 o, 초록색은 g, 파란색은 b.
			char color;
			switch (i)
			{
			case 0:
				color = 'w';
				break;
			case 1:
				color = 'y';
				break;
			case 2:
				color = 'r';
				break;
			case 3:
				color = 'o';
				break;
			case 4:
				color = 'g';
				break;
			case 5:
				color = 'b';
				break;
			}
			for (int j = 0; j < 3; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					cubing[i][j][k] = color;
				}
			}
		}

		int N;
		cin >> N;
		for (int i = 0; i < N; i++)
		{
			char board, dir;//면, 방향
			cin >> board;
			cin >> dir;
			if(dir=='+')rotate(board);
			else 
			{
				for (int j = 0; j < 3; j++)rotate(board);
			}
		}

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				cout << cubing[0][i][j];
			}
			cout << '\n';
		}
	}
	return 0;
}
