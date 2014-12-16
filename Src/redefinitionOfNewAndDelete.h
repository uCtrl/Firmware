#include "mbed.h"

extern Serial usbSerial;

void * operator new( unsigned int size, const char *filename, int line )
{
    void *ptr = (void *)malloc(size);
    usbSerial.printf("new at file %s: line %d with size %d bytes at memory adresse %d\r\n",filename,line,size,ptr);
    return(ptr);
};

void * operator new[]( unsigned int size, const char *filename, int line )
{
    void *ptr = (void *)malloc(size);
    usbSerial.printf("new[] at file %s: line %d with size %d bytes at memory adresse %d\r\n",filename,line,size,ptr);
    return(ptr);
};

void operator delete( void *ptr, const char *filename, int line )
{
    usbSerial.printf("delete ptr at adress %d, new made at %s line %d\r\n",ptr, filename, line);
    free( ptr );
}

void operator delete[]( void *ptr, const char *filename, int line )
{
    usbSerial.printf("delete[] ptr at adress %d, new made at %s line %d\r\n",ptr, filename, line);
    free( ptr );
}

#define DEBUG_NEW new(__FILE__, __LINE__)
#define new DEBUG_NEW