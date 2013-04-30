#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include "vertex.hpp"

class Polygon
{
    private:
        static int ox, oy;
        std::vector< Vertex > v;

    public:

        void addVertex( const float& x, const float& y );

        void draw() const;

        static void setOrigin( const float& ox, const float& oy );

        unsigned int getSize() const;

    private:
        void drawLine( const Vertex& v0, const Vertex& vy ) const;
};


//

#endif // POLYGON_H