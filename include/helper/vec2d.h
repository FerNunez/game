#pragma once

#include <cmath>
#include <iostream>

class Vec2D
{
public:
    // Constructor to initialize the vector
    Vec2D(double x, double y)
      : x(x)
      , y(y)
    {
    }

    Vec2D(const Vec2D& a_vec)
      : x(a_vec.x)
      , y(a_vec.y){};

    double x;
    double y;

    friend std::ostream& operator<<(std::ostream& os, const Vec2D& a_vec2d)
    {
        os << "(" << a_vec2d.x << ", " << a_vec2d.y << ")";
        return os;
    }

    // Method to calculate the length (magnitude) of the vector
    double length() const
    {
        return std::sqrt(x * x + y * y);
    }

    // Method to normalize the vector (scale it to have a length of 1)
    Vec2D normalize() const
    {
        Vec2D normalized(this->x, this->y);
        double l = this->length();
        normalized.x /= l;
        normalized.y /= l;
        return normalized;
    }

    // Addition operator for Vec2D
    Vec2D operator+(const Vec2D& other) const
    {
        return Vec2D(x + other.x, y + other.y);
    }

    // Subtraction operator for Vec2D
    Vec2D operator-(const Vec2D& other) const
    {
        return Vec2D(x - other.x, y - other.y);
    }

    // Subtraction operator for Vec2D
    Vec2D operator*(const Vec2D& other) const
    {
        return Vec2D(x * other.x, y * other.y);
    }

    // Multiplication operator for Vec2D
    Vec2D operator*(double scalar) const
    {
        return Vec2D(x * scalar, y * scalar);
    }

    // Division operator for Vec2D
    Vec2D operator/(double scalar) const
    {
        return Vec2D(x / scalar, y / scalar);
    }

    // Multiplication operator for Vec2D
    double dot(const Vec2D& other) const
    {
        return this->x * other.x + this->y * other.y;
    }

    Vec2D perpendicular()
    {
        return Vec2D(this->y, -this->x);
    }
};
