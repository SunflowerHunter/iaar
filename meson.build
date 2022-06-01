project('iaar', ['cpp', 'c'],
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++14'])

dep_glfw = dependency('glfw3')
my_inc = include_directories('include')

#subdir('include')
subdir('src')

executable('iaar',
           sources,
           dependencies : dep_glfw,
           include_directories : my_inc,
           )
