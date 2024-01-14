
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;


struct Course
{
	string name;
	int unit;
	int score;
	int gpaScore;
};

struct Student
{
	string name;
	string family;
	string nationalCode;
	float gpa;
	int courseCount;
	Course courses[5];
};

struct Manage
{
	int studentCount;
	Student list[20];

}Manager;


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

float gpaCalculator(Student* st)
{
	float unitSum = 0, rawScore = 0;

	for (int i = 0; i < st->courseCount; i++)
	{
		if (st->courses[i].name != "")
		{
			unitSum += st->courses[i].unit;
			rawScore += st->courses[i].gpaScore;
		}
	}
	return rawScore / unitSum;
	return 0;
}

bool addCourse(string nationalCode, string name, int unit, int score)
{
	Student* st = search(nationalCode);
	if (st != nullptr)
	{
		Course temp;
		temp.name = name;
		temp.unit = unit;
		temp.score = score;
		temp.gpaScore = unit * score;
		st->courses[st->courseCount++] = temp;
		st->gpa = gpaCalculator(st);
		return true;
	}
	return false;
}

bool removeCourse(Student* stu, string courseName)
{
	for (int i = 0; i < stu->courseCount; i++)
	{
		if (courseName.compare(stu->courses[i].name) == 0)
		{
			Course temp;
			stu->courses[i] = temp;
			stu->courseCount--;
			stu->gpa = gpaCalculator(stu);
			return true;
		}
	}
	return false;

}

void printInfo(Student* st)
{
	cout << "Student info:" << endl;
	cout << "\tName : " << st->name << "\tFamily : " << st->family << "\t National Code : " << st->nationalCode << endl;
	cout << "Course info:" << endl;
	if (st->courseCount != 0)
	{
		for (int i = 0; i < st->courseCount; i++)
		{
			if (st->courses[i].name != "")
			{
				cout << "\tCourse : " << st->courses[i].name << "\tUnit: " << st->courses[i].unit << "\t Score : " << st->courses[i].score << endl;
			}
		}
		cout << "Student GPA:" << st->gpa << endl;
	}
	else
	{
		cout << "Not found any Courses. Please first add a course" << endl;
	}
	cout << "\n----------------------------------------------" << endl;
}

void getStudentList()
{
	if (Manager.studentCount == 0)
	{
		cout << "Not found any students. Please first add a student" << endl;
		return;
	}
	for (int i = 0; i < Manager.studentCount; i++)
	{
		printInfo(search(Manager.list[i].nationalCode));
		cout << "\n";
	}
}

void getReportFile()
{
	if (Manager.studentCount == 0)
	{
		cout << "Not found any students. please first add a student" << endl;
		return;
	}
	ofstream out("Report.txt");
	streambuf* coutBuf = cout.rdbuf(); //save old buf
	cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
	getStudentList();
	cout.flush();
	out.flush();
	cout.rdbuf(coutBuf);
	out.close();
	cout << "Student info saved in Report.txt" << endl;
}


void menuAddStudent()
{
	string name, family, nationalCode;
	cout << "Please enter student name:" << endl;
	cin >> name;
	cout << "Please enter student family:" << endl;
	cin >> family;
	cout << "Please enter student nationalCode:" << endl;
	cin >> nationalCode;
	if (addStudent(name, family, nationalCode))
	{
		cout << "-------------- Student added successful ---------------\n" << endl;
	}
	else
	{
		cout << "-------------- National code is exist!!---------------\n" << endl;
	}
}

void menuAddCourse(string nationalCode)
{
	string name;
	int unit, score;
	Student* stu;
	stu = search(nationalCode);
	if (stu != nullptr)
	{
		cout << "Please enter Course name:" << endl;
		cin >> name;
		cout << "Please enter Course unit:" << endl;
		cin >> unit;
		cout << "Please enter Course score:" << endl;
		cin >> score;
		if (addCourse(nationalCode, name, unit, score))
		{
			cout << "-------------- Course added successful ---------------\n" << endl;
		}
		else
		{
			cout << "-------------- Course not added! ---------------\n" << endl;
		}
	}
	else
		cout << "-------------- Not found this Student!!! ---------------\n" << endl;

}

void editStudent(Student* stu, int choose)
{
	if (choose != 0)
	{
		string name, family;
		switch (choose)
		{
		case 1:
			cout << "Please enter new student name:" << endl;
			cin >> name;
			stu->name = name;
			break;

		case 2:
			cout << "Please enter new student family:" << endl;
			cin >> family;
			stu->family = family;
			break;
		case 3:
			menuAddCourse(stu->nationalCode);
			break;
		case 4:
			cout << "Please enter course name:" << endl;
			cin >> name;
			if (removeCourse(stu, name))
			{
				cout << "-------------- Course removed successful ---------------\n" << endl;
			}
			else
			{
				cout << "-------------- Course not found!! ---------------\n" << endl;
			}
			break;
		default:
			cout << "-------------- Please enter valid number!! ---------------\n" << endl;
			break;
		}
	}
	else
	{
		return;
	}


}

void menuSearch()
{
	string nationalCode;
	Student* stu;
	cout << "Please enter student nationalCode:" << endl;
	cin >> nationalCode;
	stu = search(nationalCode);
	if (stu != nullptr)
	{
		printInfo(stu);
	}
	else
		cout << "-------------- Not found this Student!!! ---------------\n" << endl;
}

void menuEditStudent()
{
	string nationalCode;
	Student* stu;

	cout << "Please enter student nationalCode:" << endl;
	cin >> nationalCode;
	stu = search(nationalCode);
	if (stu != nullptr)
	{
		printInfo(stu);
		int choose = 100;
		while (choose != 0) {
			cout << "Please enter number of that property you want to edit: " << endl;
			cout << "\t 1 - Edit name" << endl;
			cout << "\t 2 - Edit family" << endl;
			cout << "\t 3 - Add course" << endl;
			cout << "\t 4 - Remove course" << endl;
			cout << "\t 5 - Edit course" << endl;
			cout << "\t 0 - Back" << endl;
			cin >> choose;
			editStudent(stu, choose);
		}

	}
	else
		cout << "-------------- Not found this Student!!! ---------------\n" << endl;
}


void menuHandler(int choose)
{
	string nationalCode;
	system("cls");
	switch (choose)
	{
	case 1:
		menuAddStudent();
		break;
	case 2:
		menuEditStudent();
		break;
	case 3:
		cout << "Please enter student nationalCode:" << endl;
		cin >> nationalCode;
		menuAddCourse(nationalCode);
		break;
	case 4:
		menuSearch();
		break;
	case 5:
		getStudentList();
		break;
	case 6:
		getReportFile();
		break;
	case 0:
		exit(0);
		break;
	default:
		cout << "-------------- Please enter valid number!! ---------------\n" << endl;
		break;
	}
}

int main()
{
	int choose;
	while (true) {
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
		menuHandler(choose);
	}
}

