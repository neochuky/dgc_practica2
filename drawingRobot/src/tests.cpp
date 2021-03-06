#include "tests.hpp"

void Test::testAll()
{
    testTranslations();
    testScales();
    testRotations();

    testCompoundTrasnformations();
}


void Test::testTranslations()
{
    for( unsigned int i=0; i<100; i++ ){
        // Set random original 2D vertex and transformation
        x = -250+rand()%500;
        y = -250+rand()%500;
        tx = -250+rand()%500;
        ty = -250+rand()%500;

        // Translate previous vertex.
        originalVertex.set( x, y );
        transMatrix.setTranslation( tx, ty );
        resultVertex = originalVertex*transMatrix;

        // Check if resulting vertex equals to expected result.
        assert( (resultVertex[X] == x+tx)
               && (resultVertex[Y] == y+ty)
               && (resultVertex[H] == 1) );
    }

    cout << "Translation test ...OK" << endl;
}


void Test::testScales()
{
    for( unsigned int i=0; i<100; i++ ){
        // Set random original 2D vertex and transformation
        x = -250+rand()%500;
        y = -250+rand()%500;
        sx = -250+rand()%500;
        sy = -250+rand()%500;

        // Scale previous vertex.
        originalVertex.set( x, y );
        transMatrix.setScale( sx, sy );
        resultVertex = originalVertex*transMatrix;

        // Check if resulting vertex equals to expected result.
        assert( (resultVertex[X] == x*sx)
               && (resultVertex[Y] == y*sy)
               && (resultVertex[H] == 1) );
    }

    cout << "Scale test ...OK" << endl;
}


void Test::testRotations()
{
    for( unsigned int i=0; i<100; i++ ){
        // Set random original 2D vertex and transformation
        x = -250+rand()%500;
        y = -250+rand()%500;
        angle = -250+rand()%500;

        // Rotate previous vertex.
        originalVertex.set( x, y );
        transMatrix.setRotation( angle );
        resultVertex = originalVertex*transMatrix;

        // Check if resulting vertex equals to expected result.
        angle *= PI/180;
        assert( (resultVertex[X] == x*cos(angle)+y*sin(angle))
               && (resultVertex[Y] == -x*sin(angle)+y*cos(angle))
               && (resultVertex[H] == 1) );
    }

    cout << "Rotation test ...OK" << endl;
}

void Test::testCompoundTrasnformations()
{
    Matrix auxMatrix;
    Vertex expectedVertex;
    float aux;

    for( unsigned int i=0; i<100; i++ ){
        // Set random original 2D vertex and transformations
        x = -250+rand()%500;
        y = -250+rand()%500;
        tx = -250+rand()%500;
        ty = -250+rand()%500;
        sx = -250+rand()%500;
        sy = -250+rand()%500;
        angle = -250+rand()%500;

        // Transform 2D vertex.
        originalVertex.set( x, y );
        transMatrix.setTranslation( tx, ty );

        auxMatrix.setScale( sx, sy );
        transMatrix = transMatrix*auxMatrix;

        auxMatrix.setRotation( angle );
        transMatrix = transMatrix*auxMatrix;

        resultVertex = originalVertex*transMatrix;


        // Compute expected result.
        angle *= PI/180;

        x = x+tx;
        y = y+ty;

        x = x*sx;
        y = y*sy;

        aux = x;
        x = x*cos(angle)+y*sin(angle);
        y = -aux*sin(angle)+y*cos(angle);


        // Check if resulting vertex equals to expected result.
        assert( (resultVertex[X] == x)
               && (resultVertex[Y] == y)
               && (resultVertex[H] == 1) );
    }

    cout << "Compound transformation test ...OK" << endl;
}
