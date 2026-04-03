#include <iostream>
#include <string>
#include <vector>

class Fraction{
public:
  Fraction(int num, int den)
    : numerator_(num)
    , denominator_(den) {}

  Fraction(int num)
    : Fraction(num, 1) {}

  int Numerator() const {
    return numerator_;
  }

  int Denominator() const {
    return denominator_;
  }

  void PrintFraction() const {
    std::cout << this->Numerator() << "/" << this->Denominator() << std::endl;
  }

  friend Fraction operator*(const Fraction& lhs, const Fraction& rhs) {
    return Fraction(lhs.numerator_ * rhs.numerator_, lhs.denominator_ * rhs.denominator_);
  }

  Fraction& operator*=(const Fraction& rhs) {
    numerator_ *= rhs.numerator_;
    denominator_ *= rhs.denominator_;
    return *this;
  }

private:
  int numerator_;
  int denominator_;
};

class Point{
private:
    int x_;
    int y_;
public:

    Point(int x, int y) {
        this->x_ = x;
        this->y_ = y;
    }

    int X() {return x_;} int Y() {return y_;}

    void PrintPoint() {
        std::cout << '(' << this->X() << ',' << this->Y() << ')' << std::endl;
    }

    friend Point operator + (const Point& lhs, const Point& rhs) {
        return Point(lhs.x_ + rhs.x_, rhs.y_ + lhs.y_);
    }

    Point operator += (const Point& p) {
        x_ += p.x_;
        y_ += p.y_;
        return *this;
    }

    friend bool operator > (const Point& lhs, const Point& rhs) {
        if (lhs.x_ + rhs.y_ > rhs.x_ + lhs.y_) {return true;}
        else {return false;} 
    }

    friend bool operator < (const Point& lhs, const Point& rhs) {
        return (not (lhs>rhs));
    }
};

int main() {
  Fraction foo(2, 4);
  std::cout << foo.Numerator() << std::endl;
  foo.PrintFraction();
  const Fraction bar(2);
  bar.PrintFraction();

  const Fraction foo_bar_mul = foo * bar;
  foo_bar_mul.PrintFraction();
  
  foo *= bar;
  foo.PrintFraction();
  
  std::cout << std::endl;

    Point spam(1, 2);
    Point eggs(5, 3);

    (spam+eggs).PrintPoint();
    
    std::cout << (spam > eggs) << ' ' << (spam < eggs) << std::endl;

    spam += eggs;
    spam.PrintPoint();

  return 0;
}