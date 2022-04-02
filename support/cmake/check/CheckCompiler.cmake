#
# 添加检测模块
#
INCLUDE(CheckCXXCompilerFlag)


#
# 平台判断
#
IF(WIN32 AND CMAKE_CXX_COMPILER_ID MATCHES "MSVC")

	#
	# 检测C++编译器支持的特性
	#
	CHECK_CXX_COMPILER_FLAG("/std:c++14" CXX_COMPILER_SUPPORTS_14)
	CHECK_CXX_COMPILER_FLAG("/std:c++17" CXX_COMPILER_SUPPORTS_17)
	CHECK_CXX_COMPILER_FLAG("/std:c++20" CXX_COMPILER_SUPPORTS_20)

	#
	# 设置编译特性
	#
	IF(CXX_COMPILER_SUPPORTS_20)

		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++20")

	ELSEIF(CXX_COMPILER_SUPPORTS_17)

		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")

	ELSEIF(CXX_COMPILER_SUPPORTS_14)

		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++14")

	ENDIF()

ELSE()

	#
	# 检测C++编译器支持的特性
	#
	CHECK_CXX_COMPILER_FLAG("-std=c++11" CXX_COMPILER_SUPPORTS_11)
	CHECK_CXX_COMPILER_FLAG("-std=c++14" CXX_COMPILER_SUPPORTS_14)
	CHECK_CXX_COMPILER_FLAG("-std=c++17" CXX_COMPILER_SUPPORTS_17)
	CHECK_CXX_COMPILER_FLAG("-std=c++20" CXX_COMPILER_SUPPORTS_20)

	#
	# 设置编译特性
	#
	IF(CXX_COMPILER_SUPPORTS_20)

		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

	ELSEIF(CXX_COMPILER_SUPPORTS_17)

		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

	ELSEIF(CXX_COMPILER_SUPPORTS_14)

		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

	ELSEIF(CXX_COMPILER_SUPPORTS_11)

		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

	ELSE()

		MESSAGE(FATAL_ERROR "The CXX compiler ${CMAKE_CXX_COMPILER} does not support more than C++11 features.")

	ENDIF()

ENDIF()


#
# 设置C/C++编译选项
#
IF(CMAKE_CXX_COMPILER_ID MATCHES "GNU")

	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl")							# 支持显示加载动态库
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")							# 告诉编译器产生与位置无关代码, 则产生的代码中, 没有绝对地址, 全部使用相对地址
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")						# 链接线程库
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")						# 允许发出 ANSI C 标准所列的全部警告信息
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -rdynamic")						# 将所有符号添加到动态符号表中
	SET(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -fstack-check")					# 检测栈信息
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsigned-char")					# 将 char 类型设置成 signed char
	SET(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -fbounds-check")				# 检测数组边界
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finline-functions")			# 把所有简单的函数内联进调用者. 编译器会探索式地决定哪些函数足够简单, 值得做这种内联
	SET(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -fstack-protector-all")			# 保护栈信息
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer")		# 保留函数 SFP(Stack Frame Pointer), 即在函数调用时保存栈帧指针SFP
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")							# 会打开一些很有用的警告选项
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")						# 打印一些额外的警告信息
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow")						# 当一个局部变量遮盖住了另一个局部变量, 或者全局变量, 给出警告
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wreorder")						# 如果代码中的成员变量的初始化顺序和它们实际执行时初始化顺序不一致, 给出警告
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverflow")					# 范围溢出, 给出警告
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-align")					# 某个指针类型强制转换导致目标所需的地址对齐增加, 给出警告
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wconversion")					# 对一些可能改变值的隐式转换, 给出警告
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wfatal-errors")				# 出现错误的时候停止编译
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wwrite-strings")				# 把字符串常量赋值给 non-const char * 指针, 给出警告
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpointer-arith")				# 对函数指针或者 void * 类型的指针进行算术操作, 给出警告
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wold-style-cast")				# 如果存在 c 风格类型转换, 给出警告
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wredundant-decls")				# 如果在同一个可见域内某定义多次声明, 给出警告
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-result")			# 如果存在未使用的返回值, 忽略警告
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunreachable-code")			# 如果编译器探测到永远不会执行到的代码, 给出警告
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wctor-dtor-privacy")			# 当一个类没有用时, 给出警告
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wreturn-local-addr")			# 如果返回临时引用, 给出警告
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual")			# 如果函数的声明隐藏住了基类的虚函数, 给出警告
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused-but-set-variable")		# 设置了但未使用的变量, 给出警告
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wsizeof-pointer-memaccess")	# 无法保证完整初始化类, 给出警告

	IF(${CMAKE_BUILD_TYPE} MATCHES Debug)

		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")						# 生成操作系统本地格式的调试信息
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb")						# 生成gdb专用的调试信息, 会有一些gdb专用的扩展

	ELSE()

		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")						# 优化代码空间

	ENDIF()

ELSEIF(CMAKE_CXX_COMPILER_ID MATCHES "Clang")

	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")							# 告诉编译器产生与位置无关代码, 则产生的代码中, 没有绝对地址, 全部使用相对地址
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")						# 链接线程库
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsigned-char")					# 将char类型设置成signed char
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finline-functions")			# 把所有简单的函数内联进调用者. 编译器会探索式地决定哪些函数足够简单, 值得做这种内联
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer")		# 保留函数 SFP(Stack Frame Pointer), 即在函数调用时保存栈帧指针SFP
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")							# 会打开一些很有用的警告选项
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")						# 打印一些额外的警告信息
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow")						# 当一个局部变量遮盖住了另一个局部变量, 或者全局变量, 给出警告
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverflow")					# 范围溢出, 给出警告
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wconversion")					# 对一些可能改变值的隐式转换, 给出警告
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-align")					# 某个指针类型强制转换导致目标所需的地址对齐增加, 给出警告
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wfatal-errors")				# 出现错误的时候停止编译
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wwrite-strings")				# 把字符串常量赋值给 non-const char * 指针, 给出警告
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpointer-arith")				# 对函数指针或者 void * 类型的指针进行算术操作, 给出警告
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wold-style-cast")				# 如果存在 c 风格类型转换, 给出警告
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wredundant-decls")				# 如果在同一个可见域内某定义多次声明, 给出警告
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunreachable-code")			# 如果编译器探测到永远不会执行到的代码, 给出警告
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual")			# 如果函数的声明隐藏住了基类的虚函数, 给出警告
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wreturn-stack-address")		# 如果返回临时引用, 给出警告
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused-const-variable")		# 设置了但未使用的const变量, 给出警告
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wsizeof-pointer-memaccess")	# 无法保证完整初始化类, 给出警告

	IF(${CMAKE_BUILD_TYPE} MATCHES Debug)

		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")						# 生成操作系统本地格式的调试信息
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb")						# 生成gdb专用的调试信息, 会有一些gdb专用的扩展

	ELSE()

		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")						# 优化代码空间

	ENDIF()

ELSEIF(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")

	SET(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} /GF")			# 启用字符串池
	SET(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} /GR")			# 启用运行时类型信息 (RTTI)
	SET(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} /GS")			# 检查缓冲区安全性
	SET(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} /GT")			# 支持使用静态线程本地存储分配的数据的纤程安全
	SET(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} /MP")			# 启用多处理器编译
	SET(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} /EHs")			# 启用同步 C++ 异常处理
	SET(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} /sdl")			# 启用更多安全功能和警告
	SET(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} /utf-8")		# 将源和执行字符集设置为 UTF-8

	IF(${CMAKE_BUILD_TYPE} MATCHES Debug)

		SET(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} /Zi")		# 生成完整的调试信息
		SET(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} /MDd")		# 采用多线程CRT库的动态dll版本
		SET(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} /DEBUG")	# 定义

	ELSE()

		SET(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} /MD")		# 采用多线程CRT库的动态dll版本

	ENDIF()

ENDIF()
