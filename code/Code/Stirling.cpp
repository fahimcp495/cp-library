/**
 * Description:
 *  \begin{itemize}[noitemsep]
 *    \item Number of permutations of n elements with k disjoint cycles = Str1(n,k) = (n-1) * Str1(n-1,k) + Str1(n-1,k-1).
 *    \item Str1(0,0) = 1
 *    \item $\sum_{k=0}^n c(n,k)x^k = x(x+1) \dots (x+n-1)$
 *    \item $Str1(8,k) = 8, 0, 5040, 13068, 13132, 6769, 1960, 322, 28, 1$ \\
 *    \item $Str1(n,2) = 0, 0, 1, 3, 11, 50, 274, 1764, 13068, 109584, \dots$
 *    \item n! = Sum(Str1(n,k)) (for all 0 <= k <= n).
 *    \item Ways to partition n labelled objects into k unlabelled subsets = Str2(n,k) = k * Str2(n-1,k) + Str2(n-1,k-1).
 *    \item $Str2(n,1) = Str2(n,n) = 1$
 *    \item $Str2(n,k) = \frac{1}{k!}\sum_{j=0}^k (-1)^{k-j}\binom{k}{j}j^n$
 *    \item Parity of Str2(n,k) : ( (n-k) \& Floor((k-1)/2) ) == 0).
 *    \item Ways to partition n labelled objects into k unlabelled subsets, with each subset containing at least r elements: SR(n,k) = k * SR(n-1,k) + C(n-1,r-1) * SR(n-r,k-1).
 *    \item Number of ways to partition n labelled objects 1,2,3, ... n into k non-empty subsets so that for any integers i and j in a given subset |i-j| >= d: Str2(n-d+1, k-d+1), n >= k >= d.
 *    \item Number of ways to color a $1 \times n$ grid using $k$ colors such that each color is used at least once = $ k! . Str2(n,k) $
 *    \item Denote the $n$ objects to partition by the integers $1, 2, \dots, n$. Define the reduced Stirling numbers of the second kind, denoted $S^d(n, k)$, to be the number of ways to partition the integers $1, 2, \dots, n$ into $k$ nonempty subsets such that all elements in each subset have pairwise distance at least $d$. That is, for any integers $i$ and $j$ in a given subset, it is required that $|i - j| \geq d$. It has been shown that these numbers satisfy, $S^d(n, k) = S(n - d + 1, k - d + 1), \quad n \geq k \geq d.$
 *  \end{itemize}
 */

// O(k*log(n))
ll get_sn2(int n, int k) {
  ll sn2 = 0;
  for (int i = 0; i <= k; ++i) {
    ll now = nCr(k, i) * poww(k - i, n, mod) % mod;
    if (i & 1) now = now * (mod - 1) % mod;
    add(sn2, now);
  }
  sn2 = sn2 * ifact[k] % mod;
  return sn2;
}
NTT ntt(mod);
vector<ll> v[MAX];
//Stirling1 (n,k) = co-eff of x^k in x*(x+1)*(x+2)*....(x+n-1)
int Stirling1(int n, int r) {
  int nn = 1;
  while (nn < n) nn <<= 1;

  for (int i = 0; i < n; ++i) {v[i].push_back(i); v[i].push_back(1);}
  for (int i = n; i < nn; ++i) v[i].push_back(1);

  for (int j = nn; j > 1; j >>= 1) {
    int hn = j >> 1;
    for (int i = 0; i < hn; ++i) ntt.multiply(v[i], v[i + hn], v[i]);
  }
  return v[0][r];
}
NTT ntt(mod);
vector<ll> a, b, res;
//Stirling2 (n,k) = co-eff of x^k in product of polynomials A & B
//where A(i) = (-1)^i / i!  and B(i) = i^n / i!
int Stirling2(int n, int r) {
  a.resize(n + 1); b.resize(n + 1);
  for (int i = 0; i <= n; i++) {
    a[i] = invfct[i];
    if (i % 2 == 1) a[i] = mod - a[i];
  }
  for (int i = 0; i <= n; i++) {
    b[i] = bigMod(i, n, mod);
    b[i] = (b[i] * invfct[i]) % mod;
  }
  NTT ntt(mod);
  ntt.multiply(a, b, res);
  return res[r];
}