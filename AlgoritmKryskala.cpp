#include <iostream>
#include <fstream>
using namespace std;

struct ribs
{
	char way[2];
	int length;
};

struct connectedvertices
{
	int size;
	int capacity;
	char* verticices;
	connectedvertices()
	{
		size = 0;
		capacity = 10;
		verticices = new char[10];
	}
	connectedvertices(int a)
	{
		size = a;
		capacity = (int)((double)a * 1.6);
		verticices = new char[capacity];
	}
};

void change_char(char& a, char& b)
{
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
}

void change_ribs(ribs& a, ribs& b)
{
	ribs c;
	c = b;
	b = a;
	a = c;
}

void change_position_of_symbols(char*& a, char*& b)
{
	for (int i = 0; i < 2; i++)
	{
		a[i] = a[i] ^ b[i];
		b[i] = a[i] ^ b[i];
		a[i] = a[i] ^ b[i];
	}
}

int get_graf(ribs*& graf, int& size)
{
	ifstream file("graf.txt");
	graf = new ribs[10];
	int capacity = 10;
	size = 0;
	if (!file.is_open())
		return 1;
	while (!file.eof())
	{
		if (size < capacity)
		{
			file >> graf[size].way;
			file >> graf[size].length;
			if (graf[size].way[0] > graf[size].way[1])
				change_char(graf[size].way[0], graf[size].way[1]);
			size += 1;
		}
		else
		{
			if (file.tellg() == ' ')
				break;
			capacity = (int)(1, 6 * (float)capacity);
			ribs* a = new ribs[capacity];
			for (int i = 0; i < size; i++)
			{
				a[i] = graf[i];
			}
			delete[] graf;
			graf = a;
			file >> graf[size].way;
			file >> graf[size].length;
			if (graf[size].way[0] > graf[size].way[1])
				change_char(graf[size].way[0], graf[size].way[1]);
			size += 1;
		}
	}
	ribs* a = new ribs[size];
	for (int i = 0; i < size; i++)
	{
		a[i] = graf[i];
	}
	delete[] graf;
	graf = a;
	file.close();
	return 0;
}

void insert_sort_graf(ribs*& graf, int size)
{
	for (int i = 1; i < size; i++)
	{
		for (int j = i; j > 0; j--)
		{
			if (graf[j].length < graf[j - 1].length)
				change_ribs(graf[j], graf[j - 1]);
			else
				break;
		}
	}
}

void merge_of_disjoint_sets(connectedvertices& a, connectedvertices& b, char c)
{
	bool flag = false;
	if (a.capacity > (a.size + b.size - 1))
	{
		for (int i = 0; i < (b.size - 1); i++)
		{
			if (b.verticices[i] == c)
			{
				a.verticices[a.size + i] = b.verticices[i + 1];
				flag = true;
			}
			else
			{
				if (flag == true)
					a.verticices[a.size + i] = b.verticices[i + 1];
				else
					a.verticices[a.size + i] = b.verticices[i];
			}
		}
		a.size = (a.size + b.size - 1);
	}
	else
	{
		connectedvertices d(a.size + b.size);
		d.size -= 1;
		bool flag = false;
		for (int i = 0; i < a.size - 1; i++)
		{
			if (a.verticices[i] == c)
			{
				d.verticices[i] = a.verticices[i + 1];
				flag = true;
			}
			else
			{
				if (flag == true)
					d.verticices[i] = a.verticices[i + 1];
				else
				    d.verticices[i] = a.verticices[i];
			}
		}
		for (int i = 0; i < d.size; i++)
		{
			d.verticices[a.size - 1 + i] = b.verticices[i];
		}
		a = d;
	}
}

void delete_disjoint_set(connectedvertices*& table, int& size, int number)
{
	for (int i = number; i < (size - 1); i++)
	{
		table[i] = table[i + 1];
	}
	size -= 1;
}

void array_of_ribs(char**& connectedribs, int& capacity_of_connectedribs, int& size_of_connectedribs, char b[2])
{
	if (size_of_connectedribs < capacity_of_connectedribs)
	{
		connectedribs[size_of_connectedribs][0] = b[0];
		connectedribs[size_of_connectedribs][1] = b[1];
		size_of_connectedribs += 1;
		for (int i = (size_of_connectedribs - 1); i > 0; i--)
		{
			if (connectedribs[i][0] <= connectedribs[i - 1][0])
			{
				if (connectedribs[i][0] == connectedribs[i - 1][0])
					if (connectedribs[i][1] < connectedribs[i - 1][1])
						change_position_of_symbols(connectedribs[i], connectedribs[i - 1]);
				if (connectedribs[i][0] < connectedribs[i - 1][0])
					change_position_of_symbols(connectedribs[i], connectedribs[i - 1]);
			}
			else
				break;
		}
	}
	else
	{
		capacity_of_connectedribs = (int)((double)capacity_of_connectedribs * 1.6);
		char** c = new char* [capacity_of_connectedribs];
		for (int i = 0; i < capacity_of_connectedribs; i++)
		{
			c[i] = new char[2];
		}
		for (int i = 0; i < size_of_connectedribs; i++)
		{
			c[i][0] = connectedribs[i][0];
			c[i][1] = connectedribs[i][1];
		}
		delete[] connectedribs;
		connectedribs = c;
		connectedribs[size_of_connectedribs][0] = b[0];
		connectedribs[size_of_connectedribs][1] = b[1];
		size_of_connectedribs += 1;
		for (int i = (size_of_connectedribs - 1); i > 0; i--)
		{
			if (connectedribs[i][0] <= connectedribs[i - 1][0])
			{
				if (connectedribs[i][0] == connectedribs[i - 1][0])
					if (connectedribs[i][1] < connectedribs[i - 1][1])
						change_position_of_symbols(connectedribs[i], connectedribs[i - 1]);
				if (connectedribs[i][0] < connectedribs[i - 1][0])
					change_position_of_symbols(connectedribs[i], connectedribs[i - 1]);
			}
			else
				break;
		}
	}
}

void algoritm_kryskala(ribs*& graf, const int size)// Здесь разбиваются вершины на подмножества, суммируется длина
{
	connectedvertices* table = new connectedvertices [10];
	int capacity_of_table = 10;
	int employed = 0;
	int length_of_graf = 0;
	char** connectedribs = new char*[10];
	int capacity_of_connectedribs = 10;
	int size_of_connectedribs = 0;
	for (int i = 0; i < 10; i++)
	{
		connectedribs[i] = new char[2];
	}
	for (int i = 1; i < size; i++)
	{
		if (employed == 0)
		{
			table[0].verticices[0] = graf[0].way[0];
			table[0].verticices[1] = graf[0].way[1];
			table[0].size = 2;
			length_of_graf = graf[0].length;
			employed = 1;
			connectedribs[0][0] = graf[0].way[0];
			connectedribs[0][1] = graf[0].way[1];
			size_of_connectedribs += 1;
		}
		int number_of_true = -1;
		bool symbol0 = false, symbol1 = false;
		for (int j = 0; j < employed; j++)
		{
			bool flag = false;
			if (number_of_true == -1)
			{
				for (int k = 0; k < table[j].size; k++)
				{
					if (graf[i].way[0] == table[j].verticices[k])
					{
						number_of_true = j;
						symbol0 = true;
					}
					if (graf[i].way[1] == table[j].verticices[k])
					{
						number_of_true = j;
						symbol1 = true;
					}
				}
				if ((symbol0 && symbol1) != true)
				{
					if ((symbol0 || symbol1) == true)
					{
						if (table[j].capacity > table[j].size)
						{
							if (symbol0 == true)
							{
								table[j].verticices[table[j].size] = graf[i].way[1];
								array_of_ribs(connectedribs, capacity_of_connectedribs, size_of_connectedribs, graf[i].way);
							}
							if (symbol1 == true)
							{
								table[j].verticices[table[j].size] = graf[i].way[0];
								array_of_ribs(connectedribs, capacity_of_connectedribs, size_of_connectedribs, graf[i].way);
							}
							table[j].size += 1;
							length_of_graf += graf[i].length;
						}
						else
						{
							connectedvertices a(table[j].capacity);
							for (int k = 0; k < table[j].size; k++)
								a.verticices[k] = table[j].verticices[k];
							table[j] = a;
							if (symbol0 == true)
							{
								table[j].verticices[table[j].size] = graf[i].way[1];
								array_of_ribs(connectedribs, capacity_of_connectedribs, size_of_connectedribs, graf[i].way);
							}
							if (symbol1 == true)
							{
								table[j].verticices[table[j].size] = graf[i].way[0];
								array_of_ribs(connectedribs, capacity_of_connectedribs, size_of_connectedribs, graf[i].way);
							}
							table[j].size += 1;
							length_of_graf += graf[i].length;
						}
					}
					else
					{//Здесь я добавляю новую строку в таблицу, если до этого два элемента не встретились
						if ((employed - j) == 1)
						{
							if (capacity_of_table > employed)
							{
								table[employed].verticices[0] = graf[i].way[0];
								table[employed].verticices[1] = graf[i].way[1];
								table[employed].size = 2;
								employed += 1;
								length_of_graf += graf[i].length;
								array_of_ribs(connectedribs, capacity_of_connectedribs, size_of_connectedribs, graf[i].way);
								break;
							}
							else
							{
								capacity_of_table = (int)((double)capacity_of_table * 1.6);
								connectedvertices* a = new connectedvertices[capacity_of_table];
								for (int i = 0; i < employed; i++)
								{
									a[i] = table[i];
								}
								delete[] table;
								table = a;
								table[employed].verticices[0] = graf[i].way[0];
								table[employed].verticices[1] = graf[i].way[1];
								table[employed].size = 2;
								employed += 1;
								length_of_graf += graf[i].length;
								array_of_ribs(connectedribs, capacity_of_connectedribs, size_of_connectedribs, graf[i].way);
								break;
							}
						}
					}
				}
				else
					break;
			}
			else
			{// Тут я сливаю множества вершин и удаляю ненужное множество после слияния
				for (int k = 0; k < table[j].size; k++)
				{
					if ((table[j].verticices[k] == graf[i].way[0]) && (symbol0 == false))
					{
						merge_of_disjoint_sets(table[number_of_true], table[j], graf[i].way[0]);
						delete_disjoint_set(table, employed, j);
						flag = true;
					}
					if ((table[j].verticices[k] == graf[i].way[1]) && (symbol1 == false))
					{
						merge_of_disjoint_sets(table[number_of_true], table[j], graf[i].way[1]);
						delete_disjoint_set(table, employed, j);
						flag = true;
					}
					if (flag == true)
						break;
				}
				if (flag == true)
					break;
			}
		}
	}
	if (employed != 1)
	{
		cout << "Введена система непересекающихся множеств\n";
	}
	else
	{
		cout << endl << "-------------------------" << endl;
		for (int i = 0; i < size_of_connectedribs; i++)
		{
			cout << connectedribs[i][0] << connectedribs[i][1] << endl;
		}
		cout << length_of_graf << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	ribs* graf;
	int size;
	if (get_graf(graf, size))
	{
		cout << "Ошибка открытия файла" << endl;
		return 0;
	}
	insert_sort_graf(graf, size);
	for (int i = 0; i < size; i++)
	{
	    cout << graf[i].way << " " << graf[i].length << endl;
	}
    algoritm_kryskala(graf, size);
	system("pause");
	return 0;
}

