#include <stdarg.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include "buildins.h"

/*
 *! some helper/debug function
 */
extern "C"
DECLSPEC int printvalue( int val )
{
    std::cout << /*"IDEBUG: " <<*/ val << "\n";
    return 1;
}

extern "C"
DECLSPEC double printdouble( double val )
{
    std::cout << /*"DDEBUG: " << */ val << "\n";
    return 1.;
}

/*! built in display function
 * it works like the C printf function and uses the same format string definition.
 */
extern "C"
DECLSPEC void display( char * str, ... )
{
    va_list argp;
    va_start( argp, str );
    vprintf( str, argp );
    va_end( argp );
}

/*! built in display function with newline
 * it works like the C printf function and uses the same format string definition.
 */
extern "C"
DECLSPEC void displayln( char * str, ... )
{
    char * outstr;
    va_list argp;
    va_start( argp, str );
    outstr = ( char* ) malloc( strlen( str ) + 2 );
    strcpy( outstr, str );
    strcat( outstr, "\n" );
    vprintf( outstr, argp );
    va_end( argp );
    free( outstr );
}

/*create file*/
extern "C"
DECLSPEC void createfile( char * fn)
{
    	std::ofstream outfile(fn);
	outfile.close();
}

/*append to file string*/
extern "C"
DECLSPEC void appendfilestring( char * fn, char * val)
{
	std::ofstream outfile;
  	outfile.open(fn, std::ios_base::app);
  	outfile << val; 
	outfile.close();
}

extern "C"
DECLSPEC void appendfileinteger( char * fn, int val)
{
	std::ofstream outfile;
  	outfile.open(fn, std::ios_base::app);
  	outfile << val; 
	outfile.close();
}

extern "C"
DECLSPEC void appendfiledouble( char * fn, double val)
{
	std::ofstream outfile;
  	outfile.open(fn, std::ios_base::app);
  	outfile << val; 
	outfile.close();
}

extern "C"
DECLSPEC double powdouble( double val )
{
        return val*val;
}

extern "C"
DECLSPEC double lessdouble( double val1 , double val2)
{
	if(val1>val2)
	{
		return val2;
	}
	else 
	{
        	return val1;
	}
}

extern "C"
DECLSPEC void help( char * str)
{
	std::cout << "\nTHIS IS HELP FUNCTIONS:" << "\n"; 
	std::cout << "int printvalue( int val )" << "\n"; 
	std::cout << "double printdouble( double val )" << "\n"; 
	std::cout << "void display( char * str, ... )"<< "\n"; 
	std::cout << "void displayln( char * str, ... )"<< "\n"; 
	std::cout << "void createfile( char * str)"<< "\n"; 
	std::cout << "void appendfilestring(  char * fn, char * val)"<< "\n"; 
	std::cout << "void appendfileinteger(  char * fn, int val)"<< "\n"; 
	std::cout << "void appendfiledouble(  char * fn, double val)"<< "\n"; 
	std::cout << "double powdouble( double val )"<< "\n"; 
	std::cout << "double lessdouble( double val1 , double val2)"<< "\n"; 
	std::cout << "void help( char * str)"<< "\n";
}

