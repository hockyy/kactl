/**
 * Author: Simon Lindholm
 * Date: 2016-07-23
 * License: CC0
 * Source: me
 * Description: Elapsed time from the beginning of running program
 * Usage: cek_time()
 * Status: tested
 */
clock_t first_attempt = clock();
inline void cek_time(){
	clock_t cur = clock()- first_attempt;
	cerr<<"TIME : "<<(double) cur/CLOCKS_PER_SEC<<endl;
      auto current = chrono::high_resolution_clock::now();
      chrono::duration<double> elapsed = current - start;
      // cout << fixed << setprecision(3) << elapsed.count() << "\n";
      if (elapsed.count() < runtime[i].se) continue;
}
