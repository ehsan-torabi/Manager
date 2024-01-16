#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_STUDENTS = 20;
const int MAX_COURSES = 5;

// Structures for Course, Student, and Manage
struct Course {
    string name;
    int unit = 0;
    float score = 0;
    float gpaRawScore = 0;
};

struct Student {
    string name;
    string family;
    string nationalCode;
    float gpa = 0;
    int courseCount = 0;
    Course courses[MAX_COURSES];
};

struct Manage {
    int studentCount = 0;
    Student list[MAX_STUDENTS];
} Manager;


// Function to clear the console screen
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


// Function to search for a student by national code
Student* searchStudentByNationalCode(const string& nationalCode) {
    for (int i = 0; i < MAX_STUDENTS; i++) {
        if (nationalCode == Manager.list[i].nationalCode) {
            return &Manager.list[i];
        }
    }
    return nullptr;
}

// Function to search for a course by name in a student's courses
Course* searchCourseByCourseName(Student* student, const string& courseName) {
    for (int i = 0; i < student->courseCount; i++) {
        if (courseName == student->courses[i].name) {
            return &student->courses[i];
        }
    }
    return nullptr;
}

// Function to add a student
bool addStudent(const string& name, const string& family, const string& nationalCode) {
    if (searchStudentByNationalCode(nationalCode) == nullptr) {
        Student temp;
        temp.name = name;
        temp.family = family;
        temp.nationalCode = nationalCode;
        Manager.list[Manager.studentCount++] = temp;
        return true;
    }
    return false;
}

// Function to calculate GPA for a student
float calculateGPA(Student* student) {
    float unitSum = 0, rawScore = 0;

    for (int i = 0; i < student->courseCount; i++) {
        if (!student->courses[i].name.empty()) {
            unitSum += student->courses[i].unit;
            rawScore += student->courses[i].gpaRawScore;
        }
    }
    return (unitSum == 0) ? 0 : rawScore / unitSum;
}

// Function to add a course for a student
bool addCourse(const string& nationalCode, const string& name, int unit, float score) {
    Student* student = searchStudentByNationalCode(nationalCode);
    if (student != nullptr) {
        if (searchCourseByCourseName(student, name) == nullptr) {
            Course temp;
            temp.name = name;
            temp.unit = unit;
            temp.score = score;
            temp.gpaRawScore = score * unit;
            student->courses[student->courseCount++] = temp;
            student->gpa = calculateGPA(student);
            return true;
        }
    }
    return false;
}

// Function to remove a course for a student
bool removeCourse(Student* student, const string& courseName) {
    int answer = 0;
    for (int i = 0; i < student->courseCount; i++) {
        if (courseName == student->courses[i].name) {
            clearScreen();
            cout << "Are you sure to remove " << courseName << "?" << endl;
            cout << "\t 1 - No " << endl;
            cout << "\t 2 - Yes " << endl;
            cin >> answer;
            if (answer == 2) {
                Course temp;
                student->courses[i] = temp;
                student->courseCount--;
                student->gpa = calculateGPA(student);
                return true;
            }
            else {
                return false;
            }
        }
    }
    return false;
}

// Function to print student information
void printStudentInfo(Student* student) {
    clearScreen();
    cout << "Student info:" << endl;
    cout << "\tName : " << student->name << "\tFamily : " << student->family;
    cout << "\tNational Code : " << student->nationalCode << endl;
    cout << "Course info:" << endl;
    if (student->courseCount != 0) {
        for (int i = 0; i < student->courseCount; i++) {
            if (!student->courses[i].name.empty()) {
                cout << "\tCourse : " << student->courses[i].name << "\tUnit: " << student->courses[i].unit;
                cout << "\t Score : " << student->courses[i].score << endl;
            }
        }
        cout << "Student GPA:" << student->gpa << endl;
    }
    else {
        cout << "\nNot found any Courses. Please first add a course" << endl;
    }
    cout << "\n----------------------------------------------" << endl;
}

// Function to display the list of students
void displayStudentList() {
    clearScreen();
    cout << "Student list:\n" << endl;
    if (Manager.studentCount == 0) {
        cout << "Not found any students. Please first add a student" << endl;
        return;
    }
    for (int i = 0; i < Manager.studentCount; i++) {
        printStudentInfo(searchStudentByNationalCode(Manager.list[i].nationalCode));
        cout << "\n";
    }
}

// Function to generate a report file
void generateReportFile() {
    if (Manager.studentCount == 0) {
        cout << "Not found any students. Please first add a student" << endl;
        return;
    }

    ofstream outFile("Report.txt");
    if (!outFile.is_open()) {
        cout << "Error: Unable to open the output file." << endl;
        return;
    }

    for (int i = 0; i < Manager.studentCount; i++) {
        Student* student = &Manager.list[i];
        outFile << "Student info:" << endl;
        outFile << "\tName : " << student->name << "\tFamily : " << student->family;
        outFile << "\tNational Code : " << student->nationalCode << endl;
        outFile << "Course info:" << endl;

        if (student->courseCount != 0) {
            for (int j = 0; j < student->courseCount; j++) {
                if (!student->courses[j].name.empty()) {
                    outFile << "\tCourse : " << student->courses[j].name << "\tUnit: " << student->courses[j].unit;
                    outFile << "\t Score : " << student->courses[j].score << endl;
                }
            }
            outFile << "Student GPA:" << student->gpa << endl;
        }
        else {
            outFile << "\nNot found any Courses. Please first add a course" << endl;
        }

        outFile << "\n----------------------------------------------" << endl;
    }

    outFile.close();
    cout << "\nStudent info saved in Report.txt" << endl;
}

// Function to add a student
void menuAddStudent() {
    string name, family, nationalCode;
    cout << "Please enter student name:" << endl;
    cin >> name;
    cout << "Please enter student family:" << endl;
    cin >> family;
    cout << "Please enter student nationalCode:" << endl;
    cin >> nationalCode;

    if (addStudent(name, family, nationalCode)) {
        cout << "-------------- Student added successful ---------------\n" << endl;
    }
    else {
        cout << "-------------- National code is exist!!---------------\n" << endl;
    }
}

// Function to add a course
void menuAddCourse(const string& nationalCode) {
    Student* student = searchStudentByNationalCode(nationalCode);
    if (student != nullptr) {
        string name;
        int unit, score;

        cout << "Please enter Course name:" << endl;
        cin >> name;
        cout << "Please enter Course unit:" << endl;
        cin >> unit;
        cout << "Please enter Course score:" << endl;
        cin >> score;

        if (addCourse(nationalCode, name, unit, score)) {
            cout << "\n-------------- Course added successful ---------------\n" << endl;
        }
        else {
            cout << "\n-------------- Course not added! This course is exist!! ---------------\n" << endl;
        }
    }
    else {
        cout << "-------------- Not found this Student!!! ---------------\n" << endl;
    }
}

// Function to edit a student
void editStudent(Student* student, int choice) {
    if (choice != 0) {
        string name, family, temp;

        switch (choice) {
        case 1:
            cout << "Please enter new student name:" << endl;
            temp = student->name;
            cin >> name;
            student->name = name;
            cout << "\tName changed successful from " << temp << " to " << name << "\n" << endl;
            break;
        case 2:
            cout << "Please enter new student family:" << endl;
            temp = student->family;
            cin >> family;
            student->family = family;
            cout << "\tFamily changed successful from " << temp << " to " << family << "\n" << endl;
            break;
        case 3:
            menuAddCourse(student->nationalCode);
            break;
        case 4:
            cout << "Please enter course name:" << endl;
            cin >> name;
            if (removeCourse(student, name)) {
                cout << "\n-------------- Course removed successful ---------------\n" << endl;
            }
            else {
                cout << "\n-------------- Course not removed ---------------\n" << endl;
            }
            break;
        default:
            cout << "\n-------------- Please enter valid number!! ---------------\n" << endl;
            break;
        }
    }
    clearScreen();
}

// Function to edit a student
void menuEditStudent() {
    string nationalCode;
    displayStudentList();
    cout << "Please enter student nationalCode:" << endl;
    cin >> nationalCode;
    Student* student = searchStudentByNationalCode(nationalCode);
    if (student != nullptr) {
        clearScreen();
        int choice = 100;
        while (choice != 0) {
            printStudentInfo(student);
            cout << "Please enter number of that property you want to edit: " << endl;
            cout << "\t 1 - Edit name" << endl;
            cout << "\t 2 - Edit family" << endl;
            cout << "\t 3 - Add course" << endl;
            cout << "\t 4 - Remove course" << endl;
            cout << "\t 0 - Back" << endl;
            cin >> choice;
            editStudent(student, choice);
        }
        clearScreen();
    }
    else {
        cout << "-------------- Not found this Student!!! ---------------\n" << endl;
    }
}

// Function to search for a student
void menuSearch() {
    string nationalCode;
    cout << "Please enter student nationalCode:" << endl;
    cin >> nationalCode;
    Student* student = searchStudentByNationalCode(nationalCode);
    if (student != nullptr) {
        printStudentInfo(student);
    }
    else {
        cout << "\n-------------- Not found this Student!!! ---------------\n" << endl;
    }
}

// Function to handle the menu options
void menuHandler(int choice) {
    string nationalCode;
    int back = -1;
    clearScreen();
    switch (choice) {
    case 1:
        menuAddStudent();
        break;
    case 2:
        menuEditStudent();
        break;
    case 3:
        displayStudentList();
        cout << "Please enter student nationalCode:" << endl;
        cin >> nationalCode;
        menuAddCourse(nationalCode);
        break;
    case 4:
        while (back == -1) {
            menuSearch();
            cout << "\t 0 - Back" << endl;
            cin >> back;
        }
        clearScreen();
        break;
    case 5:
        while (back == -1) {
            displayStudentList();
            cout << "\t 0 - Back" << endl;
            cin >> back;
        }
        clearScreen();
        break;
    case 6:
        generateReportFile();
        break;
    case 0:
        exit(0);
        break;
    default:
        cout << "-------------- Please enter valid number!! ---------------\n" << endl;
        break;
    }
}



// Main function
int main() {
    int choice;
    while (true) {
        cout << "Please enter number of option:" << endl;
        cout << "\t 1 - Add student" << endl;
        cout << "\t 2 - Edit student" << endl;
        cout << "\t 3 - Add course" << endl;
        cout << "\t 4 - Search" << endl;
        cout << "\t 5 - Student List" << endl;
        cout << "\t 6 - Save info" << endl;
        cout << "\t 0 - Exit" << endl;
        cin >> choice;
        cout << "-----------------------------\n" << endl;
        clearScreen(); // Clear the console
        menuHandler(choice);
    }
}
