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


# :warning: starry-sky tree <small>(DataStructure/starry_sky_tree.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#5e248f107086635fddcead5bf28943fc">DataStructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/DataStructure/starry_sky_tree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-20 05:22:34+09:00




## Depends on

* :heavy_check_mark: <a href="../integer/bit.cpp.html">ビット演算 <small>(integer/bit.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_starry_sky_tree
#define H_starry_sky_tree

/**
 * @brief starry-sky tree
 * @author えびちゃん
 */

#include <cstddef>
#include <algorithm>

#include "integer/bit.cpp"

template <typename Tp>
class starry_sky_tree {
public:
  using size_type = size_t;
  using value_type = Tp;

private:
  size_type M_n = 0;
  std::vector<value_type> M_c;

  void M_fix_up(size_type i) {
    for (; i > 1; i >>= 1) {
      value_type d = std::max(M_c[i], M_c[i^1]);
      M_c[i] -= d;
      M_c[i^1] -= d;
      M_c[i >> 1] += d;
    }
  }

public:
  starry_sky_tree() = default;
  starry_sky_tree(size_type n): M_n(ceil2(n)), M_c(2*M_n, value_type{0}) {}

  void add(size_type l, size_type r, value_type const& x) {
    if (l >= r) return;
    l += M_n, r += M_n;
    for (size_type il = l, ir = r; il < ir; il >>= 1, ir >>= 1) {
      if (il & 1) M_c[il++] += x;
      if (ir & 1) M_c[--ir] += x;
    }
    M_fix_up(l), M_fix_up(r-1);
  }

  value_type max() const { return M_c[1]; }
};

#endif  /* !defined(H_starry_sky_tree) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "DataStructure/starry_sky_tree.cpp"



/**
 * @brief starry-sky tree
 * @author えびちゃん
 */

#include <cstddef>
#include <algorithm>

#line 1 "integer/bit.cpp"



/** 
 * @brief ビット演算
 * @author えびちゃん
 */

// XXX integral promotion 関連の注意をあまりしていません

#include <climits>
#include <type_traits>

template <typename Tp>
constexpr auto countl_zero(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, int>::type
{
  using value_type = typename std::make_unsigned<Tp>::type;
  int bits = (sizeof(value_type) * CHAR_BIT);
  if (n == 0) return bits;
  int res = 0;
  for (int i = bits / 2; i > 0; i /= 2) {
    value_type mask = ((static_cast<value_type>(1) << i) - 1) << i;
    if (n & mask) n >>= i;
    else res += i;
  }
  return res;
}
template <typename Tp>
constexpr auto countl_one(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, int>::type
{
  using value_type = typename std::make_unsigned<Tp>::type;
  return countl_zero(static_cast<value_type>(~n));
}

template <typename Tp>
constexpr auto countr_zero(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, int>::type
{
  using value_type = typename std::make_unsigned<Tp>::type;
  int bits = (sizeof(value_type) * CHAR_BIT);
  if (n == 0) return bits;
  int res = 0;
  for (int i = bits / 2; i > 0; i /= 2) {
    value_type mask = ((static_cast<value_type>(1) << i) - 1);
    if (!(n & mask)) res += i, n >>= i;
  }
  return res;
}
template <typename Tp>
constexpr auto countr_one(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, int>::type
{
  using value_type = typename std::make_unsigned<Tp>::type;
  return countr_zero(static_cast<value_type>(~n));
}

constexpr unsigned long long half_mask[] = {
  0x5555555555555555uLL, 0x3333333333333333uLL, 0x0F0F0F0F0F0F0F0FuLL,
  0x00FF00FF00FF00FFuLL, 0x0000FFFF0000FFFFuLL, 0x00000000FFFFFFFFuLL
};

template <typename Tp>
constexpr auto popcount(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, int>::type
{
  int bits = static_cast<int>((sizeof n) * CHAR_BIT);
  for (int i = 0, j = 1; j < bits; ++i, j *= 2) {
    if (j <= 8) n = (n & half_mask[i]) + ((n >> j) & half_mask[i]);
    else n += n >> j;
  }
  return n & 0xFF;
}

template <typename Tp>
constexpr auto parity(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, int>::type
{ return popcount(n) & 1; }


template <typename Tp>
int clz(Tp n) { return countl_zero(static_cast<typename std::make_unsigned<Tp>::type>(n)); }
template <typename Tp>
int ctz(Tp n) { return countr_zero(static_cast<typename std::make_unsigned<Tp>::type>(n)); }

template <typename Tp>
int ilog2(Tp n) {
  return (CHAR_BIT * sizeof(Tp) - 1) - clz(static_cast<typename std::make_unsigned<Tp>::type>(n));
}
template <typename Tp>
bool is_pow2(Tp n) { return (n > 0) && ((n & (n-1)) == 0); }
template <typename Tp>
Tp floor2(Tp n) { return is_pow2(n)? n: static_cast<Tp>(1) << ilog2(n); }
template <typename Tp>
Tp ceil2(Tp n) { return is_pow2(n)? n: static_cast<Tp>(2) << ilog2(n); }

template <typename Tp>
constexpr auto reverse(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, Tp>::type
{
  int bits = static_cast<int>((sizeof n) * CHAR_BIT);
  for (int i = 0, j = 1; j < bits; ++i, j *= 2) {
    n = ((n & half_mask[i]) << j) | ((n >> j) & half_mask[i]);
  }
  return n;
}


#line 13 "DataStructure/starry_sky_tree.cpp"

template <typename Tp>
class starry_sky_tree {
public:
  using size_type = size_t;
  using value_type = Tp;

private:
  size_type M_n = 0;
  std::vector<value_type> M_c;

  void M_fix_up(size_type i) {
    for (; i > 1; i >>= 1) {
      value_type d = std::max(M_c[i], M_c[i^1]);
      M_c[i] -= d;
      M_c[i^1] -= d;
      M_c[i >> 1] += d;
    }
  }

public:
  starry_sky_tree() = default;
  starry_sky_tree(size_type n): M_n(ceil2(n)), M_c(2*M_n, value_type{0}) {}

  void add(size_type l, size_type r, value_type const& x) {
    if (l >= r) return;
    l += M_n, r += M_n;
    for (size_type il = l, ir = r; il < ir; il >>= 1, ir >>= 1) {
      if (il & 1) M_c[il++] += x;
      if (ir & 1) M_c[--ir] += x;
    }
    M_fix_up(l), M_fix_up(r-1);
  }

  value_type max() const { return M_c[1]; }
};



```
{% endraw %}

<a href="../../index.html">Back to top page</a>
