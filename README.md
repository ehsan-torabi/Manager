# Student Management System

This is a simple student management system implemented in C++. It provides functionalities to add students, edit student information, add courses to students, calculate GPA, and print student information.

## Structures

The program uses two main structures: `Student` and `Course`. The `Student` structure represents a student with fields for name, family name, national code, GPA, course count, and an array of `Course` structures. The `Course` structure represents a course with fields for name, unit, score, and GPA raw score.

## Functions

The program includes several functions to manage students and courses:

- `addStudent`: Adds a new student.
- `addCourse`: Adds a new course to a student.
- `search`: Searches for a student by their national code.
- `searchCourse`: Searches for a course by its name.
- `removeCourse`: Removes a course from a student's list of courses.
- `gpaCalculator`: Calculates the GPA of a student.
- `printInfo`: Prints the information of a student.
- `getStudentList`: Prints the information of all students.
- `getReportFile`: Generates a report file with the information of all students.

## How to Run

To run the program, compile the C++ file and run the resulting executable. The program will display a menu with options to add a student, edit a student, add a course, search for a student, display the list of students, save the student info to a file, or exit the program.

## Note

This is a simple student management system and is not intended for use with large amounts of data. For larger data sets, consider using a database or a more efficient data structure.

