// TIE-02206 Project-01 selections.hh
// Rafia Bushra
// ID: 268449

#ifndef SELECTIONS_HH
#define SELECTIONS_HH

#include <iostream>

using namespace std;

class selections{
public:
    selections();
    void set_values(string& product_name, double price);
    double fetch_price(const string& product);
    void print_pairs() const;
    bool sort_comparator(selections& second_pair);
private:
    string product_;
    double price_;
};

#endif // SELECTIONS_HH
