// TIE-02206 Project-01 splitter.cpp
// Rafia Bushra
// ID: 268449

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "splitter.hh"

using namespace std;

const unsigned int SPLIT_ERROR = 0;


Splitter::Splitter(const string& string_to_split) :
    original_string_(string_to_split), split_result_({}) {
}


void Splitter::set_string_to_split(const string& string_to_split) {
    original_string_ = string_to_split;
    split_result_ = {};
}


unsigned int Splitter::split(char separator, bool skip_empty_fields) {
    split_result_.clear();
    string::size_type startpos = 0;
    string field_content;

    while (true) {
        string::size_type endpos;

        endpos = original_string_.find(separator, startpos);
        if (endpos == string::npos) {
            break;
        }
        field_content = original_string_.substr(startpos, endpos - startpos);
        if (!(skip_empty_fields && field_content.empty())) {
            split_result_.push_back(field_content);
        }
        startpos = endpos + 1;
    }
    field_content = original_string_.substr(startpos);

        if (!(skip_empty_fields && field_content.empty())) {
        split_result_.push_back(field_content);
    }

    return split_result_.size();
}


unsigned int Splitter::number_of_fields() const {
    if (split_result_.size() == 0) {
        return SPLIT_ERROR;

    }
    else {

        return split_result_.size();
    }
}


string Splitter::fetch_field(unsigned int field_index) const {
        if (split_result_.empty() || field_index >= split_result_.size()) {
        throw out_of_range("too large index or split not called");
    }

    return split_result_.at(field_index);
}
