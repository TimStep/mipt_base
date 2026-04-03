#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

unsigned search(unsigned iter, unsigned a) {
  if (a >= pow(2, iter - 1)) {
    return search(iter - 1, a - pow(2, iter - 1));
  } else if (a == 0) {
    return iter;
  } else {
    return search(iter - 1, a - 1);
  }
}

int main() {
  unsigned N;
  cin >> N;
  vector<unsigned> v(N);
  for (unsigned i = 0; i < N; i++) {
    unsigned a;
    cin >> a;
    v[i] = a;
  }
  for (unsigned i = 0; i < N; i++) {
    unsigned a = search(4, v[i]);
    cout << a << " ";
  }
  return 0;
}