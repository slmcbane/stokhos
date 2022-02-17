cppc = meson.get_compiler('cpp')

testu01_mylib = cppc.find_library('mylib', dirs : get_option('testu01_dir'), static : true)

testu01_probdistlib = cppc.find_library('probdist',
    dirs : get_option('testu01_dir'), static : true)

testu01_lib = cppc.find_library('testu01', dirs : get_option('testu01_dir'), static : true)

executable('xoshiro256starstar_smallcrush', 'xoshiro256starstar_smallcrush.cpp',
  dependencies : [testu01_mylib, testu01_probdistlib, testu01_lib, stokhos_dep])

executable('xoshiro256starstar_crush', 'xoshiro256starstar_crush.cpp',
  dependencies : [testu01_mylib, testu01_probdistlib, testu01_lib, stokhos_dep])

