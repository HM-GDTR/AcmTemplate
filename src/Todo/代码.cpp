/**
 * date   : 2023-08-18 17:59:47
 * author : Nyaan
 */

#define NDEBUG

using namespace std;

// intrinstic
#include <immintrin.h>

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cfenv>
#include <cfloat>
#include <chrono>
#include <cinttypes>
#include <climits>
#include <cmath>
#include <complex>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fstream>
#include <functional>
#include <initializer_list>
#include <iomanip>
#include <ios>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <streambuf>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// utility

namespace Nyaan {
using ll = long long;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;
using u128 = __uint128_t;

template <typename T>
using V = vector<T>;
template <typename T>
using VV = vector<vector<T>>;
using vi = vector<int>;
using vl = vector<long long>;
using vd = V<double>;
using vs = V<string>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<long long>>;
template <typename T>
using minpq = priority_queue<T, vector<T>, greater<T>>;

template <typename T, typename U>
struct P : pair<T, U> {
  template <typename... Args>
  P(Args... args) : pair<T, U>(args...) {}

  using pair<T, U>::first;
  using pair<T, U>::second;

  P &operator+=(const P &r) {
    first += r.first;
    second += r.second;
    return *this;
  }
  P &operator-=(const P &r) {
    first -= r.first;
    second -= r.second;
    return *this;
  }
  P &operator*=(const P &r) {
    first *= r.first;
    second *= r.second;
    return *this;
  }
  template <typename S>
  P &operator*=(const S &r) {
    first *= r, second *= r;
    return *this;
  }
  P operator+(const P &r) const { return P(*this) += r; }
  P operator-(const P &r) const { return P(*this) -= r; }
  P operator*(const P &r) const { return P(*this) *= r; }
  template <typename S>
  P operator*(const S &r) const {
    return P(*this) *= r;
  }
  P operator-() const { return P{-first, -second}; }
};

using pl = P<ll, ll>;
using pi = P<int, int>;
using vp = V<pl>;

constexpr int inf = 1001001001;
constexpr long long infLL = 4004004004004004004LL;

template <typename T>
int sz(const T &t) {
  return t.size();
}

template <typename T, typename U>
inline bool amin(T &x, U y) {
  return (y < x) ? (x = y, true) : false;
}
template <typename T, typename U>
inline bool amax(T &x, U y) {
  return (x < y) ? (x = y, true) : false;
}

template <typename T>
inline T Max(const vector<T> &v) {
  return *max_element(begin(v), end(v));
}
template <typename T>
inline T Min(const vector<T> &v) {
  return *min_element(begin(v), end(v));
}
template <typename T>
inline long long Sum(const vector<T> &v) {
  return accumulate(begin(v), end(v), 0LL);
}

template <typename T>
int lb(const vector<T> &v, const T &a) {
  return lower_bound(begin(v), end(v), a) - begin(v);
}
template <typename T>
int ub(const vector<T> &v, const T &a) {
  return upper_bound(begin(v), end(v), a) - begin(v);
}

constexpr long long TEN(int n) {
  long long ret = 1, x = 10;
  for (; n; x *= x, n >>= 1) ret *= (n & 1 ? x : 1);
  return ret;
}

template <typename T, typename U>
pair<T, U> mkp(const T &t, const U &u) {
  return make_pair(t, u);
}

template <typename T>
vector<T> mkrui(const vector<T> &v, bool rev = false) {
  vector<T> ret(v.size() + 1);
  if (rev) {
    for (int i = int(v.size()) - 1; i >= 0; i--) ret[i] = v[i] + ret[i + 1];
  } else {
    for (int i = 0; i < int(v.size()); i++) ret[i + 1] = ret[i] + v[i];
  }
  return ret;
};

template <typename T>
vector<T> mkuni(const vector<T> &v) {
  vector<T> ret(v);
  sort(ret.begin(), ret.end());
  ret.erase(unique(ret.begin(), ret.end()), ret.end());
  return ret;
}

template <typename F>
vector<int> mkord(int N, F f) {
  vector<int> ord(N);
  iota(begin(ord), end(ord), 0);
  sort(begin(ord), end(ord), f);
  return ord;
}

template <typename T>
vector<int> mkinv(vector<T> &v) {
  int max_val = *max_element(begin(v), end(v));
  vector<int> inv(max_val + 1, -1);
  for (int i = 0; i < (int)v.size(); i++) inv[v[i]] = i;
  return inv;
}

vector<int> mkiota(int n) {
  vector<int> ret(n);
  iota(begin(ret), end(ret), 0);
  return ret;
}

template <typename T>
T mkrev(const T &v) {
  T w{v};
  reverse(begin(w), end(w));
  return w;
}

template <typename T>
bool nxp(vector<T> &v) {
  return next_permutation(begin(v), end(v));
}

// 返り値の型は入力の T に依存
// i 要素目 : [0, a[i])
template <typename T>
vector<vector<T>> product(const vector<T> &a) {
  vector<vector<T>> ret;
  vector<T> v;
  auto dfs = [&](auto rc, int i) -> void {
    if (i == (int)a.size()) {
      ret.push_back(v);
      return;
    }
    for (int j = 0; j < a[i]; j++) v.push_back(j), rc(rc, i + 1), v.pop_back();
  };
  dfs(dfs, 0);
  return ret;
}

// F : function(void(T&)), mod を取る操作
// T : 整数型のときはオーバーフローに注意する
template <typename T>
T Power(T a, long long n, const T &I, const function<void(T &)> &f) {
  T res = I;
  for (; n; f(a = a * a), n >>= 1) {
    if (n & 1) f(res = res * a);
  }
  return res;
}
// T : 整数型のときはオーバーフローに注意する
template <typename T>
T Power(T a, long long n, const T &I) {
  return Power(a, n, I, function<void(T &)>{[](T &) -> void {}});
}

}  // namespace Nyaan


// bit operation

namespace Nyaan {
__attribute__((target("popcnt"))) inline int popcnt(const u64 &a) {
  return _mm_popcnt_u64(a);
}
inline int lsb(const u64 &a) { return a ? __builtin_ctzll(a) : 64; }
inline int ctz(const u64 &a) { return a ? __builtin_ctzll(a) : 64; }
inline int msb(const u64 &a) { return a ? 63 - __builtin_clzll(a) : -1; }
template <typename T>
inline int gbit(const T &a, int i) {
  return (a >> i) & 1;
}
template <typename T>
inline void sbit(T &a, int i, bool b) {
  if (gbit(a, i) != b) a ^= T(1) << i;
}
constexpr long long PW(int n) { return 1LL << n; }
constexpr long long MSK(int n) { return (1LL << n) - 1; }
}  // namespace Nyaan


// inout

namespace Nyaan {

template <typename T, typename U>
ostream &operator<<(ostream &os, const pair<T, U> &p) {
  os << p.first << " " << p.second;
  return os;
}
template <typename T, typename U>
istream &operator>>(istream &is, pair<T, U> &p) {
  is >> p.first >> p.second;
  return is;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v) {
  int s = (int)v.size();
  for (int i = 0; i < s; i++) os << (i ? " " : "") << v[i];
  return os;
}
template <typename T>
istream &operator>>(istream &is, vector<T> &v) {
  for (auto &x : v) is >> x;
  return is;
}

istream &operator>>(istream &is, __int128_t &x) {
  string S;
  is >> S;
  x = 0;
  int flag = 0;
  for (auto &c : S) {
    if (c == '-') {
      flag = true;
      continue;
    }
    x *= 10;
    x += c - '0';
  }
  if (flag) x = -x;
  return is;
}

istream &operator>>(istream &is, __uint128_t &x) {
  string S;
  is >> S;
  x = 0;
  for (auto &c : S) {
    x *= 10;
    x += c - '0';
  }
  return is;
}

ostream &operator<<(ostream &os, __int128_t x) {
  if (x == 0) return os << 0;
  if (x < 0) os << '-', x = -x;
  string S;
  while (x) S.push_back('0' + x % 10), x /= 10;
  reverse(begin(S), end(S));
  return os << S;
}
ostream &operator<<(ostream &os, __uint128_t x) {
  if (x == 0) return os << 0;
  string S;
  while (x) S.push_back('0' + x % 10), x /= 10;
  reverse(begin(S), end(S));
  return os << S;
}

void in() {}
template <typename T, class... U>
void in(T &t, U &...u) {
  cin >> t;
  in(u...);
}

void out() { cout << "\n"; }
template <typename T, class... U, char sep = ' '>
void out(const T &t, const U &...u) {
  cout << t;
  if (sizeof...(u)) cout << sep;
  out(u...);
}

struct IoSetupNya {
  IoSetupNya() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);
    cerr << fixed << setprecision(7);
  }
} iosetupnya;

}  // namespace Nyaan


// debug


#ifdef NyaanDebug
#define trc(...) (void(0))
#else
#define trc(...) (void(0))
#endif

#ifdef NyaanLocal
#define trc2(...) (void(0))
#else
#define trc2(...) (void(0))
#endif


// macro

#define each(x, v) for (auto&& x : v)
#define each2(x, y, v) for (auto&& [x, y] : v)
#define all(v) (v).begin(), (v).end()
#define rep(i, N) for (long long i = 0; i < (long long)(N); i++)
#define repr(i, N) for (long long i = (long long)(N)-1; i >= 0; i--)
#define rep1(i, N) for (long long i = 1; i <= (long long)(N); i++)
#define repr1(i, N) for (long long i = (N); (long long)(i) > 0; i--)
#define reg(i, a, b) for (long long i = (a); i < (b); i++)
#define regr(i, a, b) for (long long i = (b)-1; i >= (a); i--)
#define fi first
#define se second
#define ini(...)   \
  int __VA_ARGS__; \
  in(__VA_ARGS__)
#define inl(...)         \
  long long __VA_ARGS__; \
  in(__VA_ARGS__)
#define ins(...)      \
  string __VA_ARGS__; \
  in(__VA_ARGS__)
#define in2(s, t)                           \
  for (int i = 0; i < (int)s.size(); i++) { \
    in(s[i], t[i]);                         \
  }
#define in3(s, t, u)                        \
  for (int i = 0; i < (int)s.size(); i++) { \
    in(s[i], t[i], u[i]);                   \
  }
#define in4(s, t, u, v)                     \
  for (int i = 0; i < (int)s.size(); i++) { \
    in(s[i], t[i], u[i], v[i]);             \
  }
#define die(...)             \
  do {                       \
    Nyaan::out(__VA_ARGS__); \
    return;                  \
  } while (0)


namespace Nyaan {
void solve();
}
int main() { Nyaan::solve(); }


//



using namespace std;

// コンストラクタの MAX に 「C(n, r) や fac(n) でクエリを投げる最大の n 」
// を入れると倍速くらいになる
// mod を超えて前計算して 0 割りを踏むバグは対策済み
template <typename T>
struct Binomial {
  vector<T> f, g, h;
  Binomial(int MAX = 0) {
    assert(T::get_mod() != 0 && "Binomial<mint>()");
    f.resize(1, T{1});
    g.resize(1, T{1});
    h.resize(1, T{1});
    if (MAX > 0) extend(MAX + 1);
  }

  void extend(int m = -1) {
    int n = f.size();
    if (m == -1) m = n * 2;
    m = min<int>(m, T::get_mod());
    if (n >= m) return;
    f.resize(m);
    g.resize(m);
    h.resize(m);
    for (int i = n; i < m; i++) f[i] = f[i - 1] * T(i);
    g[m - 1] = f[m - 1].inverse();
    h[m - 1] = g[m - 1] * f[m - 2];
    for (int i = m - 2; i >= n; i--) {
      g[i] = g[i + 1] * T(i + 1);
      h[i] = g[i] * f[i - 1];
    }
  }

  T fac(int i) {
    if (i < 0) return T(0);
    while (i >= (int)f.size()) extend();
    return f[i];
  }

  T finv(int i) {
    if (i < 0) return T(0);
    while (i >= (int)g.size()) extend();
    return g[i];
  }

  T inv(int i) {
    if (i < 0) return -inv(-i);
    while (i >= (int)h.size()) extend();
    return h[i];
  }

  T C(int n, int r) {
    if (n < 0 || n < r || r < 0) return T(0);
    return fac(n) * finv(n - r) * finv(r);
  }

  inline T operator()(int n, int r) { return C(n, r); }

  template <typename I>
  T multinomial(const vector<I>& r) {
    static_assert(is_integral<I>::value == true);
    int n = 0;
    for (auto& x : r) {
      if (x < 0) return T(0);
      n += x;
    }
    T res = fac(n);
    for (auto& x : r) res *= finv(x);
    return res;
  }

  template <typename I>
  T operator()(const vector<I>& r) {
    return multinomial(r);
  }

  T C_naive(int n, int r) {
    if (n < 0 || n < r || r < 0) return T(0);
    T ret = T(1);
    r = min(r, n - r);
    for (int i = 1; i <= r; ++i) ret *= inv(i) * (n--);
    return ret;
  }

  T P(int n, int r) {
    if (n < 0 || n < r || r < 0) return T(0);
    return fac(n) * finv(n - r);
  }

  // [x^r] 1 / (1-x)^n
  T H(int n, int r) {
    if (n < 0 || r < 0) return T(0);
    return r == 0 ? 1 : C(n + r - 1, r);
  }
};


template <typename mint>
struct FormalPowerSeries : vector<mint> {
  using vector<mint>::vector;
  using FPS = FormalPowerSeries;

  FPS &operator+=(const FPS &r) {
    if (r.size() > this->size()) this->resize(r.size());
    for (int i = 0; i < (int)r.size(); i++) (*this)[i] += r[i];
    return *this;
  }

  FPS &operator+=(const mint &r) {
    if (this->empty()) this->resize(1);
    (*this)[0] += r;
    return *this;
  }

  FPS &operator-=(const FPS &r) {
    if (r.size() > this->size()) this->resize(r.size());
    for (int i = 0; i < (int)r.size(); i++) (*this)[i] -= r[i];
    return *this;
  }

  FPS &operator-=(const mint &r) {
    if (this->empty()) this->resize(1);
    (*this)[0] -= r;
    return *this;
  }

  FPS &operator*=(const mint &v) {
    for (int k = 0; k < (int)this->size(); k++) (*this)[k] *= v;
    return *this;
  }

  FPS &operator/=(const FPS &r) {
    if (this->size() < r.size()) {
      this->clear();
      return *this;
    }
    int n = this->size() - r.size() + 1;
    if ((int)r.size() <= 64) {
      FPS f(*this), g(r);
      g.shrink();
      mint coeff = g.back().inverse();
      for (auto &x : g) x *= coeff;
      int deg = (int)f.size() - (int)g.size() + 1;
      int gs = g.size();
      FPS quo(deg);
      for (int i = deg - 1; i >= 0; i--) {
        quo[i] = f[i + gs - 1];
        for (int j = 0; j < gs; j++) f[i + j] -= quo[i] * g[j];
      }
      *this = quo * coeff;
      this->resize(n, mint(0));
      return *this;
    }
    return *this = ((*this).rev().pre(n) * r.rev().inv(n)).pre(n).rev();
  }

  FPS &operator%=(const FPS &r) {
    *this -= *this / r * r;
    shrink();
    return *this;
  }

  FPS operator+(const FPS &r) const { return FPS(*this) += r; }
  FPS operator+(const mint &v) const { return FPS(*this) += v; }
  FPS operator-(const FPS &r) const { return FPS(*this) -= r; }
  FPS operator-(const mint &v) const { return FPS(*this) -= v; }
  FPS operator*(const FPS &r) const { return FPS(*this) *= r; }
  FPS operator*(const mint &v) const { return FPS(*this) *= v; }
  FPS operator/(const FPS &r) const { return FPS(*this) /= r; }
  FPS operator%(const FPS &r) const { return FPS(*this) %= r; }
  FPS operator-() const {
    FPS ret(this->size());
    for (int i = 0; i < (int)this->size(); i++) ret[i] = -(*this)[i];
    return ret;
  }

  void shrink() {
    while (this->size() && this->back() == mint(0)) this->pop_back();
  }

  FPS rev() const {
    FPS ret(*this);
    reverse(begin(ret), end(ret));
    return ret;
  }

  FPS dot(FPS r) const {
    FPS ret(min(this->size(), r.size()));
    for (int i = 0; i < (int)ret.size(); i++) ret[i] = (*this)[i] * r[i];
    return ret;
  }

  FPS pre(int sz) const {
    return FPS(begin(*this), begin(*this) + min((int)this->size(), sz));
  }

  FPS operator>>(int sz) const {
    if ((int)this->size() <= sz) return {};
    FPS ret(*this);
    ret.erase(ret.begin(), ret.begin() + sz);
    return ret;
  }

  FPS operator<<(int sz) const {
    FPS ret(*this);
    ret.insert(ret.begin(), sz, mint(0));
    return ret;
  }

  FPS diff() const {
    const int n = (int)this->size();
    FPS ret(max(0, n - 1));
    mint one(1), coeff(1);
    for (int i = 1; i < n; i++) {
      ret[i - 1] = (*this)[i] * coeff;
      coeff += one;
    }
    return ret;
  }

  FPS integral() const {
    const int n = (int)this->size();
    FPS ret(n + 1);
    ret[0] = mint(0);
    if (n > 0) ret[1] = mint(1);
    auto mod = mint::get_mod();
    for (int i = 2; i <= n; i++) ret[i] = (-ret[mod % i]) * (mod / i);
    for (int i = 0; i < n; i++) ret[i + 1] *= (*this)[i];
    return ret;
  }

  mint eval(mint x) const {
    mint r = 0, w = 1;
    for (auto &v : *this) r += w * v, w *= x;
    return r;
  }

  FPS log(int deg = -1) const {
    assert((*this)[0] == mint(1));
    if (deg == -1) deg = (int)this->size();
    return (this->diff() * this->inv(deg)).pre(deg - 1).integral();
  }

  FPS pow(int64_t k, int deg = -1) const {
    const int n = (int)this->size();
    if (deg == -1) deg = n;
    if (k == 0) {
      FPS ret(deg);
      if (deg) ret[0] = 1;
      return ret;
    }
    for (int i = 0; i < n; i++) {
      if ((*this)[i] != mint(0)) {
        mint rev = mint(1) / (*this)[i];
        FPS ret = (((*this * rev) >> i).log(deg) * k).exp(deg);
        ret *= (*this)[i].pow(k);
        ret = (ret << (i * k)).pre(deg);
        if ((int)ret.size() < deg) ret.resize(deg, mint(0));
        return ret;
      }
      if (__int128_t(i + 1) * k >= deg) return FPS(deg, mint(0));
    }
    return FPS(deg, mint(0));
  }

  static void *ntt_ptr;
  static void set_fft();
  FPS &operator*=(const FPS &r);
  void ntt();
  void intt();
  void ntt_doubling();
  static int ntt_pr();
  FPS inv(int deg = -1) const;
  FPS exp(int deg = -1) const;
};
template <typename mint>
void *FormalPowerSeries<mint>::ntt_ptr = nullptr;

/**
 * @brief 多項式/形式的冪級数ライブラリ
 * @docs docs/fps/formal-power-series.md
 */


template <typename mint>
FormalPowerSeries<mint> Pi(vector<FormalPowerSeries<mint>> v) {
  using fps = FormalPowerSeries<mint>;
  if ((int)v.size() == 0) return fps{mint(1)};
  sort(begin(v), end(v), [](fps& a, fps& b) { return a.size() < b.size(); });
  queue<fps> q;
  for (auto& f : v) q.push(f);
  while ((int)q.size() > 1) {
    fps a = q.front();
    q.pop();
    fps b = q.front();
    q.pop();
    q.push(a * b);
  }
  return q.front();
}

template <typename mint>
void OGFtoEGF(FormalPowerSeries<mint>& f, Binomial<mint>& C) {
  for (int i = 0; i < (int)f.size(); i++) f[i] *= C.finv(i);
}

template <typename mint>
void EGFtoOGF(FormalPowerSeries<mint>& f, Binomial<mint>& C) {
  for (int i = 0; i < (int)f.size(); i++) f[i] *= C.fac(i);
}

template <typename mint>
FormalPowerSeries<mint> e_x(int deg, Binomial<mint>& C) {
  while ((int)C.g.size() < deg) C.extend();
  FormalPowerSeries<mint> ret{begin(C.g), begin(C.g) + deg};
  return ret;
}

// f *= (1 + c x^n)
template <typename mint>
void sparse_mul(FormalPowerSeries<mint>& f, int n, mint c, int expand = true) {
  if (expand) f.resize(f.size() + n);
  for (int i = (int)f.size() - 1; i >= 0; --i) {
    if (i - n >= 0) f[i] += f[i - n] * c;
  }
}

// f /= (1 + c x^n)
template <typename mint>
void sparse_div(FormalPowerSeries<mint>& f, int n, mint c) {
  for (int i = 0; i < (int)f.size(); ++i) {
    if (i + n < (int)f.size()) f[i + n] -= f[i] * c;
  }
}


//




template <uint32_t mod>
struct LazyMontgomeryModInt {
  using mint = LazyMontgomeryModInt;
  using i32 = int32_t;
  using u32 = uint32_t;
  using u64 = uint64_t;

  static constexpr u32 get_r() {
    u32 ret = mod;
    for (i32 i = 0; i < 4; ++i) ret *= 2 - mod * ret;
    return ret;
  }

  static constexpr u32 r = get_r();
  static constexpr u32 n2 = -u64(mod) % mod;
  static_assert(mod < (1 << 30), "invalid, mod >= 2 ^ 30");
  static_assert((mod & 1) == 1, "invalid, mod % 2 == 0");
  static_assert(r * mod == 1, "this code has bugs.");

  u32 a;

  constexpr LazyMontgomeryModInt() : a(0) {}
  constexpr LazyMontgomeryModInt(const int64_t &b)
      : a(reduce(u64(b % mod + mod) * n2)){};

  static constexpr u32 reduce(const u64 &b) {
    return (b + u64(u32(b) * u32(-r)) * mod) >> 32;
  }

  constexpr mint &operator+=(const mint &b) {
    if (i32(a += b.a - 2 * mod) < 0) a += 2 * mod;
    return *this;
  }

  constexpr mint &operator-=(const mint &b) {
    if (i32(a -= b.a) < 0) a += 2 * mod;
    return *this;
  }

  constexpr mint &operator*=(const mint &b) {
    a = reduce(u64(a) * b.a);
    return *this;
  }

  constexpr mint &operator/=(const mint &b) {
    *this *= b.inverse();
    return *this;
  }

  constexpr mint operator+(const mint &b) const { return mint(*this) += b; }
  constexpr mint operator-(const mint &b) const { return mint(*this) -= b; }
  constexpr mint operator*(const mint &b) const { return mint(*this) *= b; }
  constexpr mint operator/(const mint &b) const { return mint(*this) /= b; }
  constexpr bool operator==(const mint &b) const {
    return (a >= mod ? a - mod : a) == (b.a >= mod ? b.a - mod : b.a);
  }
  constexpr bool operator!=(const mint &b) const {
    return (a >= mod ? a - mod : a) != (b.a >= mod ? b.a - mod : b.a);
  }
  constexpr mint operator-() const { return mint() - mint(*this); }
  constexpr mint operator+() const { return mint(*this); }

  constexpr mint pow(u64 n) const {
    mint ret(1), mul(*this);
    while (n > 0) {
      if (n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }

  constexpr mint inverse() const {
    int x = get(), y = mod, u = 1, v = 0, t = 0, tmp = 0;
    while (y > 0) {
      t = x / y;
      x -= t * y, u -= t * v;
      tmp = x, x = y, y = tmp;
      tmp = u, u = v, v = tmp;
    }
    return mint{u};
  }

  friend ostream &operator<<(ostream &os, const mint &b) {
    return os << b.get();
  }

  friend istream &operator>>(istream &is, mint &b) {
    int64_t t;
    is >> t;
    b = LazyMontgomeryModInt<mod>(t);
    return (is);
  }

  constexpr u32 get() const {
    u32 ret = reduce(a);
    return ret >= mod ? ret - mod : ret;
  }

  static constexpr u32 get_mod() { return mod; }
};








__attribute__((target("sse4.2"))) inline __m128i my128_mullo_epu32(
    const __m128i &a, const __m128i &b) {
  return _mm_mullo_epi32(a, b);
}

__attribute__((target("sse4.2"))) inline __m128i my128_mulhi_epu32(
    const __m128i &a, const __m128i &b) {
  __m128i a13 = _mm_shuffle_epi32(a, 0xF5);
  __m128i b13 = _mm_shuffle_epi32(b, 0xF5);
  __m128i prod02 = _mm_mul_epu32(a, b);
  __m128i prod13 = _mm_mul_epu32(a13, b13);
  __m128i prod = _mm_unpackhi_epi64(_mm_unpacklo_epi32(prod02, prod13),
                                    _mm_unpackhi_epi32(prod02, prod13));
  return prod;
}

__attribute__((target("sse4.2"))) inline __m128i montgomery_mul_128(
    const __m128i &a, const __m128i &b, const __m128i &r, const __m128i &m1) {
  return _mm_sub_epi32(
      _mm_add_epi32(my128_mulhi_epu32(a, b), m1),
      my128_mulhi_epu32(my128_mullo_epu32(my128_mullo_epu32(a, b), r), m1));
}

__attribute__((target("sse4.2"))) inline __m128i montgomery_add_128(
    const __m128i &a, const __m128i &b, const __m128i &m2, const __m128i &m0) {
  __m128i ret = _mm_sub_epi32(_mm_add_epi32(a, b), m2);
  return _mm_add_epi32(_mm_and_si128(_mm_cmpgt_epi32(m0, ret), m2), ret);
}

__attribute__((target("sse4.2"))) inline __m128i montgomery_sub_128(
    const __m128i &a, const __m128i &b, const __m128i &m2, const __m128i &m0) {
  __m128i ret = _mm_sub_epi32(a, b);
  return _mm_add_epi32(_mm_and_si128(_mm_cmpgt_epi32(m0, ret), m2), ret);
}

__attribute__((target("avx2"))) inline __m256i my256_mullo_epu32(
    const __m256i &a, const __m256i &b) {
  return _mm256_mullo_epi32(a, b);
}

__attribute__((target("avx2"))) inline __m256i my256_mulhi_epu32(
    const __m256i &a, const __m256i &b) {
  __m256i a13 = _mm256_shuffle_epi32(a, 0xF5);
  __m256i b13 = _mm256_shuffle_epi32(b, 0xF5);
  __m256i prod02 = _mm256_mul_epu32(a, b);
  __m256i prod13 = _mm256_mul_epu32(a13, b13);
  __m256i prod = _mm256_unpackhi_epi64(_mm256_unpacklo_epi32(prod02, prod13),
                                       _mm256_unpackhi_epi32(prod02, prod13));
  return prod;
}

__attribute__((target("avx2"))) inline __m256i montgomery_mul_256(
    const __m256i &a, const __m256i &b, const __m256i &r, const __m256i &m1) {
  return _mm256_sub_epi32(
      _mm256_add_epi32(my256_mulhi_epu32(a, b), m1),
      my256_mulhi_epu32(my256_mullo_epu32(my256_mullo_epu32(a, b), r), m1));
}

__attribute__((target("avx2"))) inline __m256i montgomery_add_256(
    const __m256i &a, const __m256i &b, const __m256i &m2, const __m256i &m0) {
  __m256i ret = _mm256_sub_epi32(_mm256_add_epi32(a, b), m2);
  return _mm256_add_epi32(_mm256_and_si256(_mm256_cmpgt_epi32(m0, ret), m2),
                          ret);
}

__attribute__((target("avx2"))) inline __m256i montgomery_sub_256(
    const __m256i &a, const __m256i &b, const __m256i &m2, const __m256i &m0) {
  __m256i ret = _mm256_sub_epi32(a, b);
  return _mm256_add_epi32(_mm256_and_si256(_mm256_cmpgt_epi32(m0, ret), m2),
                          ret);
}

namespace ntt_inner {
using u64 = uint64_t;
constexpr uint32_t get_pr(uint32_t mod) {
  if (mod == 2) return 1;
  u64 ds[32] = {};
  int idx = 0;
  u64 m = mod - 1;
  for (u64 i = 2; i * i <= m; ++i) {
    if (m % i == 0) {
      ds[idx++] = i;
      while (m % i == 0) m /= i;
    }
  }
  if (m != 1) ds[idx++] = m;

  uint32_t pr = 2;
  while (1) {
    int flg = 1;
    for (int i = 0; i < idx; ++i) {
      u64 a = pr, b = (mod - 1) / ds[i], r = 1;
      while (b) {
        if (b & 1) r = r * a % mod;
        a = a * a % mod;
        b >>= 1;
      }
      if (r == 1) {
        flg = 0;
        break;
      }
    }
    if (flg == 1) break;
    ++pr;
  }
  return pr;
}

constexpr int SZ_FFT_BUF = 1 << 23;
uint32_t _buf1[SZ_FFT_BUF] __attribute__((aligned(64)));
uint32_t _buf2[SZ_FFT_BUF] __attribute__((aligned(64)));
}  // namespace ntt_inner

template <typename mint>
struct NTT {
  static constexpr uint32_t mod = mint::get_mod();
  static constexpr uint32_t pr = ntt_inner::get_pr(mint::get_mod());
  static constexpr int level = __builtin_ctzll(mod - 1);
  mint dw[level], dy[level];
  mint *buf1, *buf2;

  constexpr NTT() {
    setwy(level);
    union raw_cast {
      mint dat;
      uint32_t _;
    };
    buf1 = &(((raw_cast *)(ntt_inner::_buf1))->dat);
    buf2 = &(((raw_cast *)(ntt_inner::_buf2))->dat);
  }

  constexpr void setwy(int k) {
    mint w[level], y[level];
    w[k - 1] = mint(pr).pow((mod - 1) / (1 << k));
    y[k - 1] = w[k - 1].inverse();
    for (int i = k - 2; i > 0; --i)
      w[i] = w[i + 1] * w[i + 1], y[i] = y[i + 1] * y[i + 1];
    dw[0] = dy[0] = w[1] * w[1];
    dw[1] = w[1], dy[1] = y[1], dw[2] = w[2], dy[2] = y[2];
    for (int i = 3; i < k; ++i) {
      dw[i] = dw[i - 1] * y[i - 2] * w[i];
      dy[i] = dy[i - 1] * w[i - 2] * y[i];
    }
  }

  __attribute__((target("avx2"))) void ntt(mint *a, int n) {
    int k = n ? __builtin_ctz(n) : 0;
    if (k == 0) return;
    if (k == 1) {
      mint a1 = a[1];
      a[1] = a[0] - a[1];
      a[0] = a[0] + a1;
      return;
    }
    if (k & 1) {
      int v = 1 << (k - 1);
      if (v < 8) {
        for (int j = 0; j < v; ++j) {
          mint ajv = a[j + v];
          a[j + v] = a[j] - ajv;
          a[j] += ajv;
        }
      } else {
        const __m256i m0 = _mm256_set1_epi32(0);
        const __m256i m2 = _mm256_set1_epi32(mod + mod);
        int j0 = 0;
        int j1 = v;
        for (; j0 < v; j0 += 8, j1 += 8) {
          __m256i T0 = _mm256_loadu_si256((__m256i *)(a + j0));
          __m256i T1 = _mm256_loadu_si256((__m256i *)(a + j1));
          __m256i naj = montgomery_add_256(T0, T1, m2, m0);
          __m256i najv = montgomery_sub_256(T0, T1, m2, m0);
          _mm256_storeu_si256((__m256i *)(a + j0), naj);
          _mm256_storeu_si256((__m256i *)(a + j1), najv);
        }
      }
    }
    int u = 1 << (2 + (k & 1));
    int v = 1 << (k - 2 - (k & 1));
    mint one = mint(1);
    mint imag = dw[1];
    while (v) {
      if (v == 1) {
        mint ww = one, xx = one, wx = one;
        for (int jh = 0; jh < u;) {
          ww = xx * xx, wx = ww * xx;
          mint t0 = a[jh + 0], t1 = a[jh + 1] * xx;
          mint t2 = a[jh + 2] * ww, t3 = a[jh + 3] * wx;
          mint t0p2 = t0 + t2, t1p3 = t1 + t3;
          mint t0m2 = t0 - t2, t1m3 = (t1 - t3) * imag;
          a[jh + 0] = t0p2 + t1p3, a[jh + 1] = t0p2 - t1p3;
          a[jh + 2] = t0m2 + t1m3, a[jh + 3] = t0m2 - t1m3;
          xx *= dw[__builtin_ctz((jh += 4))];
        }
      } else if (v == 4) {
        const __m128i m0 = _mm_set1_epi32(0);
        const __m128i m1 = _mm_set1_epi32(mod);
        const __m128i m2 = _mm_set1_epi32(mod + mod);
        const __m128i r = _mm_set1_epi32(mint::r);
        const __m128i Imag = _mm_set1_epi32(imag.a);
        mint ww = one, xx = one, wx = one;
        for (int jh = 0; jh < u;) {
          if (jh == 0) {
            int j0 = 0;
            int j1 = v;
            int j2 = j1 + v;
            int j3 = j2 + v;
            int je = v;
            for (; j0 < je; j0 += 4, j1 += 4, j2 += 4, j3 += 4) {
              const __m128i T0 = _mm_loadu_si128((__m128i *)(a + j0));
              const __m128i T1 = _mm_loadu_si128((__m128i *)(a + j1));
              const __m128i T2 = _mm_loadu_si128((__m128i *)(a + j2));
              const __m128i T3 = _mm_loadu_si128((__m128i *)(a + j3));
              const __m128i T0P2 = montgomery_add_128(T0, T2, m2, m0);
              const __m128i T1P3 = montgomery_add_128(T1, T3, m2, m0);
              const __m128i T0M2 = montgomery_sub_128(T0, T2, m2, m0);
              const __m128i T1M3 = montgomery_mul_128(
                  montgomery_sub_128(T1, T3, m2, m0), Imag, r, m1);
              _mm_storeu_si128((__m128i *)(a + j0),
                               montgomery_add_128(T0P2, T1P3, m2, m0));
              _mm_storeu_si128((__m128i *)(a + j1),
                               montgomery_sub_128(T0P2, T1P3, m2, m0));
              _mm_storeu_si128((__m128i *)(a + j2),
                               montgomery_add_128(T0M2, T1M3, m2, m0));
              _mm_storeu_si128((__m128i *)(a + j3),
                               montgomery_sub_128(T0M2, T1M3, m2, m0));
            }
          } else {
            ww = xx * xx, wx = ww * xx;
            const __m128i WW = _mm_set1_epi32(ww.a);
            const __m128i WX = _mm_set1_epi32(wx.a);
            const __m128i XX = _mm_set1_epi32(xx.a);
            int j0 = jh * v;
            int j1 = j0 + v;
            int j2 = j1 + v;
            int j3 = j2 + v;
            int je = j1;
            for (; j0 < je; j0 += 4, j1 += 4, j2 += 4, j3 += 4) {
              const __m128i T0 = _mm_loadu_si128((__m128i *)(a + j0));
              const __m128i T1 = _mm_loadu_si128((__m128i *)(a + j1));
              const __m128i T2 = _mm_loadu_si128((__m128i *)(a + j2));
              const __m128i T3 = _mm_loadu_si128((__m128i *)(a + j3));
              const __m128i MT1 = montgomery_mul_128(T1, XX, r, m1);
              const __m128i MT2 = montgomery_mul_128(T2, WW, r, m1);
              const __m128i MT3 = montgomery_mul_128(T3, WX, r, m1);
              const __m128i T0P2 = montgomery_add_128(T0, MT2, m2, m0);
              const __m128i T1P3 = montgomery_add_128(MT1, MT3, m2, m0);
              const __m128i T0M2 = montgomery_sub_128(T0, MT2, m2, m0);
              const __m128i T1M3 = montgomery_mul_128(
                  montgomery_sub_128(MT1, MT3, m2, m0), Imag, r, m1);
              _mm_storeu_si128((__m128i *)(a + j0),
                               montgomery_add_128(T0P2, T1P3, m2, m0));
              _mm_storeu_si128((__m128i *)(a + j1),
                               montgomery_sub_128(T0P2, T1P3, m2, m0));
              _mm_storeu_si128((__m128i *)(a + j2),
                               montgomery_add_128(T0M2, T1M3, m2, m0));
              _mm_storeu_si128((__m128i *)(a + j3),
                               montgomery_sub_128(T0M2, T1M3, m2, m0));
            }
          }
          xx *= dw[__builtin_ctz((jh += 4))];
        }
      } else {
        const __m256i m0 = _mm256_set1_epi32(0);
        const __m256i m1 = _mm256_set1_epi32(mod);
        const __m256i m2 = _mm256_set1_epi32(mod + mod);
        const __m256i r = _mm256_set1_epi32(mint::r);
        const __m256i Imag = _mm256_set1_epi32(imag.a);
        mint ww = one, xx = one, wx = one;
        for (int jh = 0; jh < u;) {
          if (jh == 0) {
            int j0 = 0;
            int j1 = v;
            int j2 = j1 + v;
            int j3 = j2 + v;
            int je = v;
            for (; j0 < je; j0 += 8, j1 += 8, j2 += 8, j3 += 8) {
              const __m256i T0 = _mm256_loadu_si256((__m256i *)(a + j0));
              const __m256i T1 = _mm256_loadu_si256((__m256i *)(a + j1));
              const __m256i T2 = _mm256_loadu_si256((__m256i *)(a + j2));
              const __m256i T3 = _mm256_loadu_si256((__m256i *)(a + j3));
              const __m256i T0P2 = montgomery_add_256(T0, T2, m2, m0);
              const __m256i T1P3 = montgomery_add_256(T1, T3, m2, m0);
              const __m256i T0M2 = montgomery_sub_256(T0, T2, m2, m0);
              const __m256i T1M3 = montgomery_mul_256(
                  montgomery_sub_256(T1, T3, m2, m0), Imag, r, m1);
              _mm256_storeu_si256((__m256i *)(a + j0),
                                  montgomery_add_256(T0P2, T1P3, m2, m0));
              _mm256_storeu_si256((__m256i *)(a + j1),
                                  montgomery_sub_256(T0P2, T1P3, m2, m0));
              _mm256_storeu_si256((__m256i *)(a + j2),
                                  montgomery_add_256(T0M2, T1M3, m2, m0));
              _mm256_storeu_si256((__m256i *)(a + j3),
                                  montgomery_sub_256(T0M2, T1M3, m2, m0));
            }
          } else {
            ww = xx * xx, wx = ww * xx;
            const __m256i WW = _mm256_set1_epi32(ww.a);
            const __m256i WX = _mm256_set1_epi32(wx.a);
            const __m256i XX = _mm256_set1_epi32(xx.a);
            int j0 = jh * v;
            int j1 = j0 + v;
            int j2 = j1 + v;
            int j3 = j2 + v;
            int je = j1;
            for (; j0 < je; j0 += 8, j1 += 8, j2 += 8, j3 += 8) {
              const __m256i T0 = _mm256_loadu_si256((__m256i *)(a + j0));
              const __m256i T1 = _mm256_loadu_si256((__m256i *)(a + j1));
              const __m256i T2 = _mm256_loadu_si256((__m256i *)(a + j2));
              const __m256i T3 = _mm256_loadu_si256((__m256i *)(a + j3));
              const __m256i MT1 = montgomery_mul_256(T1, XX, r, m1);
              const __m256i MT2 = montgomery_mul_256(T2, WW, r, m1);
              const __m256i MT3 = montgomery_mul_256(T3, WX, r, m1);
              const __m256i T0P2 = montgomery_add_256(T0, MT2, m2, m0);
              const __m256i T1P3 = montgomery_add_256(MT1, MT3, m2, m0);
              const __m256i T0M2 = montgomery_sub_256(T0, MT2, m2, m0);
              const __m256i T1M3 = montgomery_mul_256(
                  montgomery_sub_256(MT1, MT3, m2, m0), Imag, r, m1);
              _mm256_storeu_si256((__m256i *)(a + j0),
                                  montgomery_add_256(T0P2, T1P3, m2, m0));
              _mm256_storeu_si256((__m256i *)(a + j1),
                                  montgomery_sub_256(T0P2, T1P3, m2, m0));
              _mm256_storeu_si256((__m256i *)(a + j2),
                                  montgomery_add_256(T0M2, T1M3, m2, m0));
              _mm256_storeu_si256((__m256i *)(a + j3),
                                  montgomery_sub_256(T0M2, T1M3, m2, m0));
            }
          }
          xx *= dw[__builtin_ctz((jh += 4))];
        }
      }
      u <<= 2;
      v >>= 2;
    }
  }

  __attribute__((target("avx2"))) void intt(mint *a, int n,
                                            int normalize = true) {
    int k = n ? __builtin_ctz(n) : 0;
    if (k == 0) return;
    if (k == 1) {
      mint a1 = a[1];
      a[1] = a[0] - a[1];
      a[0] = a[0] + a1;
      if (normalize) {
        a[0] *= mint(2).inverse();
        a[1] *= mint(2).inverse();
      }
      return;
    }
    int u = 1 << (k - 2);
    int v = 1;
    mint one = mint(1);
    mint imag = dy[1];
    while (u) {
      if (v == 1) {
        mint ww = one, xx = one, yy = one;
        u <<= 2;
        for (int jh = 0; jh < u;) {
          ww = xx * xx, yy = xx * imag;
          mint t0 = a[jh + 0], t1 = a[jh + 1];
          mint t2 = a[jh + 2], t3 = a[jh + 3];
          mint t0p1 = t0 + t1, t2p3 = t2 + t3;
          mint t0m1 = (t0 - t1) * xx, t2m3 = (t2 - t3) * yy;
          a[jh + 0] = t0p1 + t2p3, a[jh + 2] = (t0p1 - t2p3) * ww;
          a[jh + 1] = t0m1 + t2m3, a[jh + 3] = (t0m1 - t2m3) * ww;
          xx *= dy[__builtin_ctz(jh += 4)];
        }
      } else if (v == 4) {
        const __m128i m0 = _mm_set1_epi32(0);
        const __m128i m1 = _mm_set1_epi32(mod);
        const __m128i m2 = _mm_set1_epi32(mod + mod);
        const __m128i r = _mm_set1_epi32(mint::r);
        const __m128i Imag = _mm_set1_epi32(imag.a);
        mint ww = one, xx = one, yy = one;
        u <<= 2;
        for (int jh = 0; jh < u;) {
          if (jh == 0) {
            int j0 = 0;
            int j1 = v;
            int j2 = v + v;
            int j3 = j2 + v;
            for (; j0 < v; j0 += 4, j1 += 4, j2 += 4, j3 += 4) {
              const __m128i T0 = _mm_loadu_si128((__m128i *)(a + j0));
              const __m128i T1 = _mm_loadu_si128((__m128i *)(a + j1));
              const __m128i T2 = _mm_loadu_si128((__m128i *)(a + j2));
              const __m128i T3 = _mm_loadu_si128((__m128i *)(a + j3));
              const __m128i T0P1 = montgomery_add_128(T0, T1, m2, m0);
              const __m128i T2P3 = montgomery_add_128(T2, T3, m2, m0);
              const __m128i T0M1 = montgomery_sub_128(T0, T1, m2, m0);
              const __m128i T2M3 = montgomery_mul_128(
                  montgomery_sub_128(T2, T3, m2, m0), Imag, r, m1);
              _mm_storeu_si128((__m128i *)(a + j0),
                               montgomery_add_128(T0P1, T2P3, m2, m0));
              _mm_storeu_si128((__m128i *)(a + j2),
                               montgomery_sub_128(T0P1, T2P3, m2, m0));
              _mm_storeu_si128((__m128i *)(a + j1),
                               montgomery_add_128(T0M1, T2M3, m2, m0));
              _mm_storeu_si128((__m128i *)(a + j3),
                               montgomery_sub_128(T0M1, T2M3, m2, m0));
            }
          } else {
            ww = xx * xx, yy = xx * imag;
            const __m128i WW = _mm_set1_epi32(ww.a);
            const __m128i XX = _mm_set1_epi32(xx.a);
            const __m128i YY = _mm_set1_epi32(yy.a);
            int j0 = jh * v;
            int j1 = j0 + v;
            int j2 = j1 + v;
            int j3 = j2 + v;
            int je = j1;
            for (; j0 < je; j0 += 4, j1 += 4, j2 += 4, j3 += 4) {
              const __m128i T0 = _mm_loadu_si128((__m128i *)(a + j0));
              const __m128i T1 = _mm_loadu_si128((__m128i *)(a + j1));
              const __m128i T2 = _mm_loadu_si128((__m128i *)(a + j2));
              const __m128i T3 = _mm_loadu_si128((__m128i *)(a + j3));
              const __m128i T0P1 = montgomery_add_128(T0, T1, m2, m0);
              const __m128i T2P3 = montgomery_add_128(T2, T3, m2, m0);
              const __m128i T0M1 = montgomery_mul_128(
                  montgomery_sub_128(T0, T1, m2, m0), XX, r, m1);
              __m128i T2M3 = montgomery_mul_128(
                  montgomery_sub_128(T2, T3, m2, m0), YY, r, m1);
              _mm_storeu_si128((__m128i *)(a + j0),
                               montgomery_add_128(T0P1, T2P3, m2, m0));
              _mm_storeu_si128(
                  (__m128i *)(a + j2),
                  montgomery_mul_128(montgomery_sub_128(T0P1, T2P3, m2, m0), WW,
                                     r, m1));
              _mm_storeu_si128((__m128i *)(a + j1),
                               montgomery_add_128(T0M1, T2M3, m2, m0));
              _mm_storeu_si128(
                  (__m128i *)(a + j3),
                  montgomery_mul_128(montgomery_sub_128(T0M1, T2M3, m2, m0), WW,
                                     r, m1));
            }
          }
          xx *= dy[__builtin_ctz(jh += 4)];
        }
      } else {
        const __m256i m0 = _mm256_set1_epi32(0);
        const __m256i m1 = _mm256_set1_epi32(mod);
        const __m256i m2 = _mm256_set1_epi32(mod + mod);
        const __m256i r = _mm256_set1_epi32(mint::r);
        const __m256i Imag = _mm256_set1_epi32(imag.a);
        mint ww = one, xx = one, yy = one;
        u <<= 2;
        for (int jh = 0; jh < u;) {
          if (jh == 0) {
            int j0 = 0;
            int j1 = v;
            int j2 = v + v;
            int j3 = j2 + v;
            for (; j0 < v; j0 += 8, j1 += 8, j2 += 8, j3 += 8) {
              const __m256i T0 = _mm256_loadu_si256((__m256i *)(a + j0));
              const __m256i T1 = _mm256_loadu_si256((__m256i *)(a + j1));
              const __m256i T2 = _mm256_loadu_si256((__m256i *)(a + j2));
              const __m256i T3 = _mm256_loadu_si256((__m256i *)(a + j3));
              const __m256i T0P1 = montgomery_add_256(T0, T1, m2, m0);
              const __m256i T2P3 = montgomery_add_256(T2, T3, m2, m0);
              const __m256i T0M1 = montgomery_sub_256(T0, T1, m2, m0);
              const __m256i T2M3 = montgomery_mul_256(
                  montgomery_sub_256(T2, T3, m2, m0), Imag, r, m1);
              _mm256_storeu_si256((__m256i *)(a + j0),
                                  montgomery_add_256(T0P1, T2P3, m2, m0));
              _mm256_storeu_si256((__m256i *)(a + j2),
                                  montgomery_sub_256(T0P1, T2P3, m2, m0));
              _mm256_storeu_si256((__m256i *)(a + j1),
                                  montgomery_add_256(T0M1, T2M3, m2, m0));
              _mm256_storeu_si256((__m256i *)(a + j3),
                                  montgomery_sub_256(T0M1, T2M3, m2, m0));
            }
          } else {
            ww = xx * xx, yy = xx * imag;
            const __m256i WW = _mm256_set1_epi32(ww.a);
            const __m256i XX = _mm256_set1_epi32(xx.a);
            const __m256i YY = _mm256_set1_epi32(yy.a);
            int j0 = jh * v;
            int j1 = j0 + v;
            int j2 = j1 + v;
            int j3 = j2 + v;
            int je = j1;
            for (; j0 < je; j0 += 8, j1 += 8, j2 += 8, j3 += 8) {
              const __m256i T0 = _mm256_loadu_si256((__m256i *)(a + j0));
              const __m256i T1 = _mm256_loadu_si256((__m256i *)(a + j1));
              const __m256i T2 = _mm256_loadu_si256((__m256i *)(a + j2));
              const __m256i T3 = _mm256_loadu_si256((__m256i *)(a + j3));
              const __m256i T0P1 = montgomery_add_256(T0, T1, m2, m0);
              const __m256i T2P3 = montgomery_add_256(T2, T3, m2, m0);
              const __m256i T0M1 = montgomery_mul_256(
                  montgomery_sub_256(T0, T1, m2, m0), XX, r, m1);
              const __m256i T2M3 = montgomery_mul_256(
                  montgomery_sub_256(T2, T3, m2, m0), YY, r, m1);
              _mm256_storeu_si256((__m256i *)(a + j0),
                                  montgomery_add_256(T0P1, T2P3, m2, m0));
              _mm256_storeu_si256(
                  (__m256i *)(a + j2),
                  montgomery_mul_256(montgomery_sub_256(T0P1, T2P3, m2, m0), WW,
                                     r, m1));
              _mm256_storeu_si256((__m256i *)(a + j1),
                                  montgomery_add_256(T0M1, T2M3, m2, m0));
              _mm256_storeu_si256(
                  (__m256i *)(a + j3),
                  montgomery_mul_256(montgomery_sub_256(T0M1, T2M3, m2, m0), WW,
                                     r, m1));
            }
          }
          xx *= dy[__builtin_ctz(jh += 4)];
        }
      }
      u >>= 4;
      v <<= 2;
    }
    if (k & 1) {
      v = 1 << (k - 1);
      if (v < 8) {
        for (int j = 0; j < v; ++j) {
          mint ajv = a[j] - a[j + v];
          a[j] += a[j + v];
          a[j + v] = ajv;
        }
      } else {
        const __m256i m0 = _mm256_set1_epi32(0);
        const __m256i m2 = _mm256_set1_epi32(mod + mod);
        int j0 = 0;
        int j1 = v;
        for (; j0 < v; j0 += 8, j1 += 8) {
          const __m256i T0 = _mm256_loadu_si256((__m256i *)(a + j0));
          const __m256i T1 = _mm256_loadu_si256((__m256i *)(a + j1));
          __m256i naj = montgomery_add_256(T0, T1, m2, m0);
          __m256i najv = montgomery_sub_256(T0, T1, m2, m0);
          _mm256_storeu_si256((__m256i *)(a + j0), naj);
          _mm256_storeu_si256((__m256i *)(a + j1), najv);
        }
      }
    }
    if (normalize) {
      mint invn = mint(n).inverse();
      for (int i = 0; i < n; i++) a[i] *= invn;
    }
  }

  __attribute__((target("avx2"))) void inplace_multiply(
      int l1, int l2, int zero_padding = true) {
    int l = l1 + l2 - 1;
    int M = 4;
    while (M < l) M <<= 1;
    if (zero_padding) {
      for (int i = l1; i < M; i++) ntt_inner::_buf1[i] = 0;
      for (int i = l2; i < M; i++) ntt_inner::_buf2[i] = 0;
    }
    const __m256i m0 = _mm256_set1_epi32(0);
    const __m256i m1 = _mm256_set1_epi32(mod);
    const __m256i r = _mm256_set1_epi32(mint::r);
    const __m256i N2 = _mm256_set1_epi32(mint::n2);
    for (int i = 0; i < l1; i += 8) {
      __m256i a = _mm256_loadu_si256((__m256i *)(ntt_inner::_buf1 + i));
      __m256i b = montgomery_mul_256(a, N2, r, m1);
      _mm256_storeu_si256((__m256i *)(ntt_inner::_buf1 + i), b);
    }
    for (int i = 0; i < l2; i += 8) {
      __m256i a = _mm256_loadu_si256((__m256i *)(ntt_inner::_buf2 + i));
      __m256i b = montgomery_mul_256(a, N2, r, m1);
      _mm256_storeu_si256((__m256i *)(ntt_inner::_buf2 + i), b);
    }
    ntt(buf1, M);
    ntt(buf2, M);
    for (int i = 0; i < M; i += 8) {
      __m256i a = _mm256_loadu_si256((__m256i *)(ntt_inner::_buf1 + i));
      __m256i b = _mm256_loadu_si256((__m256i *)(ntt_inner::_buf2 + i));
      __m256i c = montgomery_mul_256(a, b, r, m1);
      _mm256_storeu_si256((__m256i *)(ntt_inner::_buf1 + i), c);
    }
    intt(buf1, M, false);
    const __m256i INVM = _mm256_set1_epi32((mint(M).inverse()).a);
    for (int i = 0; i < l; i += 8) {
      __m256i a = _mm256_loadu_si256((__m256i *)(ntt_inner::_buf1 + i));
      __m256i b = montgomery_mul_256(a, INVM, r, m1);
      __m256i c = my256_mulhi_epu32(my256_mullo_epu32(b, r), m1);
      __m256i d = _mm256_and_si256(_mm256_cmpgt_epi32(c, m0), m1);
      __m256i e = _mm256_sub_epi32(d, c);
      _mm256_storeu_si256((__m256i *)(ntt_inner::_buf1 + i), e);
    }
  }

  void ntt(vector<mint> &a) {
    int M = (int)a.size();
    for (int i = 0; i < M; i++) buf1[i].a = a[i].a;
    ntt(buf1, M);
    for (int i = 0; i < M; i++) a[i].a = buf1[i].a;
  }

  void intt(vector<mint> &a) {
    int M = (int)a.size();
    for (int i = 0; i < M; i++) buf1[i].a = a[i].a;
    intt(buf1, M, true);
    for (int i = 0; i < M; i++) a[i].a = buf1[i].a;
  }

  vector<mint> multiply(const vector<mint> &a, const vector<mint> &b) {
    if (a.size() == 0 && b.size() == 0) return vector<mint>{};
    int l = a.size() + b.size() - 1;
    if (min<int>(a.size(), b.size()) <= 40) {
      vector<mint> s(l);
      for (int i = 0; i < (int)a.size(); ++i)
        for (int j = 0; j < (int)b.size(); ++j) s[i + j] += a[i] * b[j];
      return s;
    }
    assert(l <= ntt_inner::SZ_FFT_BUF);
    int M = 4;
    while (M < l) M <<= 1;
    for (int i = 0; i < (int)a.size(); ++i) buf1[i].a = a[i].a;
    for (int i = (int)a.size(); i < M; ++i) buf1[i].a = 0;
    for (int i = 0; i < (int)b.size(); ++i) buf2[i].a = b[i].a;
    for (int i = (int)b.size(); i < M; ++i) buf2[i].a = 0;
    ntt(buf1, M);
    ntt(buf2, M);
    for (int i = 0; i < M; ++i)
      buf1[i].a = mint::reduce(uint64_t(buf1[i].a) * buf2[i].a);
    intt(buf1, M, false);
    vector<mint> s(l);
    mint invm = mint(M).inverse();
    for (int i = 0; i < l; ++i) s[i] = buf1[i] * invm;
    return s;
  }

  void ntt_doubling(vector<mint> &a) {
    int M = (int)a.size();
    for (int i = 0; i < M; i++) buf1[i].a = a[i].a;
    intt(buf1, M);
    mint r = 1, zeta = mint(pr).pow((mint::get_mod() - 1) / (M << 1));
    for (int i = 0; i < M; i++) buf1[i] *= r, r *= zeta;
    ntt(buf1, M);
    a.resize(2 * M);
    for (int i = 0; i < M; i++) a[M + i].a = buf1[i].a;
  }
};



template <typename mint>
void FormalPowerSeries<mint>::set_fft() {
  if (!ntt_ptr) ntt_ptr = new NTT<mint>;
}

template <typename mint>
FormalPowerSeries<mint>& FormalPowerSeries<mint>::operator*=(
    const FormalPowerSeries<mint>& r) {
  if (this->empty() || r.empty()) {
    this->clear();
    return *this;
  }
  set_fft();
  auto ret = static_cast<NTT<mint>*>(ntt_ptr)->multiply(*this, r);
  return *this = FormalPowerSeries<mint>(ret.begin(), ret.end());
}

template <typename mint>
void FormalPowerSeries<mint>::ntt() {
  set_fft();
  static_cast<NTT<mint>*>(ntt_ptr)->ntt(*this);
}

template <typename mint>
void FormalPowerSeries<mint>::intt() {
  set_fft();
  static_cast<NTT<mint>*>(ntt_ptr)->intt(*this);
}

template <typename mint>
void FormalPowerSeries<mint>::ntt_doubling() {
  set_fft();
  static_cast<NTT<mint>*>(ntt_ptr)->ntt_doubling(*this);
}

template <typename mint>
int FormalPowerSeries<mint>::ntt_pr() {
  set_fft();
  return static_cast<NTT<mint>*>(ntt_ptr)->pr;
}

template <typename mint>
FormalPowerSeries<mint> FormalPowerSeries<mint>::inv(int deg) const {
  assert((*this)[0] != mint(0));
  if (deg == -1) deg = (int)this->size();
  FormalPowerSeries<mint> res(deg);
  res[0] = {mint(1) / (*this)[0]};
  for (int d = 1; d < deg; d <<= 1) {
    FormalPowerSeries<mint> f(2 * d), g(2 * d);
    for (int j = 0; j < min((int)this->size(), 2 * d); j++) f[j] = (*this)[j];
    for (int j = 0; j < d; j++) g[j] = res[j];
    f.ntt();
    g.ntt();
    for (int j = 0; j < 2 * d; j++) f[j] *= g[j];
    f.intt();
    for (int j = 0; j < d; j++) f[j] = 0;
    f.ntt();
    for (int j = 0; j < 2 * d; j++) f[j] *= g[j];
    f.intt();
    for (int j = d; j < min(2 * d, deg); j++) res[j] = -f[j];
  }
  return res.pre(deg);
}

template <typename mint>
FormalPowerSeries<mint> FormalPowerSeries<mint>::exp(int deg) const {
  using fps = FormalPowerSeries<mint>;
  assert((*this).size() == 0 || (*this)[0] == mint(0));
  if (deg == -1) deg = this->size();

  fps inv;
  inv.reserve(deg + 1);
  inv.push_back(mint(0));
  inv.push_back(mint(1));

  auto inplace_integral = [&](fps& F) -> void {
    const int n = (int)F.size();
    auto mod = mint::get_mod();
    while ((int)inv.size() <= n) {
      int i = inv.size();
      inv.push_back((-inv[mod % i]) * (mod / i));
    }
    F.insert(begin(F), mint(0));
    for (int i = 1; i <= n; i++) F[i] *= inv[i];
  };

  auto inplace_diff = [](fps& F) -> void {
    if (F.empty()) return;
    F.erase(begin(F));
    mint coeff = 1, one = 1;
    for (int i = 0; i < (int)F.size(); i++) {
      F[i] *= coeff;
      coeff += one;
    }
  };

  fps b{1, 1 < (int)this->size() ? (*this)[1] : 0}, c{1}, z1, z2{1, 1};
  for (int m = 2; m < deg; m *= 2) {
    auto y = b;
    y.resize(2 * m);
    y.ntt();
    z1 = z2;
    fps z(m);
    for (int i = 0; i < m; ++i) z[i] = y[i] * z1[i];
    z.intt();
    fill(begin(z), begin(z) + m / 2, mint(0));
    z.ntt();
    for (int i = 0; i < m; ++i) z[i] *= -z1[i];
    z.intt();
    c.insert(end(c), begin(z) + m / 2, end(z));
    z2 = c;
    z2.resize(2 * m);
    z2.ntt();
    fps x(begin(*this), begin(*this) + min<int>(this->size(), m));
    x.resize(m);
    inplace_diff(x);
    x.push_back(mint(0));
    x.ntt();
    for (int i = 0; i < m; ++i) x[i] *= y[i];
    x.intt();
    x -= b.diff();
    x.resize(2 * m);
    for (int i = 0; i < m - 1; ++i) x[m + i] = x[i], x[i] = mint(0);
    x.ntt();
    for (int i = 0; i < 2 * m; ++i) x[i] *= z2[i];
    x.intt();
    x.pop_back();
    inplace_integral(x);
    for (int i = m; i < min<int>(this->size(), 2 * m); ++i) x[i] += (*this)[i];
    fill(begin(x), begin(x) + m, mint(0));
    x.ntt();
    for (int i = 0; i < 2 * m; ++i) x[i] *= y[i];
    x.intt();
    b.insert(end(b), begin(x) + m, end(x));
  }
  return fps{begin(b), begin(b) + deg};
}

/**
 * @brief NTT mod用FPSライブラリ
 * @docs docs/fps/ntt-friendly-fps.md
 */


template <typename mint>
vector<mint> FastMultiEval(const FormalPowerSeries<mint> &f,
                           const vector<mint> &xs) {
  using fps = FormalPowerSeries<mint>;
  int s = xs.size();
  int N = 1 << (32 - __builtin_clz((int)xs.size() - 1));
  if(f.empty() || xs.empty()) return vector<mint>(s, mint(0));
  vector<FormalPowerSeries<mint>> buf(2 * N);
  for (int i = 0; i < N; i++) {
    mint n = mint{i < s ? -xs[i] : mint(0)};
    buf[i + N] = fps{n + 1, n - 1};
  }
  for (int i = N - 1; i > 0; i--) {
    fps &g(buf[(i << 1) | 0]), &h(buf[(i << 1) | 1]);
    int n = g.size();
    int m = n << 1;
    buf[i].reserve(m);
    buf[i].resize(n);
    for (int j = 0; j < n; j++) buf[i][j] = g[j] * h[j] - mint(1);
    if (i != 1) {
      buf[i].ntt_doubling();
      for (int j = 0; j < m; j++) buf[i][j] += j < n ? mint(1) : -mint(1);
    }
  }

  int fs = f.size();
  fps root = buf[1];
  root.intt();
  root.push_back(1);
  reverse(begin(root), end(root));
  root = root.inv(fs).rev() * f;
  root.erase(begin(root), begin(root) + fs - 1);
  root.resize(N, mint(0));

  vector<mint> ans(s);

  auto calc = [&](auto rec, int i, int l, int r, fps g) -> void {
    if (i >= N) {
      ans[i - N] = g[0];
      return;
    }
    int len = g.size(), m = (l + r) >> 1;
    g.ntt();
    fps tmp = buf[i * 2 + 1];
    for (int j = 0; j < len; j++) tmp[j] *= g[j];
    tmp.intt();
    rec(rec, i * 2 + 0, l, m, fps{begin(tmp) + (len >> 1), end(tmp)});
    if (m >= s) return;
    tmp = buf[i * 2 + 0];
    for (int j = 0; j < len; j++) tmp[j] *= g[j];
    tmp.intt();
    rec(rec, i * 2 + 1, m, r, fps{begin(tmp) + (len >> 1), end(tmp)});
  };
  calc(calc, 1, 0, N, root);
  return ans;
}

/**
 * @brief Multipoint Evaluation(高速化版)
 */




// calculate F(x + a)
template <typename mint>
FormalPowerSeries<mint> TaylorShift(FormalPowerSeries<mint> f, mint a,
                                    Binomial<mint>& C) {
  using fps = FormalPowerSeries<mint>;
  int N = f.size();
  for (int i = 0; i < N; i++) f[i] *= C.fac(i);
  reverse(begin(f), end(f));
  fps g(N, mint(1));
  for (int i = 1; i < N; i++) g[i] = g[i - 1] * a * C.inv(i);
  f = (f * g).pre(N);
  reverse(begin(f), end(f));
  for (int i = 0; i < N; i++) f[i] *= C.finv(i);
  return f;
}

/**
 * @brief 平行移動
 * @docs docs/fps/fps-taylor-shift.md
 */


template <typename mint>
vector<pair<mint, vector<mint>>> PartialFractionDecomposition(
    FormalPowerSeries<mint> numer, vector<pair<mint, int>> denom) {
  using fps = FormalPowerSeries<mint>;

  if (denom.empty()) return {};

  sort(begin(denom), end(denom),
       [](auto p1, auto p2) { return p1.second < p2.second; });
  Binomial<mint> C(denom[0].second + 1);

  int s = 1;
  while (s < (int)denom.size()) s *= 2;
  vector<fps> fs(2 * s);
  for (int i = 0; i < s; i++) {
    if ((int)denom.size() <= i) {
      fs[s + i] = fps{1};
      continue;
    }
    auto [m, d] = denom[i];
    fps f(denom[i].second + 1);
    mint buf = 1;
    for (int j = d; j >= 0; j--) {
      f[j] = buf * C(d, j);
      buf *= m;
    }
    fs[s + i] = f;
  }
  for (int i = s - 1; i; i--) {
    fs[i] = fs[2 * i + 0] * fs[2 * i + 1];
  }
  vector<fps> F(2 * s);
  vector<fps> G(2 * s);
  F[1] = numer % fs[1];
  G[1] = fps{1};
  for (int i = 1; i < s; i++) {
    G[i * 2 + 0] = G[i] * fs[i * 2 + 1] % fs[i * 2 + 0];
    G[i * 2 + 1] = G[i] * fs[i * 2 + 0] % fs[i * 2 + 1];
  }

  vector<mint>xs;
  rep(i,denom.size()){
    xs.push_back(-denom[i].first);
  }
  auto ys=FastMultiEval(F[1],xs);

  vector<pair<mint, vector<mint>>> res;
  for (int i = s; i - s < (int)denom.size(); i++) {
    auto [m, d] = denom[i - s];
    trc(ys[i-s]/F[i].eval(0));
    F[i] = fps{ys[i-s]};
    G[i] = TaylorShift<mint>(G[i], -m, C);
    fps f = (F[i] * G[i].inv()).pre(d);
    if ((int)f.size() < d) f.resize(d);
    f = f.rev();
    trc(f);
    res.emplace_back(m, vector<mint>{begin(f), end(f)});
  }
  return res;
}

/**
 * @brief 部分分数分解(分母が1次式の積で表せる場合)
 */


//


template <typename fps>
struct fps_fraction {
  using frac = fps_fraction;
  using mint = typename fps::value_type;

  fps p, q;
  fps_fraction(const fps& numerator = fps{0}, const fps& denominator = fps{1})
      : p(numerator), q(denominator) {}

  friend frac operator+(const frac& l, const frac& r) {
    return frac{l.p * r.q + r.p * l.q, l.q * r.q};
  }
  friend frac operator-(const frac& l, const frac& r) {
    return frac{l.p * r.q - r.p * l.q, l.q * r.q};
  }
  friend frac operator*(const frac& l, const frac& r) {
    return frac{l.p * r.p, l.q * r.q};
  }
  friend frac operator/(const frac& l, const frac& r) {
    return frac{l.p * r.q, l.q * r.p};
  }

  frac& operator+=(const mint& r) {
    (*this).p += (*this).q * r;
    return *this;
  }
  frac& operator-=(const mint& r) {
    (*this).p -= (*this).q * r;
    return *this;
  }
  frac& operator*=(const mint& r) {
    (*this).p *= r;
    return *this;
  }

  frac operator+(const mint& r) { return frac{*this} += r; }
  frac operator-(const mint& r) { return frac{*this} -= r; }
  frac operator*(const mint& r) { return frac{*this} *= r; }
  frac operator/(const mint& r) { return frac{*this} /= r; }
  frac& operator+=(const frac& r) { return *this = (*this) + r; }
  frac& operator-=(const frac& r) { return *this = (*this) - r; }
  frac& operator*=(const frac& r) { return *this = (*this) * r; }
  frac operator-() const { return frac{-p, q}; }
  frac inverse() const { return frac{q, p}; };

  void shrink() { p.shrink(), q.shrink(); }
  friend bool operator==(const frac& l, const frac& r) {
    return l.p == r.p && l.q == r.q;
  }
  friend bool operator!=(const frac& l, const frac& r) {
    return l.p != r.p || l.q != r.q;
  }
  friend ostream& operator<<(ostream& os, const frac& r) {
    os << "[ ";
    for (auto& x : r.p) os << x << ", ";
    os << "], ";
    os << "[ ";
    for (auto& x : r.q) os << x << ", ";
    os << " ]";
    return os;
  }
};


//






// #include "fps/arbitrary-fps.hpp"
//
using namespace Nyaan;
using mint = LazyMontgomeryModInt<998244353>;
// using mint = LazyMontgomeryModInt<1000000007>;
using vm = vector<mint>;
using vvm = vector<vm>;
Binomial<mint> C;
using fps = FormalPowerSeries<mint>;
using namespace Nyaan;

fps divide(fps f) {
  int n = sz(f);
  if (n <= 1) return f;
  int M = n / 2;
  int L = n - n / 2;
  // f = (x+2)^M g + x^L h
  // f ≡ (x+2)^M g (mod x^L)
  fps b(M + 1);
  mint p2 = 1;
  for (int i = M; i >= 0; p2 += p2, i--) b[i] = C(M, i) * p2;
  fps g = (f * b.inv(L)).pre(L);
  fps h = (f - b * g) >> L;
  fps upper = divide(g);
  fps lower = divide(h);
  copy(all(upper), back_inserter(lower));
  return lower;
}

void q() {
  inl(n_input, x0);

  ll N = n_input + 1;
  fps e2(2 * N + 20);
  rep(i, sz(e2)) e2[i] = C.finv(i) * mint{2}.pow(i);

  fps a;
  {
    fps num = fps{1} - e2;
    fps den = fps{1} + e2;
    fps g = num * den.inv();
    a.resize(N + 1);
    rep(i, N + 1) a[i] = g[i + n_input] * C.fac(i + n_input) * C.finv(i);
    a *= (fps{1} + e2).pow(n_input + 1);
    a.resize(N + 1);
  }

  // e^T

  // OGF 化
  rep(i, N + 1) a[i] *= C.fac(i);
  fps old_a = a;
  trc("OGF", a);
  fps b(N + 1);
  // b の定数項は？
  {
    // (1-x) ... (1-nx) を掛ける
    V<fps> fs;
    rep1(i, N) fs.emplace_back(fps{1, -i * 2});
    fps prod = Pi(fs);
    a *= prod;
    a = a.pre(N + 1);
    b[0] = a[N] / prod[N];
    a -= prod * b[0];
    a = a.pre(N);
    // a / (1-x)(1-2x)...(1-Nx) + b[0]
    // このあと monomial な多項式で評価するので
    // 分子分母 prod[N] で割る
    a *= prod[N].inverse();
  }
  // 部分分数分解
  V<pair<mint, int>> denom;
  rep1(i, N) denom.push_back({-mint{i * 2}.inverse(), 1});
  auto fa = PartialFractionDecomposition(a, denom);

  rep(i, sz(fa)) {
    int n = (-fa[i].first.inverse()).get();
    n /= 2;
    b[n] = fa[i].second[0] * -(n * 2);
  }
  trc(b);
  // b を復元できた。ここから s を求める
  b = TaylorShift(b, mint{1}, C);
  fps s = divide(b);
  reverse(all(s));
  trc(s);
  if (n_input % 2 == 0) s *= -1;
  out(s.eval(x0));
}

void Nyaan::solve() {
  int t = 1;
  // in(t);
  while (t--) q();
}