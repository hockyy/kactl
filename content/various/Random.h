/**
 * Author: Hocky Yudhiono
 * Date: 2022-11-23
 * License: CC0
 * Source: me
 * Description: Random using mersenne twister
 * Usage: rng()
 * Status: tested
 */

#include <random>
#include <chrono>
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count()); 
// shuffle(isi.begin(),isi.end(),rng);

LL getRange(LL a, LL b){
   LL ran = b-a+1;
   return (rng()%ran)+a;
}