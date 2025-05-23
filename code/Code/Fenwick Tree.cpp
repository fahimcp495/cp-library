## Range Update Range Sum
ll ft[2][N];
void add(int no, int i, ll x) {
  i++;
  while (i<=n){
    ft[no][i] += x;
    i += i & -i;
  }
}
void radd(int l, int r, ll x){
  add(0, l, x);
  add(0, r+1, -x);
  add(1, l, x*(l-1));
  add(1, r+1, -x*r);
}
ll csumft(int no, int i) {
  i++;
  ll ret = 0;
  while (i>0){
    ret += ft[no][i];
    i -= i & -i;
  }
  return ret;
}
ll csum(int i) {
  return csumft(0, i)*i - csumft(1, i);
}
ll rsum(int l, int r) {
  return csum(r)- csum(l-1);
}
## Binary Search on Prefix Sum
int lb(ll x) {
  int i = 0;
  for (int k = K - 1; k >= 0; --k) {
    int j = i + (1 << k);
    if (j <= n and ft[j] < x) {
      i = j, x -= ft[j];
    }
  }
  return i;
}
