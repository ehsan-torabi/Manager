#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Define a structure for Course
struct Course
{
	string name; // Name of the course
	int unit = 0; // Number of units in the course
	float score = 0; // Score of the course
	float gpaRawScore = 0; // Raw score for GPA calculation
};

// Define a structure for Student
struct Student
{
	string name; // Name of the student
	string family; // Family name of the student
	string nationalCode; // National code of the student
	float gpa = 0; // GPA of the student
	int courseCount = 0; // Number of courses the student is taking
	Course courses[5]; // Array of courses the student is taking
};

// Define a structure for Manage
struct Manage
{
	int studentCount = 0; // Number of students
	Student list[20]; // List of students

}Manager; // Manager object of Manage structure

// Function to search a student by national code
Student* search(string nationalCode)
{
	for (int i = 0; i < 20; i++)
	{
		if (nationalCode.compare(Manager.list[i].nationalCode) == 0)
		{
			return &Manager.list[i];
		}
	}
	return nullptr;
}

// Function to search a course by course name
Course* searchCourse(Student* stu, string courseName)
{
	for (int i = 0; i < stu->courseCount; i++)
	{
		if (courseName.compare(stu->courses[i].name) == 0)
		{
			return &stu->courses[i];
		}
	}
	return nullptr;
}

// Function to add a student
bool addStudent(string name, string family, string nationalCode)
{
	if (search(nationalCode) == nullptr)
	{
		Student temp;
		temp.name = name;
		temp.family = family;
		temp.nationalCode = nationalCode;
		temp.gpa = 0;
		temp.courseCount = 0;
		Manager.list[Manager.studentCount++] = temp;
		return true;
	}
	return false;
}

// Function to calculate GPA
float gpaCalculator(Student* st)
{
	float unitSum = 0, rawScore = 0;

	for (int i = 0; i < st->courseCount; i++)
	{
		if (st->courses[i].name != "")
		{
			unitSum += st->courses[i].unit;
			rawScore += st->courses[i].gpaRawScore;
		}
	}
	return rawScore / unitSum;
	return 0;
}

// Function to add a course
bool addCourse(string nationalCode, string name, int unit, float score)
{
	Student* st = search(nationalCode);
	if (st != nullptr)
	{
		if (searchCourse(st, name) == nullptr)
		{
			Course temp;
			temp.name = name;
			temp.unit = unit;
			temp.score = score;
			temp.gpaRawScore = score * unit;
			st->courses[st->courseCount++] = temp;
			st->gpa = gpaCalculator(st);
			return true;
		}
	}
	return false;
}

// Function to remove a course
bool removeCourse(Student* stu, string courseName)
{
	int answer = 0;
	for (int i = 0; i < stu->courseCount; i++)
	{
		if (courseName.compare(stu->courses[i].name) == 0)
		{
			cout << "Are you sure to remove " << courseName << "?" << endl;
			cout << "\t 1 - No " << endl;
			cout << "\t 2 - Yes " << endl;
			cin >> answer;
			if (answer == 2)
			{
				Course temp;
				stu->courses[i] = temp;
				stu->courseCount--;
				stu->gpa = gpaCalculator(stu);
				return true;
			}
			else
			{
				return false;
			}

		}
	}
	return false;

}

// Function to print student information
void printInfo(Student* st)
{
	cout << "Student info:" << endl;
	cout << "\tName : " << st->name << "\tFamily : " << st->family;
	cout << "\tNational Code : " << st->nationalCode << endl;
	cout << "Course info:" << endl;
	if (st->courseCount != 0)
	{
		for (int i = 0; i < st->courseCount; i++)
		{
			if (st->courses[i].name != "")
			{
				cout << "\tCourse : " << st->courses[i].name << "\tUnit: " << st->courses[i].unit;
				cout << "\t Score : " << st->courses[i].score << endl;
			}
		}
		cout << "Student GPA:" << st->gpa << endl;
	}
	else
	{
		cout << "\nNot found any Courses. Please first add a course" << endl;
	}
	cout << "\n----------------------------------------------" << endl;
}

// Function to get the list of students
void getStudentList()
{
	cout << "Student list:\n" << endl;
	if (Manager.studentCount == 0)
	{
		system("cls");
		cout << "Not found any students. Please first add a student" << endl;
		return;
	}
	for (int i = 0; i < Manager.studentCount; i++)
	{
		printInfo(search(Manager.list[i].nationalCode));
		cout << "\n";
	}
}

// Function to generate a report file
void getReportFile()
{
	// Check if there are any students
	if (Manager.studentCount == 0)
	{
		system("cls");
		cout << "Not found any students. please first add a student" << endl;
		return;
	}
	// Create an output file stream
	ofstream out("Report.txt");
	// Save the old buffer
	streambuf* coutBuf = cout.rdbuf();
	// Redirect std::cout to out.txt
	cout.rdbuf(out.rdbuf());
	// Get the list of students
	getStudentList();
	// Flush the output
	cout.flush();
	out.flush();
	// Restore the old buffer
	cout.rdbuf(coutBuf);
	// Close the output file
	out.close();
	// Print a message indicating that the student info has been saved
	system("cls");
	cout << "\nStudent info saved in Report.txt" << endl;
}

// Function to add a student
void menuAddStudent()
{
	string name, family, nationalCode;
	// Get the student's information from the user
	cout << "Please enter student name:" << endl;
	cin >> name;
	cout << "Please enter student family:" << endl;
	cin >> family;
	cout << "Please enter student nationalCode:" << endl;
	cin >> nationalCode;
	// Add the student
	if (addStudent(name, family, nationalCode))
	{
		system("cls");
		cout << "-------------- Student added successful ---------------\n" << endl;
	}
	else
	{
		system("cls");
		cout << "-------------- National code is exist!!---------------\n" << endl;
	}
}

// Function to add a course
void menuAddCourse(string nationalCode)
{
	string name;
	int unit, score;
	// Search for the student
	Student* stu;
	stu = search(nationalCode);
	if (stu != nullptr)
	{
		// Get the course information from the user
		cout << "Please enter Course name:" << endl;
		cin >> name;
		cout << "Please enter Course unit:" << endl;
		cin >> unit;
		cout << "Please enter Course score:" << endl;
		cin >> score;
		// Add the course
		if (addCourse(nationalCode, name, unit, score))
		{
			system("cls");
			cout << "\n-------------- Course added successful ---------------\n" << endl;
		}
		else
		{
			system("cls");
			cout << "\n-------------- Course not added! This course is exist!! ---------------\n" << endl;
		}
	}
	else {
		system("cls");
		cout << "-------------- Not found this Student!!! ---------------\n" << endl;
	}

}

// Function to edit a student
void editStudent(Student* stu, int choose)
{
	if (choose != 0)
	{
		string name, family, temp;
		// Choose the property to edit
		switch (choose)
		{
		case 1:
			// Edit the student's name
			system("cls");
			cout << "Please enter new student name:" << endl;
			temp = stu->name;
			cin >> name;
			stu->name = name;
			system("cls");
			cout << "\tName changed successful from " << temp << " to " << name << "\n" << endl;
			break;

		case 2:
			// Edit the student's family
			system("cls");
			cout << "Please enter new student family:" << endl;
			temp = stu->family;
			cin >> family;
			stu->family = family;
			system("cls");
			cout << "\tFamily changed successful from " << temp << " to " << family << "\n" << endl;

			break;
		case 3:
			// Add a course
			system("cls");
			menuAddCourse(stu->nationalCode);
			break;
		case 4:
			// Remove a course
			cout << "Please enter course name:" << endl;
			cin >> name;
			if (removeCourse(stu, name))
			{
				system("cls");
				cout << "\n-------------- Course removed successful ---------------\n" << endl;
			}
			else
			{
				system("cls");
				cout << "\n-------------- Course not removed ---------------\n" << endl;
			}
			break;
		default:
			cout << "\n-------------- Please enter valid number!! ---------------\n" << endl;
			break;
		}
	}
	else
	{
		return;
	}


}

// Function to edit a student
void menuEditStudent()
{
	string nationalCode;
	// Get the list of students
	getStudentList();
	// Get the national code from the user
	cout << "Please enter student nationalCode:" << endl;
	cin >> nationalCode;
	// Search for the student
	Student* stu = search(nationalCode);
	if (stu != nullptr)
	{
		system("cls");
		int choose = 100;
		while (choose != 0) {
			// Print the student's information
			printInfo(stu);
			cout << "Please enter number of that property you want to edit: " << endl;
			cout << "\t 1 - Edit name" << endl;
			cout << "\t 2 - Edit family" << endl;
			cout << "\t 3 - Add course" << endl;
			cout << "\t 4 - Remove course" << endl;
			cout << "\t 0 - Back" << endl;
			cin >> choose;
			// Edit the student
			editStudent(stu, choose);
		}
		system("cls");

	}
	else
	{
		system("cls");
		cout << "-------------- Not found this Student!!! ---------------\n" << endl;
	}
}

// Function to search for a student
void menuSearch()
{
	string nationalCode;
	// Get the national code from the user
	cout << "Please enter student nationalCode:" << endl;
	cin >> nationalCode;
	// Search for the student
	Student* stu = search(nationalCode);
	if (stu != nullptr)
	{
		// Print the student's information
		printInfo(stu);
	}
	else {
		system("cls");
		cout << "\n-------------- Not found this Student!!! ---------------\n" << endl;
	}
}

// Function to handle the menu options
void menuHandler(int choose)
{
	string nationalCode;
	int back = -1;
	system("cls"); // Clear the console
	switch (choose)
	{
	case 1:
		// Add a student
		menuAddStudent();
		break;
	case 2:
		// Edit a student
		menuEditStudent();
		break;
	case 3:
		// Add a course
		getStudentList();
		cout << "Please enter student nationalCode:" << endl;
		cin >> nationalCode;
		menuAddCourse(nationalCode);
		break;
	case 4:
		// Search for a student
		while (back == -1)
		{
			menuSearch();
			cout << "\t 0 - back" << endl;
			cin >> back;
		}
		system("cls"); // Clear the console
		break;
	case 5:
		// Display the list of students
		while (back == -1)
		{
			getStudentList();
			cout << "\t 0 - back" << endl;
			cin >> back;
		}
		system("cls"); // Clear the console
		break;
	case 6:
		// Save the student info to a file
		getReportFile();
		break;
	case 0:
		// Exit the program
		exit(0);
		break;
	default:
		// Invalid option
		system("cls");
		cout << "-------------- Please enter valid number!! ---------------\n" << endl;
		break;
	}
}

// Main function
int main()
{
	int choose;
	while (true) {
		// Display the menu options
		cout << "Please enter number of option:" << endl;
		cout << "\t 1 - Add student" << endl;
		cout << "\t 2 - Edit student" << endl;
		cout << "\t 3 - Add course" << endl;
		cout << "\t 4 - Search" << endl;
		cout << "\t 5 - Student List" << endl;
		cout << "\t 6 - Save info" << endl;
		cout << "\t 0 - Exit" << endl;
		cin >> choose;
		cout << "-----------------------------\n" << endl;
		system("cls"); // Clear the console
		// Handle the chosen menu option
		menuHandler(choose);
	}
}

