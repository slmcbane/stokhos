testu01_lib = cppc.find_library('testu01', dirs : get_option('testu01_dir'), static : true)

executable('xorshiro256starstar_smallcrush', xoshiro256starstar_smallcrush.cpp,
  link_with : testu01_lib, dependencies : stokhos_dep)
