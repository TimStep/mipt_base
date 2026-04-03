#include <iostream>
using namespace std;

struct A {
  char a;
  char b;
  char c;
  int d;
  int e;
};

struct B {
  char a;
  int d;
  char b;
  int e;
  char c;
};

int main() {
  A st_a;
  cout<<"sizeof(A): "<<sizeof(A)<<endl;
  cout<<"sizeof(B): "<<sizeof(B)<<endl;
  cout<<"sizeof(st_a.a): "<<sizeof(st_a.a)<<endl;

  cout<<"offsetof(A, a): "<<offsetof(A, a)<<endl;
  cout<<"offsetof(A, b): "<<offsetof(A, b)<<endl;
  cout<<"offsetof(A, c): "<<offsetof(A, c)<<endl;
  cout<<"offsetof(A, d): "<<offsetof(A, d)<<endl;
  cout<<"offsetof(A, e): "<<offsetof(A, e)<<endl;
  cout << endl;
  cout<<"offsetof(B, a): "<<offsetof(B, a)<<endl;
  cout<<"offsetof(A, b): "<<offsetof(B, b)<<endl;
  cout<<"offsetof(A, c): "<<offsetof(B, c)<<endl;
  cout<<"offsetof(B, d): "<<offsetof(B, d)<<endl;
  cout<<"offsetof(A, e): "<<offsetof(B, e)<<endl;
  return 0;
}
