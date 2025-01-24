// grade.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Yochanan Allen

//Write the program so that the
//data is stored in partially filled arrays and the actual number of students represented in the file is
//counted as the file is read.The number of test scores on the file should be stored as a global
//constant.


#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;


const string fileName = "studentFile"; 
const int NUM_TEST = 5; 
const int MAX_STUDENTS = 20; 


int getStudentData(ifstream& infile, string names[], double scores[][NUM_TEST]);
int calculateAverages(double scores[][NUM_TEST], double averages[], int numStudents);
string calculateGrade(double average);
int printReport(string names[], double averages[], int numStudents);

int main() {
    ifstream inputfile;
    string names[MAX_STUDENTS];
    double testScores[MAX_STUDENTS][NUM_TEST];
    double averages[MAX_STUDENTS];
    int numStudents;

    
    inputfile.open(fileName);
    if (!inputfile.is_open()) {
        cout << "File did not open." << endl;
        return 1;
    }


    numStudents = getStudentData(inputfile, names, testScores);

    
    calculateAverages(testScores, averages, numStudents);

    
    printReport(names, averages, numStudents);

    inputfile.close();
    return 0;
}


int getStudentData(ifstream& infile, string names[], double scores[][NUM_TEST]) {
    int count = 0;
    while (infile >> names[count]) {
        
        for (int t = 0; t < NUM_TEST; t++) {
            infile >> scores[count][t];
        }
        count++;
        if (count >= MAX_STUDENTS) break; 
    }
    return count; 
}

int calculateAverages(double scores[][NUM_TEST], double averages[], int numStudents) {
    for (int i = 0; i < numStudents; i++) {
        double total = 0;
        for (int t = 0; t < NUM_TEST; t++) {
            total += scores[i][t];
        }
        averages[i] = total / NUM_TEST; 
    }
    return numStudents; 
}


string calculateGrade(double average) {
    if (average >= 90) return "A";
    if (average >= 80) return "B";
    if (average >= 70) return "C";
    if (average >= 60) return "D";
    return "F"; 
    
}
int printReport(string names[], double averages[], int numStudents) {

    cout << "Name    Average   Grade" << endl;



    for (int i = 0; i < numStudents; i++) {
        string grade = calculateGrade(averages[i]);
        cout << names[i] << "      " << fixed << setprecision(2) << averages[i] << "     " << grade << endl;
    }

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
