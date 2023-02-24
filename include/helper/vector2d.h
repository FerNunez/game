#pragma once

#include <cmath>
#include <iostream>
#include <tuple>

template<class T>
class Vector2d
{
public:
    // Constructor to initialize the vector
    Vector2d()
      : x(T(0), y(0))
    {
    }

    Vector2d(const T& x, const T& y)
      : x(x)
      , y(y)
    {
    }

    T x;
    T y;

    // operators (= something)
    Vector2d& operator+=(const Vector2d& v)
    {
        this->x += v.x;
        this->y += v.y;
        return *this;
    }

    Vector2d& operator-=(const Vector2d& v)
    {
        this->x -= v.x;
        this->y -= v.y;
        return *this;
    }

    Vector2d& operator*=(const Vector2d& v)
    {
        this->x *= v.x;
        this->y *= v.y;
        return *this;
    }

    Vector2d& operator/=(const Vector2d& v)
    {
        this->x /= v.x;
        this->y /= v.y;
        return *this;
    }

    // egal
    friend bool operator==(const Vector2d& L, const Vector2d& R)
    {
        return std::tie(L.x, L.y) == std::tie(R.x, R.y);
    }

    friend bool operator!=(const Vector2d& L, const Vector2d& R)
    {
        return !(L == R);
    }

    // minus
    Vector2d operator-() const
    {
        Vector2d(-this->x, -this->y);
    }

    // scalar
    Vector2d& operator*(const T& s)
    {
        this->x *= s;
        this->y *= s;
        return *this;
    }

    Vector2d& operator/(const T& s)
    {
        this->x /= s;
        this->y /= s;
        return *this;
    }
};

// non-member functions
// two vectors
template<class T>
Vector2d<T> operator+(const Vector2d<T>& L, const Vector2d<T>& R)
{
    return Vector2d<T>(L) += R;
}
template<class T>
Vector2d<T> operator-(const Vector2d<T>& L, const Vector2d<T>& R)
{
    return Vector2d<T>(L) -= R;
}

template<class T>
Vector2d<T> operator*(const Vector2d<T>& L, const Vector2d<T>& R)
{
    return Vector2d<T>(L) *= R;
}

template<class T>
Vector2d<T> operator/(const Vector2d<T>& L, const Vector2d<T>& R)
{
    return Vector2d<T>(L) /= R;
}

// vector scalar
template<class T>
Vector2d<T> operator*(const T& s, const Vector2d<T>& R)
{
    return Vector2d<T>(R) * s;
}
template<class T>
Vector2d<T> operator*(const Vector2d<T>& L, const T& s)
{
    return Vector2d<T>(L) * s;
}
template<class T>
Vector2d<T> operator/(const T& s, const Vector2d<T>& R)
{
    return Vector2d<T>(R) / s;
}
template<class T>
Vector2d<T> operator/(const Vector2d<T>& L, const T& s)
{
    return Vector2d<T>(L) / s;
}

// Products
template<class T>
T dotProduct(const Vector2d<T>& v1, const Vector2d<T>& v2)
{
    return (v1.x * v2.x + v1.y * v2.y);
}

template<class T>
T crossProduct(const Vector2d<T>& v1, const Vector2d<T>& v2)
{
    return (v1.x * v2.y - v1.y * v2.x);
}

// Norm
template<class T>
T euclideanNorm(const Vector2d<T>& v)
{
    return std::sqrt(v.x * v.x + v.y * v.y);
}

// Others
template<class T>
Vector2d<T> normalVector(const Vector2d<T>& v)
{
    T euclidean_norm = euclideanNorm(v);
    return Vector2d<T>(v.x / euclidean_norm, v.y / euclidean_norm);
}

template<class T>
Vector2d<T> perpendicularVector(const Vector2d<T>& v)
{
    return Vector2d<T>(-v.y, v.x);
}

// template<class T> bool Intersect(const Vector2d<T>&, const Vector2d<T>&, const Vector2d<T>&,
// const Vector2d<T>&); template<class T> Vector2d<T> GetIntersect(const Vector2d<T>&, const
// Vector2d<T>&, const Vector2d<T>&, const Vector2d<T>&);

// define
typedef Vector2d<int> vec2i;
typedef Vector2d<double> vec2d;
typedef Vector2d<float> vec2f;
