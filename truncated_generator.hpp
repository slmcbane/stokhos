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

