#ifndef _PHPTMP_
#define _PHPTMP_ 1


#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>//for INT_MAX

void efree(void* p);
//clq add test
void * emalloc(int len);
void * erealloc(void *mem_address, unsigned int newsize);

char * estrdup(char *s);

void * ecalloc(size_t n, size_t size);

void * gdPMalloc(size_t n);

char * gdPEstrdup(char *s);

void gdPFree(void* p);

size_t php_stream_read  (FILE *stream, void *buffer, size_t size);

size_t php_stream_write(const void* buffer, size_t size, size_t count, FILE* stream);

size_t php_stream_close(FILE* stream);

FILE * php_stream_open(const char * path,const char * mode);

long php_stream_tell (FILE* stream);

int php_stream_seek(FILE *stream, long offset, int fromwhere);

int php_stream_eof (FILE* stream);

//php.h 中的
//PHPAPI void php_error_docref0(const char *docref TSRMLS_DC, int type, const char *format, ...)
void php_error_docref(const char *docref, int type, const char *format, ...);

void * safe_emalloc(size_t size, size_t count, int v);

#define RETURN_FALSE return

#define TSRMLS_CC

#define E_WARNING 1

#define RETURN_TRUE return

//2147483647
//#define INT_MAX 65536

#define zend_bool int

#define zval void

#define FAILURE 0

// #define ZEND_FETCH_RESOURCE(rsrc, rsrc_type, passed_id, default_id, resource_type_name, resource_type)	\
// 	rsrc = (rsrc_type) zend_fetch_resource(passed_id TSRMLS_CC, default_id, resource_type_name, NULL, 1, resource_type);	\
// 	ZEND_VERIFY_RESOURCE(rsrc);

#define PHP_FUNCTION(fun) void fun()

#define ZEND_FETCH_RESOURCE(rsrc, rsrc_type, passed_id, default_id, resource_type_name, resource_type)	

#define RETURN_LONG(ct)

#define ZEND_NUM_ARGS() 1

int zend_parse_parameters(int ZEND_NUM_ARGS1, ...);//必须 return 1

#define E_NOTICE 1
#define E_WARNING 1
#define E_ERROR 1

#define ssize_t int

#define MAXPATHLEN  1024

#define ZEND_REGISTER_RESOURCE(return_value1, im, le_gd)

#define return_value 1

#define TSRMLS_DC

#define php_stream FILE

//应当是将文件内容读取到缓冲区中//char *buff
//int php_stream_copy_to_mem(stream, &buff, PHP_STREAM_COPY_ALL, 1);
int php_stream_copy_to_mem(FILE * stream, char ** buf, int t, int i_1);


#endif

