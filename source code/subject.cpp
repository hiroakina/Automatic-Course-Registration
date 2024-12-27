#include <iostream>
#include <string>
#include<fstream>
#include <limits>
#include "subject.h"
using namespace std;

// Constructor to initialize the subject
subject::subject() : subjectName(""), Type(0) {}

//receive a subject name from user
void subject::setsubject() {
	int n;
	do {

		cout << "Enter the subject name." << endl;
		cin >> subjectName;
		while (true) {
			cout << "Is the name " << subjectName << " right? Enter a number" << endl << "1 -> Yes, 2 -> NO" << endl;
			cin >> n;
			if (n != 2 && n != 1) {
				cerr << "Invalid input. Please enter 1 (Yes) or 2 (No).\n";
			}
			else
				break;
		}

	} while (n != 1);
}

//receive a class type from user
void subject::setType() {
	while (true) {
		std::cout << "Enter the number corresponding to the class type:\n";
		std::cout << "1 - Lecture, 2 - Practice, 3 - Laboratory: ";
		std::cin >> Type;

		if (Type >= 1 && Type <= 3) break;
		else {
			std::cerr << "Invalid input. Please enter a number between 1 and 3.\n";
		}
	}
}

//receive a day of week and the time of the subject from user
void subject::set_day_time() {
	int day, time_slot;

	// Get the day of the week
	while (true) {
		std::cout << "Enter the number corresponding to the day of the week:\n";
		std::cout << "1 - Monday, 2 - Tuesday, 3 - Wednesday, 4 - Thursday, 5 - Friday: ";
		std::cin >> day;

		if (day >= 1 && day <= 5) break;
		else {
			std::cerr << "Invalid input. Please enter a number between 1 and 5.\n";
		}
	}

	// Get the time slot
	while (true) {
		std::cout << "Enter the number corresponding to the time slot:\n";
		std::cout << "1 - 8:15~10:00, 2 - 10:15~12:00, 3 - 12:15~14:00, 4 - 14:15~16:00, 5 - 16:15~18:00: ";
		std::cin >> time_slot;

		if (time_slot >= 1 && time_slot <= 5) break;
		else {
			std::cerr << "Invalid input. Please enter a number between 1 and 5.\n";
		}
	}

	// Store the time as a single integer
	time.push_back((day - 1) * 5 + (time_slot - 1));
}

//save the subject to the file subject_database.txt
void subject::Save_subject() {
	ofstream file("subject_database.txt", std::ios::app);
	if (!file.is_open()) {
		throw runtime_error("Failed to open the file for writing.");
	}

	for (int t : time) {
		file << subjectName << "\n" << Type << "\n" << t << "\n";
	}

}


//set all element of subject
void subject::set_all(std::string name, int T, int t) {
	subjectName = name;
	Type = T;
	time.push_back(t);
}

//add the time ofsubject
void subject::add_time(int t) {
	time.push_back(t);
}

//show the subjectname and type
void subject::print_subject_name_and_type() const {
	cout << subjectName << ": ";
	switch (Type) {
	case 1:
		cout << "lecture" << endl;
		break;
	case 2:
		cout << "practice" << endl;
		break;
	case 3:
		cout << "laboratory" << endl;
		break;
	}
}

//print all time options of the subject
void subject::print_all_time() {
	for (int i = 0;i < time.size();i++) {
		cout << i + 1 << ": ";
		print_dayof_week(time[i] / 5);
		print_time(time[i] % 5);
	}
}

//print the day of week of the subject
void subject::print_dayof_week(int d) {
	switch (d) {
	case 0:
		cout << "Monday ";
		break;
	case 1:
		cout << "Tuseday ";
		break;
	case 2:
		cout << "Wednesday ";
		break;
	case 3:
		cout << "Thrusday ";
		break;
	case 4:
		cout << "Friday ";
		break;
	}
}

//print the time of the subject
void subject::print_time(int t) {
	switch (t) {
	case 0:
		cout << " 8:15~10:00" << endl;
		break;
	case 1:
		cout << "10:15~12:00" << endl;
		break;
	case 2:
		cout << "12:15~ 14:00" << endl;
		break;
	case 3:
		cout << "14:15~16:00" << endl;
		break;
	case 4:
		cout << "16:15~18:00" << endl;
		break;
	}
}

//print all element of the subject
void subject::printall() {
	print_subject_name_and_type();
	cout << "The number of options of the time: " << time.size() << endl;
	print_all_time();
	cout << endl;
}

//return the time of the subject
int subject::get_time(int n) {
	if (n < 0 || n >= time.size()) {
		throw std::out_of_range("Index out of range.");
	}
	return time[n];
}

//return the number of class options
int subject::get_element() {
	return time.size();
}

string subject::get_subject_name() {
	return subjectName;
}

int subject::get_class_type() {
	return Type;
}

vector<int> subject::get_all_times() const {
	return time;
}