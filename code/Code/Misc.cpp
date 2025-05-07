## Build Command
g++ -std=c++17 -Wshadow -Wall -o t t.cpp -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG && ./t <in> out

## Pragmas
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("O3,unroll-loops,Ofast,fast-math")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC target("avx2", "popcnt")
## bitset
BS._Find_first()
BS._Find_next(x) //Return first set bit after xth bit, x on failure
## Gray Code, G(0) = 000, G(1) = 001, G(2) = 011, G(3) = 010
inline int g(int n) { return n ^ (n >> 1); }
## Inverse Gray Code
int rev_g(int g) {
  int n = 0;
  for ( ; g; g >>= 1) n ^= g;
  return n;
}
## Only for non-negative integers
## Returns the immediate next number with same count of one bits, -1 on failure
long long hakmemItem175(long long n) {
  if (!n) return -1;
  long long x = (n & -n);
  long long left = (x + n);
  long long right = ((n ^ left) / x) >> 2;
  long long res = (left | right);
  return res;
}
## Returns the immediate previous number with same count of one bits, -1 on failure
long long lol(long long n) {
  if (n < 2) return -1;
  long long res = ~hakmemItem175(~n);
  return (!res) ? -1 : res;
}
int __builtin_clz(int x);// number of leading zero
int __builtin_ctz(int x);// number of trailing zero
int __builtin_clzll(long long x);// number of leading zero
int __builtin_ctzll(long long x);// number of trailing zero
int __builtin_popcount(int x);// number of 1-bits in x
int __builtin_popcountll(long long x);// number of 1-bits in x
lsb(n): (n & -n); // last bit (smallest)
floor(log2(n)): 31 - __builtin_clz(n | 1);
floor(log2(n)): 63 - __builtin_clzll(n | 1);
## compute next perm. ex) 00111, 01011, 01101, 01110, 10011, 10101..
long long next_perm(long long v){
  long long t = v | (v-1);
  return (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(v) + 1));
}
## Next Combination Mask
int next_combs_mask(int mask) {
  int lsb = -mask & mask;
  return (((mask + lsb) ^ mask) / (lsb << 2)) | (mask + lsb);
}
## Iterate over submask in decreasing order
for (int s=mask; s > 0; s = (s-1)&mask) {}
## GNU Pbds
#include <ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T> using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename R> using omap = tree<T, R, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
## unordered_map
struct chash{
  size_t operator()(const pair<int,int>&x)const{
    return hash<long long>()(((long long)x.first)^(((long long)x.second)<<32));
  }
};
struct chash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};
gp_hash_table<ii, int, chash> cnt;
## set custom operator
struct comp {
  bool operator()(const int& a, const int& b) const {
    return a < b;
  }
};
set<int, comp> st;
priority_queue<int, vector<int>, comp> pq;
## Random Number
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int x = rng() % 495;
## Running time
clock_t st = clock();
double t = (clock() - st) / (1.0 * CLOCKS_PER_SEC);
string line;  getline(cin, line);
istringstream iss(line);
string word;
while (iss >> word) {
  cout << word << "\n";
}
merge(t[v].begin(), t[v].end(), t[w].begin(), t[w].end(), back_inserter(t[u]));
ulimit -s 65532
## Rollback
vector<pair<int*, int>> cng[N];
cng[i].push_back({&x, x});
for (auto [x, y]: cng[i]) {
  *x = y;
}
