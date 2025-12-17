#include <iostream>
#include "ascii_draw.hpp"

int main()
{
  using topit::Dot;
  using topit::f_t;
  using topit::p_t;
  topit::IDraw *shps[3] = {};
  p_t *pts = nullptr;
  size_t s = 0;
  size_t err = 0;
  try
  {
    shps[0] = new Dot(0, 0);
    shps[1] = new Dot(5, 7);
    shps[2] = new Dot(-5, -2);
    for (size_t i = 0; i < 3; ++i)
    {
      s += topit::points(*(shps[i]), std::addressof(pts), s);
    }
    f_t fr = frame(pts, s);
    char *cnv = topit::canvas(fr, '.');
    for (size_t i = 0; i < s; ++i)
    {
      paint(cnv, fr, pts[i], '#');
    }
    flush(std::cout, cnv, fr);
    delete[] cnv;
  }
  catch (std::exception &e)
  {
    err = 2;
    std::cerr << "Bad drawing\n" << e.what() << '\n';
  }
  delete[] pts;
  delete shps[0];
  delete shps[1];
  delete shps[2];
  return err;
}
