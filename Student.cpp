#include <iostream>
#include <fstream>
using namespace std;

class Student {
public:
    int id;
    char name[50];
    float marks;

    void input() {
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() {
        cout << "ID: " << id << " | Name: " << name << " | Marks: " << marks << endl;
    }
};

// Add Student
void addStudent() {
    Student s;
    ofstream file("students.dat", ios::binary | ios::app);

    s.input();
    file.write((char*)&s, sizeof(s));

    file.close();
    cout << "Student Added!\n";
}

// Display All
void displayStudents() {
    Student s;
    ifstream file("students.dat", ios::binary);

    while(file.read((char*)&s, sizeof(s))) {
        s.display();
    }

    file.close();
}

// Search Student
void searchStudent() {
    Student s;
    int id, found = 0;

    cout << "Enter ID to search: ";
    cin >> id;

    ifstream file("students.dat", ios::binary);

    while(file.read((char*)&s, sizeof(s))) {
        if(s.id == id) {
            s.display();
            found = 1;
        }
    }

    if(!found) cout << "Student not found\n";

    file.close();
}

// Delete Student
void deleteStudent() {
    Student s;
    int id;

    cout << "Enter ID to delete: ";
    cin >> id;

    ifstream file("students.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    while(file.read((char*)&s, sizeof(s))) {
        if(s.id != id) {
            temp.write((char*)&s, sizeof(s));
        }
    }

    file.close();
    temp.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    cout << "Student Deleted!\n";
}

// Update Student
void updateStudent() {
    Student s;
    int id, found = 0;

    cout << "Enter ID to update: ";
    cin >> id;

    fstream file("students.dat", ios::binary | ios::in | ios::out);

    while(file.read((char*)&s, sizeof(s))) {
        if(s.id == id) {
            cout << "Enter new details:\n";
            s.input();

            file.seekp(-sizeof(s), ios::cur);
            file.write((char*)&s, sizeof(s));

            found = 1;
        }
    }

    if(!found) cout << "Student not found\n";

    file.close();
}

// Main Menu
int main() {
    int choice;

    do {
        cout << "\n1. Add Student";
        cout << "\n2. Display";
        cout << "\n3. Search";
        cout << "\n4. Update";
        cout << "\n5. Delete";
        cout << "\n6. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
        }

    } while(choice != 6);

    return 0;
}
