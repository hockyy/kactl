/**
 * Author: Hocky Yudhiono
 * Date: 2017-05-11
 * License: CC0
 * Source: folklore
 * Description: Offline solve 2d commutative query
 * This query is exclusive 1-based, change to [st, ed). Reduce to 0-based indexing!
 * Time: $O(N \log^2 N)$, query in $O(1)$
 * Status: tested
 */
#pragma once
const int LOGN = 13;
int sparset[LOGN][LOGN][205][205];
rep(i,0,n) rep(j,0,m) cin >> sparset[0][0][i][j];
rep(i,0,n) rep(logj,1,LOGN) rep(j,0,m-(1<<logj)+1)
  sparset[0][logj][i][j] = min(sparset[0][logj-1][i][j],
  	sparset[0][logj-1][i][j+(1<<(logj-1))]);
rep(logi, 1, LOGN) rep(logj, 0, LOGN)
	rep(i,0,n-(1<<logi)+1)
	rep(j,0,m-(1<<logj)+1)
  	sparset[logi][logj][i][j] = min(sparset[logi-1][logj][i][j],
  		sparset[logi-1][logj][i+(1<<(logi-1))][j]);
cin >> st.fi >> st.se >> ed.fi >> ed.se; st.fi--; st.se--;
int lenrow = 31-__builtin_clz(ed.fi-st.fi);
int lencol = 31-__builtin_clz(ed.se-st.se);
res1 = min(min(min(sparset[lenrow][lencol][st.fi][st.se],
sparset[lenrow][lencol][st.fi][ed.se-(1<<lencol)]),
sparset[lenrow][lencol][ed.fi-(1<<lenrow)][st.se]),
sparset[lenrow][lencol][ed.fi-(1<<lenrow)][ed.se-(1<<lencol)]);