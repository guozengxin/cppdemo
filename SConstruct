
import sys
sys.path.insert(0, '/data00/tiger/typhoon-blade/src/blade')


import os
import subprocess
import signal
import time
import socket
import glob

import blade_util
import console
import scons_helper

from build_environment import ScacheManager
from console import colors
from scons_helper import MakeAction
from scons_helper import create_fast_link_builders
from scons_helper import echospawn
from scons_helper import error_colorize
from scons_helper import generate_python_binary
from scons_helper import generate_resource_file
from scons_helper import generate_resource_index

if not os.path.exists('build64_release'):
    os.mkdir('build64_release')
os.environ["LC_ALL"] = "C"
top_env = Environment(ENV=os.environ,LINKCOM = '$LINK -o $TARGET $LINKFLAGS $__RPATH $SOURCES $_LIBDIRFLAGS -Wl,--start-group $_LIBFLAGS -Wl,--end-group')
top_env.Decider("MD5-timestamp")
top_env.SetOption("implicit_cache", 1)
top_env.SetOption("max_drift", 1)
console.color_enabled=True
top_env["SPAWN"] = echospawn

compile_proto_cc_message = console.erasable('%sCompiling %s$SOURCE%s to cc source%s' %     (colors('cyan'), colors('purple'), colors('cyan'), colors('end')))

compile_proto_java_message = console.erasable('%sCompiling %s$SOURCE%s to java source%s' %     (colors('cyan'), colors('purple'), colors('cyan'), colors('end')))

compile_proto_php_message = console.erasable('%sCompiling %s$SOURCE%s to php source%s' %     (colors('cyan'), colors('purple'), colors('cyan'), colors('end')))

compile_proto_python_message = console.erasable('%sCompiling %s$SOURCE%s to python source%s' %     (colors('cyan'), colors('purple'), colors('cyan'), colors('end')))

generate_proto_descriptor_message = console.inerasable('%sGenerating proto descriptor set %s$TARGET%s' %     (colors('cyan'), colors('purple'), colors('end')))

compile_thrift_cc_message = console.erasable('%sCompiling %s$SOURCE%s to cc source%s' %     (colors('cyan'), colors('purple'), colors('cyan'), colors('end')))

compile_thrift_java_message = console.erasable('%sCompiling %s$SOURCE%s to java source%s' %     (colors('cyan'), colors('purple'), colors('cyan'), colors('end')))

compile_thrift_python_message = console.erasable( '%sCompiling %s$SOURCE%s to python source%s' %     (colors('cyan'), colors('purple'), colors('cyan'), colors('end')))

compile_fbthrift_cpp_message = console.erasable('%sCompiling %s$SOURCE%s to cpp source%s' %     (colors('cyan'), colors('purple'), colors('cyan'), colors('end')))

compile_fbthrift_cpp2_message = console.erasable('%sCompiling %s$SOURCE%s to cpp2 source%s' %     (colors('cyan'), colors('purple'), colors('cyan'), colors('end')))

compile_resource_index_message = console.erasable('%sGenerating resource index for %s$SOURCE_PATH/$TARGET_NAME%s%s' %     (colors('cyan'), colors('purple'), colors('cyan'), colors('end')))

compile_resource_message = console.erasable('%sCompiling %s$SOURCE%s as resource file%s' %     (colors('cyan'), colors('purple'), colors('cyan'), colors('end')))

compile_source_message = console.erasable('%sCompiling %s$SOURCE%s%s' %     (colors('cyan'), colors('purple'), colors('cyan'), colors('end')))

assembling_source_message = console.erasable('%sAssembling %s$SOURCE%s%s' %     (colors('cyan'), colors('purple'), colors('cyan'), colors('end')))

link_program_message = console.inerasable('%sLinking Program %s$TARGET%s%s' %     (colors('green'), colors('purple'), colors('green'), colors('end')))

link_library_message = console.inerasable('%sCreating Static Library %s$TARGET%s%s' %     (colors('green'), colors('purple'), colors('green'), colors('end')))

ranlib_library_message = console.inerasable('%sRanlib Library %s$TARGET%s%s' %     (colors('green'), colors('purple'), colors('green'), colors('end')))

link_shared_library_message = console.inerasable('%sLinking Shared Library %s$TARGET%s%s' %     (colors('green'), colors('purple'), colors('green'), colors('end')))

compile_java_jar_message = console.inerasable('%sGenerating java jar %s$TARGET%s%s' %     (colors('cyan'), colors('purple'), colors('cyan'), colors('end')))

compile_python_binary_message = console.erasable('%sGenerating python binary %s$TARGET%s%s' %     (colors('cyan'), colors('purple'), colors('cyan'), colors('end')))

compile_yacc_message = console.erasable('%sYacc %s$SOURCE%s to $TARGET%s' %     (colors('cyan'), colors('purple'), colors('cyan'), colors('end')))

compile_swig_python_message = console.erasable('%sCompiling %s$SOURCE%s to python source%s' %     (colors('cyan'), colors('purple'), colors('cyan'), colors('end')))

compile_swig_java_message = console.erasable('%sCompiling %s$SOURCE%s to java source%s' %     (colors('cyan'), colors('purple'), colors('cyan'), colors('end')))

compile_swig_php_message = console.erasable('%sCompiling %s$SOURCE%s to php source%s' %     (colors('cyan'), colors('purple'), colors('cyan'), colors('end')))


top_env.Append(
    CXXCOMSTR = compile_source_message,
    CCCOMSTR = compile_source_message,
    ASCOMSTR = assembling_source_message,
    SHCCCOMSTR = compile_source_message,
    SHCXXCOMSTR = compile_source_message,
    ARCOMSTR = link_library_message,
    RANLIBCOMSTR = ranlib_library_message,
    SHLINKCOMSTR = link_shared_library_message,
    LINKCOMSTR = link_program_message,
    JAVACCOMSTR = compile_source_message
)
VariantDir("build64_release", ".", duplicate=0)

env_version = Environment(ENV = os.environ)
env_version.Append(SHCXXCOMSTR = console.erasable('%sUpdating version information%s' % (colors('cyan'), colors('end'))))
env_version.Append(CPPFLAGS = '-m64')
version_obj = env_version.SharedObject('build64_release/version.cpp')

time_value = Value("Fri Dec  7 12:22:39 2018")

def proto_generator(source, target, env, for_signature):
    proto_path = " ".join("--proto_path='%s'" % (p) for p in env['PROTOPATH'])
    return MakeAction("cpp3rdlib/protobuf/bin/protoc --proto_path=. --proto_path= %s --cpp_out=build64_release $SOURCE" % (proto_path), compile_proto_cc_message)
proto_bld = Builder(generator = proto_generator)

proto_java_bld = Builder(action = MakeAction("cpp3rdlib/protobuf/bin/protoc --proto_path=. --proto_path= --java_out=build64_release/`dirname $SOURCE` $SOURCE", compile_proto_java_message))
proto_php_bld = Builder(action = MakeAction("cpp3rdlib/protobuf/bin/protoc thirdparty/Protobuf-PHP/protoc-gen-php.php --proto_path=. --plugin=protoc-gen-php= -I. -Ithirdparty/Protobuf-PHP/library -I=`dirname $SOURCE` --php_out=build64_release/`dirname $SOURCE` $SOURCE", compile_proto_php_message))
proto_python_bld = Builder(action = MakeAction("cpp3rdlib/protobuf/bin/protoc  --proto_path=. -I. -I=`dirname $SOURCE` --python_out=build64_release $SOURCE", compile_proto_python_message))
proto_descriptor_bld = Builder(action = MakeAction("cpp3rdlib/protobuf/bin/protoc  --proto_path=. -I. -I=`dirname $SOURCE` --descriptor_set_out=$TARGET --include_imports --include_source_info $SOURCES", generate_proto_descriptor_message))
thrift_bld = Builder(action = MakeAction("cpp3rdlib/thrift/bin/thrift --gen cpp:include_prefix -I . -I `dirname $SOURCE` -out build64_release/`dirname $SOURCE` $SOURCE", compile_thrift_cc_message))
thrift_java_bld = Builder(action = MakeAction("cpp3rdlib/thrift/bin/thrift --gen java -I . -I cpp3rdlib/thrift/include -I `dirname $SOURCE` -out build64_release/`dirname $SOURCE` $SOURCE", compile_thrift_java_message))
thrift_python_bld = Builder(action = MakeAction("cpp3rdlib/thrift/bin/thrift --gen py -I . -I cpp3rdlib/thrift/include -I `dirname $SOURCE` -out build64_release/`dirname $SOURCE` $SOURCE", compile_thrift_python_message))

def fbthrift1_generator(source, target, env, for_signature):
    src = os.path.dirname(str(source[0]))
    dest = os.path.dirname(str(target[0]))
    return MakeAction("cpp3rdlib/fbthrift/bin/thrift1.sh --gen cpp:enum_strict,include_prefix -I .  -I '%s' -out '%s' $SOURCE" % (src, dest), compile_fbthrift_cpp_message)
fbthrift1_bld = Builder(generator = fbthrift1_generator)


def fbthrift2_generator(source, target, env, for_signature):
    src = os.path.dirname(str(source[0]))
    dest = os.path.dirname(str(target[0]))
    pos = dest.rfind("gen-cpp2")
    dest = dest[:pos]
    return MakeAction("cpp3rdlib/fbthrift/bin/thrift2.sh --gen cpp2:include_prefix='%s',compatibility -I . -I '%s' -o '%s' $SOURCE" % (src, dest, dest), compile_fbthrift_cpp2_message)
fbthrift2_bld = Builder(generator = fbthrift2_generator)


blade_jar_bld = Builder(action = MakeAction('jar cf $TARGET -C `dirname $SOURCE` .',
    compile_java_jar_message))

yacc_bld = Builder(action = MakeAction('bison $YACCFLAGS -d -o $TARGET $SOURCE',
    compile_yacc_message))

resource_index_bld = Builder(action = MakeAction(generate_resource_index,
    compile_resource_index_message))

resource_file_bld = Builder(action = MakeAction(generate_resource_file,
    compile_resource_message))

python_binary_bld = Builder(action = MakeAction(generate_python_binary,
    compile_python_binary_message))

top_env.Append(BUILDERS = {"Proto" : proto_bld})
top_env.Append(BUILDERS = {"ProtoJava" : proto_java_bld})
top_env.Append(BUILDERS = {"ProtoPhp" : proto_php_bld})
top_env.Append(BUILDERS = {"ProtoPython" : proto_python_bld})
top_env.Append(BUILDERS = {"ProtoDescriptors" : proto_descriptor_bld})
top_env.Append(BUILDERS = {"Thrift" : thrift_bld})
top_env.Append(BUILDERS = {"ThriftJava" : thrift_java_bld})
top_env.Append(BUILDERS = {"ThriftPython" : thrift_python_bld})
top_env.Append(BUILDERS = {"FBThrift1" : fbthrift1_bld})
top_env.Append(BUILDERS = {"FBThrift2" : fbthrift2_bld})
top_env.Append(BUILDERS = {"BladeJar" : blade_jar_bld})
top_env.Append(BUILDERS = {"Yacc" : yacc_bld})
top_env.Append(BUILDERS = {"ResourceIndex" : resource_index_bld})
top_env.Append(BUILDERS = {"ResourceFile" : resource_file_bld})
top_env.Append(BUILDERS = {"PythonBinary" : python_binary_bld})
nvcc_object_bld = Builder(action = MakeAction("nvcc -ccbin g++  $NVCCFLAGS -o $TARGET -c $SOURCE", compile_source_message))
nvcc_binary_bld = Builder(action = MakeAction("nvcc  $NVCCFLAGS -o $TARGET ", link_program_message))
top_env.Append(BUILDERS = {"NvccObject" : nvcc_object_bld})
top_env.Append(BUILDERS = {"NvccBinary" : nvcc_binary_bld})
top_env.Replace(CC="gcc", CXX="g++", NVCC="nvcc", CPPPATH=["", "build64_release", "/usr/include/python2.7"], CPPFLAGS=['-m64', '-mcx16', '-pipe', '-g', '-DNDEBUG', '-D_FILE_OFFSET_BITS=64', '-D__STDC_CONSTANT_MACROS', '-D__STDC_FORMAT_MACROS', '-D__STDC_LIMIT_MACROS'], CFLAGS=['-DHAVE_CONFIG_H', '-DHAVE_NETINET_IN_H', '-DHAVE_INTTYPES_H', '-DLINUX'], CXXFLAGS=['-std=c++14'], LINK="g++", LINKFLAGS=['-m64'])
env_with_error = top_env.Clone()
env_no_warning = top_env.Clone()
env_with_error.Append(CPPFLAGS=['-Wall', '-Wextra', '-Wno-unused-function', '-Wno-unused-local-typedefs', '-Wno-unused-parameter', '-Wno-unused-variable', '-Wno-error=missing-field-initializers', '-Wno-error=sign-compare', '-Wno-error=unused-but-set-variable'], CFLAGS=['-Werror-implicit-function-declaration'], CXXFLAGS=['-Wnon-virtual-dtor', '-Wvla'])

env_v___mAgIc_demo = env_with_error.Clone()
env_v___mAgIc_demo.Append(CPPFLAGS=['-O2', '-fno-omit-frame-pointer'])
env_v___mAgIc_demo.Append(ASFLAGS=['--64'])
obj_v___mAgIc_demo__src_x_main_cpp = env_v___mAgIc_demo.SharedObject(target = "build64_release/./demo.objs/src/main.cpp" + top_env["OBJSUFFIX"], source = "build64_release/./src/main.cpp")
obj_v___mAgIc_demo__src_x_cpp11_x_auto_cpp = env_v___mAgIc_demo.SharedObject(target = "build64_release/./demo.objs/src/cpp11/auto.cpp" + top_env["OBJSUFFIX"], source = "build64_release/./src/cpp11/auto.cpp")
v___mAgIc_demo_objects = [obj_v___mAgIc_demo__src_x_main_cpp,obj_v___mAgIc_demo__src_x_cpp11_x_auto_cpp]
env_v___mAgIc_demo.Append(LINKFLAGS=[])
v___mAgIc_demo = env_v___mAgIc_demo.Program("build64_release/./demo", v___mAgIc_demo_objects, LIBS=['glog'])
env_v___mAgIc_demo.Append(LINKFLAGS=str(version_obj[0]))
env_v___mAgIc_demo.Requires(v___mAgIc_demo, version_obj)
