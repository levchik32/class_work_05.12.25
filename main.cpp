#include <iostream>
#include <cstddef>

namespace topit
{
  struct p_t
  {
    int x, y;
  };
  bool operator==(p_t, p_t);
  bool operator!=(p_t, p_t);
  struct f_t
  {
    p_t aa, bb;
  };

  struct IDraw
  {
    virtual p_t begin() const = 0;
    virtual p_t next(p_t) const = 0;
    virtual ~IDraw() = default;
  };

  struct Dot : IDraw
  {
    Dot(int x, int y);
    explicit Dot(p_t dd);
    p_t begin() const override;
    p_t next(p_t) const override;

    p_t d;
  };

  struct Vline : IDraw
  {
    Vline(int x, int y, size_t ll);
    Vline(p_t dd, size_t ll);
    p_t begin() const override;
    p_t next(p_t dd) const override;

    p_t d;
    size_t l;
  };

  struct Hline : IDraw
  {
    Hline(int x, int y, size_t ll);
    Hline(p_t dd, size_t ll);
    p_t begin() const override;
    p_t next(p_t dd) const override;

    p_t d;
    size_t l;
  };

  size_t points(const IDraw &d, p_t **pts, size_t s);
  f_t frame(p_t * pts, size_t s);
  char * canvas(f_t fr, char fill);
  void paint(char *cnv, f_t ft, p_t p, char fill);
  void flush(std::ostream &, const char *cnv, f_t fr);
}

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
      s += topit::points(*(shps[i]), &pts, s);
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
  catch (...)
  {
    err = 2;
    std::cerr << "Bad drawing\n";
  }
  delete[] pts;
  delete shps[0];
  delete shps[1];
  delete shps[2];
  return err;
}

//
bool topit::operator==(p_t a, p_t b)
{
  return a.x == b.x && a.y == b.y;
}

bool topit::operator!=(p_t a, p_t b)
{
  return (a == b);
}

//Dot
topit::p_t topit::Dot::begin() const
{
  return d;
}

topit::Dot::Dot(int x, int y) : IDraw(),
  d{x, y}
{}
topit::Dot::Dot(p_t dd) : IDraw(),
  d{dd}
{}

topit::p_t topit::Dot::next(p_t prev) const
{
  if (prev != begin())
  {
    throw std::logic_error("bad impl");
  }
  return d;
}

//Vline
topit::Vline::Vline(int x, int y, size_t ll):
  IDraw(),
  d{x, y}, l(ll)
{}

topit::Vline::Vline(p_t dd, size_t ll):
  IDraw(),
  d{dd}, l(ll)
{}

topit::p_t topit::Vline::begin() const
{
  return d;
}

topit::p_t topit::Vline::next(p_t dd) const
{
  if (dd.x != d.x || dd.y < d.y)
  {
    throw std::logic_error("bad impl");
  }
  if (dd.y - d.y + 1 == l)
  {
    return d;
  }
  return {d.x, d.y + 1};
}

//Hline
topit::Hline::Hline(int x, int y, size_t ll):
  IDraw(),
  d{x, y}, l(ll)
{}

topit::Hline::Hline(p_t dd, size_t ll):
  IDraw(),
  d{dd}, l(ll)
{}

topit::p_t topit::Hline::begin() const
{
  return d;
}

topit::p_t topit::Hline::next(p_t dd) const
{
  if (dd.y != d.y || dd.x < d.x)
  {
    throw std::logic_error("bad impl");
  }
  if (dd.x - d.x + 1 == l)
  {
    return d;
  }
  return {d.x + 1, d.y};
}
