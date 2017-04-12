#include <string>

using namespace std;

class product_prices
{
public:
	product_prices(const string& product_name, double price);
	void reset_values(const string& product_name, double price);
	const void print_values();
	string fetch_product_name();
	double fetch_price();
private:
	string product_name_;
	double price_;
};
