#include "cooler_lines.hpp"
#include <cmath>
#include <stdexcept>

topit::p_t topit::Cline::begin() const
{
    return st;
}

topit::Cline::Cline(int x1, int y1, int x2, int y2) : IDraw()
{
    if (x1 < x2)
    {
        st = {x1, y1};
        nd = {x2, y2};
    }
    else
    {
        st = {x2, y2};
        nd = {x1, y1};
    }
}

topit::Cline::Cline(p_t dd1, p_t dd2) : IDraw()
{
    if (dd1.x < dd2.x)
    {
        st = dd1;
        nd = dd2;
    }
    else
    {
        st = dd2;
        nd = dd1;
    }
}

topit::p_t topit::Cline::next(p_t prev) const
{
    if (prev == nd) {
        return st;
    }

    int dx = nd.x - st.x;
    int dy = nd.y - st.y;
    
    if (abs(dx) > abs(dy))
    {
        int step_x = (dx > 0) ? 1 : -1;
        int D = 2 * abs(dy) - abs(dx);
        int x = st.x;
        int y = st.y;
        
        for (int i = 0; i <= abs(dx); i++)
        {
            if (x == prev.x && y == prev.y)
            {
                if (i == abs(dx)) return nd;
                
                x += step_x;
                if (D > 0)
                {
                    y += (dy > 0) ? 1 : -1;
                    D -= 2 * abs(dx);
                }
                D += 2 * abs(dy);

                return {x, y};
            }
            
            x += step_x;
            if (D > 0)
            {
                y += (dy > 0) ? 1 : -1;
                D -= 2 * abs(dx);
            }
            D += 2 * abs(dy);
        }
    }
    else
    {
        int step_y = (dy > 0) ? 1 : -1;
        int D = 2 * abs(dx) - abs(dy);
        int x = st.x;
        int y = st.y;
        
        for (int i = 0; i <= abs(dy); i++)
        {
            if (x == prev.x && y == prev.y)
            {
                if (i == abs(dy)) return nd;
                
                y += step_y;
                if (D > 0)
                {
                    x += (dx > 0) ? 1 : -1;
                    D -= 2 * abs(dy);
                }
                D += 2 * abs(dx);

                return {x, y};
            }
            
            y += step_y;
            if (D > 0)
            {
                x += (dx > 0) ? 1 : -1;
                D -= 2 * abs(dy);
            }
            D += 2 * abs(dx);
        }
    }
    throw std::logic_error("bad impl");
}
