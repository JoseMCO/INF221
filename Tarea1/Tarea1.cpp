#include <iostream>
#include <cctype>
#include <vector>
#include <string>
#include <sstream>
using std::vector;
using std::getline;
using std::stringstream;
using std::cin;
using std::cout;
using std::endl;

int main(void)
{
	std::string string;
	getline(std::cin, string);

	vector<std::string> map;
	map.resize(1);

	map[0] = string;
	int lmax = string.length();	
	int nlines = 1;
	while ( getline(cin, string) && string.length() && !isdigit(string[0]) )
	{
		map.resize(++nlines);
		map[nlines-1] = string;
	}

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
	} while ( getline(cin, string) && string.length() ); nqueries--;

	for (int i = 0; i < nlines; i++)
	{
		for (int j = 0; j < lmax; j++)
		{
			cout << map[i][j];
		}
		cout << '\n';
	}

	for (int i = 0; i < nqueries; i++)
	{
		cout << queries[i][0];
		cout << queries[i][1];
		cout << '\n';
	}

	return 0;
}
