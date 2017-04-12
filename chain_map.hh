#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "product_prices.hh"

using namespace std;
using stores_map = map<string, vector<product_prices>>;


class chain_map
{
public:
	chain_map();

	void modify_map(string& chain_name, string& store_location, product_prices& item);
	void print_chains() const;
	void print_locations(const string& chain) const;
	void print_selection(const string& chain, const string& location) const;
	void print_cheapest(const string& product_name) const;

private:
	map<string, stores_map> chain_map_;
};

