/*
 * Copyright 2022 Sean McBane
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
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

