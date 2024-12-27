#include <iostream>
#include <string>
#include<fstream>
#include <limits>
#include <vector>
#include <algorithm>
#include "subject.h"
#include "BipartiteMatching.h"
using namespace std;


//read the file
int Load_subject(vector<subject>& subjects) {
    try {
        ifstream file("subject_database.txt");
        if (!file.is_open()) {
            throw runtime_error("Error opening file!");
        }

        string name;
        int type, time;
        vector<subject> temp_subjects;

        while (file >> name >> type >> time) {
            bool found = false;
            for (auto& subj : temp_subjects) {
                if (subj.get_subject_name() == name && subj.get_class_type() == type) {
                    subj.add_time(time);
                    found = true;
                    break;
                }
            }
            if (!found) {
                subject new_subject;
                new_subject.set_all(name, type, time);
                temp_subjects.push_back(new_subject);
            }
        }

        subjects = move(temp_subjects);
        cout << "Loaded " << subjects.size() << " classes successfully.\n";
        return subjects.size();
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
        return 0;
    }
}

void display_all_subjects(vector<subject>& subjects) {
    for (auto& subj : subjects) {
        subj.printall();
    }
}

//ask user yes or no question
bool ask_yes_no(const string& question) {
    int choice;
    while (true) {
        cout << question << " (1: Yes, 2: No): ";
        cin >> choice;
        if (choice == 1) return true;
        if (choice == 2) return false;
        cerr << "Invalid input. Please enter 1 or 2.\n";
    }
}

// Create a schedule using bipartite matching
void create_schedule(const vector<subject>& subjects, vector<int>& preferred_times, const vector<int>& free_times) {
    try {
        if (subjects.size() > 24) {
            throw runtime_error("Number of classes exceeds 24. Cannot create a schedule.");
        }

        if (preferred_times.empty()) {
            preferred_times.resize(subjects.size(), -1);
            for (auto& preferred : preferred_times)
                preferred = -1;
        }
        BipartiteMatching matcher(subjects.size() + 25);


        // Add edges to the bipartite graph
        for (size_t i = 0; i < subjects.size(); ++i) {
            if (i >= preferred_times.size()) {
                cerr << "Error: preferred_times size mismatch." << endl;
                return;
            }

            if (preferred_times[i] != -1) {
                matcher.add_edge(i, subjects.size() + preferred_times[i]);
            }
            else {
                for (int time : subjects[i].get_all_times()) {
                    if (find(free_times.begin(), free_times.end(), time) == free_times.end()) {
                        matcher.add_edge(i, subjects.size() + time);
                    }
                }
            }
        }

        int matches = matcher.bipartite_matching();
        if (matches < static_cast<int>(subjects.size())) {
            throw matches;
        }

        // Print the schedule
        for (int day = 0; day < 5; ++day) {
            cout << "Day " << day + 1 << ": ";
            bool has_classes = false;
            for (int slot = 0; slot < 5; ++slot) {
                int time_vertex = subjects.size() + day * 5 + slot;
                //if (time_vertex >= static_cast<int>(matcher.match.size())) {
                //    continue; // Skip if out of range
                //}

                int subject_idx = matcher.get_match(time_vertex);
                if (subject_idx != -1) {
                    subjects[subject_idx].print_subject_name_and_type();
                    has_classes = true;
                }
            }
            if (!has_classes) {
                cout << "No classes.\n";
            }
        }
    }
    catch (const runtime_error& e) {
        cerr << e.what() << endl;
    }
    catch (int matches) {
        cerr << "You need to take " << subjects.size() << " classes, but only " << matches << " can be scheduled.\n";
    }
}


int main(void) {
    int n;
    vector<subject> subjects;
    vector<int> preferred_times;
    vector<int> free_times;
    Load_subject(subjects);

    do {

        cout << "1: Add a subject" << endl << "2: Enter request" << endl << "3: Display  all class stored in file" << endl << "4: Create schedule" << endl << "5: Exit" << endl;
        cout << "Enter the number corresponding to the menu: ";
        cin >> n;
        if (cin.fail()) {
            cin.clear(); // Clear the error flag set by cin.fail()
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            throw "Invalid input. Please enter a number between 1 and 5";
        }

        switch (n) {

            //add subject
        case 1: {
            subject new_subject;
            new_subject.setsubject();//set subject name
            new_subject.setType();
            do {
                new_subject.set_day_time();
            } while (ask_yes_no("Add another day and time for this class?"));
            new_subject.Save_subject();
            subjects.push_back(new_subject);

            break;
        }
              // Enter request 
        case 2:
        {
            if (subjects.empty()) {
                cerr << "No subjects loaded.Please load the subject file first." << endl;

            }
            preferred_times.resize(subjects.size(), -1); // Resize preferred_times after subjects update
            free_times.clear();

            for (auto& preferred : preferred_times)
                preferred = -1;

            if (ask_yes_no("Do you want to specify preferred times for some classes?")) {
                while (true) {
                    cout << "Select a class to specify preferred time:\n";
                    for (size_t i = 0; i < subjects.size(); ++i) {
                        cout << i << ": ";
                        subjects[i].print_subject_name_and_type();
                    }

                    int class_idx;
                    cin >> class_idx;

                    if (class_idx < 0 || class_idx >= static_cast<int>(subjects.size())) {
                        cerr << "Invalid class index. Try again.\n";
                        continue;
                    }

                    cout << "Available times for the selected class:\n";
                    subjects[class_idx].print_all_time();

                    int time_idx;
                    cin >> time_idx;

                    if (time_idx < 1 || time_idx > subjects[class_idx].get_element()) {
                        cerr << "Invalid time index. Try again.\n";
                        continue;
                    }

                    preferred_times[class_idx] = subjects[class_idx].get_time(time_idx - 1);

                    if (!ask_yes_no("Do you want to specify preferred times for another class?")) {
                        break;
                    }
                }
            }

            if (ask_yes_no("Do you want to leave some times free?")) {
                while (true) {
                    int day, time_slot;

                    cout << "Enter the day of the week (1: Monday, ..., 5: Friday): ";
                    cin >> day;

                    if (day < 1 || day > 5) {
                        cerr << "Invalid day. Try again.\n";
                        continue;
                    }

                    cout << "Enter the time slot (1: 8:15~10:00, ..., 5: 16:15~18:00): ";
                    cin >> time_slot;

                    if (time_slot < 1 || time_slot > 5) {
                        cerr << "Invalid time slot. Try again.\n";
                        continue;
                    }

                    int free_time = (day - 1) * 5 + (time_slot - 1);
                    if (find(free_times.begin(), free_times.end(), free_time) == free_times.end()) {
                        free_times.push_back(free_time);
                    }

                    if (!ask_yes_no("Do you want to leave another time free?")) {
                        break;
                    }
                }
            }

            break;
        }
        //Display  all class stored in file
        case 3:
            display_all_subjects(subjects);
            break;

            //Create schedule
        case 4:
            create_schedule(subjects, preferred_times, free_times);
            break;

            //exit the program
        case 5:
            cout << "Exiting the program." << endl;
            break;
        default:
            cout << "Invalid option, please try again." << endl;
        }

    } while (n != 5);

    return 0;
}