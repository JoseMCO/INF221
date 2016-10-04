#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using std::vector;
using std::getline;
using std::stringstream;
using std::cin;
using std::cout;
using std::endl;

void joinAreas(vector< vector<int> > *areas, int currentPoint, int toReplace);

	// Posiciones respecto a la coordenada actual (X)
	// +---+---+---+
	// | 1 | 2 | 3 |
	// +---+---+---+
	// | 4 | X | 5 |
	// +---+---+---+
	// | 6 | 7 | 8 |
	// +---+---+---+

int main(void)
{
	std::string string;
	vector< vector<int> > results;
	int problems = 0;

	while ( getline(std::cin, string) )
	{
		// contador para los problemas y matriz para el problema actual, 
		// en donde -1 será tierra (L) y agua (W) estará representado por una etiqueta de área
		problems++;
		vector< vector<int> > areas;
		vector<int> counts;
		// contador de áreas
		int pools = 0;

		// se leen los 'mapas' con la información inicial
		int lmax = string.length();	
		int nlines = 1;

		do
		{
			// aumenta el tamaño de areas para agregar la nueva linea
			areas.resize(nlines);
			areas[nlines-1].resize(lmax, -1);

			// itera por la linea
			for (int i = 0; i < lmax; i++)
			{
				// si la posición actual corresponde a agua
				if (string[i] == 'W')
				{
					int currentPoint = -1;

					// se revisa (de ser posible) las posiciones 1, 2, 3 y 4, de encontrarse, la posición actual se agrega a el área ya existente
					// posición 1
					if ( i>1 && nlines>1 && areas[nlines-2][i-1] > -1)
					{
						counts[areas[nlines-2][i-1]]++;
						currentPoint = areas[nlines-2][i-1];
					}
					// posición 2
					if ( nlines>1 && areas[nlines-2][i] > -1 && currentPoint != areas[nlines-2][i])
					{
						if (currentPoint == -1)
						{
							currentPoint = areas[nlines-2][i];
						}
						else
						{
							joinAreas(&areas, currentPoint, areas[nlines-2][i]);
						}
						counts[currentPoint]++;
					}
					// posición 3
					if ( i<lmax-2 && nlines>1 && areas[nlines-2][i+1] > -1 && currentPoint != areas[nlines-2][i+1])
					{
						if (currentPoint == -1)
						{
							currentPoint = areas[nlines-2][i+1];
						}
						else
						{
							joinAreas(&areas, currentPoint, areas[nlines-2][i+1]);
						}
						counts[currentPoint]++;
					}
					// posición 4
					if ( i>0 && areas[nlines-1][i-1] > -1 && currentPoint != areas[nlines-1][i-1])
					{
						if (currentPoint == -1)
						{
							currentPoint = areas[nlines-1][i-1];
						}
						else
						{
							joinAreas(&areas, currentPoint, areas[nlines-1][i-1]);
						}
						counts[currentPoint]++;
					}

					// de no encontrarse un área colindante, se marca el punto como una nueva área
					if (currentPoint == -1)
					{
						counts.resize(++pools, 1);
						counts[pools-1] = 1;
						currentPoint = pools-1;
					}

					// se guarda en areas el valor corespondiente a el área
					areas[nlines-1][i] = currentPoint;
				}
				else
				{
					areas[nlines-1][i] = -1;
				}
			}

			// imprime paso a paso la detección de áreas y la lista con las cuentas
			///////////////////////////////////////////////////////////////////////
			// for (int i = 0; i < counts.size(); ++i)
			// {
			// 	cout << i << ": " << counts[i] << "\t";
			// }
			// cout << '\n';

			// for (unsigned int i = 0; i < areas.size(); ++i)
			// {
			// 	for (unsigned int j = 0; j < areas[i].size(); ++j)
			// 	{
			// 		if (areas[i][j] != -1)
			// 		{
			// 			cout << areas[i][j] << " ";
			// 		}
			// 		else
			// 		{
			// 			cout << "- ";
			// 		}
			// 	}
			// 	cout << '\n';
			// }
			// cout << '\n';
			/////////////////////////////////////////////////////////////////////////

			// lectura de nueva linea
			nlines++;
		} while ( getline(cin, string) && !isdigit(string[0]) );

		// se leen las consultas sobre el mapa
		do
		{
			// se parsean los 2 números
			stringstream stream(string);
			int row, col;
			stream >> row;
			stream >> col;
			// se consulta por el área
			cout << counts[areas[row-1][col-1]] << "\n";
		} while ( getline(cin, string) && string.length() ); 
		cout << "\n";
	}

	return 0;
}

// busca etiquetas toReplace y las cambia a currentPoint
void joinAreas(vector< vector<int> > *areas, int currentPoint, int toReplace)
{
	for (unsigned int i = 0; i < (*areas).size(); ++i)
	{
		for (unsigned int j = 0; j < (*areas)[i].size(); ++j)
		{
			if ((*areas)[i][j] == toReplace)
			{
				(*areas)[i][j] = currentPoint;
			}
		}
	}

}