#ifndef H_chinese_remaindering
#define H_chinese_remaindering

/**
 * @brief 連立合同式の解の構成
 * @author えびちゃん
 */

#include <tuple>
#include <utility>

#include "integer/fused_operations.cpp"

class simultaneous_congruences {
public:
  using value_type = intmax_t;

private:
  value_type M_mod = 1;
  value_type M_sol = 0;

  static auto S_gcd_bezout(value_type a, value_type b) {
    value_type x{1}, y{0};
    for (value_type u{y}, v{x}; b != 0;) {
      value_type q{a/b};
      std::swap(x -= q*u, u);
      std::swap(y -= q*v, v);
      std::swap(a -= q*b, b);
    }
    return std::make_tuple(a, x, y);
  }

public:
  simultaneous_congruences() = default;

  bool push(value_type a, value_type m) {
    if (M_mod == 0) return false;
    if ((a %= m) < 0) a += m;

    auto [g, x, y] = S_gcd_bezout(M_mod, m);
    value_type mod = M_mod / g * m;
    value_type sol0 = fused_mul_mod(fused_mul_mod(M_mod / g, a, mod), x, mod);
    value_type sol1 = fused_mul_mod(fused_mul_mod(m / g, M_sol, mod), y, mod);
    value_type sol = fused_add_mod(sol0, sol1, mod);

    if (g > 1 && (sol % M_mod != M_sol || sol % m != a)) {
      M_mod = M_sol = 0;
      return false;
    }
    M_sol = sol;
    M_mod = mod;
    return true;
  }

  auto get() const { return std::make_pair(M_sol, M_mod); }
};

#endif  /* !defined(H_chinese_remaindering) */
