#ifndef REGISTER_H
#define REGISTER_H
#include <string>
#include <vector>
#include "BipartiteMatching.h"

class subject {

	std::string subjectName;
	int Type; //1- lecture, 2- practice, 3- laboratory  
	std::vector<int> time; //Class time as a 5 x 5 matrix and make it a number from 0 to 24.  
	// day of the week (1- Monday 2- Tuesday 3- Wednesday 4- Thursday 5- Friday)
	// time(1 - 8:15~10:00,2 - 10:15~12:00 ...5 - 16:15~18:00) 
	// ->(day of week-1)*5+(time-1)


public:
	// Constructor to initialize the subject
	subject();

	//receive a subject name from user
	void setsubject();

	//receive a subject type from user
	void setType();

	//receive a day of week and the time of the subject from user and save it
	void set_day_time();

	//save the subject to the file subject_database.txt
	void Save_subject();

	//set all element of subject
	void set_all(std::string name, int T, int t);

	//add the time ofsubject
	void add_time(int t);

	//show the subjectname and type 
	void print_subject_name_and_type() const;

	//print all time options of the subject 
	void print_all_time();

	//print the day of week of the subject
	void  print_dayof_week(int d);

	//print the time of the subject
	void print_time(int t);

	//print all element of the subject
	void printall();

	//return the time of the subject
	int get_time(int n);

	//return the number of class options
	int get_element();

	std::string get_subject_name();

	int get_class_type();

	std::vector<int> get_all_times() const;


};





#endif