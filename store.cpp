// TIE-02206 Project-01 store.cpp
// Rafia Bushra
// ID: 268449

#include "store.hh"
#include "selections.hh"
#include <iostream>
#include <algorithm>

using namespace std;

Store::Store()
{
    store_location_ = "";
}

void Store::add_location(string &location_name)
{
    store_location_ = location_name;
}

void Store::add_product(string &product_name, double price)
{
    selections temp_variable;
    temp_variable.set_values (product_name, price);
    selections_.push_back (temp_variable);
}

void Store::print_store_location() const
{
    cout << store_location_ << endl;
}

void Store::sort_implementation(){
    for(int index = 0; index < selections_.size () - 1; index++){
        for(int next_index = index + 1; next_index < selections_.size (); next_index++){
            if(selections_.at (index).sort_comparator (selections_.at (next_index))){
                auto temp_variable = selections_.at(index);
                selections_.at(index) = selections_.at(next_index);
                selections_.at(next_index) = temp_variable;
            }
        }
    }
}

void Store::print_selections()
{
    sort_implementation ();
    for(auto item:selections_){
        print_selections ();
    }
}

string Store::fetch_store_location()
{
    return store_location_;
}

double Store::fetch_price(const string &product_name)
{
    double temp_variable;
    for(auto pair:selections_){
        temp_variable = pair.fetch_price(product_name);
        if(temp_variable != -1){
            return temp_variable;
        }
    }
    return -1;
}
