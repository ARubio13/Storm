#include <string>
#include <iostream>
#include "defns.h"

using namespace std;

void state_print(storm_event* event){
	cout << "\tState: " << event->state;
	cout << "\tEvent ID: " << event->event_id;
	cout << "\tYear: " << event->year;
	cout << "\tEvent Type: " << event->event_type;
	cout << "\tCountry/Zone Type: " << event->cz_type;
	cout << "\tCountry/Zone Name: " << event->cz_name;
}

void month_print(storm_event* event){
	cout << "\tMonth Name: " << event->month_name;
	cout << "\tEvent ID: " << event->event_id;
	cout << "\tYear: " << event->year;
	cout << "\tEvent Type: " << event->event_type;
	cout << "\tCountry/Zone Type: " << event->cz_type;
	cout << "\tCountry/Zone Name: " << event->cz_name;
}

bool sgte(string* a, string* b){ // Determine if string a >= string b
	int n = a->length();
	for(int i=0; i<n; i++){
		if((int)(*a)[i] > (int)(*b)[i])
			return true;
		if((int)(*a)[i] < (int)(*b)[i])
			return false;
	}
	return true;
}

bool slte(string* a, string* b){ // Determine if string a <= string b
	int n = a->length();
	for(int i=0; i<n; i++){
		if((int)(*a)[i] < (int)(*b)[i])
			return true;
		if((int)(*a)[i] > (int)(*b)[i])
			return false;
	}
	return true;
}

bool ngtn(bst* a, bst* b){ // Returns boolean value of a>b
	if(a->s.compare(b->s) == 0){ // When a == b 
		if(a->event_id > b->event_id){ // Look at event_id to see if a>b
			return true;
		}
		return false;
	}else if(sgte(&(a->s), &(b->s))){
		return true;
	}
	return false;
}

int file_lines(int year){ // Converts year into number of lines in its file
    switch(year){
            case 1950:
                return 223;
            case 1951:
                return 269;
            case 1952:
                return 272;
            case 1966:
                return 2388;
            case 1996:
                return 48561;
    }
    return -1; // Unrecognized files return -1
}

int shtoi(string* s){ // Short hand number to integer
    int n = s->length(); // Length of string
    float x; // Scalar Number to be multiplied by i
    int i; // Short hand character to multiply x by
    if(n==1){ // If 0 return the 0
        return stoi(*s);
    }else{ // Seperate the number and character
        char c = s->at(n-1); // Finds what the char is
        s->pop_back(); // Removes the char from the string
        x = stof(*s); // Turns that string into a float
        if(c == 'K'){
            i = 1000;
        }else if(c == 'M'){
            i = 1000000;
        }else if(c == 'B'){
            i = 1000000000;
        }
    }
    return x*i;
}

storm_event *build_events(int year){ // Builds array of storm_event* for year
	int x;
	string s, file;
	char c, cztype;

	file = "details-";
	file += to_string(year);
	file += ".csv";

	ifstream infile(file);

	getline(infile, s);

	int numLines = file_lines(year); // Get number of lines in the file

	storm_event *events; // Pointer of struct array to be returned later
    
	if(numLines > 0){
		events = new storm_event[numLines];

		for(int i=0; i<numLines; i++){

			infile >> x; infile >> c; // collects ','
			events[i].event_id = x; // Turns int into event_id

			getline(infile, s, ',');
			events[i].state = s; // Turns string into state

			infile >> x; infile >> c; // collects ','
			events[i].year = x; // Turns int into year

			getline(infile, s, ',');
			events[i].month_name = s; // Turns string into month_name

			getline(infile, s, ',');
			events[i].event_type = s; // Turns string into event_type

			infile >> cztype; infile >> c; // collects ','
			events[i].cz_type = cztype; // Turns char into cz_type

			getline(infile, s, ',');
			events[i].cz_name = s; // Turns string into cz_name

			infile >> x; infile >> c; // collects ','
			events[i].injuries_direct = x; // Turns int into injuries_direct

			infile >> x; infile >> c; // collects ','
			events[i].injuries_indirect = x; // Turns int into injuries_indirect

			infile >> x; infile >> c; // collects ','
			events[i].deaths_direct = x; // Turns int into deaths_direct

			infile >> x; infile >> c; // collects ','
			events[i].deaths_indirect = x; // Turns int into deaths_indirect

			getline(infile, s, ',');
			events[i].damage_property = shtoi(&s); // Turns string into dmg_prop

			getline(infile, s);
			events[i].damage_crops = shtoi(&s); // Turns string into dmg_crp

			events[i].f = NULL; // Initialize fatality array
			}
	    }
    return events;
}

bst* bst_insert(bst* root, storm_event* event, string s, int index){
	if(root == NULL){
		root = new bst();
		root->s = s;
		root->event_id = event->event_id;
		root->year = event->year;
		root->event_index = index;
		root->left = NULL;
		root->right = NULL;
	}else{
		if(root->s.compare(s) >=0 && root->event_id > event->event_id){
			root->left = bst_insert(root->left, event, s, index);
		}else{
			root->right = bst_insert(root->right, event, s, index);
		}
		return root;
	}
}

void state_search(bst* root, annual_storms* years, int y, string lo, string hi){
	int n = (sizeof(years)/sizeof(*years));
	if(y < 0){
		for(int i=0; i<n; i++){
			int m = file_lines(years[i].year);
			if(m < 0)
				return;
			for(int j=0; j<m; j++){
				if(lo.compare(years[i].events[j].state) <= 0 && hi.compare(years[i].events[j].state) >= 0){
					root = bst_insert(root, &(years[i].events[j]), years[i].events[j].state, j);
				}
			}
		}
	}else{
		for(int i=0; i<n; i++){
			if(y == years[i].year){
				int m = file_lines(years[i].year);
				if(m < 0)
					return;
				for(int j=0; j<m; j++){
					if(lo.compare(years[i].events[j].state) <= 0 && hi.compare(years[i].events[j].state) >= 0){
						root = bst_insert(root, &(years[i].events[j]), years[i].events[j].state, j);
					}
				}
			}
		}
	}
}

void month_search(bst* root, annual_storms* years, int y, string lo, string hi){
	int n = (sizeof(years)/sizeof(*years));
	if(y < 0){
		for(int i=0; i<n; i++){
			int m = file_lines(years[i].year);
			if(m < 0)
				return;
			for(int j=0; j<m; j++){
				if(lo.compare(years[i].events[j].month_name) <= 0 && hi.compare(years[i].events[j].month_name) >= 0){
					root = bst_insert(root, &(years[i].events[j]), years[i].events[j].month_name, j);
				}
			}
		}
	}else{
		for(int i=0; i<n; i++){
			if(y == years[i].year){
				int m = file_lines(years[i].year);
				if(m < 0)
					return;
				for(int j=0; j<m; j++){
					if(lo.compare(years[i].events[j].month_name) <= 0 && hi.compare(years[i].events[j].month_name) >= 0){
						root = bst_insert(root, &(years[i].events[j]), years[i].events[j].month_name, j);
					}
				}
			}
		}
	}
}

void print_bst(bst* root,annual_storms* years,char p){
	int n = sizeof(years)/sizeof(*years);
	if(p == 's'){
		for(int h=0; h<n; h++){
			for(int i=0; i<file_lines(years[h].year); i++){
				if(root->event_id == years[h].events[i].event_id){
					state_print(&(years[h].events[i]));
				}
			}
		}
	}
	if(p == 'm'){
		for(int h=0; h<n; h++){
			for(int i=0; i<file_lines(years[h].year); i++){
				if(root->event_id == years[h].events[i].event_id){
					month_print(&(years[h].events[i]));
				}
			}
		}
		
	}
}

void range(annual_storms* years){ // Range query
	bst* root = NULL;
	int n, year;
	string y, lo, hi, field_name;
	char p;

	cin >> n;
	getline(cin, y);
	cout << n << endl;

	for(int i=0; i<n; i++){
		root = NULL;
		getline(cin, y, ' ');
		getline(cin, y, ' ');
		getline(cin, field_name, ' ');
		getline(cin, lo, ' ');
		getline(cin, hi);

		if(y.compare("all") == 0){
			year = -1;
		}else{
			year = stoi(y);
		}

		cout << "\nQuery:range " << y << " " << field_name << " " << lo;
		cout << " " << hi << "\n" << endl;
		if(field_name.compare("state") == 0){
			state_search(root, years, year, lo, hi);
			p = 's';
		}else if(field_name.compare("month_name") == 0){
			month_search(root, years, year, lo, hi);
			p = 'm';
		}
		if(root == NULL){
			cout << "\n\tNo storm events found for the given range\n" << endl;
		}else{
			print_bst(root,years,p); 
		} 
	}
}

void query(int year, int n){ // Takes n and does queries that many times
	annual_storms storm_year[n]; // Create array of storm years with n years in
	for(int i=0; i<n; i++){ // Does query n times
		string f = to_string(year); // Turns year into string for finding data
        storm_year[i].year = year + i; // Year to be added in storm_year array
        storm_year[i].events = build_events(year+i); // Builds storm_event*
	}
	range(storm_year);
}
