
#if defined(_MSC_VER)
#define DECLSPEC __declspec(dllexport) 
#else
#define DECLSPEC 
#endif


extern "C" DECLSPEC int printvalue( int val );
extern "C" DECLSPEC double printdouble( double val );
extern "C" DECLSPEC void display( char * str, ... );
extern "C" DECLSPEC void displayln( char * str, ... );
extern "C" DECLSPEC void createfile( char * str);
extern "C" DECLSPEC void appendfilestring(  char * fn, char * val);
extern "C" DECLSPEC void appendfileinteger(  char * fn, int val);
extern "C" DECLSPEC void appendfiledouble(  char * fn, double val);
extern "C" DECLSPEC double powdouble( double val );
extern "C" DECLSPEC double lessdouble( double val1 , double val2);
extern "C" DECLSPEC void help( char * str);
