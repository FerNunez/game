#pragma once

class Color
{
public:
    // Constructor to initialize the vector
    Color()
      : r(255)
      , g(255)
      , b(255)
      , alpha(255)
    {
    }

    Color(int a_r, int a_g, int a_b)
      : r(a_r)
      , g(a_g)
      , b(a_b)
      , alpha(255)
    {
    }

    Color(int a_r, int a_g, int a_b, int a_alpha)
      : r(a_r)
      , g(a_g)
      , b(a_b)
      , alpha(a_alpha)
    {
    }

    int r;
    int g;
    int b;
    int alpha; // alpha
};
