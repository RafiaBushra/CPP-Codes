#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "splitter.hh"
#include "product_prices.hh"
#include "chain_map.hh"

using namespace std;

chain_map::chain_map()
{
	chain_map_ = {};
}

void chain_map::modify_map(string& chain_name, string& store_location, product_prices& item)
{
	chain_map_[chain_name][store_location].push_back(item);
}

void chain_map::print_chains() const {
	if (chain_map_.empty()) {
		cout << "Error: Nothing to print.\n";
		return;
	}

	for(auto map_object:chain_map_){
		cout << map_object.first << endl;
	}
}

void chain_map::print_locations(const string& chain) const {
	if (chain_map_.find(chain) == chain_map_.end()) {
		cout << "Error: Chain does not exist.\n";
		return;
	}
	for (auto store : chain_map_.at(chain)) {
		cout << store.first << endl;
	}
}

void chain_map::print_selection(const string& chain, const string& location) const {
	if (chain_map_.find(chain) == chain_map_.end()) {
		cout << "Error: Chain does not exist.\n";
		return;
	}
	else if (chain_map_.at(chain).find(location) == chain_map_.at(chain).end()) {
		cout << "Error: Store location does not exist.\n";
		return;
	}
	auto pair_vector = chain_map_.at(chain).at(location);
		
	for (auto item : pair_vector) {
		item.print_values();
	}
}

bool find_product(const string& product_name, vector<product_prices>& items_vector) {
	for (int index = 0; index != items_vector.size(); index++) {
		product_prices item_info = items_vector[index];
		if (product_name == item_info.fetch_product_name()) {
			return index;
		}
	}
	return -1;
}

bool compare_function(string& first, string& second) {
	Splitter first_object(first);
	Splitter second_object(second);
	first_object.split(' ');
	second_object.split(' ');
	if (first_object.fetch_field(0) == second_object.fetch_field(0)) {
		return first_object.fetch_field(1) < second_object.fetch_field(1);
	}
	return first_object.fetch_field(0) < second_object.fetch_field(0);
}

void chain_map::print_cheapest(const string& product_name) const {
	vector<string> record_vector;
	int counter = 0;
	double cheapest_price = 0.0;
	for (auto map_object : chain_map_) {
		for (auto store_location : map_object.second) {
			int index = find_product(product_name, store_location.second);
			if ( index != -1) {
				if (cheapest_price == 0.0) {
					cheapest_price = store_location.second[index].fetch_price();
					record_vector.push_back(map_object.first + " " + store_location.first);
				}
				else if (store_location.second[index].fetch_price() < cheapest_price) {
					cheapest_price = store_location.second[index].fetch_price();
					record_vector.push_back(map_object.first + " " + store_location.first);
					counter++;
				}
			}
		}
	}
	if (cheapest_price == 0.0) {
		cout << "This product is not available anywhere.\n";
		return;
	}
	sort(record_vector.begin(), record_vector.end(), compare_function);
	cout << setprecision(2) << cheapest_price << endl;
	for (int index = 0; index <= counter; index++) {
		cout << record_vector[index] << endl;
	}
}
