//project3

#include<iostream>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>
#include<algorithm>
using namespace std;

// fills vectors
bool get_data(vector <string>& part_number, vector <char>& part_class, vector <int>& part_ohb, vector <double>& part_cost);

// Does a binary search  
int bin_search(string key, const vector<string>& part_number);

// Asks user for a part number to search for
string get_target();

// gets remaining info to add a part number
void get_more_data(char& class_in, int& part_ohb_in, double& part_cost_in);

// Inserts part number data into vectors into the proper location
// See book for information on how to write this
void insert_data(vector <string>& part_number, vector <char>& part_class, vector <int>& part_ohb, vector <double>& part_cost, string part_in, char class_in, int part_ohb_in, double part_cost_in);

// Displays info on part number
void display(const vector <string>& part_number, const vector <char>& part_class, const vector <int>& part_ohb, const vector <double>& part_cost, int finder);

// sorts vectors (Calls swapper) 
void sort(vector <string>& part_number, vector <char>& part_class, vector <int>& part_ohb, vector <double>& part_cost);

// prints search stats
void print_stats(int searches, int good, int bad);

// writes out file when program ends, so additions are saved to file
void put_data(const vector <string>& part_number, const vector <char>& part_class, const vector <int>& part_ohb,
	const vector <double>& part_cost);

// templated swap function – Swaps two items in a vector of any type
// Put this BEFORE main()  Called from sort function
template <class CType>
void swapper(CType& a, CType & b)
{
	CType temp;
	temp = a;
	a = b;
	b = temp;
}


int main()
{

	vector<string>part_number;
	vector<char>part_class;
	vector<int> part_ohb;
	vector<double>part_cost;
	bool file;
	char reply;
	char class_in;
	int ohb_in;
	double cost_in;
	int find_name, num_search, num_view, num_adds;

	num_search = 0;
	num_view = 0;
	num_adds = 0;

	file = get_data(part_number, part_class, part_ohb, part_cost);

	if (!file)
	{
		cout << "Fail to open part.txt";
	}
	else
	{
		sort(part_number, part_class, part_ohb, part_cost);
		do
		{   
			string target;
			target = get_target();
			find_name = bin_search(target, part_number);
			num_search++;

			if (find_name != -1)
			{
				display(part_number, part_class, part_ohb, part_cost, find_name);
				num_view++;
			}
			else
			{
				cout << target << " was not found\n";
				get_more_data(class_in, ohb_in, cost_in);
				insert_data(part_number, part_class, part_ohb, part_cost, target, class_in, ohb_in, cost_in);
				num_adds++;
			}
			cout << "Would you like to look up another part number? (Y/N) ";
			cin >> reply;
		} while (reply == 'Y' || reply == 'y');

		put_data(part_number, part_class, part_ohb, part_cost);
		print_stats(num_search, num_view, num_adds);
	}
}


bool get_data(vector<string>& part_number, vector <char>& part_class, vector <int>& part_ohb, vector <double>& part_cost)
{
	bool status = true;
	string item_name;
	string target;
	char item_class;
	int item_ohb;
	double item_cost;
	ifstream fin("C:\\Users\\83832\\Desktop\\parts.txt");
	if (fin.fail())
	{
		status = false;
		cout << "Fail to open part.txt";
	}
	else
	{
		status = true;

		while (fin >> item_name >> item_class >> item_ohb >> item_cost)
		{
			part_number.push_back(item_name);
			part_class.push_back(item_class);
			part_ohb.push_back(item_ohb);
			part_cost.push_back(item_cost);
		}
	}
	fin.close();
	return status;
}
void sort(vector <string>& part_number, vector <char>& part_class, vector <int>& part_ohb, vector <double>& part_cost)
{

	int i, j, p;
	string temp_name;
	char temp_class;
	int temp_ohb;
	double temp_cost;
	p = 3;

	while (p > 0)
	{
		for (i = 0; i < part_number.size(); i++)
		{
			j = i;
			temp_name = part_number[i];
			temp_class = part_class[i];
			temp_ohb = part_ohb[i];
			temp_cost = part_cost[i];
			while ((j >= p) && (part_number[j - p]> temp_name))
			{
				swapper(part_number[j], part_number[j - p]);
				swapper(part_class[j], part_class[j - p]);
				swapper(part_ohb[j], part_ohb[j - p]);
				swapper(part_cost[j], part_cost[j - p]);
				j = j - p;
			}
			part_number[j] = temp_name;
			part_class[j] = temp_class;
			part_ohb[j] = temp_ohb;
			part_cost[j] = temp_cost;
		}
		if (p / 2 != 0)
			p = p / 2;
		else if (p == 1)
			p = 0;
		else
			p = 1;
	}
}

string get_target()
{
	string target_name;
	cout << "Enter the part number to search for: ";
	cin >> target_name;
	return target_name;
}

int bin_search(string key, const vector<string>& part_number)
{
	int last = part_number.size() - 1;
	int first = 0;
	int position;
	position = (last + first) / 2;

	while (last >= first && part_number[position] != key)
	{
		if (part_number[position] < key)
		{
			first = position + 1;
		}
		else if (part_number[position]>key)
		{
			last = position - 1;
		}
		position = (last + first) / 2;
	}
	if (part_number[position] != key)
	{
		position = -1;
	}
	return position;
}

void get_more_data(char& class_in, int& part_ohb_in, double& part_cost_in)
{
	cout << "Enter the class: ";
	cin >> class_in;
	cout << "Enter the ohb: ";
	cin >> part_ohb_in;
	cout << "Enter cost: ";
	cin >> part_cost_in;
}

void insert_data(vector <string>& part_number, vector <char>& part_class, vector <int>& part_ohb, vector <double>& part_cost, string part_in, char class_in, int part_ohb_in, double part_cost_in)
{
	int i;
	i = part_number.size() - 1,
	part_number.resize(part_number.size() + 1);
	part_class.resize(part_class.size() + 1);
	part_ohb.resize(part_ohb.size() + 1);
	part_cost.resize(part_cost.size() + 1);

	while (i >= 0 && part_in < part_number[i])
	{
		part_number[i + 1] = part_number[i];
		part_class[i + 1] = part_class[i];
		part_ohb[i + 1] = part_ohb[i];
		part_cost[i + 1] = part_cost[i];
		i--;
	}
	part_number[i + 1] = part_in;
	part_class[i + 1] = class_in;
	part_ohb[i + 1] = part_ohb_in;
	part_cost[i + 1] = part_cost_in;

}

void display(const vector <string>& part_number, const vector <char>& part_class, const vector <int>& part_ohb, const vector <double>& part_cost, int finder)
{
	double sum = 0;
	cout << fixed << setprecision(2);
	sum = (part_cost[finder] * part_ohb[finder]);
	cout << "There are " << part_ohb[finder] << " of th Part Number " << part_number[finder] << " in invertory. It is a class " << part_class[finder] << 
		" part. The cost is $" << part_cost[finder] << endl;
	cout << "The value of that inventory is $" << sum << endl;

}

void print_stats(int searches, int good, int bad)
{
	cout << "Session report: " << searches << " searches were made, "
		<< good << " on existing items and " << bad << " new items were added.\n";

}

void put_data(const vector <string>& part_number, const vector <char>& part_class, const vector <int>& part_ohb, const vector <double>& part_cost)
{
	fstream fin("C:\\Users\\83832\\Desktop\\parts.txt");

	for (int i = 0; i < part_number.size(); i++)
	{
		fin << part_number[i] << " " << part_class[i] << " " << part_ohb[i] << " " << part_cost[i] << endl;
	}
	fin.close();
}

/*
Enter the part number to search for: P-12345
P-12345 was not found
Enter the class: A
Enter the ohb: 10
Enter cost: 10
Would you like to look up another part number? (Y/N) Y
Enter the part number to search for: P-12009
There are 3 of th Part Number P-12009 in invertory. It is a class D part. The cost is $12.80
The value of that inventory is $38.40
Would you like to look up another part number? (Y/N) Y
Enter the part number to search for: P-43000
P-43000 was not found
Enter the class: B
Enter the ohb: 12
Enter cost: 23
Would you like to look up another part number? (Y/N) N
Session report: 3 searches were made, 1 on existing items and 2 new items were added.
Press any key to continue . . .
*/