#include <iostream>
#include <stdlib.h>
#include <iomanip>

using namespace std;

void print (double matrix[][100], double sol[], int rowSize, int colSize)
{
	for (int row=0; row<rowSize; row++)
	{
		for (int col=0; col<colSize; col++)
		{
			cout << setw(5) << matrix[row][col];
		}

		cout << " | " << sol[row] << '\n';
	}

	cout << '\n';
}

void gaussDown (double matrix[][100], double sol[], int rowSize, int colSize)
{
	double death;
	int lynch=0, killer=0;
	int row, col, swap, bump;

	do
	{
		if (matrix[lynch][killer]!=0)
		{
			for (row=lynch+1; row<rowSize; row++)
			{
				death = matrix[row][killer]/matrix[lynch][killer];

				for (col=killer; col<colSize; col++)
				{
					matrix[row][col] -= matrix[lynch][col]*death;
				}

				sol[row] -= sol[lynch]*death;
			}
		}

		else if (matrix[lynch][killer]==0)
		{
		/*
			//Uncomment to place 0 rows on the bottom and leave the inependant rows at the top
			swap=lynch;
			do
			{
				swap++;
				if (matrix[swap][killer]!=0)
				{
					for (int n=0; n<colSize; n++)
					{
						bump=matrix[lynch][n];
						matrix[lynch][n]=matrix[swap][n]; 
						matrix[swap][n]=bump;
					}

					bump=sol[lynch];
					sol[lynch]=sol[swap];
					sol[swap]=bump;
				}
			}
			while (matrix[swap][killer]==0 && swap<rowSize);
			
			lynch--;
		*/
			killer--;
		}

		lynch++;
		killer++;
	}
	while (killer<colSize && lynch<rowSize);
}

void gaussUp (double matrix[][100], double sol[], int rowSize, int colSize)
{
	double death;
	int lynch=rowSize, killer=colSize;
	int row, col;
	bool found;

	do
	{
		lynch--;
		killer--;

		if (matrix[lynch][killer]==0)
		{
			found=0;
			for (int j=killer; j>=0 && !found; j--)
			{
				for (int i=lynch; i>=0 && !found; i--)
				{
					if (matrix[i][j]!=0)
					{
						found=1;
						lynch=i;
						killer=j;
					}
				}
			}
		}

		if (matrix[lynch][killer]!=0)
		{
			for (row=lynch-1; row>=0; row--)
			{
				death = matrix[row][killer]/matrix[lynch][killer];
				for (col=killer; col>=0; col--)
				{
					matrix[row][col] -= matrix[lynch][col]*death;
				}

				sol[row] -= sol[lynch]*death;
			}
		}
	}
	while (killer>0 && lynch>0);
}

int dontCountYourZeroesTillTheyHatch (double matrix[][100], double sol[], int rowSize, int colSize, bool *solution)
{
	int zeroRows=0;
	bool zerod=1;

	for (int row=0; row<rowSize; row++)
	{
		for (int col=0; col<colSize; col++)
		{
			if (matrix[row][col]!=0)
			{
				zerod=0;
			}
		}

		if (zerod)
		{
			zeroRows++;

			if (sol[row]!=0)
			{
				*solution=0;
			}
		}

		else
		{
			zerod=1;
		}
	}

	return zeroRows;
}

int main()
{

	double matrix[100][100]={0};
	double sol[100]={0};
	int rowSize, colSize, zeroRows;
	bool solution=1;

	cout << "How many rows? ";
	cin >> rowSize;

	cout << "How many columns? ";
	cin >> colSize;

	cout << "\nEnter matrix\n";

	for (int i=0; i<rowSize; i++)
	{
		for (int j=0; j<colSize; j++)
		{
			cin >> matrix[i][j];
		}
	}

	cout << "\nEnter solutions\n";

	for (int s=0; s<rowSize; s++)
	{
		cin >> sol[s];
	}

	cout << '\n';

	gaussDown (matrix, sol, rowSize, colSize);

	print (matrix, sol, rowSize, colSize);

	gaussUp (matrix, sol, rowSize, colSize);

	print (matrix, sol, rowSize, colSize);


	zeroRows = dontCountYourZeroesTillTheyHatch (matrix, sol, rowSize, colSize, &solution);

	//
	//Parameter assignment sometime later
	//

	if (colSize == rowSize-zeroRows)
	{
		for (int i=0; i<rowSize; i++)
		{
			for (int j=0; j<colSize && matrix[i][j-1]==0; j++)
			{
				if (matrix[i][j]!=0)
				{
					if (sol[i])
					{
						sol[i]/=matrix[i][j];
					}

					matrix[i][j]=1;
				}
			}
		}
	
		print (matrix, sol, rowSize, colSize);
	}	

	else if (colSize > rowSize-zeroRows)
	{
		cout << "Many solutions.\n";
	}


	if (!solution)
	{
		cout << "No solution.\n";
	}

	return 0;
}
