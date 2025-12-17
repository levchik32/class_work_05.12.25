#include <stdexcept>
#include "lines.hpp"

// Vline
topit::Vline::Vline(int x, int y, size_t ll) : IDraw(),
	d{x, y}, l(ll)
{}

topit::Vline::Vline(p_t dd, size_t ll) : IDraw(),
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

// Hline
topit::Hline::Hline(int x, int y, size_t ll) : IDraw(),
	d{x, y}, l(ll)
{}

topit::Hline::Hline(p_t dd, size_t ll) : IDraw(),
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
