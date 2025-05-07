/**
 * Description:
 * \begin{itemize}[noitemsep]
 *    \item $\mathrm{dp}[i][j] = \min_{k<j}\{\mathrm{dp}[i-1][k] + C[k][j]\}$
 *    \item $A[i][j] \leq A[i][j+1]$
 *    \item $O(kn^2)$ to $O(kn\log{n})$
 *    \item sufficient: $C[a][c] + C[b][d] \leq C[a][d] + C[b][c]$, $a\leq b\leq c\leq d$ (QI)
 * \end{itemize}
 */

// Divide an array into k parts
// Minimize the sum of squre of each subarray
ll pref[N], dp[N][N];
void compute(int l, int r, int j, int kl, int kr) {
  if (l > r)  return ;
  int m = (l + r) / 2;
  array<ll, 2> best = {LLONG_MAX, -1};
  for (int k = kl; k <= min(m - 1, kr); ++k) {
    best = min(best, {dp[k][j - 1] + (pref[m] - pref[k]) * (pref[m] - pref[k]), k});
  }
  dp[m][j] = best[0];
  compute(l, m - 1, j, kl, best[1]);
  compute(m + 1, r, j, best[1], kr);
}