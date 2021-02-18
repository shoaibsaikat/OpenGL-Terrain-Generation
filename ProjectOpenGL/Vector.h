/*--------------------------------------------------------------------
Name: Mina Shoaib Rahman Saikat
Roll: 0705096
Sec : B
CSE, BUET
---------------------------------------------------------------------*/
#include <cmath>

typedef float	M3DVector3f[3];		// Vector of three floats (x, y, z)

// Scale Vectors (in place)
inline void m3dScaleVector3(M3DVector3f v, float scale)  { v[0] *= scale; v[1] *= scale; v[2] *= scale; }

// Get Square of a vectors length
// Only for three component vectors
inline float m3dGetVectorLengthSquared(const M3DVector3f u)  { return (u[0] * u[0]) + (u[1] * u[1]) + (u[2] * u[2]); }

// Get lenght of vector
// Only for three component vectors.
inline float m3dGetVectorLength(const M3DVector3f u)  { return float(sqrt(double(m3dGetVectorLengthSquared(u)))); }

// Normalize a vector
// Scale a vector to unit length. Easy, just scale the vector by it's length
inline void m3dNormalizeVector(M3DVector3f u) { m3dScaleVector3(u, 1.0f / m3dGetVectorLength(u)); }

/*
* Cross Product
* u x v = result
*/
inline void m3dCrossProduct(M3DVector3f result, const M3DVector3f u, const M3DVector3f v) {
	result[0] = u[1]*v[2] - v[1]*u[2];
	result[1] = -u[0]*v[2] + v[0]*u[2];
	result[2] = u[0]*v[1] - v[0]*u[1];
}

/*
* Calculates the normal of a triangle specified by the three points
* p1, p2, and p3. Each pointer points to an array of three floats. The
* triangle is assumed to be wound counter clockwise.
*/
void m3dFindNormal(M3DVector3f result, const M3DVector3f point1, const M3DVector3f point2, const M3DVector3f point3) {
	M3DVector3f v1,v2;		// Temporary vectors

	// Calculate two vectors from the three points. Assumes counter clockwise
	// winding!
	v1[0] = point1[0] - point2[0];
	v1[1] = point1[1] - point2[1];
	v1[2] = point1[2] - point2[2];

	v2[0] = point2[0] - point3[0];
	v2[1] = point2[1] - point3[1];
	v2[2] = point2[2] - point3[2];

	// Take the cross product of the two vectors to get
	// the normal vector.
	m3dCrossProduct(result, v1, v2);
}