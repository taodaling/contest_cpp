#include <bits/stdc++.h>

#include <cmath>

using namespace std;
using ll = long long;

static int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

using pll = pair<ll, ll>;
const int P = 998244353;

vector<bool> notp;
vector<int> primes;
void Euler(int n) {
  notp.resize(n + 1);
  auto _ = [&](int i) {
    if (!notp[i]) primes.push_back(i);
    for (auto pj : primes) {
      if (pj > n / i) break;
      notp[i * pj] = true;
      if (i % pj == 0) break;
    }
  };
  _(2), _(3), _(5);
  for (int i = 1; i <= n / 6; i++) {
    _(i * 6 + 1), _(i * 6 + 5);
  }
}

int qpow(int a, int b = P - 2, int m = P) {
  int ret = m != 1;
  for (; b; b >>= 1) {
    if (b & 1) ret = 1ll * ret * a % m;
    a = 1ll * a * a % m;
  }
  return ret;
}

int main() {
  ll n, k;
  cin >> n >> k;

  Euler(max<int>(sqrt(n * 1.0) + 1, k));

  vector<ll> v2(k + 1);
  for (int i = 1; i <= k; i++) {
    v2[i] = n - k + i;
  }

  ll ans = 1;
  for (auto p : primes) {
    int cnt = 0;
    int tk = k;
    while (tk > 0) {
      tk /= p, cnt -= tk;
    }
    for (int i = p - (n - k) % p; i <= k; i += p) {
      while (v2[i] % p == 0) {
        cnt++, v2[i] /= p;
      }
    }
    ans = ans * (cnt + 1) % P;
  }
  int cnt = 0;
  for (auto v2i : v2)
    if (v2i > 1) cnt++;

  cout << ans * qpow(2, cnt) % P;

  return 0;
}