#include "Vector2D.h"

template<>
struct std::hash<Vector2D>
{
    size_t operator()(const Vector2D& v) const
    {
        size_t res = 17;
        res = res * 31 + std::hash<int>()(v.x);
        res = res * 31 + std::hash<int>()(v.y);

        return res;
    }
};