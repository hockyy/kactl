/**
 * Author: Simon Lindholm
 * Date: 2016-07-23
 * License: CC0
 * Source: me
 * Description: Given degree of n nodes. Is it possible to build the graph?
 * Status: tested
 */

sort(d+1, d+n+1, greater<int>);
for (i=1;i<=n;i++)
    x[i] = x[i-1] + d[i];
if (x[n]&1) {
    printf("Not possible\n");
    continue;
}
can = true;
for (k=1;k<=n;k++) {
    sum = x[k];
    tmp = k*(k-1);
    for (i=k+1;i<=n;i++)
        tmp += min(d[i], k);
    if (sum > tmp) {
        can = false;
        break;
    }
}
if (can) printf("Possible\n");
else printf("Not possible\n");
