/**
 * Author: Hocky Yudhiono
 * Date: 2020-03-09
 * License: CC0
 * Source: own work
 * Description: Stab the polygon isi, with line a, b, find the longest segment with valid stab
 * Time: O(N^2 \log N)
 * Status: tested
 */

#include "Point.h"

typedef pair<P, PII> Intersect;
pair<LD, P> rayCast(P a, P b, const vector <P> &isi){
	vector <Intersect> inter; int n = sz(isi);
	rep(i,0,n){
		auto &nx = isi[i+1 == n ? 0 : i + 1];
		auto res = lineInter(a, b, isi[i], nx);
		if(res.fi == 1 && eq(segDist2(isi[i], nx, res.se), (LD)0.0)) {
			inter.pb({res.se, {a.ccw(b, isi[i]), a.ccw(b, nx)}});
		}
	}
	auto vec = b - a;
	
	// Uncomment this to stop at b
	// inter.pb({b, {0,0}});
	sort(all(inter), [&](const Intersect&aa, const Intersect&bb){
		return lt(vec.dot(aa.fi - a), vec.dot(bb.fi - a));
	});
	int furthest = 0; int pre, inside = -1; // set inside=1 if strictly inside
	rep(i,0,sz(inter)){
		// If a is strictly inside polygon, you can uncomment this
		//~ if(vec.dot(inter[i].fi - a) < 0) continue;
		if(inside >= 0) { furthest = i - 1;/* inter[i].fi, isi[i - 1].fi is an active segment */}
		if(inter[i].se.fi * inter[i].se.se == -1) inside = -inside;
		else if(inside == 0) inside = (inter[i].se.fi+inter[i].se.se) * pre;
		else {
			pre = (inter[i].se.fi + inter[i].se.se) * inside;
			inside = 0;
		}
		// do operations here, inside == 0 means parallel to segment
		//~ if(inside == -1) {}
		// Uncomment this to stop at b;
		// if(inter[i].fi == b) return {(inter[i].fi - inter[furthest].fi).dist2(), b};
		if(inside == -1) furthest = i + 1;
	}
	return {0, b};
}
