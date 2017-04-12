#include <iostream>
#include <map>
#include <string>
#include <iomanip>

using namespace std;

using PositionMap = map< string, map<int, string> >;

void print_map(const PositionMap& map_data) {
	for (auto events : map_data) {
		cout << "Event:\t";
		cout << setw(10) << events.first << endl;
		for (auto athletes : events.second) {
			cout << "Position " << athletes.first << ":\t";
			cout << athletes.second << endl;
		}
	}
}


void add_connection(PositionMap& map_data, const string& event, int position, const string& athlete_name) {
	if (map_data.find(event) == map_data.end()) {
		map_data.insert( { event, {} } );
		map_data.at(event).insert({ position, athlete_name });
	}
	else {
		if (map_data.at(event).find(position) == map_data.at(event).end()) {
			map_data.at(event).insert({ position, athlete_name });
		}
		else {
			map_data.at(event).at(position) = athlete_name;
		}
	}
}


int main() {
	 
	PositionMap original_map = {
		{ "Javelin",   { { 1, "A" }, { 2, "B" }, { 3, "C" }, { 4, "D" }, { 5, "E" }, { 6, "F" }, } },
		{ "Pole Jump", { { 1, "G" }, { 2, "H" }, { 3, "I" }, { 4, "J" }, { 5, "K" }, { 6, "L" }, } },
	};
	//print_map(original_map);
	add_connection(original_map, "Marathon", 1, "M");
	add_connection(original_map, "Marathon", 2, "N");
	add_connection(original_map, "Marathon", 3, "O");
	print_map(original_map);
}