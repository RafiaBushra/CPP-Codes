// TIE-02206 Project-01 main.cpp
// Rafia Bushra
// ID: 268449

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "splitter.hh"
#include "store.hh"

using namespace std;
using chain_map = map<string, vector<Store>>;

// This function simply prints the chain names
// in alphabetical order.
void print_chains(const chain_map& original_map){

    for(auto item:original_map){
        cout << item.first << endl;
    }
}

// This is a helper function to sort the location vector
// according to location name alphabetically.
bool sort_comparator(Store& first, Store& second){
    return first.fetch_store_location () < second.fetch_store_location ();
}

void sorter(vector<Store> location_vector){
    for(int index = 0; index < location_vector.size () - 1; index++){
        for(int next_index = index + 1; next_index < location_vector.size (); next_index++){
            if(sort_comparator (location_vector.at (index), location_vector.at (next_index))){
                auto temp_variable = location_vector.at(index);
                location_vector.at(index) = location_vector.at(next_index);
                location_vector.at(next_index) = temp_variable;
            }
        }
    }
}

// This function prints all the store locations of the given
// chain name, sorted alphabetically.
void print_locations(const chain_map& original_map, const string& chain_name){
    // original_map.find(chain_name) will return an iterator at
    // original_map.end() if the chain_name cannot be found.
    if(original_map.find (chain_name) != original_map.end ()){
        // original_map.at(chain_name) returns the locations vector
        // which is then sorted alphabetically with help from the sort_comparator.
        sorter(original_map.at(chain_name));
        // temp_variable iterates through each Store object and calls the
        // print_store_location() function, which simply prints the locations.
        for(auto temp_variable:original_map.at(chain_name)){
            temp_variable.print_store_location();
        }
    }
    else{
        cout << "Error: No chains named " << chain_name << endl;
    }
}

// This function first derives the cheapest price of the given product
// and then prints all the chains and locations that sell with this price.
void print_cheapest(const chain_map& original_map, const string& product){
    // A temporary vector to store the name(s) of the chains and locations.
    vector<string> temp_vector;
    double minimum;
    // product_exists will tell us if the product name given actually exists
    // in any of the stores.
    bool product_exists = false;
    // This loop fetches the cheapest price of the given product.
    // temp_variable iterates through each individual chain map.
    for(auto temp_variable:original_map){
        // temp_store iterates through each individual store location
        // of the chain map.
        for(auto temp_store:temp_variable.second){
            // fetch_price() returns -1 if the product is not found.
            if(temp_store.fetch_price(product) != -1){
                // We need a value for minimum so we can
                // compare it with the other prices of the product.
                // Since product_exists is False in the beginning,
                // it is used as an initialization check. After this,
                // its value is changed to True so this condition is
                // useless after its first use.
                if(!product_exists){
                    minimum = temp_store.fetch_price(product);
                    product_exists = true;
                }
                // minimum will be replaced by the cheapest price
                // each time a new price is found.
                if(temp_store.fetch_price(product) < minimum){
                    minimum = temp_store.fetch_price(product);
                }
            }
        }
    }
    // If there is at least one product by the given name, product_exists
    // will be 'true'. Otherwise it will still be 'false' from the first
    // time we initialized it.
    if(!product_exists){
        cout << "Error: The product does not exist in any stores.\n";
        return;
    }
    // Now that we have the cheapest price, this loop fills temp_vector
    // with the names of the chain and location of the stores that sell
    // at the minimum price.
    for(auto temp_map:original_map){
        for(auto temp_store:temp_map.second){
            if(temp_store.fetch_price(product) == minimum){
                // temp_map.first = chain name
                // For ease of display, we combine the chain name and the
                // location as one string, with a space between.
                temp_vector.push_back (temp_map.first + " " + temp_store.fetch_store_location());
            }
        }
    }
    // Finally we sort the store names alphabetically
    // and print them.
    sort(temp_vector.begin (), temp_vector.end ());
    cout << setprecision(2) << minimum << endl;
    for(string temp_variable:temp_vector){
        cout << temp_variable << endl;
    }
}

// This function prints the selection of the given chain and location.
void print_selection(const chain_map& original_map, const string& chain_name, const string& store_location){
    // store_found is a error checking flag.
    bool store_found = false;
    // original_map.find (chain_name) will return an iterator on
    // original_map.end() if chain_name is not found.
    if(original_map.find (chain_name) != original_map.end ()){
        // original_map.at (chain_name) returns the locations vector
        // and temp_store iterates through each Store object and
        // prints its selection if the location name is the same as
        // the store_location entered by the user.
        for(auto temp_store:original_map.at(chain_name)){
            if(temp_store.fetch_store_location() == store_location){
                temp_store.print_selections();
                store_found = true;
                break;
            }
        }
        // For cases when the chain_name is correct, but the store_location
        // is incorrect.
        if(!store_found){
            cout << "Error: " << chain_name << " has no stores in " << store_location << endl;
        }
    }
    else{
        cout << "Error: There are no chains named " << chain_name << endl;
    }

}

// This is the prompt menu where the user types in their queries.
void prompt_menu(const chain_map& original_map){
    string answer;
    Splitter split_answer;

    while (true) {
        cout << "product search> ";
        getline(cin, answer);

        // split_answer is used for cases when the queries have more information along with
        // the keyword. e.g. 'cheapest milk'
        // It is also used for error checking. e.g. to quit the program, the user needs to
        // type only 'quit'. If they enter anything before or after 'quit', e.g. 'quit now',
        // split_answer will split into two parts and split_answer.number_of_fields () will
        // return 2, which will cause an error message.
        split_answer.set_string_to_split(answer);
        split_answer.split(' ', true);

        // The program will only end when the user enters 'quit'.
        if (split_answer.fetch_field(0) == "quit" && split_answer.number_of_fields () == 1) {
            return;
        }
        else if (split_answer.fetch_field(0) == "chains" && split_answer.number_of_fields () == 1) {
            print_chains(original_map);
        }
        // split_answer.fetch_field(1) = chain name.
        else if (split_answer.fetch_field(0) == "stores" && split_answer.number_of_fields () == 2) {
            print_locations(original_map, split_answer.fetch_field(1));
        }
        // split_answer.fetch_field(1) = product name.
        else if (split_answer.fetch_field(0) == "cheapest" && split_answer.number_of_fields () == 2) {
            print_cheapest(original_map, split_answer.fetch_field(1));
        }
        // split_answer.fetch_field(1) = chain name.
        // split_answer.fetch_field(2) = store location.
        else if (split_answer.fetch_field(0) == "selection" && split_answer.number_of_fields () == 3) {
            print_selection(original_map, split_answer.fetch_field(1), split_answer.fetch_field(2));
        }
    }
}

// This function enters the data into the correct places of the original_map.
void fill_map(Splitter& line, chain_map& original_map) {
    try{
        string chain = line.fetch_field (0);
        string location = line.fetch_field (1);
        string product_name = line.fetch_field (2);
        double price = stod(line.fetch_field (3));
        // temp_vector is only used to initialize original_map
        vector<Store> temp_vector;
        if(original_map.find(chain) == original_map.end()){
            original_map.insert ({chain, temp_vector});
        }

        Store temp_variable;
        temp_variable.add_location (location);
        temp_variable.add_product (product_name, price);
        original_map.at (chain).push_back (temp_variable);
    }
    // If converting price from string to double fails.
    catch (const invalid_argument&)
    {
        cout << "Error: Prices are not in the correct format." <<endl;
    }
}

// The main function reads the file, splits each text row and then calls fill_map
// to input data into original_map.
int main()
{
    map<string, vector<Store>> original_map;
    ifstream file_stream;

    file_stream.open("products.txt");
    if (file_stream.is_open()) {
        string line;
        Splitter row;
        for (getline(file_stream, line); !file_stream.eof();) {
            row.set_string_to_split(line);
            int fields = row.split(';');
            // There should be exactly 4 fields after splitting.
            // Missing or additional fields mean missing or additional information
            // that the program is ready to process.
            if (fields != 4) {
                cout << "Error: Wrong text format.\n";
                return 0;
            }
            // Insert fields into correct places in the original_map
            else {
                fill_map(row, original_map);
            }
        }
        // If the whole file is read succesfully, prompt_menu starts
        // the query program.
        prompt_menu (original_map);
    }
    else {
        cout << "Error: the input file can not be read.\n";
    }

}
