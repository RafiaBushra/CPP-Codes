// TIE-02206 Project-01 store.hh
// Rafia Bushra
// ID: 268449

#ifndef STORE_HH
#define STORE_HH

#include "selections.hh"
#include <vector>
#include <string>


class Store
{
public:
    Store();

    void add_location(string& location_name);
    void add_product(string& product_name, double price);
    void print_store_location() const;
    void print_selections();
    string fetch_store_location();
    double fetch_price(const string& product_name);
    void sort_implementation();

private:
    string store_location_;
    vector<selections> selections_;
};

#endif // STORE_HH
