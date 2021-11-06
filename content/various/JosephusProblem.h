/**
 * Author: Simon Lindholm
 * Date: 2016-07-23
 * License: CC0
 * Source: me
 * Description: There are n person in a table waiting to be executed. 
 * Person 1 hold a knife. Each step whoever has the knife, kill the person next to him.
 * Who's alive at the end?
 * Status: tested
 */

int x = 0;
for (int i = 2; i <= n; ++i)
	x = (x + i) % i;
	
int josephus(int n, int k) {
    if (n == 1) return 0;
    if (k == 1) return n-1;
    if (k > n) return (josephus(n-1, k) + k) % n;
    int cnt = n / k, res = josephus(n - cnt, k) - (n % k);
    res += (res < 0 ? n : (res / (k - 1)));
    return res;
}
