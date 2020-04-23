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


# :heavy_check_mark: test/yc_306_maximize.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yc_306_maximize.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-06 05:07:20+09:00


* see: <a href="https://yukicoder.me/problems/no/306">https://yukicoder.me/problems/no/306</a>


## Depends on

* :heavy_check_mark: <a href="../../library/algorithm/ternary_search.cpp.html">黄金比分割探索 <small>(algorithm/ternary_search.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://yukicoder.me/problems/no/306"
#define ERROR 1e-6

#include <cstdio>
#include <cmath>

#include "algorithm/ternary_search.cpp"

int main() {
  long double xa, ya, xb, yb;
  scanf("%Lf %Lf %Lf %Lf", &xa, &ya, &xb, &yb);

  auto f = [&](auto y) { return -(std::hypot(xa, y-ya) + std::hypot(xb, yb-y)); };
  long double y = optimize_convex(f, 0.0L, 1e3L, 1e-6L).first;
  printf("%.20Lf\n", y);
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yc_306_maximize.test.cpp"
#define PROBLEM "https://yukicoder.me/problems/no/306"
#define ERROR 1e-6

#include <cstdio>
#include <cmath>

#line 1 "algorithm/ternary_search.cpp"



/**
 * @brief 黄金比分割探索
 * @author えびちゃん
 */

#line 10 "algorithm/ternary_search.cpp"
#include <utility>

template <typename Fn, typename Tp>
std::pair<Tp, Tp> optimize_convex(Fn&& f, Tp xl, Tp xu, Tp err, bool maximize = true) {
  // Returns {argmin f(x), min f(x)}.
  Tp const phi = (1 + std::sqrt(static_cast<Tp>(5))) / 2;
  int const iter = (std::log(xu-xl) - std::log(err)) / std::log(phi) + 1;
  Tp xml = (phi * xl + xu) / (1 + phi);
  Tp xmu = (xl + phi * xu) / (1 + phi);
  Tp yml = f(xml);
  Tp ymu = f(xmu);
  for (int i = 0; i < iter; ++i) {
    if (!maximize ^ (yml > ymu)) {
      xu = xmu;
      xmu = xml;
      ymu = yml;
      xml = (phi * xl + xu) / (1 + phi);
      yml = f(xml);
    } else {
      xl = xml;
      xml = xmu;
      yml = ymu;
      xmu = (xl + phi * xu) / (1 + phi);
      ymu = f(xmu);
    }
  }
  return std::make_pair(xml, yml);
}


#line 8 "test/yc_306_maximize.test.cpp"

int main() {
  long double xa, ya, xb, yb;
  scanf("%Lf %Lf %Lf %Lf", &xa, &ya, &xb, &yb);

  auto f = [&](auto y) { return -(std::hypot(xa, y-ya) + std::hypot(xb, yb-y)); };
  long double y = optimize_convex(f, 0.0L, 1e3L, 1e-6L).first;
  printf("%.20Lf\n", y);
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
