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
#include "cdecls.hpp"

#include "pcg_xsl_rr_mcg.hpp"
#include "truncated_generator.hpp"

using namespace stokhos;

static_assert(std::is_same<uint32_t, unsigned int>::value, "Uh oh");

uint32_t reverse_bits(uint32_t n)
{
    n = ((n >> 1) & 0x55555555) | ((n << 1) & 0xaaaaaaaa);
    n = ((n >> 2) & 0x33333333) | ((n << 2) & 0xcccccccc);
    n = ((n >> 4) & 0x0f0f0f0f) | ((n << 4) & 0xf0f0f0f0);
    n = ((n >> 8) & 0x00ff00ff) | ((n << 8) & 0xff00ff00);
    n = ((n >> 16) & 0x0000ffff) | ((n << 16) & 0xffff0000);
    return n;
}

uint32_t get_next()
{
    static auto rng = TruncatedGenerator<PCG_XSL_RR_MCG, uint32_t>(PCG_XSL_RR_MCG());
    return rng();
}

uint32_t get_next_reversed() { return reverse_bits(get_next()); }

int main()
{
    char name1[] = "pcg_xsl_rr_mcg lower 32";
    unif01_Gen *gen = unif01_CreateExternGenBits(name1, get_next);
    bbattery_Crush(gen);
    unif01_DeleteExternGenBits(gen);

    char name2[] = "pcg_xsl_rr_mcg lower 32 reversed";
    gen = unif01_CreateExternGenBits(name2, get_next_reversed);
    bbattery_Crush(gen);
    unif01_DeleteExternGenBits(gen);

    return 0;
}
