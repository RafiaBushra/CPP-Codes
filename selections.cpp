// TIE-02206 Project-01 selections.cpp
// Rafia Bushra
// ID: 268449

#include "selections.hh"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

selections::selections()
{
    product_ = "";
    price_ = 0.0;
}

double selections::fetch_price(const string &product)
{
    if(product == product_){
        return price_;
    }
    return -1;
}

void selections::print_pairs() const
{
    cout << setprecision(2) << product_ << " " << price_ << endl;
}

void selections::set_values(string &product_name, double price)
{
    product_ = product_name;
    price_ = price;
}

bool selections::sort_comparator(selections& second_pair){
    return product_ < second_pair.product_;
}
