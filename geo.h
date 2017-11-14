#ifndef GEO_H_
#define GEO_H_

// Basic geometric typedefs
typedef int P2[2];
typedef int Point[3];
typedef int Vector[3];
typedef double Rotation[3];
typedef char Color[3];

//Compound geometric typedefs
typedef Point segment[2];
typedef Point triangle[3];

//Functions
void plot(int x, int y, Color c);
void plotLine(int x0, int y0, int x1, int y1, Color c);
void plotTri(P2 v1, P2 v2, P2 v3, Color c);

#endif
