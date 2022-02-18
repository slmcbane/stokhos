#include "cdecls.hpp"

#include "pcg_xsl_rr_mcg.hpp"

#include <random>

using namespace stokhos;

double get_next()
{
    static auto rng = stokhos::PCG_XSL_RR_MCG();

    return std::generate_canonical<double, 64>(rng);
}

int main()
{
    char name[] = "pcg_xsl_rr_mcg";
    unif01_Gen *gen = unif01_CreateExternGen01(name, get_next);

    bbattery_Crush(gen);
    unif01_DeleteExternGen01(gen);

    return 0;
}
