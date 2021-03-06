#ifndef H_integral_intervals
#define H_integral_intervals

/**
 * @brief 整数の区間の集合
 * @author えびちゃん
 */

#include <cstddef>
#include <set>
#include <utility>

template <typename Tp>
class integral_intervals {
public:
  using size_type = size_t;
  using value_type = Tp;
  using interval_type = std::pair<value_type, value_type>;

private:
  std::set<interval_type> intervals;
  size_type M_size = 0;

public:
  integral_intervals() = default;
  integral_intervals(integral_intervals const&) = default;
  integral_intervals(integral_intervals&&) = default;

  integral_intervals& operator =(integral_intervals const&) = default;
  integral_intervals& operator =(integral_intervals&&) = default;

  template <typename InputIt>
  integral_intervals(InputIt first, InputIt last) { assign(first, last); }
  integral_intervals(std::initializer_list<interval_type> il) { assign(il.begin(), il.end()); }

  template <typename InputIt>
  void assign(InputIt first, InputIt last) {
    while (first != last) {
      insert(first->first, first->second);
      ++first;
    }
  }

  void insert(value_type x) { value_type y = x; insert(x, ++y); }
  void erase(value_type x) { value_type y = x; erase(x, ++y); }

  void insert(value_type lb, value_type ub) {
    if (intervals.empty()) {
      M_size += ub - lb;
      intervals.emplace(lb, ub);
      return;
    }

    auto it = intervals.upper_bound({lb, lb});
    if (it != intervals.begin() && !(std::prev(it)->second < lb)) {
      auto pit = std::prev(it);
      if (!(pit->second < ub)) return;
      lb = pit->first;
      M_size -= pit->second - pit->first;
      intervals.erase(pit);
    }
    while (it != intervals.end() && !(ub < it->first)) {
      if (ub < it->second) ub = it->second;
      M_size -= it->second - it->first;
      it = intervals.erase(it);
    }
    M_size += ub - lb;
    intervals.emplace(lb, ub);
  }

  void erase(value_type lb, value_type ub) {
    if (intervals.empty()) return;

    auto it = intervals.upper_bound({lb, lb});
    if (it != intervals.begin() && !(std::prev(it)->second < lb)) {
      auto pit = std::prev(it);
      if (!(pit->second < ub)) {
        // [ ...* [ ...+ ) ...* )
        --it;
        value_type lb0 = it->first;
        value_type ub0 = it->second;
        M_size -= it->second - it->first;
        intervals.erase(it);
        if (lb0 < lb) {
          M_size += lb - lb0;
          intervals.emplace(lb0, lb);
        }
        if (ub < ub0) {
          M_size += ub0 - ub;
          intervals.emplace(ub, ub0);
        }
        return;
      }

      // [ ...+ )      [ ...+ )*
      //      [ ...+ ) <- erase this
      value_type lb0 = pit->first;
      M_size -= pit->second - pit->first;
      M_size += lb - lb0;
      intervals.erase(pit);
      intervals.emplace(lb0, lb);
    }

    while (it != intervals.end() && !(ub < it->first)) {
      if (ub < it->second) {
        value_type ub0 = it->second;
        M_size -= it->second - it->first;
        M_size += ub0 - ub;
        intervals.erase(it);
        intervals.emplace(ub, ub0);
        break;
      }
      M_size -= it->second - it->first;
      it = intervals.erase(it);
    }
  }

  interval_type range(value_type x) const {
    if (intervals.empty()) return {x, x};
    auto it = intervals.upper_bound({x, x});

    if (it != intervals.end())
      if (!(x < it->first) && x < it->second) return *it;

    if (it == intervals.begin() || !(x < (--it)->second)) return {x, x};
    return *it;
  }

  bool contains(value_type x) const { return (range(x).second != x); }
  value_type mex() const { return range(0).second; }

  bool empty() const noexcept { return (M_size == 0); }
  size_type size() const { return M_size; }
  size_type count() const { return intervals.size(); }
};

#endif  /* !defined(H_integral_intervals) */
