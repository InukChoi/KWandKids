import java.util.*;
public class Main {

	static int[][] circles; //����
	static int[] startIdx; //������ �� ���� �ε���
	static int N, M; //���� ��, �� ������ ���� ����
	static int[] dr = {0, 1, 0, -1}; //���� Ž�� �� ����� ����(��, �Ʒ�)
	static int[] dc = {1, 0, -1, 0}; //���� Ž�� �� ����� ����(��, ��)
	
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		N = in.nextInt();
		M = in.nextInt();
		int T = in.nextInt();	//���� ȸ�� �� �Է�
		circles = new int[N][M];
		startIdx = new int[N];
		for(int i=0; i<N; i++)
			for(int j=0; j<M; j++)
				circles[i][j] = in.nextInt();
		int x,d,k;	//ȸ���� ����(x�� ����� �ش��ϴ� ���� ȸ��), ȸ�� ����, ȸ�� �� 
		for(int i=0; i<T; i++)
		{
			Queue<Pos> queue = new LinkedList<>(); //Ž���� ���� ť
			x=in.nextInt();
			d = in.nextInt();
			k = in.nextInt();
			rotate(x, d, k);	//���ǵ� ȸ��
			boolean flag = false; //ȸ�� ���� ���� Ž�� �� �������� �� ���� ��츦 ����  flag
			for(int n=0; n<N; n++)
				for(int m=0; m<M; m++)
				{
					queue = new LinkedList<>();
					queue.add(new Pos(n, m));	//������ ���� �ϳ��� ť�� �߰�
					if(bfs(queue, circles[n][m])) //���ǵ��� �� ���Ҹ��� ���� Ž��
						flag = true;			  //������ �� �ϳ��� ������ true
				}
			if(!flag)	//�������� ������ ��� ����Ͽ� ����
				meanCalc();
		}
		int sum=0;
		//���������� ���� ���ϱ�
		for(int n=0; n<N; n++)
			for(int m=0; m<M; m++)
			{
				if(circles[n][m]>0)
					sum+=circles[n][m];
			}
		System.out.println(sum);
		in.close();
	}
	
	public static void rotate(int x, int d, int k) {
		k%=M;	//ȸ�� ���� ��ⷯ �����Ͽ� ������ ����(M)�� �� �Ѱ� ����
		int dir = d==0 ? -1*k : 1*k; //ȸ�� ���⿡ ���� -�� �� �� +�� �� ���� 
		for(int i=1; i*x-1<N; i++) //x�� ����� �ش��ϴ� ���ǿ� ���� ���� �ε��� ����
		{
			//�ش� ���� �ε����� ȸ������ �����ֵ� ������ �� �� �����Ƿ� ����(M)�� ������(������ ����� 2*M-1 ���ϰ� ��)
			//�������� ��� M�� ������ �͸����ε� ���ϴ� ���� �ε����� ��
			//������� ��� M�� ���������Ƿ� %M�� �ϰ� �Ǹ� ���ϴ� ���� �ε����� ��
			startIdx[(i*x)-1] = (startIdx[(i*x)-1]+dir+M)%M; 
		}
	}
	
	public static boolean bfs(Queue<Pos> queue, int ori) {
		boolean flag = false;	//�� ���̶� ������ ���� �־� ������ ���� �ִ��� Ȯ���ϴ� flag
		
		/*
		 *���� ��, ���� ��, ������, ������(�߻�), ���� ������.
		 *nextC�� ��� ȸ���� �迭�鿡 ���� �ش� ���� �������� ��, �Ʒ� ������ ���� �ǹ�
		 *r=0, c=0�� �� nextR=1, nextC=0�̸� �Ʒ� ��, ���� ���� �ǹ� ��
		 *�׷��� ���� �ٷ� ���� �Ʒ��� ������ ���� �ε����� �ش� ������ ���� �ε����ʹ� �ٸ�
		 *���� ���� ������ �����ε����� 1, �Ʒ� �࿡ �ش��ϴ� ����(�ٱ��� ����)�� �����ε����� M-1�� ���
		 *���� ������ ���� 0�� �ƴ϶� M-3�� ��(M>2�� ��).
		 *���� ������ �迭�� �ε����� Ȱ���� realC�� ����.
		*/
		int r, c, nextR, nextC, realC;  
		Pos pos; //r,c�� ���� Pos ��ü
		if(ori<0) //�ش� ��ġ�� ������ ���� 0���ϸ� �̹� ������ ���̹Ƿ� false�� ��ȯ�ϸ� ����.
			return flag;
		while(!queue.isEmpty()) //ť�� ���� ����� �� ����(���� ���� ������ ����)
		{
			pos = queue.poll();
			r = pos.r;
			c = pos.c;
			for(int i=0; i<dr.length; i++) //��,��,��,�쿡 ���� Ž��
			{
				nextR = r+dr[i]; 
				nextC = c+dc[i];
				if(0<=nextR&&nextR<N) //������ ���� �ȿ� �ش� �� ��(0���� �����̳� M�Ѵ� ������ �����Ƿ�)
				{
					/*���� ���� �� �ε����� ���� �� 
					 *���� ������ ���� �ε�����ŭ ���༭ ���� �迭(ȸ������ ���� ����)�̾��� ���� ���� ���ϰ�
					 *���� ������ ���� �ε�����ŭ �����༭ ���� ���ǿ� �´� �� �ε����� ���ϵ�
					 *���� �� �� �����Ƿ� M�� �����ְ� M���� ū ���� �� ��츦 ���� %M�� ����
					 */
					realC = (nextC-startIdx[r]+startIdx[nextR]+M)%M;
					
					//����� ���� (���� ��, ���� ���� ��)�� ���ڰ� ���� ���� ������ Ž�� ���� 
					if(circles[nextR][realC]==ori)
					{
						circles[r][c]=-1;	//���� �� ����
						circles[nextR][realC] = -1; //(���� ��, ���� ���� ��)�� �� ����
						queue.add(new Pos(nextR, realC)); //ť�� �߰� �Ͽ� ���� Ž�� ����
						flag = true; //���� �� ���� ������ ǥ���ϱ� ���� flag
					}
				}
			}
		}
		return flag;
	}
	
	//����� ���� �� ��� ���� ���� ������ +1 ��� ���� ū ������ -1
	public static void meanCalc() {
		int sum = 0, count=0;;
		for(int n=0; n<N; n++)
			for(int m=0; m<M; m++)
			{
				if(circles[n][m]>0)
				{
					sum+=circles[n][m];
					count++;
				}
			}
		
		double mean = (double)sum/(double)count;
		
		int num=0;
		for(int n=0; n<N; n++)
			for(int m=0; m<M; m++)
			{
				num = circles[n][m];
				if(num>0)
				{
					if(num>mean)
						circles[n][m]--;
					else if(num<mean)
						circles[n][m]++;
				}
			}
	}
	
	static class Pos{ //��, ���� �ε����� ���� ��ü
		int r;
		int c;
		public Pos(int r, int c) {
			this.r = r;
			this.c = c;
		}
	}
}