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


# :warning: test/yc_1036_test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yc_1036_test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-25 02:58:44+09:00


* see: <a href="https://yukicoder.me/problems/no/1036">https://yukicoder.me/problems/no/1036</a>


## Depends on

* :heavy_check_mark: <a href="../DataStructure/foldable_queue.cpp.html">fold 可能キュー <small>(DataStructure/foldable_queue.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://yukicoder.me/problems/no/1036"

#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <numeric>
#include <vector>

#include "DataStructure/foldable_queue.cpp"

template <typename Tp>
class gcd_monoid {
public:
  using value_type = Tp;

private:
  value_type M_x = 0;

public:
  gcd_monoid() = default;  // identity

  gcd_monoid(value_type const& x): M_x(x) {}

  gcd_monoid& operator +=(gcd_monoid const& that) {
    M_x = std::gcd(M_x, that.M_x);
    return *this;
  }
  friend bool operator ==(gcd_monoid const& lhs, gcd_monoid const& rhs) {
    return lhs.M_x == rhs.M_x;
  }

  friend gcd_monoid operator +(gcd_monoid lhs, gcd_monoid const& rhs) {return lhs += rhs; }
  friend bool operator !=(gcd_monoid const& lhs, gcd_monoid const& rhs) {
    return !(lhs == rhs);
  }

  value_type const& get() const { return M_x; }
};

int main() {
  size_t n;
  scanf("%zu", &n);

  std::vector<intmax_t> a(n);
  for (auto& ai: a) scanf("%jd", &ai);

  foldable_queue<gcd_monoid<intmax_t>> q;
  intmax_t res = n*(n+1)/2;
  for (size_t il = 0, ir = 0; il < n; ++il) {
    while (ir < n && (q.fold() + a[ir]).get() != 1) {
      q.push(a[ir++]);
    }
    res -= ir-il;
    if (ir == il) ++ir; else q.pop();
  }

  printf("%jd\n", res);
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yc_1036_test.cpp"
#define PROBLEM "https://yukicoder.me/problems/no/1036"

#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <numeric>
#include <vector>

#line 1 "DataStructure/foldable_queue.cpp"



/**
 * @brief fold 可能キュー
 * @author えびちゃん
 */

#include <cstddef>
#include <stack>
#include <utility>

template <class Monoid>
class foldable_queue {
public:
  using size_type = size_t;
  using value_type = Monoid;

private:
  std::stack<value_type> M_front, M_back;
  value_type M_back_folded{};

  void M_distribute_to_front() {
    if (!M_back.empty()) {
      M_front.push(std::move(M_back.top()));
      M_back.pop();
    }
    while (!M_back.empty()) {
      M_back.top() += M_front.top();
      M_front.push(std::move(M_back.top()));
      M_back.pop();
    }
    M_back_folded = value_type{};
  }

public:
  size_type size() const { return M_front.size() + M_back.size(); }
  bool empty() const noexcept { return M_front.empty() && M_back.empty(); }

  void push(value_type const& x) {
    M_back.push(x);
    M_back_folded += M_back.top();
  }

  template <typename... Args>
  void emplace(Args&&... args) {
    M_back.emplace(std::forward<Args>(args)...);
    M_back_folded += M_back.top();
  }

  void pop() {
    if (M_front.empty()) M_distribute_to_front();
    M_front.pop();
  }

  value_type fold() const {
    if (M_front.empty()) return M_back_folded;
    return M_front.top() + M_back_folded;
  }
};


#line 10 "test/yc_1036_test.cpp"

template <typename Tp>
class gcd_monoid {
public:
  using value_type = Tp;

private:
  value_type M_x = 0;

public:
  gcd_monoid() = default;  // identity

  gcd_monoid(value_type const& x): M_x(x) {}

  gcd_monoid& operator +=(gcd_monoid const& that) {
    M_x = std::gcd(M_x, that.M_x);
    return *this;
  }
  friend bool operator ==(gcd_monoid const& lhs, gcd_monoid const& rhs) {
    return lhs.M_x == rhs.M_x;
  }

  friend gcd_monoid operator +(gcd_monoid lhs, gcd_monoid const& rhs) {return lhs += rhs; }
  friend bool operator !=(gcd_monoid const& lhs, gcd_monoid const& rhs) {
    return !(lhs == rhs);
  }

  value_type const& get() const { return M_x; }
};

int main() {
  size_t n;
  scanf("%zu", &n);

  std::vector<intmax_t> a(n);
  for (auto& ai: a) scanf("%jd", &ai);

  foldable_queue<gcd_monoid<intmax_t>> q;
  intmax_t res = n*(n+1)/2;
  for (size_t il = 0, ir = 0; il < n; ++il) {
    while (ir < n && (q.fold() + a[ir]).get() != 1) {
      q.push(a[ir++]);
    }
    res -= ir-il;
    if (ir == il) ++ir; else q.pop();
  }

  printf("%jd\n", res);
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
