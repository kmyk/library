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


# :heavy_check_mark: test/ALDS1_5_D.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/ALDS1_5_D.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-01 04:11:17+09:00


* see: <a href="https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_5_D">https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_5_D</a>


## Depends on

* :heavy_check_mark: <a href="../../library/DataStructure/bit_vector.cpp.html">rank/select 辞書 <small>(DataStructure/bit_vector.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/DataStructure/wavelet_matrix.cpp.html">ウェーブレット行列 <small>(DataStructure/wavelet_matrix.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/utility/literals.cpp.html">ユーザ定義リテラル <small>(utility/literals.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_5_D"

#define CALL_FROM_TEST
#include "DataStructure/wavelet_matrix.cpp"
#undef CALL_FROM_TEST

#include <cstdint>
#include <cstdio>
#include <vector>

int main() {
  int n;
  scanf("%d", &n);

  std::vector<int> a(n);
  for (auto& ai: a) scanf("%d", &ai);

  wavelet_matrix<31> wm(a.begin(), a.end());
  intmax_t res = 0;
  for (size_t i = 1; i < n; ++i) {
    res += wm.rank_3way(a[i], 0, i)[2];
  }
  printf("%jd\n", res);
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 343, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=self.cpp_source_path)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 63, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 182, in update
    self.update(self._resolve(included, included_from=path))
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 181, in update
    raise BundleError(path, i + 1, "unable to process #include in #if / #ifdef / #ifndef other than include guards")
onlinejudge_verify.languages.cplusplus_bundle.BundleError: DataStructure/wavelet_matrix.cpp: line 15: unable to process #include in #if / #ifdef / #ifndef other than include guards

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
