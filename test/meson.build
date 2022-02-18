cppc = meson.get_compiler('cpp')

testu01_mylib = cppc.find_library('mylib', dirs : get_option('testu01_dir'), static : true)

testu01_probdistlib = cppc.find_library('probdist',
    dirs : get_option('testu01_dir'), static : true)

testu01_lib = cppc.find_library('testu01', dirs : get_option('testu01_dir'), static : true)

executable('xoshiro256starstar_lower32', 'xoshiro256starstar_lower32.cpp',
  dependencies : [testu01_mylib, testu01_probdistlib, testu01_lib, stokhos_dep])

executable('xoshiro256starstar_upper32', 'xoshiro256starstar_upper32.cpp',
  dependencies : [testu01_mylib, testu01_probdistlib, testu01_lib, stokhos_dep])

executable('xoshiro256starstar', 'xoshiro256starstar.cpp',
  dependencies : [testu01_mylib, testu01_probdistlib, testu01_lib, stokhos_dep])

executable('pcg_xsl_rr_mcg', 'pcg_xsl_rr_mcg.cpp',
  dependencies : [testu01_mylib, testu01_probdistlib, testu01_lib, stokhos_dep])

executable('pcg_xsl_rr_mcg_lower32', 'pcg_xsl_rr_mcg_lower32.cpp',
  dependencies : [testu01_mylib, testu01_probdistlib, testu01_lib, stokhos_dep])

executable('pcg_xsl_rr_mcg_upper32', 'pcg_xsl_rr_mcg_upper32.cpp',
  dependencies : [testu01_mylib, testu01_probdistlib, testu01_lib, stokhos_dep])

