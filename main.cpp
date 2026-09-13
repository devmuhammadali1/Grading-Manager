#include <climits>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

class Student {
private:
  int grade;

public:
  string name;
  Student(int grade, string name) {
    this->name = name;
    this->grade = (grade < 0 || grade > 100 ? 0 : grade);
  }
  int getGrade() const { return grade; }
  void setGrade(int grade) {
    this->grade = (grade < 0 || grade > 100 ? 0 : grade);
  }
};

int getValidatedInput(int min, int max, string prompt) {
  int inputValue;
  cin >> inputValue;
  while (cin.fail() || inputValue < min || inputValue > max) {
    cin.clear();
    string trash;
    getline(cin, trash);
    cout << prompt << '\n';
    cout << "Enter Again: ";
    cin >> inputValue;
  }
  return inputValue;
}
double calculateAverage(vector<Student> &arr, int studentCount, int size) {
  double sum = 0;
  for (int i = 0; i < size; i++) {
    sum += arr[i].getGrade();
  }
  return sum / studentCount;
}
int findHighest(vector<Student> &arr, int size) {
  int highestGrade = arr[0].getGrade();
  for (int i = 0; i < size; i++) {
    if (arr[i].getGrade() > highestGrade) {
      highestGrade = arr[i].getGrade();
    }
  }
  return highestGrade;
}
int findLowest(vector<Student> &arr, int size) {
  int lowestGrade = arr[0].getGrade();
  for (int i = 1; i < size; i++) {
    if (arr[i].getGrade() < lowestGrade) {
      lowestGrade = arr[i].getGrade();
    }
  }
  return lowestGrade;
}

// int *findHighest(vector<Student> &arr, int size) {
//   int *ptr = &arr[0].getGrade();
//   for (int i = 1; i < size; i++) {
//     if (arr[i].getGrade() > *ptr) {
//       ptr = &arr[i].getGrade();
//     }
//   }
//   return ptr;
// }
// int *findLowest(vector<Student> &arr, int size) {
//   int *ptr = &arr[0].getGrade();
//   for (int i = 1; i < size; i++) {
//     if (arr[i].getGrade() < *ptr) {
//       ptr = &arr[i].getGrade();
//     }
//   }
//   return ptr;
// }
void displayAboveAvg(vector<Student> &arr, int size, double avg) {
  cout << "Above Average Students: \n";
  bool aboveStd = false;
  for (int i = 0; i < size; i++) {
    if (arr[i].getGrade() > avg) {
      cout << arr[i].name << ": " << arr[i].getGrade() << '\n';
      aboveStd = true;
    }
  }
  cout << "-------------------";
  if (!aboveStd) {
    cout << "- (None)\n";
  }
}
int LowestHighestCount(vector<Student> &arr, int size, int grade) {
  int count = 0;
  for (int i = 0; i < size; i++) {
    if (arr[i].getGrade() == grade) {
      count++;
    }
  }
  return count;
}
void savingToFile(vector<Student> &students, string currentFile) {
  ofstream MyFile(currentFile);
  if (MyFile.is_open()) {
    for (int i = 0; i < size(students); i++) {
      MyFile << "Student " << i + 1 << ";\n Name: " << students[i].name
             << "\n Grade: " << students[i].getGrade()
             << (i < size(students) - 1 ? "\n\n" : "");
    }
    MyFile.close();
    cout << "Successfully Saved!!!\n";
  } else {
    cout << "\nFailed To Save Data! Check The File And Try Again.\n";
  }
}
void checkExistFile(string currentFile) {
  ifstream checkFile(currentFile);
  if (checkFile.is_open()) {
    cout << "'" << currentFile
         << "' Already Exists! Enter 'y' To OverWrite Or Load It From '4. Load "
            "File'!\n";
  }
}

int main() {
  cout << "\n ****** <WELCOME TO GRADING SYSTEM> ****** \n";
  char userInput = 'n';
  int userChoice;
  string currentFile = "";
  vector<Student> students;
  do {
    cout << "\n====== Menu ======\n";
    cout << "1. Add Students & Enter Grades\n";
    cout << "2. View All Students\n";
    cout << "3. Save To File/Create File\n";
    cout << "4. Load File\n";
    cout << "5. View Statistics\n";
    cout << "0. Exit\n";
    cout << "Choose an option: ";
    userChoice = getValidatedInput(0, 5, "Invalid! Enter Correct Option!");

    switch (userChoice) {
    // Option-1******
    case 1: {
      // *****Student Count Section*****
      int studentCount;
      cout << "Enter Number Of Students: ";
      studentCount =
          getValidatedInput(1, INT_MAX, "Invalid! Number's Too Large!");
      cout << endl;
      // *****Student Count Section*****

      // *****Grading Section*****
      cout << "Enter Name/Grade For Each Student Now:\n\n";
      for (int i = 0; i < studentCount; i++) {
        cin.ignore(1, '\n');
        cout << "Student " << size(students) + 1 << ";" << '\n';
        string name;
        cout << "Name: ";
        getline(cin, name);
        cout << "Grade: ";
        int grade =
            getValidatedInput(0, 100, "Invalid! Enter Grade Only 0 to 100!");
        students.push_back(Student(grade, name));
        cout << endl;
      }
      // *****Grading Section*****
    } break;
    // Option-2******
    case 2: {

      cout << "\nStudents: \n";
      cout << "-------------------\n";
      if (size(students) < 1) {
        cout << "N/A\n";
        break;
      }
      for (int i = 0; i < size(students); i++) {
        cout << i + 1 << ") " << students[i].name << ": "
             << students[i].getGrade() << '\n';
      }
      cout << "-------------------";
    } break;
    // Option-3******
    case 3: {
      // *****Saving Data To FileSection*****
      if (currentFile == "") {
        cout << "Enter File Name To Create: ";
        cin >> currentFile;
        currentFile += ".txt";
        checkExistFile(currentFile);
      }

      char savingChoice;
      cout << "\nWant To Save Data To '" << currentFile << "'? Enter y/n:";
      cin >> savingChoice;
      if (savingChoice == 'y' || savingChoice == 'Y') {
        savingToFile(students, currentFile);
      } else {
        cout << "Want To Add Different File? Enter y/n: ";
        char fileChoice;
        cin >> fileChoice;
        if (fileChoice == 'y' || fileChoice == 'Y') {
          cout << "Enter New Name: ";
          cin >> currentFile;
          currentFile += ".txt";
          checkExistFile(currentFile);
          char savingChoice2;
          cout << "\nWant To Save Data To '" << currentFile << "'? Enter y/n:";
          cin >> savingChoice2;
          if (savingChoice2 == 'y' || savingChoice2 == 'Y') {
            savingToFile(students, currentFile);
          }
        }
      }
      // *****Saving Data To FileSection*****
    } break;
    // Option-4******
    case 4: {
      // *****Reading Data From File Section*****
      cout << "Enter File Name To Load: ";
      cin >> currentFile;
      currentFile += ".txt";
      ifstream MyFileR(currentFile);
      if (MyFileR.is_open()) {
        cout << "\n'" << currentFile << "' Loaded Successfully!!!\n";
        students.clear();
        string line;
        string name;
        string grade;
        string space;
        while (getline(MyFileR, line)) {
          getline(MyFileR, name);
          getline(MyFileR, grade);
          getline(MyFileR, space);
          students.push_back(Student(stoi(grade.substr(8)), name.substr(7)));
        }
        MyFileR.close();
      } else {
        cout << "Not Found! Enter A Valid FileName!\n";
        currentFile = "";
      }
      // *****Reading Data From File Section*****
    } break;
    // Option-5******
    case 5: {
      cout << "\n----- Results -----";
      if (size(students) < 1) {
        cout << "\nN/A\n";
        break;
      }
      // *****Total Avg Section*****
      double totalAverage;
      totalAverage = calculateAverage(students, size(students), size(students));
      cout << endl;
      cout << "Students Average: " << totalAverage;
      // *****Total Avg Section*****

      // *****Highest Grade Section*****
      int highestGrade;
      int highestStudents;
      highestGrade = findHighest(students, size(students));
      highestStudents =
          LowestHighestCount(students, size(students), highestGrade);
      cout << endl;
      cout << "Highest Grade: " << (size(students) > 0 ? highestGrade : 0)
           << " (" << highestStudents
           << (highestStudents > 1 ? " Students" : " Student") << ')';
      // *****Highest Grade Section*****

      // *****Lowest Grade Section*****
      int lowestGrade;
      int lowestStudents;
      lowestGrade = findLowest(students, size(students));
      lowestStudents =
          LowestHighestCount(students, size(students), lowestGrade);
      cout << endl;
      cout << "Lowest Grade: " << (size(students) > 0 ? lowestGrade : 0) << " ("
           << lowestStudents << (lowestStudents > 1 ? " Students" : " Student")
           << ')';
      cout << endl;
      // *****Lowest Grade Section*****

      // *****Above Avg Students Section*****
      displayAboveAvg(students, size(students), totalAverage);
      // *****Above Avg Students Section*****
    } break;
    // Option-0*****
    case 0: {
      cout << "Goodbye!\n";
      cout << "\n ****** <Program Ended> ****** \n";
    } break;
    }
  } while (userChoice != 0);
  return 0;
}