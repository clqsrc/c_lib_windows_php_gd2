/*
   +----------------------------------------------------------------------+
   | PHP Version 5                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2016 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Stanislav Malyshev <stas@php.net>                           |
   +----------------------------------------------------------------------+
 */

/* $Id$ */

#include "php_gd.h"
#include <stdlib.h>//clq add test
#include <stdio.h>//clq add test
#include "gd_io.h"//clq add test
#include "gd.h"//clq add test

#define CTX_PUTC(c,ctx) ctx->putC(ctx, c)

//clq add test
#define size_t int

//clq add test
// void efree(void* p)
// {
// 	free(p);
// }

//clq add test
// void * emalloc(int len)
// {
// 	void * p = malloc(len);
// 	memset(p, 0, len);
// 
// 	return p;
// }
int zend_parse_parameters(int ZEND_NUM_ARGS1, ...)//必须 return 1
{
	return 1;
}

void * safe_emalloc(size_t size, size_t count, int v)
{
	return emalloc(size * count);
}

size_t php_stream_read  (FILE *stream, void *buffer, size_t size)
{
	return fread(buffer, 1, size, stream);
}

size_t php_stream_write(const void* buffer, size_t size, size_t count, FILE* stream)
{
	return fwrite(buffer, size, count, stream);
}

size_t php_stream_close(FILE* stream)
{
	return fclose(stream);
}

FILE * php_stream_open(const char * path,const char * mode)
{
	return fopen(path,mode);
}

long php_stream_tell (FILE* stream)
{
	return ftell (stream);
}

int php_stream_seek(FILE *stream, long offset, int fromwhere)
{
	return fseek(stream, offset, fromwhere);
}

int php_stream_eof (FILE* stream)
{
	return feof (stream);
}



static void _php_image_output_putc(struct gdIOCtx *ctx, int c)
{
	/* without the following downcast, the write will fail
	 * (i.e., will write a zero byte) for all
	 * big endian architectures:
	 */
	unsigned char ch = (unsigned char) c;
	//TSRMLS_FETCH();
	//php_write(&ch, 1 TSRMLS_CC);
}

static int _php_image_output_putbuf(struct gdIOCtx *ctx, const void* buf, int l)
{
	//TSRMLS_FETCH();
	//return php_write((void *)buf, l TSRMLS_CC);
}

static void _php_image_output_ctxfree(struct gdIOCtx *ctx)
{
	if(ctx) {
		efree(ctx);
	}
}

static void _php_image_stream_putc(struct gdIOCtx *ctx, int c)  
{
	char ch = (char) c;
	//php_stream * stream = (php_stream *)ctx->data;
	//TSRMLS_FETCH();
	//php_stream_write(stream, &ch, 1);
}

static int _php_image_stream_putbuf(struct gdIOCtx *ctx, const void* buf, int l)
{
	//php_stream * stream = (php_stream *)ctx->data;
	//TSRMLS_FETCH();
	//return php_stream_write(stream, (void *)buf, l);
}


static void _php_image_stream_ctxfree(struct gdIOCtx *ctx)
{
	//TSRMLS_FETCH();

	if(ctx->data) {
		//php_stream_close((php_stream *) ctx->data);
		ctx->data = NULL;
	}
	if(ctx) {

		efree(ctx);
	}
}

//clq 原始函数显然太复杂,还不如直接调用各个格式自己的函数好了//而且还涉及到函数指针
//static void _php_image_output_ctx(INTERNAL_FUNCTION_PARAMETERS, int image_type, char *tn, void (*func_p)())
static void _php_image_output_ctx(int image_type, char *tn, void (*func_p)())
{
	//zval *imgind;
	char *file = NULL;
	int file_len = 0;
	long quality, basefilter;
	gdImagePtr im;
	int argc = ZEND_NUM_ARGS();
	int q = -1, i;
	int f = -1;
	gdIOCtx *ctx = NULL;
	zval *to_zval = NULL;
	php_stream *stream;

	/* The third (quality) parameter for Wbmp stands for the threshold when called from image2wbmp().
	 * The third (quality) parameter for Wbmp and Xbm stands for the foreground color index when called
	 * from imagey<type>().
	 */
// 	if (image_type == PHP_GDIMG_TYPE_XBM) {
// 		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rp!|ll", &imgind, &file, &file_len, &quality, &basefilter) == FAILURE) {
// 			return;
// 		}
// 	} else {
		/* PHP_GDIMG_TYPE_GIF
		 * PHP_GDIMG_TYPE_PNG 
		 * PHP_GDIMG_TYPE_JPG 
		 * PHP_GDIMG_TYPE_WBM 
		 * PHP_GDIMG_TYPE_WEBP 
		 * */
// 		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r|z/!ll", &imgind, &to_zval, &quality, &basefilter) == FAILURE) {
// 			return;
// 		}
// 	}

// 	ZEND_FETCH_RESOURCE(im, gdImagePtr, &imgind, -1, "Image", phpi_get_le_gd());

// 	if (argc >= 3) {
// 		q = quality; /* or colorindex for foreground of BW images (defaults to black) */
// 		if (argc == 4) {
// 			f = basefilter;
// 		}
// 	}
// 
// 	if (argc > 1 && to_zval != NULL) {
// 		if (Z_TYPE_P(to_zval) == IS_RESOURCE) {
// 			php_stream_from_zval_no_verify(stream, &to_zval);
// 			if (stream == NULL) {
// 				RETURN_FALSE;
// 			}
// 		} else if (Z_TYPE_P(to_zval) == IS_STRING) {
// 			if (CHECK_ZVAL_NULL_PATH(to_zval)) {
// 				php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid 2nd parameter, filename must not contain null bytes");
// 				RETURN_FALSE;
// 			}
// 
// 			stream = php_stream_open_wrapper(Z_STRVAL_P(to_zval), "wb", REPORT_ERRORS|IGNORE_PATH|IGNORE_URL_WIN, NULL);
// 			if (stream == NULL) {
// 				RETURN_FALSE;
// 			}
// 		} else {
// 			php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid 2nd parameter, it must a filename or a stream");
// 			RETURN_FALSE;
// 		}
	//clq 这里是说,如果要输出到文件的话
// 	} else if (argc > 1 && file != NULL) {
// 		stream = php_stream_open_wrapper(file, "wb", REPORT_ERRORS|IGNORE_PATH|IGNORE_URL_WIN, NULL);
// 		if (stream == NULL) {
// 			RETURN_FALSE;
// 		}
// 	} else {
// 		ctx = emalloc(sizeof(gdIOCtx));
// 		ctx->putC = _php_image_output_putc;
// 		ctx->putBuf = _php_image_output_putbuf;
// 		ctx->gd_free = _php_image_output_ctxfree;
// 
// #if APACHE && defined(CHARSET_EBCDIC)
// 		/* XXX this is unlikely to work any more thies@thieso.net */
// 		/* This is a binary file already: avoid EBCDIC->ASCII conversion */
// 		ap_bsetflag(php3_rqst->connection->client, B_EBCDIC2ASCII, 0);
// #endif
// 	}
// 
// 	if (!ctx)	{
// 		ctx = emalloc(sizeof(gdIOCtx));
// 		ctx->putC = _php_image_stream_putc;
// 		ctx->putBuf = _php_image_stream_putbuf;
// 		ctx->gd_free = _php_image_stream_ctxfree;
// 		ctx->data = (void *)stream;
// 	}
// 
// 	switch(image_type) {
// 		case PHP_GDIMG_CONVERT_WBM:
// 			if(q<0||q>255) {
// 				php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid threshold value '%d'. It must be between 0 and 255", q);
// 			}
// 		case PHP_GDIMG_TYPE_JPG:
// 			(*func_p)(im, ctx, q);
// 			break;
// 		case PHP_GDIMG_TYPE_WEBP:
// 			if (q == -1) {
// 				q = 80;
// 			}
// 			(*func_p)(im, ctx, q);
// 			break;
// 		case PHP_GDIMG_TYPE_PNG:
// 			(*func_p)(im, ctx, q, f);
// 			break;
// 		case PHP_GDIMG_TYPE_XBM:
// 		case PHP_GDIMG_TYPE_WBM:
// 			if (argc < 3) {
// 				for(i=0; i < gdImageColorsTotal(im); i++) {
// 					if(!gdImageRed(im, i) && !gdImageGreen(im, i) && !gdImageBlue(im, i)) break;
// 				}
// 				q = i;
// 			}
// 			if (image_type == PHP_GDIMG_TYPE_XBM) {
// 				(*func_p)(im, file ? file : "", q, ctx);
// 			} else {
// 				(*func_p)(im, q, ctx);
// 			}
// 			break;
// 		default:
// 			(*func_p)(im, ctx);
// 			break;
// 	}
// 
// 	ctx->gd_free(ctx);

	RETURN_TRUE;
}


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: sw=4 ts=4 fdm=marker
 * vim<600: sw=4 ts=4
 */
