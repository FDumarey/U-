/*
 Gauss-Jordan elimintation method to solve linear equations
 very-fast algorithm
 can be used with variable sized matrices
 
 GaussJordan function parameters:
     integer indicating the number of unknown variables
     a 2D array [vars-1][vars] with the last column the value matrix: the so called extended
     matrix
 GaussJordan returns a I-matrix with the solutions of the variables in the last column
 
 by F. Dumarey October 2022
 */

#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

void Start()
{
	cout << "Gauss-Jordan elimination method\n";
	cout << "-------------------------------\n";
}

template <typename TwoDArray>
void GaussJordan(const int& n, TwoDArray& a)
{
	for (int i=0; i<n; i++)
	{
		if(a[i][i] == 0.0)
		{
			cout << "Error, zero pivot values found!";
			exit(1);
		}
		
		for (int j=0; j<n; j++)
		{
			if (i!=j)
			{
				double ratio = a[j][i]/a[i][i];
				for (int k=0; k<n+1; k++)
				{
					a[j][k] = a[j][k] - ratio * a[i][k];
				}
			}
		}
	}
	
	for (int i=0; i<n; i++)
	{
		a[i][n] /= a[i][i];
		a[i][i] = 1.0;
	}
}

int main(int argc, const char *argv[])
{
	double matrix[3][4] {
		{2,3,1,14},
		{1,1,1,6},
		{1,2,3,11},
	};
	
	int vars=3;
	
	Start();	
	GaussJordan(vars, matrix);
	
	cout << "Solution: \n";
	for (int i=0; i<vars; i++)
	{
		cout << "x[" << i << "] = " << matrix[i][vars] << endl;
	}
	
	return 0;
}
