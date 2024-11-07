#pragma once
#include <iostream>

class Color {
  public:
    Color();
    Color(double red, double green, double blue);
    double red() const;
    double green() const;
    double blue() const;
    void setRed(double red);
    void setGreen(double green);
    void setBlue(double blue);
    friend std::istream& operator>>(std::istream& stream, Color& color);
  private:
    double r{};
    double g{};
    double b{};
};
