# Stokhos
This is my opinionated C++ implementation of several useful random number
generators. All of these generators are much more performant than the
Mersenne Twister included in the standard library, and when used with their
default output type (either 64-bit or 32-bit integer) they pass the BigCrush
test suite.

Seeding properly is probably the hardest thing to do correctly; here I have
leaned on existing implementations to make sure that the generators are
initialized well even when passed a fixed starting seed. Default constructors
generally take entropy from /dev/urandom to initialize the generator (I'm not
worrying about Windows support).

All generators inherit from a templated class
`AbstractGenerator<output type, state type, min = 0, max = std::numeric_limits<output type>::max>`,
allowing polymorphic use of the generators.

When used as a dependency this library is header-only. The 'test' directory contains
the source files and build definition needed to compile tests using the TestU01
test suite, which will require the static libraries for TestU01 to be present on
your system.

# Copyright
Copyright 2022 Sean McBane under the MIT license:

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in the
Software without restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
Software, and to permit persons to whom the Software is furnished to do so, subject
to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

# Attribution
My implementations of generators from the PCG family are derived from Melissa
O'Neill's canonical implementations; see <http://www.pcg-random.org>. These
implementations are:

Copyright 2014-2021 Melissa O'Neill and PCG Project contributors.

The distribution of this derivative work is permitted under the terms of the
Apache 2.0 license assigned to the original works, and that license is contained
in the file "apache_2.0.txt" as required by the license conditions.
