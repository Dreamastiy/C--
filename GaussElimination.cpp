#include <iostream>     
#include <cmath>    
#include <vector>
#define SIZE 20

using namespace std;

bool equalZero(float Zero);
vector < vector<double> > gauss(vector< vector<double> > A, int n, int m);

bool equalZero(double Zero)
{
	bool result = false;
	result = abs(Zero) < 0.0000001;
	return result;
}

vector < vector<double> > gauss(vector< vector<double> > A, int n, int m)
{
	//��������� ������ ��������� �������:
	//���� ���������� ������ ������� (� ��� ����� ������) ������� ������� ����� ���� �����
	//����� ���������� ������� ������� ������� ����� ���� ����� ����� ������ � �.�.
	//�������� ��������������� ����������
	//�.�. ������� ����� ���� ������������� ���������� min (n, m)
	int l = min(n, m);
	for (int i=0; i < l; i++) 
	{
		// ���� ������ ������ � ������������ ���������
		double elementMax = abs(A[i][i]); 
		int rowMax = i;
		for (int k = i + 1; k < l; k++) 
		{
			if (abs(A[k][i]) > elementMax) 
			{
				elementMax = abs(A[k][i]);
				rowMax = k;
			}
		}

		//������ ��������������� ����� ������� (���������, ��� ��� ����� ���� ������� ��������)
		for (int k = i; k < (m + 1) ; k++) {
			double tmp = A[rowMax][k];
			A[rowMax][k] = A[i][k];
			A[i][k] = tmp;
		}

		// ����������� ���������������
		for (int k = i + 1; k < n; k++) 
		{
            double c = -A[k][i] / A[i][i];
			for (int j = i; j < (m + 1); j++) 
			{
                if (i == j) 
				{
					A[k][j] = 0;
				} else 
				{
                    A[k][j] += c * A[i][j];
	            }
		    }
		}
	}

	return A;

}

int main()
{
	int n = 0;
	int m = 0;

	//������ ����������� �������
	cin >> n >> m;

    vector <double> line(m + 1, 0);
    vector< vector<double> > A(n,line);
	//��������� ������ ������� ���������� ���������
	for (int iR = 0; iR < n; iR++)
	{
		for (int iC = 0; iC < (m+1); iC++ )
		{
			cin >> A[iR][iC];
//			cout << iR << "|" << iC << endl;
		}
	}
//	cout << endl;
	vector <vector <double> > tt;

	//������ gauss elimination
	tt = gauss(A, n, m);
	//������� ���������� ������� ������� �� �����
	int l = min(n, m);
	for (int iR = 0; iR < n; iR++)
	{
		for (int iC = 0; iC < m + 1; iC++)
		{
//			cout << tt[iR][iC] << "|";
		}
//		cout << endl;
	}

	//������� ������: (0 - �����������), (1 - ����������� ����� �������), (2 - ���� ���� �������)
	int trigger = 0;
	//���������� ������� ����������� �����
	int k = 0;

	//������� ��������� ������� (��)������������ ������:
	for(int iR = 0; iR < n; iR++)
	{
		//����� ��� ������������� � ������
		double rowSum = 0;
		//������� ������ �����
		double b = 0;
		//��������� ������ ������
		for (int iC = 0; iC < m; iC++)
		{
			rowSum = abs(tt[iR][iC]);
		}
		//������� ��� ��� ����������� ������ ����� ����
		if (equalZero(rowSum))
		{
			b = tt[iR][m];
			if (equalZero(b))
			{

			}else
			{
				trigger = 0;
				k = max(n, m) + 1;
				break;
			}

		}else
		{
			//������� ������� ����������� �����
			k = k + 1;
		}
		//���� ���������� ������� ����������� ����� ������ ���������� ���������, �� ��� �������
	}

		if ( k > m )
		{
			trigger = 0;
			cout << "NO" << endl;
		}

	//���� ���������� ������� ���������� ����� ������ ���������� ���������, �� ����������� ��������� �������
	if ( k < m)
	{
		trigger = 1;
		cout << "INF" << endl;
	}
	//���� ���������� ������� ����������� ����� ����� ���������� ���������, �� ���� ������ ���� ������

//	cout << endl;
//	cout << k << endl;

	if(k == m)
	{
		trigger = 2;
		cout << "YES" << endl;
		vector<double> xx(n);
		for (int i = n-1; i >= 0;i--)
		{
			xx[i] = tt[i][m] / tt[i][i];
//			cout << xx[i] << endl;
			for (int kk = i - 1; kk >= 0; kk--)
			{
				tt[kk][m] -= tt[kk][i] * xx[i];
//				cout << kk << " " << tt[kk][m] << " ";
			}
//			cout << endl;
		}
		for (int i = 0; i < n; i++)
		{
			cout << xx[i] << " ";
		}
	}
	cin >> l;	
    return 0;
}
