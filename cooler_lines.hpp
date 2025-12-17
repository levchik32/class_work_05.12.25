#ifndef COOLER_LINES_HPP
#define COOLER_LINES_HPP
#include "idraw.hpp"
namespace topit
{
    struct Cline : IDraw
    {
        Cline(int x1, int y1, int x2, int y2);
        Cline(p_t dd1, p_t dd2);
        p_t begin() const override;
        p_t next(p_t dd) const override;

        p_t st, nd;
    };
}
#endif
