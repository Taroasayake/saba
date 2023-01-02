# CMake generated Testfile for 
# Source directory: E:/DATA/SRC/saba/gtests
# Build directory: E:/DATA/SRC/saba/gtests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(all_test "E:/DATA/SRC/saba/gtests/Debug/gtests.exe")
  set_tests_properties(all_test PROPERTIES  _BACKTRACE_TRIPLES "E:/DATA/SRC/saba/gtests/CMakeLists.txt;41;add_test;E:/DATA/SRC/saba/gtests/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(all_test "E:/DATA/SRC/saba/gtests/Release/gtests.exe")
  set_tests_properties(all_test PROPERTIES  _BACKTRACE_TRIPLES "E:/DATA/SRC/saba/gtests/CMakeLists.txt;41;add_test;E:/DATA/SRC/saba/gtests/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(all_test "E:/DATA/SRC/saba/gtests/MinSizeRel/gtests.exe")
  set_tests_properties(all_test PROPERTIES  _BACKTRACE_TRIPLES "E:/DATA/SRC/saba/gtests/CMakeLists.txt;41;add_test;E:/DATA/SRC/saba/gtests/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(all_test "E:/DATA/SRC/saba/gtests/RelWithDebInfo/gtests.exe")
  set_tests_properties(all_test PROPERTIES  _BACKTRACE_TRIPLES "E:/DATA/SRC/saba/gtests/CMakeLists.txt;41;add_test;E:/DATA/SRC/saba/gtests/CMakeLists.txt;0;")
else()
  add_test(all_test NOT_AVAILABLE)
endif()
