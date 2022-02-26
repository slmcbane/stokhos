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
#ifndef STOKHOS_TRUNCATED_GENERATOR_HPP
#define STOKHOS_TRUNCATED_GENERATOR_HPP

#include "abstract_generator.hpp"

namespace stokhos
{

template <class Generator, class OutputInteger>
class TruncatedGenerator : public AbstractRNG<OutputInteger, Generator>
{
  public:
    using AbstractRNG<OutputInteger, Generator>::AbstractRNG;

    static_assert(
        sizeof(OutputInteger) <= sizeof(typename Generator::result_type),
        "Can't truncate a smaller integer to a larger one!");

    OutputInteger operator()()
    {
        return static_cast<OutputInteger>(
            this->m_state() &
            static_cast<typename Generator::result_type>(static_cast<OutputInteger>(-1)));
    }
};

} // namespace stokhos

#endif // STOKHOS_TRUNCATED_GENERATOR_HPP

