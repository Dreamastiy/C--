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
	//сортируем строки следующим образом:
	//ищем наибольший первый элемент (и его номер строки) первого столбца среди всех строк
	//затем наибольший элемент второго столбца среди всех строк кроме первой и т.д.
	//проводим соответствующую сортировку
	//т.к. матрица может быть пр€моугольной определ€ем min (n, m)
	int l = min(n, m);
	for (int i=0; i < l; i++) 
	{
		// цикл поиска строки с максимальным элементом
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

		//мен€ем соответствующие сроки местами (учитываем, что уже могут быть нулевые элементы)
		for (int k = i; k < (m + 1) ; k++) {
			double tmp = A[rowMax][k];
			A[rowMax][k] = A[i][k];
			A[i][k] = tmp;
		}

		// постепенна€ треугонализаци€
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

	//вводим размерности матрицы
	cin >> n >> m;

    vector <double> line(m + 1, 0);
    vector< vector<double> > A(n,line);
	//заполн€ем €чейки матрицы значени€ми построчно
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

	//делаем gauss elimination
	tt = gauss(A, n, m);
	//выводим полученную верхнюю матрицу на экран
	int l = min(n, m);
	for (int iR = 0; iR < n; iR++)
	{
		for (int iC = 0; iC < m + 1; iC++)
		{
//			cout << tt[iR][iC] << "|";
		}
//		cout << endl;
	}

	//триггер вывода: (0 - несовместна), (1 - бесконечное число решений), (2 - есть одно решение)
	int trigger = 0;
	//количество линейно независимых строк
	int k = 0;

	//смотрим различные услови€ (не)совместности систем:
	for(int iR = 0; iR < n; iR++)
	{
		//сумма абс коэффициентов в строке
		double rowSum = 0;
		//элемент правой части
		double b = 0;
		//суммируем каждую строку
		for (int iC = 0; iC < m; iC++)
		{
			rowSum = abs(tt[iR][iC]);
		}
		//смотрим все лик оэффициенты строки равны нулю
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
			//подсчет линейно независимых строк
			k = k + 1;
		}
		//если количество линейно независимых строк больше количества уравнений, то нет решений
	}

		if ( k > m )
		{
			trigger = 0;
			cout << "NO" << endl;
		}

	//если количество линейно независмых строк меньше количества уравнений, то бесконечное множество решений
	if ( k < m)
	{
		trigger = 1;
		cout << "INF" << endl;
	}
	//если количество линейно независимых строк равно количество уравнений, то есть только одно решние

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
