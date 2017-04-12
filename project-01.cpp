#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "splitter.hh"
#include "product_prices.hh"
#include "chain_map.hh"

using namespace std;

// This function simply enters data into the data-structure and checks for possible errors in the data-type
void fill_map(Splitter& line, chain_map& original_map) {
	// field(0) = chain name
	// field(1) = store location
	// field(2) = product name
	// fiels(3) = price of that product
	string product_name = line.fetch_field(2);
	try
	{
		double price = stod(line.fetch_field(3));	// Turn the field from string to double 
		product_prices pairs(product_name, price);	// since in the file it was in string form
		original_map.modify_map(line.fetch_field(0), line.fetch_field(1), pairs);
	}
	catch (const invalid_argument&)		// If converting price from string to double fails
	{
		cout << "Error: Prices are not in the correct format." <<endl;
	}
}

int main()
{	
	chain_map original_map;
	ifstream file_stream;

	file_stream.open("products.txt");
	if (file_stream.is_open()) {
		string line;
		Splitter row;
		for (getline(file_stream, line); !file_stream.eof();) {
			row.set_string_to_split(line);
			int fields = row.split(';');
			if (fields != 4) {
				// There should be exactly 4 fields after splitting.
				// Missing or additional fields mean missing or additional information 
				// that the program is ready to process.
				cout << "Error: Wrong text format.";
				break;
			}
			else {
				// Insert fields into correct places in the original_map
				fill_map(row, original_map);
			}
		}
	}
	else {
		cout << "Error: the input file can not be read." << endl;
		return;
	}
	string answer;
	Splitter split_answer;
	while (true) {
		cout << "product search> ";
		getline(cin, answer);
		split_answer.set_string_to_split(answer);
		split_answer.split(' ', true);
		if (split_answer.fetch_field(0) == "quit" || split_answer.fetch_field(0) == "Quit") {
			return;
		}
		else if (split_answer.fetch_field(0) == "chains" || split_answer.fetch_field(0) == "Chains") {
			original_map.print_chains();
		}
		else if (split_answer.fetch_field(0) == "stores" || split_answer.fetch_field(0) == "Stores") {
			original_map.print_locations(split_answer.fetch_field(1));
		}
		else if (split_answer.fetch_field(0) == "cheapest" || split_answer.fetch_field(0) == "Cheapest") {
			original_map.print_cheapest(split_answer.fetch_field(1));
		}
		else if (split_answer.fetch_field(0) == "selection" || split_answer.fetch_field(0) == "Selection") {
			original_map.print_selection(split_answer.fetch_field(1), split_answer.fetch_field(2));
		}
	}
}
