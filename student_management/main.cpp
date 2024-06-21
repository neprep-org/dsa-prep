#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// Course class
class Course {
public:
    string courseName;
    Course(string name) : courseName(name) {}
};

// Student class
class Student {
public:
    string name;
    int marks;
    vector<Course> courses;

    Student(string name, int marks) : name(name), marks(marks) {}

    void enrollInCourse(Course course) {
        courses.push_back(course);
    }
};

// Node class for linked list
class Node {
public:
    Student student;
    Node* next;

    Node(Student student) : student(student), next(nullptr) {}
};

// LinkedList class
class LinkedList {
public:
    Node* head;
    LinkedList() : head(nullptr) {}

    void addStudent(Student student) {
        Node* newNode = new Node(student);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void displayStudents() {
        Node* temp = head;
        while (temp) {
            cout << "Name: " << temp->student.name << ", Marks: " << temp->student.marks;
            if (!temp->student.courses.empty()) {
                cout << ", Courses: ";
                for (auto& course : temp->student.courses) {
                    cout << course.courseName << " ";
                }
            }
            cout << endl;
            temp = temp->next;
        }
    }
    void saveToCSV(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            Node* temp = head;
            while (temp) {
                file << temp->student.name << "," << temp->student.marks;
                for (auto& course : temp->student.courses) {
                    file << "," << course.courseName;
                }
                file << endl;
                temp = temp->next;
            }
            file.close();
        } else {
            cout << "Unable to open file";
        }
    }

    Node* searchStudent(string name) {
        Node* temp = head;
        while (temp) {
            if (temp->student.name == name) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    void rankStudents() {
        vector<Student> students;
        Node* temp = head;
        while (temp) {
            students.push_back(temp->student);
            temp = temp->next;
        }

        sort(students.begin(), students.end(), [](Student& a, Student& b) {
            return a.marks > b.marks;
        });

        for (auto& student : students) {
            cout << "Name: " << student.name << ", Marks: " << student.marks << endl;
        }
    }
};

// Predefined courses
vector<Course> predefinedCourses = {
        Course("Math"),
        Course("Physics"),
        Course("Chemistry"),
        Course("Biology"),
        Course("English"),
        Course("History"),
        Course("Geography"),
        Course("Computer Science"),
        Course("Physical Education"),
        Course("Art")
};

bool isCourseAvailable(string courseName) {
    for (auto& course : predefinedCourses) {
        if (course.courseName == courseName) {
            return true;
        }
    }
    return false;
}

void simulateAddingStudents(LinkedList& studentList) {
    // Simulating the addition of predefined students
    Student student1("Alice", 90);
    Student student2("Bob", 85);
    Student student3("Charlie", 95);

    if (isCourseAvailable("Math")) student1.enrollInCourse(Course("Math"));
    if (isCourseAvailable("Physics")) student2.enrollInCourse(Course("Physics"));
    if (isCourseAvailable("Chemistry")) student3.enrollInCourse(Course("Chemistry"));

    studentList.addStudent(student1);
    studentList.addStudent(student2);
    studentList.addStudent(student3);
}

void addNewStudent(LinkedList& studentList) {
    string name;
    int marks;
    int numCourses;
    vector<Course> studentCourses;

    cout << "Enter student name: ";
    cin >> name;
    cout << "Enter student marks: ";
    cin >> marks;

    cout << "Enter number of courses to enroll: ";
    cin >> numCourses;

    for (int i = 0; i < numCourses; i++) {
        string courseName;
        cout << "Enter course name: ";
        cin >> courseName;
        if (isCourseAvailable(courseName)) {
            studentCourses.push_back(Course(courseName));
        } else {
            cout << "Course not available. Please enter a valid course name." << endl;
            i--; // to reattempt the same course input
        }
    }

    Student newStudent(name, marks);
    for (auto& course : studentCourses) {
        newStudent.enrollInCourse(course);
    }
    studentList.addStudent(newStudent);
    studentList.saveToCSV("students.csv");
    cout << "Student added and saved to CSV successfully!" << endl;
}

void menu() {
    LinkedList studentList;
//    simulateAddingStudents(studentList);

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Display Students\n";
        cout << "2. Search for a Student\n";
        cout << "3. Rank Students\n";
        cout << "4. Save Students to CSV\n";
        cout << "5. Add New Student\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                studentList.displayStudents();
                break;
            case 2: {
                string name;
                cout << "Enter student name to search: ";
                cin >> name;
                Node* foundStudent = studentList.searchStudent(name);
                if (foundStudent) {
                    cout << "Found student: " << foundStudent->student.name << ", Marks: " << foundStudent->student.marks << endl;
                } else {
                    cout << "Student not found" << endl;
                }
                break;
            }
            case 3:
                cout << "Ranking students:" << endl;
                studentList.rankStudents();
                break;
            case 4:
                studentList.saveToCSV("students.csv");
                cout << "Students saved to students.csv" << endl;
                break;
            case 5:
                addNewStudent(studentList);
                break;
            case 6:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);
}

int main() {
    menu();
    return 0;
}
