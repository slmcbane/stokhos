#ifndef STOKHOS_ABSTRACT_GENERATOR_HPP
#define STOKHOS_ABSTRACT_GENERATOR_HPP

#include <limits>
#include <type_traits>

namespace stokhos
{

template <
    class OutputInteger, class StateType,
    OutputInteger Min = std::numeric_limits<OutputInteger>::min(),
    OutputInteger Max = std::numeric_limits<OutputInteger>::max()>
class AbstractRNG
{
  public:
    static_assert(
        std::is_integral<OutputInteger>::value && std::is_unsigned<OutputInteger>::value,
        "Output type should be an unsigned integer");

    typedef OutputInteger result_type;

    explicit AbstractRNG(StateType state) noexcept : m_state(state) {}

    constexpr static OutputInteger min() noexcept { return Min; }

    constexpr static OutputInteger max() noexcept { return Max; }

    virtual ~AbstractRNG() {}

    virtual OutputInteger operator()() = 0;

    StateType state() const noexcept { return m_state; }

  protected:
    StateType m_state;
};

} // namespace stokhos

#endif // STOKHOS_ABSTRACT_GENERATOR_HPP

