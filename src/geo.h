#ifndef GEO_H_
#define GEO_H_

// Basic geometric typedefs
typedef int P2[2];
typedef int Point[3];
typedef int Vector[3];
typedef double Rotation[3];
typedef unsigned char Color[3];

//Compound geometric typedefs
typedef Point segment[2];
typedef Point triangle[3];

typedef struct {
    Point c; // 3D Position of Camera
    Rotation theta; // Orientation of the Camera in Tait-Bryan angles
    Vector e; // Display Surface's position relative to c
} Camera;

//Functions
// Returns a malloced pointer to a P2, must be freed
int* project(Point p, Camera c);

void plot(int x, int y, Color c);
void plotLine(int x0, int y0, int x1, int y1, Color c);
void plotTri(P2 v1, P2 v2, P2 v3, Color c);

#endif
