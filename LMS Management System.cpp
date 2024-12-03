#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

class Student
{
private:
    string roll;

public:
    void put();
    void get(vector<vector<string>>& data);
    void sortTimeSpent(vector<vector<string>>& data);
};

void Student::put()
{
    cout << "ENTER STUDENT ROLL NO: ";
    cin >> roll;
}

void Student::get(vector<vector<string>>& data)
{
    for (const vector<string>& row : data) {
        if (row[2] == roll) {
            cout << "ROLL NO: " << row[2] << endl;
            cout << "STUDENT NAME: " << row[3] << endl;
            cout << "ACADEMIC YEAR: " << row[4] << endl;
            cout << "STANDARD NAME: " << row[5] << endl;
            cout << "DIV: " << row[6] << endl;
            cout << "MEDIUM: " << row[7] << endl;
            cout << "SHIFT NAME: " << row[8] << endl << endl;
            cout << "SUBJECT: " << row[9] << endl;
            cout << "TOPIC WATCH: " << row[10] << endl;
            cout << "CONTENT WATCHED: " << row[11] << endl;
            cout << "DATE: " << row[12] << endl;
            cout << "TIME SPENT (IN MINUTE): " << row[13] << endl;
            cout << "SUBJECT TEACHER NAME: " << row[14] << endl;
        }
    }
}

void Student::sortTimeSpent(vector<vector<string>>& data)
{
    string nodeName;
    cout << "Enter the node name: ";
    cin.ignore();
    getline(cin, nodeName);

    int timeDurationIndex = -1;
    for (int i = 0; i < data[0].size(); i++) {
        if (data[0][i] == "TIME SPENT (IN MINUTE)") {
            timeDurationIndex = i;
            break;
        }
    }

    if (timeDurationIndex == -1) {
        cout << "Time Duration column not found." << endl;
        return;
    }

    sort(data.begin(), data.end(), [timeDurationIndex](const vector<string>& a, const vector<string>& b) {
        if (a.size() <= timeDurationIndex || b.size() <= timeDurationIndex)
            return false;

        try {
            int durationA = stoi(a[timeDurationIndex]);
            int durationB = stoi(b[timeDurationIndex]);
            return durationA > durationB;
        } catch (const exception& e) {
            return false;
        }
    });

    cout << "Sorted Time Duration for Node '" << nodeName << "':" << endl;
    bool found = false;
    for (const vector<string>& row : data) {
        if (row[9] == nodeName) {
            cout << "Name: " << row[3] << ",\t\t\t Time Duration: ";
            if (row.size() > timeDurationIndex)
                cout << row[timeDurationIndex];
            else
                cout << "N/A";
            cout << " minutes" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No records found for Node '" << nodeName << "'" << endl;
    }
}

int main()
{
    ifstream file("Book.csv");

    if (!file.is_open()) {
        cout << "Failed to open the file." << endl;
        return 1;
    }

    vector<vector<string>> data;
    string line;

    while (getline(file, line)) {
        vector<string> row;
        istringstream iss(line);
        string cell;

        while (getline(iss, cell, ',')) {
            row.push_back(cell);
        }

        data.push_back(row);
    }

    file.close();

    Student obj;
    string choice;

    do {
        int menuChoice = 0;

        cout << "------ MENU ------" << endl;
        cout << "1. Display individual Student Data" << endl;
        cout << "2. Maximum No. of times Lecture Watched by Student." << endl;
        cout << "3. Maximum time Duration of Lecture Watched by Student." << endl;
        cout << "4. Sort Time Duration for a Node" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> menuChoice;

        switch (menuChoice) {
            case 1:
                obj.put();
                obj.get(data);
                break;
            case 2:
                {
                    int watchCountIndex = 1;
                    sort(data.begin(), data.end(), [watchCountIndex](const vector<string>& a, const vector<string>& b) {
                        if (a.size() <= watchCountIndex || b.size() <= watchCountIndex)
                            return false;

                        try {
                            int countA = stoi(a[watchCountIndex]);
                            int countB = stoi(b[watchCountIndex]);
                            return countA > countB;
                        } catch (const exception& e) {
                            return false;
                        }
                    });

                    cout << "Maximum No. of times Lecture Watched by Student:" << endl;
                    for (const vector<string>& row : data) {
                        cout << "Name: " << row[3] << ", \t\t\tWatch Count: ";
                        if (row.size() > watchCountIndex)
                            cout << row[watchCountIndex];
                        else
                            cout << "N/A";
                        cout << endl;
                    }
                }
                break;
            case 3:
                {
                    int timeDurationIndex = 13;
                    sort(data.begin(), data.end(), [timeDurationIndex](const vector<string>& a, const vector<string>& b) {
                        if (a.size() <= timeDurationIndex || b.size() <= timeDurationIndex)
                            return false;

                        try {
                            int durationA = stoi(a[timeDurationIndex]);
                            int durationB = stoi(b[timeDurationIndex]);
                            return durationA > durationB;
                        } catch (const exception& e) {
                            return false;
                        }
                    });

                    cout << "Maximum time Duration of Lecture Watched by Student:" << endl;
                    for (const vector<string>& row : data) {
                        cout << "Name: " << row[3] << ",\t\t\t Time Duration: ";
                        if (row.size() > timeDurationIndex)
                            cout << row[timeDurationIndex];
                        else
                            cout << "N/A";
                        cout << " minutes" << endl;
                    }
                }
                break;
            case 4:
                obj.sortTimeSpent(data);
                break;
            case 5:
                cout << "Exiting the program..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

        cout << endl;
        cout << "Do you want to continue? (yes/no): ";
        cin >> choice;
    } while (choice == "yes" || choice == "Yes");

    return 0;
}
