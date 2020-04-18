---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: test/yj_point_set_range_composite.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yj_point_set_range_composite.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-10 16:57:52+09:00


* see: <a href="https://judge.yosupo.jp/problem/point_set_range_composite">https://judge.yosupo.jp/problem/point_set_range_composite</a>


## Depends on

* :heavy_check_mark: <a href="../../library/DataStructure/basic_segment_tree.cpp.html">単一更新セグメント木 <small>(DataStructure/basic_segment_tree.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/ModularArithmetic/modint.cpp.html">合同算術用クラス <small>(ModularArithmetic/modint.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/utility/monoid/composite.cpp.html">一次関数の合成を得る演算のモノイド <small>(utility/monoid/composite.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include <cstdint>
#include <cstdio>
#include <vector>

#include "DataStructure/basic_segment_tree.cpp"
#include "utility/monoid/composite.cpp"
#include "ModularArithmetic/modint.cpp"

constexpr intmax_t mod = 998244353;
using mi = modint<mod>;

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  std::vector<composite_monoid<mi>> f(n);
  for (size_t i = 0; i < n; ++i) {
    intmax_t a, b;
    scanf("%jd %jd", &a, &b);
    f[i] = {a, b};
  }

  basic_segment_tree<composite_monoid<mi>> st(f.begin(), f.end());
  for (size_t i = 0; i < q; ++i) {
    int t;
    scanf("%d", &t);

    if (t == 0) {
      size_t p;
      intmax_t c, d;
      scanf("%zu %jd %jd", &p, &c, &d);
      st.modify(p, {c, d});
    } else if (t == 1) {
      size_t l, r;
      intmax_t x;
      scanf("%zu %zu %jd", &l, &r, &x);
      printf("%jd\n", st.fold(l, r)(x).get());
    }
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yj_point_set_range_composite.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include <cstdint>
#include <cstdio>
#include <vector>

#line 1 "DataStructure/basic_segment_tree.cpp"



/**
 * @brief 単一更新セグメント木
 * @author えびちゃん
 */

#include <cstddef>
#line 11 "DataStructure/basic_segment_tree.cpp"

template <typename Monoid>
class basic_segment_tree {
public:
  using value_type = Monoid;
  using size_type = size_t;

private:
  std::vector<value_type> M_c;
  size_type M_n;

  std::vector<size_type> M_covering_segments(size_type l, size_type r) const {
    std::vector<size_type> left, right;
    l += M_n;
    r += M_n;
    while (l < r) {
      if (l & 1) left.push_back(l++);
      if (r & 1) right.push_back(--r);
      l >>= 1;
      r >>= 1;
    }
    left.insert(left.end(), right.rbegin(), right.rend());
    return left;
  }

public:
  basic_segment_tree() = default;
  basic_segment_tree(basic_segment_tree const&) = default;
  basic_segment_tree(basic_segment_tree&&) = default;

  explicit basic_segment_tree(size_type n): M_c(n+n), M_n(n) {}
  explicit basic_segment_tree(size_type n, value_type const& x):
    M_c(n+n, x), M_n(n)
  {
    for (size_type i = n; i--;) M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
  }

  template <typename InputIt>
  basic_segment_tree(InputIt first, InputIt last) {
    std::vector<value_type> tmp(first, last);
    M_n = tmp.size();
    M_c.resize(M_n);
    M_c.insert(M_c.end(), tmp.begin(), tmp.end());
    for (size_type i = M_n; i--;) M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
  }

  void assign(size_type n, value_type const& x) {
    M_c.assign(n+n, x);
    M_n = n;
    for (size_type i = n; i--;) M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
  }

  template <typename InputIt>
  void assign(InputIt first, InputIt last) {
    std::vector<value_type> tmp(first, last);
    M_n = tmp.size();
    M_c.resize(M_n);
    M_c.insert(M_c.end(), tmp.begin(), tmp.end());
    for (size_type i = M_n; i--;) M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
  }

  void modify(size_type i, value_type const& x) {
    i += M_n;
    M_c[i] = x;
    while (i > 1) {
      i >>= 1;
      M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
    }
  }

  void modify(size_type i, value_type&& x) {
    i += M_n;
    M_c[i] = std::move(x);
    while (i > 1) {
      i >>= 1;
      M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
    }
  }

  value_type const& operator [](size_type i) const { return M_c[i + M_n]; }

  value_type fold(size_type l, size_type r) const {
    value_type resl{}, resr{};
    l += M_n;
    r += M_n;
    while (l < r) {
      if (l & 1) resl += M_c[l++];
      if (r & 1) resr = M_c[--r] + std::move(resr);
      l >>= 1;
      r >>= 1;
    }
    return resl += resr;
  }

  template <typename Predicate>
  size_type partition_point(size_type l, Predicate pred) const {
    if (l == M_n) return l;
    value_type x{};
    size_type v = M_n + M_n;
    std::vector<size_type> cs = M_covering_segments(l, M_n);

    // search the subroot
    for (auto s: cs) {
      if (!pred(x + M_c[s])) {
        v = s;
        break;
      }
      x += M_c[s];
    }

    // search the leaf
    while (v < M_n) {
      v <<= 1;
      if (pred(x + M_c[v])) {
        x += M_c[v];
        v |= 1;
      }
    }

    return v - M_n;
  }
};


#line 1 "utility/monoid/composite.cpp"
/**
 * @brief 一次関数の合成を得る演算のモノイド
 * @author えびちゃん
 */

#include <algorithm>
#include <utility>

#ifndef H_composite_monoid
#define H_composite_monoid

template <typename Tp>
class composite_monoid {
public:
  using value_type = Tp;

private:
  value_type M_a = 1;
  value_type M_b = 0;

public:
  composite_monoid() = default;  // identity

  composite_monoid(value_type a, value_type b): M_a(a), M_b(b) {};

  composite_monoid& operator +=(composite_monoid that) {
    M_a *= that.M_a;
    M_b *= that.M_a;
    M_b += that.M_b;
    return *this;
  }

  composite_monoid operator +(composite_monoid const& that) const {
    return composite_monoid(*this) += that;
  }
  composite_monoid operator +(composite_monoid&& that) const {
    return composite_monoid(*this) += std::move(that);
  }

  bool operator ==(composite_monoid const& that) const {
    return (M_a == that.M_a && M_b == that.M_b);
  }
  bool operator !=(composite_monoid const& that) const { return !(*this == that); }

  auto get() const { return std::make_pair(M_a, M_b); }
  value_type operator ()(value_type x) const { return M_a * x + M_b; }
};

#endif  /* !defined(H_composite_monoid) */
#line 1 "ModularArithmetic/modint.cpp"



/**
 * @brief 合同算術用クラス
 * @author えびちゃん
 */
//

#line 11 "ModularArithmetic/modint.cpp"
#include <type_traits>
#line 13 "ModularArithmetic/modint.cpp"

template <intmax_t Modulo>
class modint {
public:
  using value_type = intmax_t;

private:
  static constexpr value_type S_cmod = Modulo;  // compile-time
  static value_type S_rmod;  // runtime
  value_type M_value = 0;

  static constexpr value_type S_inv(value_type n, value_type m) {
    value_type x = 0;
    value_type y = 1;
    value_type a = n;
    value_type b = m;
    for (value_type u = y, v = x; a;) {
      value_type q = b / a;
      std::swap(x -= q*u, u);
      std::swap(y -= q*v, v);
      std::swap(b -= q*a, a);
    }
    if ((x %= m) < 0) x += m;
    return x;
  }

  static value_type S_normalize(value_type n, value_type m) {
    if (n >= m) {
      n %= m;
    } else if (n < 0) {
      if ((n %= m) < 0) n += m;
    }
    return n;
  }

public:
  modint() = default;
  modint(value_type n): M_value(S_normalize(n, get_modulo())) {}

  modint& operator =(value_type n) {
    M_value = S_normalize(n, get_modulo());
    return *this;
  }

  modint& operator +=(modint const& that) {
    if ((M_value += that.M_value) >= get_modulo()) M_value -= get_modulo();
    return *this;
  }
  modint& operator -=(modint const& that) {
    if ((M_value -= that.M_value) < 0) M_value += get_modulo();
    return *this;
  }
  modint& operator *=(modint const& that) {
    (M_value *= that.M_value) %= get_modulo();
    return *this;
  }
  modint& operator /=(modint const& that) {
    (M_value *= S_inv(that.M_value, get_modulo())) %= get_modulo();
    return *this;
  }

  modint operator +(modint const& that) const { return modint(*this) += that; }
  modint operator -(modint const& that) const { return modint(*this) -= that; }
  modint operator *(modint const& that) const { return modint(*this) *= that; }
  modint operator /(modint const& that) const { return modint(*this) /= that; }

  modint operator +() const { return *this; }
  modint operator -() const {
    if (M_value == 0) return *this;
    return modint(get_modulo() - M_value);
  }

  bool operator ==(modint const& that) const { return M_value == that.M_value; }
  bool operator !=(modint const& that) const { return !(*this == that); }

  value_type get() const { return M_value; }
  static value_type get_modulo() { return ((S_cmod > 0)? S_cmod: S_rmod); }

  template <int M = Modulo, typename Tp = typename std::enable_if<(M <= 0)>::type>
  static Tp set_modulo(value_type m) { S_rmod = m; }
};

template <typename Tp, intmax_t Modulo>
modint<Modulo> operator +(Tp const& lhs, modint<Modulo> const& rhs) {
  return rhs + lhs;
}
template <typename Tp, intmax_t Modulo>
modint<Modulo> operator -(Tp const& lhs, modint<Modulo> const& rhs) {
  return -(rhs - lhs);
}
template <typename Tp, intmax_t Modulo>
modint<Modulo> operator *(Tp const& lhs, modint<Modulo> const& rhs) {
  return rhs * lhs;
}
template <typename Tp, intmax_t Modulo>
modint<Modulo> operator /(Tp const& lhs, modint<Modulo> const& rhs) {
  return modint<Modulo>(lhs) / rhs;
}
template <typename Tp, intmax_t Modulo>
bool operator ==(Tp const& lhs, modint<Modulo> const& rhs) {
  return rhs == lhs;
}
template <typename Tp, intmax_t Modulo>
bool operator !=(Tp const& lhs, modint<Modulo> const& rhs) {
  return !(lhs == rhs);
}

template <intmax_t N>
constexpr intmax_t modint<N>::S_cmod;
template <intmax_t N>
intmax_t modint<N>::S_rmod;


#line 10 "test/yj_point_set_range_composite.test.cpp"

constexpr intmax_t mod = 998244353;
using mi = modint<mod>;

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  std::vector<composite_monoid<mi>> f(n);
  for (size_t i = 0; i < n; ++i) {
    intmax_t a, b;
    scanf("%jd %jd", &a, &b);
    f[i] = {a, b};
  }

  basic_segment_tree<composite_monoid<mi>> st(f.begin(), f.end());
  for (size_t i = 0; i < q; ++i) {
    int t;
    scanf("%d", &t);

    if (t == 0) {
      size_t p;
      intmax_t c, d;
      scanf("%zu %jd %jd", &p, &c, &d);
      st.modify(p, {c, d});
    } else if (t == 1) {
      size_t l, r;
      intmax_t x;
      scanf("%zu %zu %jd", &l, &r, &x);
      printf("%jd\n", st.fold(l, r)(x).get());
    }
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
