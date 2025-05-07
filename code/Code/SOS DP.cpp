// f(i, mask) = Sum over subsets of mask which are identical to the mask considering the bits from MSB to the (i + 1)th least significant bit.
## Count Over Subset
// f(i, mask) = f(i - 1, mask)  // ith bit = 0
// f(i, mask) = f(i - 1, mask) + f(i - 1, mask ^ (1 << i)) // ith bit = 1
for (int i = 0; i < K; ++i) {
  for (int mask = MASK - 1; mask >= 0; --mask) {
    if (mask >> i & 1) {
      dp[mask] += dp[mask ^ 1 << i];
    }
  }
}
## Count Over Superset
// f(i, mask) = f(i - 1, mask) + f(i - 1, mask ^ (1 << i)) // ith bit = 0
// f(i, mask) = f(i - 1, mask)  // ith bit = 1
for (int i = 0; i < K; ++i) {
  for (int mask = 0; mask < MASK; ++mask) {
    if (mask >> i & 1 ^ 1) {
      dp[mask] += dp[mask ^ 1 << i];
    }
  }
}
## Count Over Disjoint-set
  - Sum over submask of its complement
## Number of subsequences of with bitwise OR = mask
for (int i = 0; i < K; ++i) {
  for (int mask = MASK - 1; mask >= 0; --mask) {
    if (mask >> i & 1) {
      dp[mask] += dp[mask ^ 1 << i];
    }
  }
}
for (int mask = 0; mask < MASK; ++mask) {
  dp[mask] = two[dp[mask]];
}
for (int i = 0; i < K; ++i) {
  for (int mask = MASK - 1; mask >= 0; --mask) {
    if (mask >> i & 1) {
      sub(dp[mask], dp[mask ^ 1 << i]);
    }
  }
}
// Now, dp[mask] = number of subsequences with OR = mask
## Number of subsequences of with bitwise AND = mask
- Flip the bits, then find number of subsequences with bitwise OR
