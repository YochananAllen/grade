// grade.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Yochanan Allen
//

// write a program that uses the number of students test scores stored as the first entry in the data file , followed by the students recoreds, and add the student ID 


#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;


struct Student {
    string name;
    int id;
    double* scores;
    double average;
    string grade;
};


int displayFileContents(const string& filename);
Student* getData(ifstream& file, int& studentCnt, int& testsCnt);
int calcAverage(Student students[], int studentCnt, int testsCnt);
string calculateGrade(double average);
int printReport(Student students[], int studentCnt);
int cleanup(Student* students, int studentCnt);

int main() {
    string filename = "studentFile";
    if (displayFileContents(filename) != 0) {
        return 1;
    }

    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "Error opening file." << endl;
        return 1;
    }

    int studentCnt, testsCnt;
    Student* students = getData(inputFile, studentCnt, testsCnt);
    inputFile.close();

    if (!students) {
        cout << "Error reading data." << endl;
        return 1;
    }

    calcAverage(students, studentCnt, testsCnt);
    printReport(students, studentCnt);
    cleanup(students, studentCnt);

    return 0;
}


int displayFileContents(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file for display." << endl;
        return 1;
    }
    cout << "File Contents:\n";
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
    cout << "--------------------------------------\n";
    return 0;
}


Student* getData(ifstream& file, int& studentCnt, int& testsCnt) {
    file >> studentCnt >> testsCnt;
    Student* students = new Student[studentCnt];

    for (int i = 0; i < studentCnt; i++) {
        file >> students[i].name;
        file >> students[i].id;
        students[i].scores = new double[testsCnt];

        for (int j = 0; j < testsCnt; j++) {
            file >> students[i].scores[j];
        }
    }
    return students;
}


int calcAverage(Student students[], int studentCnt, int testsCnt) {
    for (int i = 0; i < studentCnt; i++) {
        double total = 0;
        for (int j = 0; j < testsCnt; j++) {
            total += students[i].scores[j];
        }
        students[i].average = total / testsCnt;
        students[i].grade = calculateGrade(students[i].average);
    }
    return 0;
}


string calculateGrade(double average) {
    if (average >= 90) return "A";
    if (average >= 80) return "B";
    if (average >= 70) return "C";
    if (average >= 60) return "D";
    return "F";
}


int printReport(Student students[], int studentCnt) {
    cout << "Student        ID        Score     Grade" << endl;
    cout << "----------------------------------------" << endl;
    for (int i = 0; i < studentCnt; i++) {
        cout << left << setw(15) << students[i].name
            << setw(10) << students[i].id
            << setw(10) << fixed << setprecision(1) << students[i].average
            << setw(10) << students[i].grade << endl;
    }
    return 0;
}


int cleanup(Student* students, int studentCnt) {
    for (int i = 0; i < studentCnt; i++) {
        delete[] students[i].scores;
    }
    delete[] students;
    return 0;
}










// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
