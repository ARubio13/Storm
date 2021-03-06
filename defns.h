#define	STATE_LEN	20
#define	MONTH_LEN	15
#define	EVENT_LEN	30
#define	COUNTY_LEN	35
#define	DATE_LEN	25
#define	FAT_LOC		30

#include <string>

using namespace std;

struct annual_storms{
	int year; // Year of storm events
	struct storm_event *events;  // Pointer to array of storm events for the given year
};

struct storm_event{
	int event_id; // Event id
	string state; // State name
	int year; // Four digit year of event
	string month_name; // Month of event
	string event_type; // Event type
	char cz_type; // Where event happened, C, Z, or M
	string cz_name; // Name of county/zone
	int injuries_direct; // Number of direct injuries
	int injuries_indirect; // Number of indirect injuries
	int deaths_direct; // Number of direct deaths
	int deaths_indirect; // Number of indirect deaths
	int damage_property; // Amount of property damage; convert to integer
	int damage_crops; // Amount of crop damage; convert to integer
	struct fatality_event *f; // Linked list of fatalities associated with this storm event
};

struct fatality_event{
	int fatality_id; // Identifier of the fatality
	int event_id; // Identifier of the storm event
	char fatality_type; // D or I
	string fatality_date; // Date and time of fatality
	int fatality_age; // Age of fatality
	char fatality_sex; // Gender of fatality
	string fatality_location; // Location of fatality
	struct fatality_event *next; // Pointer to next fatality event
};

struct hash_table_entry{
	int event_id; // Event id -- key used to hash on
	int year; // Year of storm event
	int event_index; // For the given year, the index into array of storm events
	struct hash_table_entry *next; // Pointer to next entry in case of collisions
};

struct bst{ // A binary search tree
	string s; // String corresponding to either a state or a month_name
	int event_id; // Identifier of storm event
	int year; // Year of storm event
	int event_index; // For the given year, the index into array of storm events
	struct bst *left;  // Pointer to the left subtree
	struct bst *right;  // Pointer to the right subtree
};

struct heap_entry{ // An entry in a max-heap
	int damage_amount; // Amount of damage to property or crops
	int year; // Year of storm event
	int event_index; // For the given year, the index into array of storm events
};