#include <iostream>
#include <string>
#include "defns.h"

using namespace std;

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		cout << "[Arguments Invalid]: Input year YYYY and number of year n" << endl;
		return -1;
	}
	if(argc = 3)
	{
		int year, n;
		year = stoi(*(argv + 1));
		n = stoi(*(argv + 2));

		cout << year << " - " << n << " = " << year-n << endl;
	}
	return 0;
}
