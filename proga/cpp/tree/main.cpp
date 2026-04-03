#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

struct Student {
  string name;
  int age;
  int id;
};

vector<Student> students;
vector<Student*> p_students;

string filename = "names.txt";
string delimiter = ":";
int find_age = 27;
size_t pos = 0;

void read_students(){
  ifstream file(filename);
  if (file.is_open()) {
    string line;
    int id = 0;
    while (getline(file, line)) {
      Student tmp_student;
      tmp_student.id = id;
      id++;

      int pos = line.find(delimiter);
      tmp_student.age = stoi(line.substr(0, pos));
      tmp_student.name = line.substr(pos+1, line.size());

      //cout << tmp_student.name << ' ' << tmp_student.age << endl;
      students.push_back(tmp_student);
    }
    file.close();
  }
}

bool less_age(const Student* left, const Student* right) {
  return left->age < right->age;
}

void print_students_by_value(vector<Student> students) {
  for (int i = 0; i < students.size(); i++) {
    cout << students[i].id << ' ' << students[i].name << ' ' << students[i].age << endl;
  }
}

/*
void print_students_by_reference(vector<Student> p_students) {
  for (int i = 0; i < p_students.size(); i++) {
    cout << (p_students[i]->id) << endl;
  }
}
*/

void fill_pstudents() {
  for (int i = 0; i < students.size(); i++) {
    p_students.push_back(&students[i]);
  }
}

Student* bin_search(int x) {
  int l = 0;
  int r = p_students.size();

  while (true) {
      int pos = (l+r)/2;
      if (p_students[pos]->age > x) {r = pos;}
      else if (p_students[pos]->age < x) {l = pos;}
      else {return p_students[pos];}
  }

}

int main() {
  read_students();
  print_students_by_value(students);
  fill_pstudents();

  //cout << students[1].name << endl;
  sort(p_students.begin(), p_students.end(), less_age);
  //print_students();
  //cout << (*p_students[0]).name << endl;
  //cout << p_students[0]->name << endl;
  std::cout << bin_search(27)->name << endl;
  
}