cmake_minimum_required(VERSION 3.10)

# set the project name
project(helloword)
SET (LIB_NAME hello)

FILE (GLOB LIBHELLO_SRC "*.cpp" )

# 结果生成在编译目录下的lib目录
SET (LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
ADD_LIBRARY (${LIB_NAME} SHARED ${LIBHELLO_SRC})

# 因为hello作为一个target是不能重名的， 故把上面的hello修改为hello_static
ADD_LIBRARY (${LIB_NAME}_static STATIC ${LIBHELLO_SRC})

# 希望 "hello_static" 在输出时，不是"hello_static"，而是以"hello"的名字显示，故设置如下：
SET_TARGET_PROPERTIES (${LIB_NAME}_static PROPERTIES OUTPUT_NAME ${LIB_NAME})

# cmake在构建一个新的target时，会尝试清理掉其他使用这个名字的库，
# 为了回避这个问题，再次使用SET_TARGET_PROPERTIES定义 CLEAN_DIRECT_OUTPUT属性。
SET_TARGET_PROPERTIES (${LIB_NAME}_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES (${LIB_NAME} PROPERTIES CLEAN_DIRECT_OUTPUT 1)

# 按照规则，动态库是应该包含一个版本号的，
# VERSION指代动态库版本，SOVERSION指代API版本。
SET_TARGET_PROPERTIES (${LIB_NAME} PROPERTIES VERSION 1.2 SOVERSION 1)

# 我们需要将libhello.a, libhello.so.x以及hello.h安装到系统目录，才能真正让其他人开发使用，
# 在本例中我们将hello的共享库安装到<prefix>/lib目录；
# 将hello.h安装<prefix>/include/hello目录。
# INSTALL (TARGETS ${LIB_NAME} ${LIB_NAME}_static LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
# INSTALL (FILES hello.h DESTINATION include/hello)