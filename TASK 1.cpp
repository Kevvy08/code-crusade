#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

// Struct for Student
struct Student {
    int id;
    char name[50];
    float grade;
};

// Global array of students
Student students[100];
int studentCount = 0;

// Function to add a student
void addStudent() {
    cout << "Enter Student ID: ";
    cin >> students[studentCount].id;
    cin.ignore(); // clear newline from input buffer
    cout << "Enter Student Name: ";
    cin.getline(students[studentCount].name, 50);
    cout << "Enter Grade: ";
    cin >> students[studentCount].grade;
    studentCount++;
}

// Function to display all students
void displayStudents() {
    cout << "\n--- Student List ---\n";
    for (int i = 0; i < studentCount; i++) {
        cout << "ID: " << students[i].id
             << ", Name: " << students[i].name
             << ", Grade: " << students[i].grade << endl;
    }
}

// Function to save students to file
void saveToFile() {
    ofstream fout("students.txt", ios::binary);
    if (!fout) {
        cout << "Error saving file.\n";
        return;
    }
    fout.write((char*)students, sizeof(Student) * studentCount);
    fout.close();
    cout << "Records saved successfully.\n";
}

// Function to load students from file
void loadFromFile() {
    ifstream fin("students.txt", ios::binary);
    if (!fin) {
        cout << "No saved records found.\n";
        return;
    }
    fin.read((char*)students, sizeof(students));
    studentCount = fin.gcount() / sizeof(Student);
    fin.close();
    cout << "Records loaded successfully.\n";
}

// Function to delete a student by ID
void deleteStudent() {
    int id;
    cout << "Enter ID to delete: ";
    cin >> id;
    bool found = false;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            found = true;
            // Shift all students after this one
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            cout << "Student deleted.\n";
            break;
        }
    }
    if (!found) {
        cout << "Student not found.\n";
    }
}

int main() {
    loadFromFile();
    int choice;
    do {
        cout << "\n--- Student Management System ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Delete Student\n";
        cout << "4. Save Records\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: deleteStudent(); break;
            case 4: saveToFile(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    saveToFile(); // Save on exit
    return 0;
}

