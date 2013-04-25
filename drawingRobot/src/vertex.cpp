
#include "vertex.hpp"


/*                                 1. Initialization                         */

Vertex::Vertex()
{
    v = new float[4];
	for( unsigned int i=0; i<3; i++ ){
		v[i] = 0;
	}
	v[3] = 1;
}

Vertex::Vertex( const Vertex& b )
{
    v = new float[4];
	for( unsigned int i=0; i<4; i++ ){
		v[i] = b[i];
	}
}

Vertex::Vertex( float x, float y, float z )
{
    v = new float[4];
	set( x, y, z );
}

Vertex::~Vertex()
{
    delete [] v;
}

void Vertex::set( float x, float y, float z )
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
	v[3] = 1;
}


/*                                  2. Operators                             */

void Vertex::operator = (const Vertex& b)
{
    for( unsigned int i=0; i<4; i++ ){
        v[i] = b[i];
    }
}

Vertex Vertex::operator + (const Vertex& b) const
{
    Vertex c( b[X]+v[X], b[Y]+v[Y], b[Z]+v[Z] );
    return c;
}

Vertex Vertex::operator - (const Vertex& b) const
{
    Vertex c( v[X]-b[X], v[Y]-b[Y], v[Z]-b[Z] );
    return c;
}

Vertex Vertex::operator * (const Vertex& b) const
{
    Vertex c( v[X]*b[X], v[Y]*b[Y], v[Z]*b[Z] );
    return c;
}

Vertex Vertex::operator * (const float& b) const
{
    Vertex c( v[X]*b, v[Y]*b, v[Z]*b );
    return c;
}

Vertex Vertex::operator / (const float& b) const
{
    Vertex c( v[X]/b, v[Y]/b, v[Z]/b );
    return c;
}


float Vertex::getNorm() const
{
    return( sqrt( v[X]*v[X]+v[Y]*v[Y]+v[Z]*v[Z] ) );
}

Vertex Vertex::getUnitVector() const
{
    float invNorm = 1.0/getNorm();
    Vertex res( v[X]*invNorm, v[Y]*invNorm, v[Z]*invNorm );

    return res;
}

void Vertex::normalize(){
    float invNorm = 1.0/getNorm();
    set( v[X]*invNorm, v[Y]*invNorm, v[Z]*invNorm);
}

float Vertex::distance( const Vertex& b ) const{
    return sqrt( (v[X] - b[X])*(v[X] - b[X]) +
                (v[Y] - b[Y])*(v[Y] - b[Y]) +
                (v[Z] - b[Z])*(v[Z] - b[Z]));
}

/*                                 3. << operator                            */

ostream& operator << (ostream &out, const Vertex &vertex)
{
    out << "("
		<< vertex.v[0] << ", "
		<< vertex.v[1] << ", "
		<< vertex.v[2] << ", "
        << vertex.v[3] << ")";
    return out;
}



float dotProduct( const Vertex& a, const Vertex& b )
{
    return a[X]*b[X]+a[Y]*b[Y]+a[Z]*b[Z];
}

