#include <iostream>
#include <cctype>
#include <vector>
#include <string>
#include <sstream>
#include <stdio.h>
using std::vector;
using std::getline;
using std::stringstream;
using std::cin;
using std::cout;
using std::endl;

int check(vector<std::string> &map, int ncols, int nrows, int col, int row, int from, char obj);
void joinPointers(vector< vector<int*> > *pointers, int *currentPoint, int *toReplace);

int recurrence = 0;

int main(void)
{
	std::string string;
	vector< vector<int> > results;
	int problems = 0;

	while ( getline(std::cin, string) )
	{
		problems++;
		vector<std::string> map;
		map.resize(1);

		vector< vector<int*> > pointers;
		vector<int> counts;
		int pools = 0;

		// se leen los 'mapas' con la información inicial
		int lmax = string.length();	
		int nlines = 1;

		do
		{

			map.resize(nlines);
			map[nlines-1] = string;

			pointers.resize(nlines);
			pointers[nlines-1].resize(lmax, 0);


			for (int i = 0; i < lmax; i++)
			{

				if (map[nlines-1][i] == 'W')
				{
					int *currentPoint = NULL;

					if ( i>1 && nlines>1 && map[nlines-2][i-1] == 'W')
					{
						(*pointers[nlines-2][i-1])++;
						currentPoint = pointers[nlines-2][i-1];
					}
					if ( nlines>1 && map[nlines-2][i] == 'W' && currentPoint != pointers[nlines-2][i])
					{
						if (currentPoint == NULL)
						{
							currentPoint = pointers[nlines-2][i];
						}
						else
						{
							joinPointers(&pointers, currentPoint, pointers[nlines-2][i]);
						}
						(*currentPoint)++;
					}
					if ( i<lmax-2 && nlines>1 && map[nlines-2][i+1] == 'W' && currentPoint != pointers[nlines-2][i+1])
					{
						if (currentPoint == NULL)
						{
							currentPoint = pointers[nlines-2][i+1];
						}
						else
						{
							joinPointers(&pointers, currentPoint, pointers[nlines-2][i+1]);
						}
						(*currentPoint)++;
					}
					if ( i>1 && map[nlines-1][i-1] == 'W' && currentPoint != pointers[nlines-1][i-1])
					{
						if (currentPoint == NULL)
						{
							currentPoint = pointers[nlines-1][i-1];
						}
						else
						{
							joinPointers(&pointers, currentPoint, pointers[nlines-1][i-1]);
						}
						(*currentPoint)++;
					}

					if (currentPoint == NULL)
					{
						counts.resize(++pools, 1);
						counts[pools-1] = 1;
						currentPoint = &counts[pools-1];
						cout << "NULL " << nlines-1 << " " << i << " " << counts[pools-1] << " " << &counts[pools-1] << '\n';
					}

					pointers[nlines-1][i] = currentPoint;
				}

			}

			for (unsigned int i = 0; i < pointers.size(); ++i)
			{
				for (unsigned int j = 0; j < pointers[i].size(); ++j)
				{
					if (pointers[i][j] != 0)
					{
						cout << pointers[i][j];
					}
					else
					{
						cout << "---------";
					}
					cout << ' ';
				}
				cout << '\n';
			}
			cout << '\n';
			cout << '\n';

			nlines++;
		} while ( getline(cin, string) && !isdigit(string[0]) );

		// se leen las consultas sobre el mapa
		vector< vector<int> > queries;
		int nqueries = 1;
		do
		{
			stringstream stream(string);
			queries.resize(nqueries);
			queries[nqueries-1].resize(2);
			stream >> queries[nqueries-1][0];
			stream >> queries[nqueries-1][1];
			nqueries++;
		} while ( getline(cin, string) && string.length() ); 
		nqueries--;

		// se resuelven las consultas
		results.resize(problems);
		results[problems-1].resize(nqueries);
		for (int i = 0; i < nqueries; i++)
		{
			int col = queries[i][1]-1;
			int row = queries[i][0]-1;
			results[problems-1][i] = *(pointers[row][col]);
			// results[problems-1][i] = check(map, lmax, nlines, col, row, 0, map[row][col]);
			// check(map, lmax, nlines, queries[i][1]-1, queries[i][0]-1, 0, map[queries[i][0]-1][queries[i][1]-1]);
		}
	}

	// se entregan los resultados
	for (int i = 0; i < problems; ++i)
	{
		for (unsigned int j = 0; j < results[i].size(); ++j)
		{
			cout << results[i][j];
			cout << '\n';
		}
		cout << '\n';
	}
	cout << recurrence;

	return 0;
}

void joinPointers(vector< vector<int*> > *pointers, int *currentPoint, int *toReplace)
{
	cout << "\njoinPointers --------------------------------------------------- \n";

	for (unsigned int i = 0; i < (*pointers).size(); ++i)
	{
		for (unsigned int j = 0; j < (*pointers)[i].size(); ++j)
		{
			cout << (*pointers)[i][j];
			cout << '\t';
			cout << currentPoint;
			cout << '\t';
			cout << toReplace;
			cout << '\n';
			if ((*pointers)[i][j] == toReplace)
			{
				(*pointers)[i][j] = currentPoint;
			}
		}
	}

}


int check(vector<std::string> &map, int ncols, int nrows, int col, int row, int from, char obj)
{
	recurrence++;
	// +---+---+---+
	// | 1 | 2 | 3 |
	// +---+---+---+
	// | 4 | X | 5 |
	// +---+---+---+
	// | 6 | 7 | 8 |
	// +---+---+---+

	// se verifica que el punto esté dentro del mapa y que corresponda a lo que busco (agua)
	if (col >= ncols || row >= nrows || col < 0 || row < 0) return 0;
	if (map[row][col] != obj) return 0;

	// marco el punto como leído
	map[row][col] = 'X';
	int count = 1;

	// filtro los siguientes cuadros a buscar dependiendo de quién pregunta (coordenada de la recurrencia superior)
	if (from == 0)
	{
		count += check(map, ncols, nrows, col-1, row-1, 8, obj); // checks 1
		count += check(map, ncols, nrows, col  , row-1, 7, obj); // checks 2
		count += check(map, ncols, nrows, col+1, row-1, 6, obj); // checks 3
		count += check(map, ncols, nrows, col-1, row  , 5, obj); // checks 4
		count += check(map, ncols, nrows, col+1, row  , 4, obj); // checks 5
		count += check(map, ncols, nrows, col-1, row+1, 3, obj); // checks 6
		count += check(map, ncols, nrows, col  , row+1, 2, obj); // checks 7
		count += check(map, ncols, nrows, col+1, row+1, 1, obj); // checks 8
	}
	else if(from < 4)
	{
		count += check(map, ncols, nrows, col-1, row+1, 3, obj); // checks 6
		count += check(map, ncols, nrows, col  , row+1, 2, obj); // checks 7
		count += check(map, ncols, nrows, col+1, row+1, 1, obj); // checks 8
		if (from == 1)
		{
			count += check(map, ncols, nrows, col+1, row-1, 6, obj); // checks 3
			count += check(map, ncols, nrows, col+1, row  , 4, obj); // checks 5
		}
		else if (from == 3)
		{
			count += check(map, ncols, nrows, col-1, row-1, 8, obj); // checks 1
			count += check(map, ncols, nrows, col-1, row  , 5, obj); // checks 4
		}
	}
	else if (from == 4)
	{	
		count += check(map, ncols, nrows, col+1, row-1, 6, obj); // checks 3
		count += check(map, ncols, nrows, col+1, row  , 4, obj); // checks 5
		count += check(map, ncols, nrows, col+1, row+1, 1, obj); // checks 8
	}
	else if (from == 5)
	{	
		count += check(map, ncols, nrows, col-1, row-1, 8, obj); // checks 1
		count += check(map, ncols, nrows, col-1, row  , 5, obj); // checks 4
		count += check(map, ncols, nrows, col-1, row+1, 3, obj); // checks 6
	}
	else
	{	
		count += check(map, ncols, nrows, col-1, row-1, 8, obj); // checks 1
		count += check(map, ncols, nrows, col  , row-1, 7, obj); // checks 2
		count += check(map, ncols, nrows, col+1, row-1, 6, obj); // checks 3
		if (from == 6)
		{
			count += check(map, ncols, nrows, col+1, row  , 4, obj); // checks 5
			count += check(map, ncols, nrows, col+1, row+1, 1, obj); // checks 8
		}
		else if (from == 8)
		{
			count += check(map, ncols, nrows, col-1, row  , 5, obj); // checks 4
			count += check(map, ncols, nrows, col-1, row+1, 3, obj); // checks 6
		}
	}

	return count;
}
