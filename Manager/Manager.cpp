
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


struct course
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
	int gpa;
	int courseCount;
	course courses[5];
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

int gpaCalculator(Student* st)
{
	int unitSum = 0, rawScore = 0;

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
		course temp;
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

void printInfo(Student* st)
{
	cout << "-----------------------------" << endl;
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
	streambuf* coutbuf = cout.rdbuf(); //save old buf
	cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
	getStudentList();
	cout.flush();
	out.flush();
	cout.rdbuf(coutbuf);
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

void menuAddCourse()
{
	string name, nationalCode;
	int unit, score;
	Student* stu;
	cout << "Please enter student nationalCode:" << endl;
	cin >> nationalCode;
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

void menuHandler(int choose)
{
	switch (choose)
	{
	case 1:
		menuAddStudent();
		break;

	case 2:
		menuAddCourse();
		break;
	case 3:

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
		cout << "-----------------------------\n" << endl;
	}
}

