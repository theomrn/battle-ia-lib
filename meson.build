
project('battle_c_bot', ['c', 'cpp'],
  version: '0.1.0',
)

# Dependencies
battle_c_subproject = subproject('battle_c')
battle_c_dep = battle_c_subproject.get_variable('battle_c_dep')# Create the executable

executable_sources = ['./src/main.c','./src/tool.c','./src/movement.c','./src/shoot.c','./src/radar.c']

incdir = include_directories('/usr/local/include')
inc_local = include_directories('./include')

executable(
  'battle_c_bot',
  executable_sources,
  include_directories: [incdir, inc_local],
  dependencies: [battle_c_dep],
 )


