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


# :warning: test/mini/foldable_deque.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#9a6d2aa7b36e38045ca314a0baa2d4bd">test/mini</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/mini/foldable_deque.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-19 19:24:42+09:00




## Depends on

* :heavy_check_mark: <a href="../../DataStructure/foldable_deque.cpp.html">fold 可能両端キュー <small>(DataStructure/foldable_deque.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <cstdio>
#include <string>

#include "DataStructure/foldable_deque.cpp"

int main() {
  foldable_deque<std::string> dq;
  auto print = [&] { printf("%s\n", dq.fold().data()); };
  auto push_back = [&](auto const& x) { dq.push_back(x); print(); };
  auto push_front = [&](auto const& x) { dq.push_front(x); print(); };
  auto pop_back = [&] { dq.pop_back(); print(); };
  auto pop_front = [&] { dq.pop_front(); print(); };

  // 2 4
  //   qa
  //   R++
  //   L++
  //   L--
  //   R--

  // push_back("a");
  // push_back("b");
  // push_back("c");
  // pop_front();
  // push_front("A");
  // push_front("B");
  // pop_back();
  // pop_back();
  // pop_back();
  // pop_back();

  push_back("q");
  push_back("a");
  pop_front();
  push_front("q");
  pop_back();
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/mini/foldable_deque.cpp"
#include <cstdio>
#include <string>

#line 1 "DataStructure/foldable_deque.cpp"



/**
 * @brief fold 可能両端キュー
 * @author えびちゃん
 */

#include <cstddef>
#include <stack>
#include <utility>

template <typename Monoid>
class foldable_deque {
public:
  using size_type = size_t;
  using value_type = Monoid;

private:
  std::stack<value_type> M_front, M_back;
  std::stack<value_type> M_front_folded, M_back_folded;

  void M_distribute_to_front() {
    // precondition: M_front.empty(), M_back.size() == n > 0
    // postcondition: M_front.size() == (n+1)/2, M_back.size() == n/2
    size_type n = M_back.size();
    std::stack<value_type>().swap(M_back_folded);  // clear
    std::stack<value_type> tmp;
    for (size_type i = 0; i < n/2; ++i) {
      tmp.push(std::move(M_back.top()));
      M_back.pop();
    }
    while (!M_back.empty()) {
      push_front(M_back.top());
      M_back.pop();
    }
    while (!tmp.empty()) {
      push_back(tmp.top());
      tmp.pop();
    }
  }

  void M_distribute_to_back() {
    // precondition: M_front.size() == n > 0, M_back.empty()
    // postcondition: M_front.size() == n/2, M_back.size() == (n+1)/2
    size_type n = M_front.size();
    std::stack<value_type>().swap(M_front_folded);  // clear
    std::stack<value_type> tmp;
    for (size_type i = 0; i < n/2; ++i) {
      tmp.push(std::move(M_front.top()));
      M_front.pop();
    }
    while (!M_front.empty()) {
      push_back(M_front.top());
      M_front.pop();
    }
    while (!tmp.empty()) {
      push_front(tmp.top());
      tmp.pop();
    }
  }

public:
  size_type size() const { return M_front.size() + M_back.size(); }
  bool empty() const noexcept { return M_front.empty() && M_back.empty(); }

  void push_back(value_type const& x) {
    M_back.push(x);
    value_type f = (M_back_folded.empty()? x: M_back_folded.top() + x);
    M_back_folded.push(f);
  }
  void push_front(value_type const& x) {
    M_front.push(x);
    value_type f = (M_front_folded.empty()? x: x + M_front_folded.top());
    M_front_folded.push(f);
  }
  template <typename... Args>
  void emplace_back(Args&&... args) {
    M_back.emplace(std::forward<Args>(args)...);
    value_type f = (M_back_folded.empty()? M_back.top(): M_back_folded.top() + M_back.top());
    M_back_folded.push(f);
  }
  template <typename... Args>
  void emplace_front(Args&&... args) {
    M_front.emplace(std::forward<Args>(args)...);
    value_type f = (M_front_folded.empty()? M_front.top(): M_front.top() + M_front_folded.top());
    M_front_folded.push(f);
  }

  void pop_back() {
    if (M_back.empty()) M_distribute_to_back();
    M_back.pop();
    M_back_folded.pop();
  }
  void pop_front() {
    if (M_front.empty()) M_distribute_to_front();
    M_front.pop();
    M_front_folded.pop();
  }

  value_type fold() const {
    value_type res{};
    if (!M_front_folded.empty()) res += M_front_folded.top();
    if (!M_back_folded.empty()) res += M_back_folded.top();
    return res;
  }
};


#line 5 "test/mini/foldable_deque.cpp"

int main() {
  foldable_deque<std::string> dq;
  auto print = [&] { printf("%s\n", dq.fold().data()); };
  auto push_back = [&](auto const& x) { dq.push_back(x); print(); };
  auto push_front = [&](auto const& x) { dq.push_front(x); print(); };
  auto pop_back = [&] { dq.pop_back(); print(); };
  auto pop_front = [&] { dq.pop_front(); print(); };

  // 2 4
  //   qa
  //   R++
  //   L++
  //   L--
  //   R--

  // push_back("a");
  // push_back("b");
  // push_back("c");
  // pop_front();
  // push_front("A");
  // push_front("B");
  // pop_back();
  // pop_back();
  // pop_back();
  // pop_back();

  push_back("q");
  push_back("a");
  pop_front();
  push_front("q");
  pop_back();
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>
