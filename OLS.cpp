#include <iostream>     
#include <cmath>    
#include <vector>
#include <algorithm>
#define SIZE 20

using namespace std;

bool equalZero(float Zero);
vector < vector<double> > gauss(vector< vector<double> > A, int n, int m);
vector < vector<double> > enterMatrix(int n, int m);
vector<double> solveMatrix(int n, int m, vector <vector <double> > tt);
vector < vector<double> > OLStranform(vector < vector<double> > A, int n, int m);

bool equalZero(double Zero)
{
	bool result = false;
	result = abs(Zero) < 0.0000001;
	return result;
}

vector < vector<double> > gauss(vector< vector<double> > AA, int n, int m)
{
	//��������� ������ ��������� �������:
	//���� ���������� ������ ������� (� ��� ����� ������) ������� ������� ����� ���� �����
	//����� ���������� ������� ������� ������� ����� ���� ����� ����� ������ � �.�.
	//�������� ��������������� ����������
	//�.�. ������� ����� ���� ������������� ���������� min (n, m)
	int l = min(n, m);
	for (int i = 0; i < l; i++)
	{
		// ���� ������ ������ � ������������ ���������
		double elementMax = abs(AA[i][i]);
		int rowMax = i;
		for (int k = i + 1; k < l; k++)
		{
			if (abs(AA[k][i]) > elementMax)
			{
				elementMax = abs(AA[k][i]);
				rowMax = k;
			}
		}

		//������ ��������������� ����� ������� (���������, ��� ��� ����� ���� ������� ��������)
		for (int k = i; k < (m + 1); k++) {
			double tmp = AA[rowMax][k];
			AA[rowMax][k] = AA[i][k];
			AA[i][k] = tmp;
		}

		// ����������� ��������������
		for (int k = i + 1; k < n; k++)
		{
			double c = -AA[k][i] / AA[i][i];
			for (int j = i; j < (m + 1); j++)
			{
				if (i == j)
				{
					AA[k][j] = 0;
				}
				else
				{
					AA[k][j] += c * AA[i][j];
				}
			}
		}
	}

	return AA;

}

vector < vector<double> > enterMatrix(int n, int m) 
{
	vector <double> line(m + 1, 0);
	vector< vector<double> > A(n, line);
	//��������� ������ ������� ���������� ���������
	for (int iR = 0; iR < n; iR++)
	{
		for (int iC = 0; iC < (m + 1); iC++)
		{
			cin >> A[iR][iC];
			//			cout << iR << "|" << iC << endl;
		}
	}
	return A;
}

vector<double> solveMatrix(int n, int m , vector <vector <double> > tt) 
{
	vector <double> xx(n);
	for (int i = n - 1; i >= 0; i--)
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
	return xx;

}

vector < vector<double> > OLStranform(vector < vector<double> > A, int n, int m)
{
	//����� ����� ����������, �.�. ������� ��� ������� ��������� ������������ �� �����
	//�� �������������� �� �����
	vector <double> line(m + 1, 0);
	vector < vector<double> > B(m, line);
	double tempScalar = 0.0;
	for (int c1 = 0; c1 < m; c1++)
	{
		for (int c2 = 0; c2 < m + 1; c2++)
		{
			tempScalar = 0;
			for (int r = 0; r < n; r++)
			{
				tempScalar += A[r][c1]*A[r][c2];
			}
			B[c1][c2] = tempScalar;
		}
	}
	return B;
}


int main()
{
	int n = 0;
	int m = 0;
	//������ ����������� �������
	// n - ���������� ���������
	// m - ���������� �����������
	cin >> n >> m;
	vector <double> line(m + 1, 0);
	vector< vector<double> > A(n, line);
	//��������� ������ ������� ���������� ���������
	A = enterMatrix(n, m);
	vector <vector <double> > tt; //(m + 1, line);

	//����������� �������� ������� � ������� �: (m) x (m + 1):
	//(X1,X1) + (X1,X2) + ... + (X1, Xn) = (X1, B)
	//(X2,X1) + (X2,X2) + ... + (X2, Xn) = (X2, B)
	//...
	//(Xn,X1) + (Xn,X2) + ... + (Xn, Xn) = (Xn, B)

	vector < vector <double> > C(m, line);
	C = OLStranform(A, n, m);
	//������ gauss elimination
	tt = gauss(C, m, m);
/*	//������� ���������� ������� ������� �� �����
	int l = min(n, m);
	for (int iR = 0; iR < n; iR++)
	{
		for (int iC = 0; iC < m + 1; iC++)
		{
			//			cout << tt[iR][iC] << "|";
		}
		//		cout << endl;
	} */

	//������� ������: (0 - �����������), (1 - ����������� ����� �������), (2 - ���� ���� �������)
	int trigger = 0;
	//���������� ������� ����������� �����
	int k = 0;
	//������� ��������� ������� (��)������������ ������:
	for (int iR = 0; iR < m; iR++)
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

			}
			else
			{
				trigger = 0;
				k = max(m, m) + 1;
				break;
			}

		}
		else
		{
			//������� ������� ����������� �����
			k = k + 1;
		}
		//���� ���������� ������� ����������� ����� ������ ���������� ���������, �� ��� �������
	}

	if (k > m)
	{
		trigger = 0;
		cout << "NO" << endl;
	}

	//���� ���������� ������� ���������� ����� ������ ���������� ���������, �� ����������� ��������� �������
	if (k < m)
	{
		trigger = 1;
		cout << "INF" << endl;
	}
	//���� ���������� ������� ����������� ����� ����� ���������� ���������, �� ���� ������ ���� ������

	if (k == m)
	{
		trigger = 2;
		cout << "YES" << endl;
		vector<double> xx(m);
		xx = solveMatrix(m, m, tt);
		for (int i = 0; i < m; i++)
		{
			cout << xx[i] << " ";
		}
	}


	//cin >> l;

	return 0;
}