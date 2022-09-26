#include <iostream>
#include "point.h"

using namespace std;

bool intersect(Point pointOne, Point pointTwo, Point vertOne, Point vertTwo, Point &_intersectPoint) {
    Point
        r,s,v;
    Fraction
        d,t,u;

    r = pointTwo - pointOne;            // Distance between 2 points
    s = vertTwo - vertOne;              // Distance between 2 vertices

    v = vertOne - pointOne;
    d = r * s;

    if (d != 0) {
        t = (v * s) / d;
        u = (v * r) / d;

        if ((t > 0 && t < 1) && (u > 0 && u < 1)) {
            _intersectPoint = pointOne + (r * t);
            return true; 
        }
    }

    return false;
}

bool isInsidePolygon(Point _dart, Point _corner, Point _polygon[], int _numVertices) {
    int
        w = 0;

    Point
        belowBoundary(_dart.getXCord(), 0),                                 // Point on board boundary directly below dart
        aboveBoundary(_dart.getXCord(), _corner.getYCord()),                // Point on board boundary directly above dart
        leftOfBoundary(0, _dart.getYCord()),                                // Point on board boundary directly left of dart
        rightOfBoundary(_corner.getXCord(), _dart.getYCord()),              // Point on board boundary directly right of dart
        intersectPoint,
        z1, z2;

    for (int i = 0; i < _numVertices; i++) {
        if (intersect(belowBoundary, aboveBoundary, _polygon[i], _polygon[(i+1) % _numVertices], intersectPoint)) {
            z1 = intersectPoint - _dart;
            z2 = _polygon[(i+1) % _numVertices] - _polygon[i];

            if ((z1.getYCord() * z2.getXCord()) < 0)
                w = w + 1;
            else
                w = w - 1;
        }
        if (intersect(leftOfBoundary, rightOfBoundary, _polygon[i], _polygon[(i+1) % _numVertices], intersectPoint)) {
            z1 = intersectPoint - _dart;
            z2 = _polygon[(i+1) % _numVertices] - _polygon[i];

            if ((z1.getXCord() * z2.getYCord()) > 0)
                w = w + 1;
            else
                w = w - 1;
        }
    }

    if (w == 0)
        return false;
    else
        return true;

}

Fraction calculatePolygonArea(Point _polygon[], int _numVertices) {
    Fraction
        area, half(1,2);

    for (int i = 0; i < _numVertices; i++) {
        area = area + (_polygon[i] * _polygon[(i+1) % _numVertices]);
    }

    area = area * half;

    return area;
}

Fraction calculateBoardArea(Point _corner, Point _oppositeCorner) {
    Fraction
        boardLength((_oppositeCorner.getXCord() - _corner.getXCord())),
        boardHeight((_oppositeCorner.getYCord() - _corner.getYCord())),
        boardArea = boardHeight * boardHeight;

        return boardArea;
}

int main() {
    int
        numPolygons,                       // n
        numVertices[100],                  // k
        numDarts;                          // m
    
    bool
        polygonHit[numPolygons];

    Point
        corner,
        oppositeCorner,                 // Point b
        polygon[100][20],              // p sub i
        darts[10];                      // d sub i

    Fraction
        score,
        polygonArea,
        boardArea,
        tmp;

    // Input
    cin >> oppositeCorner;
    cin >> numPolygons;
    
    // Setting up the polygons, numVertices and isHit
    for (int i = 0; i < numPolygons; i++){
        cin >> numVertices[i];
        for (int j = 0; j < numVertices[i]; j++) {
            cin >> polygon[i][j];
        }
        polygonHit[i] = false;
    }

    // Setting point locations for each dart thrown
    cin >> numDarts;
    for (int i = 0; i < numDarts; i++) {
        cin >> darts[i];
    }

    // Calculate Score
    boardArea = calculateBoardArea(corner, oppositeCorner);
    for (int i = 0; i < numDarts; i++) {
        for (int j = 0; j < numPolygons; j++) {
            if (polygonHit[j] == false) {
                if (isInsidePolygon(darts[i], oppositeCorner, polygon[j], numVertices[j])) {
                    polygonArea = calculatePolygonArea(polygon[j], numVertices[j]);
                    score = score + (boardArea / polygonArea);
                    polygonHit[j] = true; 
                }
            }
        }
    }

    cout << "Score: " << score << endl;

    return 0;
}
