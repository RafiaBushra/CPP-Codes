#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

class Clock {
public:
	Clock(int hour, int minute);
	void tick_tock();
	void print() const;

	int fetch_hour() const;
	int fetch_minutes() const;

private:
	int minutes_since_midnight_;
};


Clock::Clock(int hour, int minute) :
	minutes_since_midnight_(60 * hour + minute) {
}


void Clock::tick_tock() {
	++minutes_since_midnight_;

	if (minutes_since_midnight_ >= 24 * 60) {
		minutes_since_midnight_ = 0;
	}
}


int Clock::fetch_hour() const {
	return minutes_since_midnight_ / 60;
}


int Clock::fetch_minutes() const {
	return minutes_since_midnight_ % 60;
}


void Clock::print() const {
	cout << setfill('0') << setw(2) << fetch_hour()
		<< "."
		<< setw(2) << fetch_minutes()
		<< endl;
}


bool compare_implementation(Clock time1, Clock time2) {
	if (time1.fetch_hour() != time2.fetch_hour()) {
		return time1.fetch_hour() < time2.fetch_hour();
	}
	return time1.fetch_minutes() < time2.fetch_minutes();
}

void main() {
	int hour = 0;
	int minute = 0;
	char answer = 'y';
	vector<Clock> times = { };
	while (answer == 'y') {
		cout << "Do you want to enter a time? (Y/N)\t";
		cin >> answer;
		if (answer == 'y') {
			cout << "Enter hour:\t";
			cin >> hour;
			cout << "Enter minutes:\t";
			cin >> minute;
			Clock new_time(hour, minute);
			times.push_back(new_time);
		}
	}
	cout << "The times in increasing order:\n";
	sort(times.begin(), times.end(), compare_implementation);
	for (Clock item : times) {
		item.print();
	}
}