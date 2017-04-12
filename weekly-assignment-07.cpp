#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


struct Student {
	string name;
	unsigned int id;
};


bool name_comparator(Student first, Student second) {
	return first.name < second.name;
}


bool id_comparator(Student* first, Student* second) {
	return first->id < second->id;
}


int main() {
	vector<Student> studentregistry = {
		{ "Teekkari, Tiina",           52401 },
		{ "Ylikuuskajaskari, Jaska",  186112 },
		{ "Repolainen, Reijo",        117118 },
		{ "Teekkari, Teemu",          196196 },
		{ "Santaholma, Santtu",       173421 },
	};

	vector<Student*> studentpointers = {};

	// Let's initialize the pointer vector with the addresses of the
	// of the students in the studentregistry vector.
	for (vector<Student>::size_type i = 0; i < studentregistry.size(); ++i) {
		studentpointers.push_back(&studentregistry.at(i));
	}

	// Sort studentregistry by the student names
	sort(studentregistry.begin(), studentregistry.end(), name_comparator);
	

	// Sort studentpointers by the student id
	sort(studentpointers.begin(), studentpointers.end(), id_comparator);


	cout << "Students sorted in alphabetical order:" << endl
		<< "--------------------------------------" << endl;
	for (Student stu : studentregistry) {
		cout << setw(24) << left << stu.name
			<< setw(6) << right << stu.id << endl;
	}

	cout << endl;

	cout << "Students sorted by the student id:" << endl
		<< "----------------------------------" << endl;
	for (Student* stu_ptr : studentpointers) {
		cout << setw(24) << left << stu_ptr->name
			<< setw(6) << right << stu_ptr->id << endl;
	}
}