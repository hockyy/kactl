/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Spheres utility function
 * Status: untested
 */

#pragma once
#include "Point3D.h"
constexpr p3 zero(0, 0, 0);

p3 sph(double r, double lat, double lon) {
  lat *= M_PI / 180, lon *= M_PI / 180;
  return {r * cos(lat)*cos(lon), r * cos(lat)*sin(lon), r * sin(lat)};
}
int sphereLine(p3 o, double r, Line3d l, pair<p3, p3> &out) {
  double h2 = r * r - l.dist2(o);
  if (h2 < 0) return 0;
  p3 p = l.proj(o);
  p3 h = l.d * sqrt(h2) / (l.d).dist();
  out = {p - h, p + h};
  return 1 + (h2 > 0);
}
double greatCircleDist(p3 o, double r, p3 a, p3 b) {
  return r * (a - o).angle(b - o);
}
bool validSegment(p3 a, p3 b) {
  return !(a * b == zero) || (a | b) > 0;
}

bool properInter(p3 a, p3 b, p3 c, p3 d, p3 &out) {
  p3 ab = a * b, cd = c * d; // normals of planes OAB and OCD
  int oa = sgn(cd | a), ob = sgn(cd | b), oc = sgn(ab | c), od = sgn(ab | d);
  out = ab * cd * od;
  return (oa != ob && oc != od && oa != oc);
}

bool onSphSegment(p3 a, p3 b, p3 p) {
  p3 n = a * b;
  if (n == zero)
    return a * p == zero && (a | p) > 0;
  return (n | p) == 0 && (n | a * p) >= 0 && (n | b * p) <= 0;
}

struct directionSet : vector<p3> {
  using vector::vector; // import constructors
  void insert(p3 p) {
    for (p3 q : *this) if (p * q == zero) return;
    push_back(p);
  }
};
directionSet intersSph(p3 a, p3 b, p3 c, p3 d) {
  assert(validSegment(a, b) && validSegment(c, d));
  p3 out;
  if (properInter(a, b, c, d, out)) return {out};
  directionSet s;
  if (onSphSegment(c, d, a)) s.insert(a);
  if (onSphSegment(c, d, b)) s.insert(b);
  if (onSphSegment(a, b, c)) s.insert(c);
  if (onSphSegment(a, b, d)) s.insert(d);
  return s;
}
double angleSph(p3 a, p3 b, p3 c) {
  return (a * b).angle(a * c);
}
double orientedAngleSph(p3 a, p3 b, p3 c) {
  if ((a * b | c) >= 0)
    return angleSph(a, b, c);
  else
    return 2 * M_PI - angleSph(a, b, c);
}
double areaOnSphere(double r, vector<p3> p) {
  int n = p.size();
  double sum = -(n - 2) * M_PI;
  for (int i = 0; i < n; i++)
    sum += orientedAngleSph(p[(i + 1) % n], p[(i + 2) % n], p[i]);
  return r * r * sum;
}

int windingNumber3D(vector<vector<p3>> fs) {
  double sum = 0;
  for (vector<p3> f : fs)
    sum += remainder(areaOnSphere(1, f), 4 * M_PI);
  return round(sum / (4 * M_PI));
}
