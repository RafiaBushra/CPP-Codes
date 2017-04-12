#include<iostream>
#include<string>
#include<vector>
#include<stdexcept>

using namespace std;

const unsigned int SPLIT_ERROR = 0;

class Splitter {
public:
	Splitter(const string& string_to_split = "");
	void set_string_to_split(const string& string_to_split);
	unsigned int split(char separator, bool ignore_empty = false);
	unsigned int number_of_fields() const;
	string fetch_field(unsigned int field_index) const;

private:
	string sentence_;
	vector<string> words_;
};

Splitter::Splitter(const string& string_to_split) {
	sentence_ = string_to_split;
	words_ = {};
}

void Splitter::set_string_to_split(const string& string_to_split) {
	sentence_ = string_to_split;
	words_ = {};
}

unsigned int Splitter::split(char separator, bool ignore_empty) {
	string::size_type position = 0;
	string::size_type end = 0;
	string::size_type start = 0;
	while (end != sentence_.size() - 1) {
		position = sentence_.find(separator, end++);
		words_.push_back(sentence_.substr(start, end - start));
		if (ignore_empty == true && separator == sentence_.at(end + 1)) {
			start = end + 1;
		}
		else start = end;
	}
	return words_.size();
}

unsigned int Splitter::number_of_fields() const {
	if (!words_.empty()) {
		return words_.size();
	}
	else {
		return SPLIT_ERROR;
	}
}

string Splitter::fetch_field(unsigned int field_index) const {
	if (field_index < words_.size()) {
		return words_.at(field_index);
	}
	else {
		throw out_of_range("too large index or split not called");
	}
}

int main() {
	Splitter splitter_object("a::bc:def::hijlkm");

	splitter_object.split(':');  // Observe: single quotes: parameter is of type char.

	cout << "fields: " << splitter_object.number_of_fields() << endl;  // 6

	cout << splitter_object.fetch_field(0) << endl;  // a
	cout << splitter_object.fetch_field(4) << endl;  // (empty)
	cout << splitter_object.fetch_field(5) << endl;  // hijlkm

													 //    for ( unsigned int i = 0; i < splitter_object.number_of_fields(); ++i ) {
													 //        string current_field_contents = splitter_object.fetch_field(i);
													 //        cout << i << ": [" << current_field_contents << "]" << endl;
													 //    }

													 //    splitter_object.set_string_to_split(" A B  C   D    E     ");
													 //    unsigned int fields = splitter_object.split(' ', true);

													 //    cout << "fields: " << fields << endl;  // 5

													 //    for ( unsigned int i = 0; i < fields; ++i ) {
													 //        string current_field_contents = splitter_object.fetch_field(i);
													 //        cout << i << ": [" << current_field_contents << "]" << endl;
													 //    }

													 //    cout << splitter_object.fetch_field(5) << endl;  // out_of_range exception
	return 0;
}
