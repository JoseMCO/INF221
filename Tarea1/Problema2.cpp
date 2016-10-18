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

struct node
{
	int value;
	int parent;
	int height;
};

int find(vector<node> nodes, int v, int p);

int main(void)
{
	// Lee la cantidad de datos y luesgo los datos mismos
	int n = 0;
	cin >> n;
	cin.ignore();
	std::string structure;
	std::string data;
	getline(cin >> std::ws, structure);
	getline(cin, data);

	stringstream stream(data);

	// lista de nodos, se insertarán en el mismo orden que fueron dados
	vector<node> nodes;
	nodes.resize(n);

	int j = 0;
	int parent = -1;
	int height = 0;
	for(unsigned int i=0; i<structure.length(); i++ )
	{
		// si hay un (, es porque hay un nuevo hijo, por lo que se inserta el nuevo nodo con los datos correspondientes y se aumenta la altura
		if(structure[i]=='(')
		{
			// insert value on child
			stream >> nodes[j].value; 
			nodes[j].parent = parent; 
			nodes[j].height = height++; 
			parent = j++;
		}
		// si hay un ) es porque es el último nodo de la rama, se sube hacia el padre y se decrece la altura
		else
		{
			parent = nodes[j-1].parent;
			height--;
		}
	}
	
	// lectura de las consultas
	int q = 0;
	cin >> q;
	cin.ignore();
	cout << q << '\n';
	getline(cin >> std::ws, data);

	for(unsigned int i=0; i < q; i++)
	{
		stringstream stream(data);
		int v,p;
		stream >> v;
		stream >> p;
		cout << find(nodes, v, p) << "\n";
		getline(cin, data);
	}

	return 0;
}

int find(vector<node> nodes, int v, int p)
{
	// se revisa el valor del padre de cada nodo, hasta encontrar un valor menor al requerido
	int last = v;
	while(last > 0 && nodes[nodes[last].parent].value > p)
		last = nodes[last].parent;
	
	return nodes[last].height;
}

