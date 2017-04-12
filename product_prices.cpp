#include <iostream>
#include <string>
#include <iomanip>
#include "product_prices.hh"
using namespace std;

void product_prices::reset_values(const string& product_name, double price) {
	product_name_ = product_name;
	price_ = price;
}

product_prices::product_prices(const string& product_name, double price) {
	product_name_ = product_name;
	price_ = price;
}

const void product_prices::print_values() {
	cout << product_name_ << " " << setprecision(2) << price_ << endl;
}

string product_prices::fetch_product_name() {
	return product_name_;
}

double product_prices::fetch_price() {
	return price_;
}
