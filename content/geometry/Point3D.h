/**
 * Author: Ulf Lundstrom, tinyKACTL, hocky, Victor Lecomte
 * Date: 2009-04-14
 * License: CC0
 * Source:
 * Description: Class to handle points in 3D space.
 * 	T can be e.g. double or long long.
 * Usage:
 * Status: untested
 */
#pragma once

template<class T> struct Point3D {
  typedef Point3D P;
  typedef const P& R;
  T x, y, z;
  bool operator<(R p) const {
    return tie(x, y, z) < tie(p.x, p.y, p.z);
  }
  bool operator==(R p) const {
    return tie(x, y, z) == tie(p.x, p.y, p.z);
  }
  P operator+(R p) const { return P(x + p.x, y + p.y, z + p.z); }
  P operator-(R p) const { return P(x - p.x, y - p.y, z - p.z); }
  P operator*(T d) const { return P(x * d, y * d, z * d); }
  P operator/(T d) const { return P(x / d, y / d, z / d); }
  T dot(R p) const { return x * p.x + y * p.y + z * p.z; }
  T operator|(R p) const { return (*this).dot(p); }
  // v * w = (v.dist() * w.dist() * sin(theta)) n;
  // n is the vector perp to the plane made by v and w
  P cross(R p) const {return P(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);}
  P operator*(R p) const { return (*this).cross(p); }
  // given plane, check whether this point is below or above it
  T orient(R p, R q, R r) {return (q - p) * (r - p) | ((*this) - p);}
  // (*this) is a normal vector of plane p,q,r
  // determine the 2d orientation of p.ccw(q, r). normal got by cross
  T orientByNormal(R p, R q, R r) {return (q - p) * (r - p) | (*this);}
  T dist2() const { return x * x + y * y + z * z; }
  double dist() const { return sqrt((double)dist2()); }
  //Azimuthal angle (longitude) to x-axis in interval [-pi, pi]
  double phi() const { return atan2(y, x); }
  //Zenith angle (latitude) to the z-axis in interval [0, pi]
  double theta() const { return atan2(sqrt(x * x + y * y), z); }
  P unit() const { return *this / (T)dist(); } //makes dist()=1
  //returns unit vector normal to *this and p
  P normal(P p) const { return cross(p).unit(); }
  //returns point rotated 'angle' radians ccw around axis
  P rotate(double angle, P axis) const {
    double s = sin(angle), c = cos(angle); P u = axis.unit();
    return u * dot(u) * (1 - c) + (*this) * c - cross(u) * s;
  }
  double angle(const P &other) const {
    return acos(min(fabs((*this) | other) / dist() / other.dist(), 1.0));
  }
};


typedef double T;
typedef Point3D<T> p3;


template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
struct Plane {
  // normal vector is better if its a unit vector.
  p3 n; T d;
  // From normal n and offset d
  Plane(p3 _n, T _d) : n(_n.unit()), d(_d) {}
  // From normal n and point P
  Plane(p3 _n, p3 p) : n(_n.unit()), d(_n | p) {}
  // From three non-collinear points P,Q,R
  Plane(p3 p, p3 q, p3 r) : Plane((q - p) * (r - p), p) {}
  // weighted distance of point p, if n is unit vector, its signed distance
  T side(p3 p) {return (n | p) - d;}
  double dist(p3 p) {return fabs(side(p));}
  // translate a plane by vector t
  Plane translate(p3 t) {return {n, d + (n | t)};}
  Plane shiftUp(double shift) {return {n, d + shift};}
  p3 proj(p3 p) {return p - n * side(p);}
  p3 refl(p3 p) {return p - n * 2 * side(p);}
  double angle(const Plane &p2) const { return n.angle(p2.n); }
};

struct Line3d {
  // d is a unit shift vector
  p3 d, o;
  Line3d(p3 p, p3 q) : d((q - p).unit()), o(p) {}
  // From two planes p1, p2 (requires T = double)
  // if d == 0, plane is parallel
  Line3d(Plane p1, Plane p2) {
    d = (p1.n * p2.n).unit();
    o = (p2.n * p1.d - p1.n * p2.d) * d;
  }
  double dist2(p3 p) const {return (d * (p - o)).dist2();}
  double dist(p3 p) const {return sqrt(dist2(p));}
  bool cmpProj(p3 p, p3 q) {return (d | p) < (d | q);}
  p3 proj(p3 p) {return o + d * (d | (p - o));}
  p3 refl(p3 p) {return proj(p) * 2 - p;}
  // when d dot p.n is 0, line is parallel with plane
  p3 inter(Plane p) {return o - d * p.side(o) / (d | p.n);}
  double dist(const Line3d &other) const {
    p3 n = d * other.d;
    if (n == p3(0, 0)) // parallel
      return dist(other.o);
    return fabs((other.o - o) | n);
  }
  p3 closestFromLine(const Line3d &other) const {
    p3 n2 = other.d * (d * other.d);
    return o + d * ((other.o - o) | n2) / (d | n2);
  }
  double angle(const Line3d &other) {
    return d.angle(other.d);
  }
  double angle(const Plane &p) { return PI / 2 - p.n.angle(d); }
};