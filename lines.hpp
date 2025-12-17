#ifndef LINES_HPP
#define LINES_HPP
#include "idraw.hpp"
namespace topit
{
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
}
#endif
