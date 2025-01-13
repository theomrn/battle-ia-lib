project('battle_c_lib', 'cpp',
  version: '1.0',
  default_options: ['cpp_std=c++17'])

inc_dir = include_directories('include')

boost_dep = dependency('boost', required: true)

# Define protobuf compiler and libraries
protobuf_dep = dependency('protobuf', required: true)

protoc = find_program('protoc', required : true)


gen = generator(protoc, \
  output    : ['@BASENAME@.pb.cc', '@BASENAME@.pb.h'],
  arguments : ['--proto_path=@CURRENT_SOURCE_DIR@', '--cpp_out=@BUILD_DIR@', '--experimental_allow_proto3_optional', '@INPUT@'])

generated = gen.process('battle_c.proto')

subdir('src')
# subdir('src/test_client')
