#include "Color.hpp"

Color::Color() = default;

Color::Color(double red, double green, double blue)
    : r{red}, g{green}, b{blue} {}

std::istream& operator>>(std::istream& stream, Color& color)
{
    double r, g, b;
    stream >> r >> g >> b;
    color.setRed(r);
    color.setGreen(g);
    color.setBlue(b);
    return stream;
}

void Color::setRed(double red)
{
    this->r = red;
}

void Color::setGreen(double green)
{
    this->g = green;
}

void Color::setBlue(double blue)
{
    this->b = blue;
}

double Color::red() const {
    return r;
}

double Color::green() const {
    return g;
}

double Color::blue() const {
    return b;
}
