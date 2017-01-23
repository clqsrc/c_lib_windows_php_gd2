
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //for memset
#include "gd.h"



//clq add test //php 暂时还要用到的接口

int main(int argc, const char **argv)
{
	//在 gd2copypal.c 中其实已经有一个了

	gdImagePtr im;
	gdImagePtr pal;
	FILE *in, *out;
	gdImagePtr dst_image;
	gdIOCtx * ctx;

    int width, height, newwidth, newheight;
	//限制缩放后图片的最大最小宽度
	int max_height = 100;
	int max_width = 100;

	//--------------------------------------------------
	FILE * fp = fopen ("c:\\1.jpg", "rb");
	FILE * smallfile = fopen ("c:\\2.jpg", "wb");
	long ignore_warning = 0;//INI_INT("gd.jpeg_ignore_warning");
	im = gdImageCreateFromJpegEx(fp, ignore_warning);

	dst_image = imagecreatetruecolor(100, 100);
	imagecopyresized(dst_image,im,0,0,0,0,100,100,200,200);

		//	ctx = emalloc(sizeof(gdIOCtx));
		//ctx->putC = _php_image_stream_putc;
		//ctx->putBuf = _php_image_stream_putbuf;
		//ctx->gd_free = _php_image_stream_ctxfree;
		//ctx->data = smallfile;//(void *)stream;

	ctx = gdNewFileCtx(smallfile);

	gdImageJpegCtx(dst_image, ctx, 90);
		//gdImagePng(dst_image, smallfile);
	//	gdImagePng(im, smallfile);

	//ImageJpeg(dst_image, smallfile); //??????? 

	fclose(smallfile);
	fclose(fp);

	//--------------------------------------------------

//	im = imagecreatefromjpeg("c:\\1.jpg");
	im = imagecreatefromwebp("c:\\1.webp");

	imagejpeg(im, "c:\\5.jpg", 90);
	imagepng(im, "c:\\6.png");

	width = im->sx;
	height = im->sy;

	//list($orig_width, $orig_height) = getimagesize($filename);//getimagesize 似乎不是 gd 库的,而且也不准确,只能判断几种格式

	newwidth = width; newheight = height;

    if (height > max_height) {
        //newwidth = (max_height / height) * width;//c 语言整数相除是有问题的
        newwidth = ((double)max_height / height) * width;
        newheight = max_height;
    }

    if (width > max_width) {
        //newheight = (max_width / width) * height;//c 语言整数相除是有问题的
        newheight = ((double)max_width / width) * height;
        newwidth = max_width;
    }

	dst_image = imagecreatetruecolor(newwidth, newheight);

	//画一个 aa 边界的圆//cr 是半径?
	//ex_imageSmoothCircle(im, 200, 200, 50, color);
	ex_imageSmoothCircle(im, 190,  90,  25, 0);
	
	imagecopyresampled(dst_image,im, 0, 0, 0, 0,
                                     newwidth, newheight, width, height);

	imagejpeg(dst_image, "c:\\3.jpg", 90);
	imagepng(dst_image, "c:\\4.png");

	efree(im);
	efree(dst_image);

	return 0;

	//--------------------------------------------------


  if (argc != 3)
    {
      fprintf (stderr, "Usage: gd2copypal palettefile.gd2 filename.gd2\n");
      exit (1);
    }
  in = fopen (argv[1], "rb");
  if (!in)
    {
      fprintf (stderr, "Palette file does not exist!\n");
      exit (1);
    }
  pal = gdImageCreateFromGd2 (in);
  fclose (in);
  if (!pal)
    {
      fprintf (stderr, "Palette is not in GD2 format!\n");
      exit (1);
    }

  in = fopen (argv[2], "rb");
  if (!in)
    {
      fprintf (stderr, "Input file does not exist!\n");
      exit (1);
    }
  im = gdImageCreateFromGd2 (in);
  fclose (in);
  if (!im)
    {
      fprintf (stderr, "Input is not in GD2 format!\n");
      exit (1);
    }

  gdImagePaletteCopy (im, pal);

  out = fopen (argv[2], "wb");
  if (!out)
    {
      fprintf (stderr, "Output file cannot be written to!\n");
      gdImageDestroy (im);
      exit (1);
    }
  gdImageGd2 (im, out, 128, 2);
  fclose (out);
  gdImageDestroy (pal);
  gdImageDestroy (im);


	return 0;
}

//应当是将文件内容读取到缓冲区中//char *buff
//int php_stream_copy_to_mem(stream, &buff, PHP_STREAM_COPY_ALL, 1);
int php_stream_copy_to_mem(FILE * stream, char ** buf, int t, int i_1)
{
    FILE *fp =NULL;
    long n = 0;

	// SEEK_SET： 文件开头
	// SEEK_CUR： 当前位置
	// SEEK_END： 文件结尾
	// 其中SEEK_SET,SEEK_CUR和SEEK_END依次为0，1和2.
	// 简言之：
	// fseek(fp,100L,0);把文件内部指针移动到离文件开头100字节处；
	// fseek(fp,100L,1);把文件内部指针移动到离文件当前位置100字节处；
	// fseek(fp,-100L,2);把文件内部指针退回到离文件结尾100字节处。

	fp = stream;

//  
//     if ((fp = fopen("Q.txt","r")) == NULL)
//     {
//         printf("文件打开失败.\n");
//         exit(0);
//     }
    fseek(fp,0,2);   //指针：移动到文件尾部
    n = ftell(fp);   //返回指针偏离文件头的位置(即文件中字符个数)

	fseek(fp, 0,0); //把文件内部指针移动到离文件开头0字节处
 
    //printf("%ld\n",n);

	if (n < 1) return 0;
	if (n > 100*1024*1024) return 0; //不读取 100m 的文件

	*buf = malloc(n);

	fread(*buf, 1, n, fp);
 
    return n;	

}

//原代码在 gd_compat.c 中//作用似乎是检验指针是否合法
int overflow2(int a, int b)
{
// 	TSRMLS_FETCH();
// 	
// 	if(a <= 0 || b <= 0) {
// 		php_error_docref(NULL TSRMLS_CC, E_WARNING, "gd warning: one parameter to a memory allocation multiplication is negative or zero, failing operation gracefully\n");
// 		return 1;
// 	}
// 	if(a > INT_MAX / b) {
// 		php_error_docref(NULL TSRMLS_CC, E_WARNING, "gd warning: product of memory allocation multiplication would exceed INT_MAX, failing operation gracefully\n");
// 		return 1;
// 	}
	return 0;
}

void php_error_docref(int i, ...)
{

}

//clq add test
 void efree(void* p)
 {
 	free(p);
 }

 void * emalloc(int len)
 {
	 void * p = malloc(len);
	 memset(p, 0, len);
	 
	 return p;
}

//应当是删除文件
void VCWD_UNLINK(char * fn)
{

}

//复制len个字符串，它比strcpy好在： 如果len小于src的长度，除了复制src中的前len个字符，还自动为新的字符串添加一个'\0'表示结尾
char* estrndup(const char* src, size_t len)
{
	char * p = emalloc(len);

	return strncpy(p, src, len);
}

void * erealloc(void *mem_address, unsigned int newsize)
{
	return  realloc(mem_address, newsize);
}

char * estrdup(char *s)
{
	return strdup(s);
}

void * ecalloc(size_t n, size_t size)
{
	return calloc(n, size);
}

void * gdPMalloc(size_t n)
{
	return emalloc(n);
}

void gdPFree(void* p)
{
	free(p);
 }

char * gdPEstrdup(char *s)
{
	return strdup(s);
}

//int stricmp(char *s1,char * s2);
int strcasecmp(char *s1,char * s2)
{
	return stricmp(s1, s2);
}

// 格式化函数
// 
// 在PHP扩展开发中，应该避免直接使用sprintf函数，取而代之的是使用main/spprintf.h 中定义的spprintf和vspprintf函数。
// 
// 在main/spprintf.h中，总共定义了两个函数API
// 
// PHPAPI int spprintf( char **pbuf, size_t max_len, const char *format, ...);
// PHPAPI int vspprintf(char **pbuf, size_t max_len, const char *format, va_list ap);　



const char php_sig_gif[3];
const char php_sig_jpg[3];
const char php_sig_png[8];

//含有 TSRMLS_FETCH(); 调用的文件恐怕是要全部重写的,比如 gdft.c gd.c


