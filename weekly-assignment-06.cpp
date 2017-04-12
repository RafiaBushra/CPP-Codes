#include <iostream>
#include <string>
#include <map>

using namespace std;

int count_names_iteration(const map<string, string>& phonebook, char initial_letter) {

	int count = 0;

	map<string, string>::const_iterator iter = phonebook.begin();

	while (iter != phonebook.end()) {
		if (iter->first.at(0) == initial_letter) {
			++count;
		}

		++iter;
	}

	return count;
}

int count_names_recursion(const map<string, string>& phonebook, char initial_letter, 
	int count, map<string, string>::const_iterator iter) {
	
	if (iter == phonebook.end()) {
		return count;
	}
	else {
		if (iter->first.at(0) == initial_letter) {
			return count_names_recursion(phonebook, initial_letter, ++count, ++iter);
		}
		else {
			return count_names_recursion(phonebook, initial_letter, count, ++iter);
		}
	}
}

void main() {
	map<string, string> phonebook = {
		{"Rafia", "268449"},
		{"Bushra", "26899"},
		{"R", "00000"},
	};
	cout << count_names_iteration(phonebook, 'R') << "\n\n";
	cout << count_names_recursion(phonebook, 'R', 0, phonebook.begin()) << "\n\n";
}