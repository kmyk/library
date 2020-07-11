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
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :heavy_check_mark: 部分和の最大値を得る演算のモノイドクラス <small>(utility/monoid/max_subsum.cpp)</small>

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#0991b1681f77f54af5325f2eb1ef5d3e">utility/monoid</a>
* <a href="{{ site.github.repository_url }}/blob/master/utility/monoid/max_subsum.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-27 03:46:28+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/test/aoj_2450.test.cpp.html">test/aoj_2450.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/test/aoj_3111.test.cpp.html">test/aoj_3111.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_max_subsum_monoid
#define H_max_subsum_monoid

/**
 * @brief 部分和の最大値を得る演算のモノイドクラス
 * @author えびちゃん
 */

#include <cstddef>
#include <algorithm>

template <typename Tp>
class max_subsum_monoid {
public:
  using size_type = size_t;
  using value_type = Tp;

private:
  value_type M_pre = 0, M_suf = 0, M_sub = 0, M_whole = 0;
  size_type M_length = 0;

public:
  max_subsum_monoid() = default;  // identity

  max_subsum_monoid(value_type const& x):
    M_pre(x), M_suf(x), M_sub(x), M_whole(x), M_length(1) {}

  max_subsum_monoid(value_type const& x, value_type n):
    M_pre(x*n), M_suf(x*n), M_sub(x*n), M_whole(x*n), M_length(n)
  {
    if (x < 0) M_pre = M_suf = M_sub = x;
  }

  max_subsum_monoid& operator +=(max_subsum_monoid const& that) {
    if (that.M_length == 0) return *this;
    if (M_length == 0) return (*this = that);
    M_sub = std::max({M_sub, M_suf + that.M_pre, that.M_sub});
    M_suf = std::max(M_suf + that.M_whole, that.M_suf);
    M_pre = std::max(M_pre, M_whole + that.M_pre);
    M_whole += that.M_whole;
    M_length += that.M_length;
    return *this;
  }
  friend bool operator ==(max_subsum_monoid const& lhs, max_subsum_monoid const& rhs) {
    if (lhs.M_length == 0 && rhs.M_length == 0) return true;
    return (
        lhs.M_length == rhs.M_length
        && lhs.M_pre == rhs.M_pre
        && lhs.M_suf == rhs.M_suf
        && lhs.M_sub == rhs.M_sub
        && lhs.M_whole == rhs.M_whole
    );
  }

  friend max_subsum_monoid operator +(max_subsum_monoid lhs, max_subsum_monoid const& rhs) {
    return lhs += rhs;
  }
  friend bool operator !=(max_subsum_monoid const& lhs, max_subsum_monoid const& rhs) {
    return !(lhs == rhs);
  }

  size_type length() const noexcept { return M_length; }
  value_type const& get() const { return M_sub; }
};

#endif  /* !defined(H_max_subsum_monoid) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "utility/monoid/max_subsum.cpp"



/**
 * @brief 部分和の最大値を得る演算のモノイドクラス
 * @author えびちゃん
 */

#include <cstddef>
#include <algorithm>

template <typename Tp>
class max_subsum_monoid {
public:
  using size_type = size_t;
  using value_type = Tp;

private:
  value_type M_pre = 0, M_suf = 0, M_sub = 0, M_whole = 0;
  size_type M_length = 0;

public:
  max_subsum_monoid() = default;  // identity

  max_subsum_monoid(value_type const& x):
    M_pre(x), M_suf(x), M_sub(x), M_whole(x), M_length(1) {}

  max_subsum_monoid(value_type const& x, value_type n):
    M_pre(x*n), M_suf(x*n), M_sub(x*n), M_whole(x*n), M_length(n)
  {
    if (x < 0) M_pre = M_suf = M_sub = x;
  }

  max_subsum_monoid& operator +=(max_subsum_monoid const& that) {
    if (that.M_length == 0) return *this;
    if (M_length == 0) return (*this = that);
    M_sub = std::max({M_sub, M_suf + that.M_pre, that.M_sub});
    M_suf = std::max(M_suf + that.M_whole, that.M_suf);
    M_pre = std::max(M_pre, M_whole + that.M_pre);
    M_whole += that.M_whole;
    M_length += that.M_length;
    return *this;
  }
  friend bool operator ==(max_subsum_monoid const& lhs, max_subsum_monoid const& rhs) {
    if (lhs.M_length == 0 && rhs.M_length == 0) return true;
    return (
        lhs.M_length == rhs.M_length
        && lhs.M_pre == rhs.M_pre
        && lhs.M_suf == rhs.M_suf
        && lhs.M_sub == rhs.M_sub
        && lhs.M_whole == rhs.M_whole
    );
  }

  friend max_subsum_monoid operator +(max_subsum_monoid lhs, max_subsum_monoid const& rhs) {
    return lhs += rhs;
  }
  friend bool operator !=(max_subsum_monoid const& lhs, max_subsum_monoid const& rhs) {
    return !(lhs == rhs);
  }

  size_type length() const noexcept { return M_length; }
  value_type const& get() const { return M_sub; }
};



```
{% endraw %}

<a href="../../../index.html">Back to top page</a>
