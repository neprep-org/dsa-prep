#include <iostream>
#include "fstream"
#include "sstream"
#include "vector"
#include "algorithm"

#define FILE_NAME "students.txt"

using namespace std;

class Student
{
private:
    int id;
    string first_name;
    string last_name;
    float marks;

public:
    Student(int id, string first_name, string last_name, float marks) : id(id), first_name(first_name),
                                                                        last_name(last_name), marks(marks){};

    int getId() { return id; }

    string getFirstName() { return first_name; }

    string getLastName() { return last_name; }

    string getFullName() { return first_name + " " + last_name; }

    float getMarks() { return marks; }
};

// used for sorting students by marks
bool comparaByMarks(Student a, Student b)
{
    return a.getMarks() > b.getMarks();
}

void printStudents(vector<Student> students)
{
    cout << "Students" << endl;
    cout << "---------------------" << endl;
    for (int i = 0; i < students.size(); i++)
    {
        cout << "(" << i + 1 << ") : " << students[i].getId() << " " << students[i].getFullName() << " "
             << students[i].getMarks() << endl;
    }
    cout << "---------------------" << endl;
}

// save a student to file
void saveStudent(Student student)
{
    ofstream file(FILE_NAME, ios::app); // open file in append mode

    if (file.is_open())
    {
        file << student.getId() << " " << student.getFirstName() << " " << student.getLastName() << " "
             << student.getMarks() << endl;
        cout << "Student " << student.getFullName() << " saved successfully!" << endl;
    }
    else
    {
        cerr << "Failed to open file  " << FILE_NAME << endl;
    }
}

// list all students in the file
void listStudents()
{
    ifstream file(FILE_NAME);
    vector<Student> students;
    string line, id, first_name, last_name, marks;
    if (file.is_open())
    {

        // get all students and push them in students vector
        while (getline(file, line))
        {
            istringstream ss(line);
            if (ss >> id >> first_name >> last_name >> marks)
            {
                auto *student = new Student(stoi(id), first_name, last_name, stof(marks));
                students.push_back(*student);
                delete student; // free memory allocated to student as its no longer in use
            }
            else
            {
                cerr << "Invalid record : " << line << endl;
            }
        }

        // sort students by marks
        sort(students.begin(), students.end(), comparaByMarks);

        // print students
        cout << "The first student is : " << students[0].getFullName() << " with " << students[0].getMarks() << " Marks"
             << endl;
        printStudents(students);
    }
    else
    {
        cerr << "Failed to open file  " << FILE_NAME << " check if it exists and try again " << endl;
    }
}

// convert a string to lowercase
string convertToLowerCase(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        str[i] = tolower(str[i]);
    }
    return str;
}

int main()
{
    string user_input, command;
    while (true)
    {
        cout << "Enter command (type help to see available commands) " << endl;
        getline(cin, user_input);
        istringstream ss(user_input);
        ss >> command;
        command = convertToLowerCase(command);
        if (command == "liststudents")
        {
            listStudents();
        }
        else if (command == "addstudents")
        {
            // get number of students the user wants to add
            int number_of_students;
            cout << "How many students do you want to add?" << endl;
            cin >> number_of_students;
            cin.ignore(); // ignore the newline character left in the buffer

            cout << "Enter students data in format : <id> <first_name> <last_name> <marks>" << endl;

            // get students data
            for (int i = 0; i < number_of_students; i++)
            {
                string input, id, first_name, last_name, marks;
                cout << "Enter the data for student (" << i + 1 << ")" << endl;
                getline(cin, input);
                istringstream student_ss(input);
                if (student_ss >> id >> first_name >> last_name >> marks)
                {
                    auto *student = new Student(stoi(id), first_name, last_name, stof(marks));
                    saveStudent(*student);
                }
                else
                {
                    cerr << "Invalid input format" << endl;
                }
            }

            cout << "Finished adding students" << endl;
        }
        else if (command == "exit")
        {
            cout << "Exiting the program..." << endl;
            exit(0);
        }
        else if (command == "help")
        {
            cout << "available commands " << endl;
            cout << "----------------------------" << endl;
            cout << "\t liststudents \n \t addstudents" << endl;
            cout << "----------------------------" << endl;
        }
        else
        {
            cout << "Invalid command" << endl;
        }
    }
}