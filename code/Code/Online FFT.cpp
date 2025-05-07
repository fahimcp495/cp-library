/**
 * Description: $ a_1, a_2, ..., a_{n - 1}$ and $b_0$ are given, find $b_1, b_2, ..., b_{n - 1}$, where $b_i = \sum_{j = 1}^{i} a_j \cdot b_{i - j}$
 * Time: $O(n \log n^2) $
 */
for (int i = 1; i < n; ++i) {
  for (int p = 1; (i & (p - 1)) == 0; p <<= 1) {
    vector<int> aa(a + p, a + min(p << 1, n));
    vector<int> bb(b + i - p, b + i);
    auto c = mul(aa, bb);
    for (int j = 0; j < c.size(); ++j) {
      if (i + j >= n)  break;
      add(b[i + j], c[j]);
    }
  }
}