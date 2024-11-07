#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
private:
    double radius;
    Point center;
    Velocity velocity;
    Color color;
    bool isCollidable;
public:
    Ball() = default;
    Ball(double radius, Point& center, Velocity& velocity, Color& color, bool isCollidable);
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    bool getCollidable() const;
};
