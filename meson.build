project('stokhos', ['cpp'])

stokhos_dep = declare_dependency(include_directories : include_directories('.'))

if not meson.is_subproject()
  subdir('test')
endif

