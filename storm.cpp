#include <iostream>
#include <fstream>
#include <string>
#include "query.cpp"

using namespace std;

int main(int argc, char** argv)
{
	if(argc != 3) // if year and n are not in parameters, exit
	{
		cout << "[arguments invalid]: ./storm <YYYY> <n>" << endl;
		return -1;

	}else{
		string line;
		int year, n;

		year = stoi(*(argv + 1)); // takes string at argv[1] and turns it into var year
		n = stoi(*(argv + 2)); // takes string at argv[2] and turns in into var n

		query(year, n); // start query for storm executable
	}
	return 0;

}
