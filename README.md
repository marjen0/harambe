

BUILD COMPILATOR:
	clone git in pkt2 catalog
	create build catalog
	go to build catalog
		cmake ..	
		make

MOVE COMPILED FILE FOR TO TESTING:
	from pkt2 -> build
	pkt2 -> test
	current catalog build:
		cp pkt2 ../test/pkt2

RUN FILE FOR TESTING:
	from directory pkt2 -> test
	./pkt2 test.pkt2 -d


CATALOG TREE:
	tree -d pkt2

		    └── pkt2
			├── build
			│   └── CMakeFiles
			│       ├── 3.10.2
			│       │   ├── CompilerIdC
			│       │   │   └── tmp
			│       │   └── CompilerIdCXX
			│       │       └── tmp
			│       ├── CMakeTmp
			│       └── pkt2.dir
			└── test
NEEDED FILES:

		    └── pkt2
			├── AstNode.cpp
			├── AstNode.h
			├── build
			├── parser.y
			├── test
			│   ├── pkt2
			│   └── test.pkt2
			├── tokens.l

FILES TREE:
	tree pkt2

		    └── pkt2
			├── Array.cpp
			├── AstNode.cpp
			├── AstNode.h
			├── build
			│   ├── CMakeCache.txt
			│   ├── CMakeFiles
			│   │   ├── 3.10.2
			│   │   │   ├── CMakeCCompiler.cmake
			│   │   │   ├── CMakeCXXCompiler.cmake
			│   │   │   ├── CMakeDetermineCompilerABI_C.bin
			│   │   │   ├── CMakeDetermineCompilerABI_CXX.bin
			│   │   │   ├── CMakeSystem.cmake
			│   │   │   ├── CompilerIdC
			│   │   │   │   ├── a.out
			│   │   │   │   ├── CMakeCCompilerId.c
			│   │   │   │   └── tmp
			│   │   │   └── CompilerIdCXX
			│   │   │       ├── a.out
			│   │   │       ├── CMakeCXXCompilerId.cpp
			│   │   │       └── tmp
			│   │   ├── cmake.check_cache
			│   │   ├── CMakeDirectoryInformation.cmake
			│   │   ├── CMakeOutput.log
			│   │   ├── CMakeRuleHashes.txt
			│   │   ├── CMakeTmp
			│   │   ├── feature_tests.bin
			│   │   ├── feature_tests.c
			│   │   ├── feature_tests.cxx
			│   │   ├── Makefile2
			│   │   ├── Makefile.cmake
			│   │   ├── pkt2.dir
			│   │   │   ├── Array.cpp.o
			│   │   │   ├── AstNode.cpp.o
			│   │   │   ├── buildins.cpp.o
			│   │   │   ├── build.make
			│   │   │   ├── ClassDeclaration.cpp.o
			│   │   │   ├── cmake_clean.cmake
			│   │   │   ├── CodeGenContext.cpp.o
			│   │   │   ├── CXX.includecache
			│   │   │   ├── Declaration.cpp.o
			│   │   │   ├── DependInfo.cmake
			│   │   │   ├── depend.internal
			│   │   │   ├── depend.make
			│   │   │   ├── flags.make
			│   │   │   ├── FunctionDeclaration.cpp.o
			│   │   │   ├── GetOpt.cpp.o
			│   │   │   ├── link.txt
			│   │   │   ├── main.cpp.o
			│   │   │   ├── parser.cpp.o
			│   │   │   ├── progress.make
			│   │   │   ├── Range.cpp.o
			│   │   │   ├── tokens.cpp.o
			│   │   │   ├── VisitorPrettyPrint.cpp.o
			│   │   │   └── VisitorSyntaxCheck.cpp.o
			│   │   ├── progress.marks
			│   │   └── TargetDirectories.txt
			│   ├── cmake_install.cmake
			│   ├── Makefile
			│   ├── parser.cpp
			│   ├── parser.hpp
			│   ├── parser.output
			│   └── tokens.cpp
			├── buildins.cpp
			├── buildins.h
			├── ClassDeclaration.cpp
			├── ClassDeclaration.h
			├── CMakeLists.txt
			├── CodeGenContext.cpp
			├── CodeGenContext.h
			├── config.h
			├── config.in
			├── Declaration.cpp
			├── FunctionDeclaration.cpp
			├── FunctionDeclaration.h
			├── GetOpt.cpp
			├── GetOpt.h
			├── LICENSE
			├── main.cpp
			├── main.h
			├── parser.y
			├── Range.cpp
			├── README.md
			├── test
			│   ├── pkt2
			│   └── test.pkt2
			├── tokens.l
			├── Visitor.h
			├── VisitorPrettyPrint.cpp
			├── VisitorPrettyPrint.h
			├── VisitorSyntaxCheck.cpp
			└── VisitorSyntaxCheck.h

Comments:
	long comment:
		/..
		../
		NOTE! "../" should be in new line
	onle line comment: 
		~
	example:
		/..displayln("IT'S LONG COMMENT")
		../

		/..
		its long comment also
		displayln("IT'S LONG COMMENT ALSO")
		../

		~it's one line comment
		~displayln("IT'S ONE LINE COMMENT")

Functions:
	int printvalue( int val );
	double printdouble( double val );
	display( char * str, ... );
	displayln( char * str, ... );
	createfile( char * str);
	appendfilestring(  char * fn, char * val);
	appendfileinteger(  char * fn, int val);
	appendfiledouble(  char * fn, double val);
	double powdouble( double val );
	double lessdouble( double val1 , double val2);
