/**
 * Author: Ulf Lundstrom
 * Date: 2009-02-26
 * License: CC0
 * Source: My head with inspiration from tinyKACTL
 * Description: Class to handle points in the plane.
 * 	T can be e.g. double or long long. (Avoid int.)
 * Status: Works fine, used a lot
 */
#pragma once
// sweet spots for eps is 1e-13 to 1e-15 for ld, and 1e-7 to 1e-9 for d
template<class T> inline bool eq(T x, T y) { return fabs(x-y) < eps; }
template<class T> inline bool le(T x, T y) { return x < y + eps; }
template<class T> inline bool lt(T x, T y) { return x + eps < y; }
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
// Ax + By + C = 0 (A = p.y-q.y; B = q.x-p.x; C = -A*P.x-B*P.y)
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	// Same direction means a.b > 0, when perp, a.b = 0
	T dot(P p) const { return x*p.x + y*p.y; } // a.b = |a|.|b|cos(t)
	// b left of a, a^b > 0, ccw sort comparator. When perp a.b = 1
	T cross(P p) const { return x*p.y - y*p.x; } // a^b = |a|.|b|sin(t)
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};
