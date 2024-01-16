# Student Management System

This is a simple student management system implemented in C++. It provides functionalities to add students, edit student information, add courses to students, calculate GPA, and print student information.

## Structures

The program uses two main structures: `Student` and `Course`. The `Student` structure represents a student with fields for name, family name, national code, GPA, course count, and an array of `Course` structures. The `Course` structure represents a course with fields for name, unit, score, and GPA raw score.

## Functions

### 1. Add Student

Allows you to add a new student to the system with the following information:

- Student Name
- Family Name
- National Code

### 2. Edit Student

Enables you to edit existing student information, including:

- Edit student's name
- Edit student's family name
- Add a new course for the student
- Remove a course for the student

### 3. Add Course

Adds a new course for a specific student, including:

- Course Name
- Course Unit
- Course Score

### 4. Remove Course

Removes a course for a specific student by providing the course name.

### 5. Search Student

Searches for a student by their national code and displays their information.

### 6. Display Student List

Displays the list of all students along with their information.

### 7. Generate Report

Generates a report file (`Report.txt`) containing information about all students and their courses.

## Getting Started

1. Clone the repository:

    ```bash
    git clone https://github.com/ehsan-torabi/Manager.git
    cd Manager
    ```

2. Compile and run the program:

    ```bash
    g++ Manager.cpp -o Manager
    ./Manager
    ```

3. Follow the on-screen instructions to use the program.

## File Structure

- `Manager.cpp`: Main source code file containing the student management system implementation.
- `Report.txt`: The output file where student information is saved when generating a report.

## Note

This is a simple student management system and is not intended for use with large amounts of data. For larger data sets, consider using a database or a more efficient data structure.

