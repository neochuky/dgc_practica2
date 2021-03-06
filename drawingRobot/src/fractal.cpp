#include "fractal.hpp"

// Macro for swapping 2 variables
#define swap(type, i, j) {type t = i; i = j; j = t;}

// Auxiliar macro with value 1/4.
#define INV4 0.25


/***
    1. Auxiliar methods
***/

void Fractal::addVertex( const Vertex& vertex, const unsigned int& index )
{
    //Vector from previous vertex to the new one
    Vertex aux;
    aux = vertex - v[index - 1];
    aux.normalize();
    vectors[index - 1].set( aux[X], aux[Y] );
    transVectors[index - 1].set( aux[X], aux[Y] );

    //Vector from the new vertex to the next one
    aux = v[index] - vertex;
    aux.normalize();
    vectors.insert(vectors.begin() + index, aux);
    transVectors.insert(transVectors.begin() + index, aux);

    //Insert vertex
    v.insert( v.begin() + index, vertex );
    transV.insert( transV.begin() + index, vertex );
    vScalated.insert(vScalated.begin() + index, vertex*0.25);
    transVScalated.insert(transVScalated.begin() + index, vertex*0.25);
}


void Fractal::copyToCore()
{
    coreVertices.clear();
    transCoreVertices.clear();

    for( unsigned int i=0; i<v.size(); i++ ){
        coreVertices.push_back(v[i]);
        transCoreVertices.push_back(v[i]);
    }
}


/***
    2. Initialization
***/

Fractal::Fractal( int divisions_ )
:Polygon()
{
    type = FRACTAL;
    Vertex aux;
    divisions = divisions_;
    for(int i = 0; i < 3; i++){
        Polygon::addVertex(aux);
    }
    copyToCore();
}

void Fractal::setVertices( const Vertex& vertex0, const Vertex& vertex1){
    clear();
    Vertex orig = (vertex1 + vertex0)*0.5;
    float distance = vertex0.distance(vertex1);
    Vertex v0(-1 - distance*0.5, 0), v1(0, 1 +  distance), v2(1 + distance*0.5, 0);

    v0 = v0 + orig;
    v1 = v1 + orig;
    v2 = v2 + orig;

    Polygon::addVertex(v0);
    Polygon::addVertex(v2);
    Polygon::addVertex(v1);
    Polygon::addVertex(v0);

    copyToCore();
}

void Fractal::set( const std::vector< Vertex >* coreTransVertexes_, int divisions_ )
{
    //Delete previous information about vertices
    clear();

    divisions = divisions_;
    //for( unsigned int i = 0; i < 3; i++ ){
    for( unsigned int i = 0; i < coreTransVertexes_->size(); i++ ){
        Polygon::addVertex( (*coreTransVertexes_)[i] );
    }
    copyToCore();

    divide();
}

void Fractal::divide()
{
    //Delete previous information about vertices
    clear();
    //Copy core vertices to vertices vector
    for( unsigned int i=0; i<transCoreVertices.size(); i++ ){
        Polygon::addVertex(transCoreVertices[i]);
    }

    Vertex newVertex, normal;
    float normalFactor;
    //Divide line as many times as divisions says
    for(int i = 0; i < divisions; i++){
        for(unsigned int j = 0; j < v.size() - 1; j++){
            //This factor defines the height of the middle vertex
            normalFactor = v[j].distance(v[j+1])*0.25;

            //Add three new vertices for each old vertex
            newVertex = (v[j+1] - v[j])*INV4 + v[j];
            j++;
            addVertex(newVertex, j);

            //Calculate normal between original vertices
            normal = v[j - 1] - v[j+1];
            swap(float, normal[X], normal[Y]);
            normal[X] = -normal[X];
            normal.normalize();
            //Normal length is inversely proportional to the number of
            //divisions
            normal = normal*normalFactor;
            //Calculate a vertex between the two original vertices
            newVertex = (v[j+1] - v[j - 1])*INV4*2 + v[j - 1];
            //Add the normal length to this vertex
            newVertex = newVertex + normal;
            j++;
            addVertex(newVertex, j);

            newVertex = (v[j+1] - v[j - 2])*INV4*3 + v[j - 2];
            j++;
            addVertex(newVertex, j);
        }
    }
}


/***
    3. Updating
***/
void Fractal::update()
{
    Polygon::update();

    // Override update methods to also update core vertices
    for( unsigned int i=0; i<coreVertices.size(); i++ ){
        transCoreVertices[i] = coreVertices[i]*transMatrix;
    }
}


/***
    4. Getters and setters
***/

const std::vector< Vertex >* Fractal::getTransCoreVertices()
{
    return &transCoreVertices;
}

