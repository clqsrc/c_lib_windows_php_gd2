#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "gd.h"

//clq modify 换用 libwebp//修改自 gd_webp.c

//--------------------------------------------------
#if defined(_WIN32)
#include <fcntl.h>   // for _O_BINARY
#include <io.h>      // for _setmode()
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "webp/decode.h"
#include "webp/encode.h"
//#include "examples/webpdec.h"
//#include "examples/example_util.h"
//#include "examples/image_dec.h"

//#include "examples/stopwatch.h"

//可参考 cwebp.c 读取一个文件


//--------------------------------------------------


#ifdef HAVE_LIBVPX
#include "webpimg.h"
#include "gdhelpers.h"

//--------------------------------------------------
static int ReadYUV(const uint8_t* const data, size_t data_size,
                   WebPPicture* const pic) {
  const int use_argb = pic->use_argb;
  const int uv_width = (pic->width + 1) / 2;
  const int uv_height = (pic->height + 1) / 2;
  const int y_plane_size = pic->width * pic->height;
  const int uv_plane_size = uv_width * uv_height;
  const size_t expected_data_size = y_plane_size + 2 * uv_plane_size;

  if (data_size != expected_data_size) {
    fprintf(stderr,
            "input data doesn't have the expected size (%d instead of %d)\n",
            (int)data_size, (int)expected_data_size);
    return 0;
  }

  pic->use_argb = 0;
  if (!WebPPictureAlloc(pic)) return 0;
  ExUtilCopyPlane(data, pic->width, pic->y, pic->y_stride,
                  pic->width, pic->height);
  ExUtilCopyPlane(data + y_plane_size, uv_width,
                  pic->u, pic->uv_stride, uv_width, uv_height);
  ExUtilCopyPlane(data + y_plane_size + uv_plane_size, uv_width,
                  pic->v, pic->uv_stride, uv_width, uv_height);

////  return use_argb ? WebPPictureYUVAToARGB(pic) : 1;

  //--------------------------------------------------
	WebPPictureYUVAToARGB(pic);

	return 1;
  //--------------------------------------------------

}

/*
//static int ReadPicture(const char* const filename, WebPPicture* const pic,
static uint8_t* ReadPicture(const char* const filename, WebPPicture* const pic,
                       int keep_alpha, Metadata* const metadata) {
  const uint8_t* data = NULL;
  size_t data_size = 0;
  int ok = 0;

  ok = ExUtilReadFile(filename, &data, &data_size);
  if (!ok) goto End;

  if (pic->width == 0 || pic->height == 0) {
    WebPImageReader reader = WebPGuessImageReader(data, data_size);
    ok = (reader != NULL) && reader(data, data_size, pic, keep_alpha, metadata);
  } else {
    // If image size is specified, infer it as YUV format.
    ok = ReadYUV(data, data_size, pic);
  }
 End:
  if (!ok) {
    fprintf(stderr, "Error! Could not process file %s\n", filename);
  }

  ////free((void*)data);
  ////return ok;

  return data;
}


//int main2(int argc, char* argv[])
WebPPicture main2(long * width, long * height)
{
	//__int64
	//long long i1 = 0;

	//printf("Hello World!\n");

	int return_value2 = -1;

	//int return_value;// = -1;
  char *in_file = NULL, *out_file = NULL, *dump_file = NULL;
  FILE *out = NULL;
  //int c;
  int short_output = 0;
  int quiet = 0;
  int keep_alpha = 1;
  int blend_alpha = 0;
  uint32_t background_color = 0xffffffu;
  int crop = 0, crop_x = 0, crop_y = 0, crop_w = 0, crop_h = 0;
  int resize_w = 0, resize_h = 0;
  int lossless_preset = 6;
  int use_lossless_preset = -1;  // -1=unset, 0=don't use, 1=use it
  int show_progress = 0;
  int keep_metadata = 0;
  int metadata_written = 0;
  WebPPicture picture;
  int print_distortion = -1;        // -1=off, 0=PSNR, 1=SSIM, 2=LSIM
  WebPPicture original_picture;    // when PSNR or SSIM is requested
  WebPConfig config;
  //WebPAuxStats stats;
  WebPMemoryWriter memory_writer;
  Metadata metadata;
  //Stopwatch stop_watch;


  //return_value = -1;




  //--------------------------------------------------
  in_file = "c:\\1.webp";
  //in_file = "c:\\1.png";

  MetadataInit(&metadata);
  WebPMemoryWriterInit(&memory_writer);
  if (!WebPPictureInit(&picture) ||
      !WebPPictureInit(&original_picture) ||
      !WebPConfigInit(&config)) {
    fprintf(stderr, "Error! Version mismatch!\n");
    return picture;//-1;
  }

  //--------------------------------------------------

  if (!ReadPicture(in_file, &picture, keep_alpha,
                   (keep_metadata == 0) ? NULL : &metadata)) {
    fprintf(stderr, "Error! Cannot read input picture file '%s'\n", in_file);
    goto Error;
  }

	//return 0;

 Error:
//   WebPMemoryWriterClear(&memory_writer);
//   free(picture.extra_info);
//   MetadataFree(&metadata);
//   WebPPictureFree(&picture);
//   WebPPictureFree(&original_picture);
//   if (out != NULL && out != stdout) {
//     fclose(out);
//   }

  //--------------------------------------------------
	*width = picture.width;
	*height = picture.height;

  return picture;//return_value;
}

//--------------------------------------------------
*/


extern void gd_YUV420toRGBA(uint8* Y,
                  uint8* U,
                  uint8* V,
                  gdImagePtr im);

extern void gd_RGBAToYUV420(gdImagePtr im2,
                  uint8* Y,
                  uint8* U,
                  uint8* V);

const char * gdWebpGetVersionString()
{
	return "not defined";
}

gdImagePtr gdImageCreateFromWebp (FILE * inFile)
{
	gdImagePtr im;
	gdIOCtx *in = gdNewFileCtx(inFile);
	im = gdImageCreateFromWebpCtx(in);
	in->gd_free(in);

	return im;
}

gdImagePtr gdImageCreateFromWebpPtr (int size, void *data)
{
	int    width, height, ret;
 	unsigned char   *Y = NULL;
	unsigned char   *U = NULL;
	unsigned char   *V = NULL;
	gdImagePtr im;

	ret = WebPDecode(data, size, &Y, &U, &V, &width, &height);
	if (ret != webp_success) {
		if (Y) free(Y);
		if (U) free(U);
		if (V) free(V);
		php_gd_error("WebP decode: fail to decode input data");
		return NULL;
	}
	im = gdImageCreateTrueColor(width, height);
	if (!im) {
		return NULL;
	}
////	gd_YUV420toRGBA(Y, U, V, im);
	return im;
}

#define GD_WEBP_ALLOC_STEP (4*1024)

/*
//clq test
gdImagePtr gdImageCreateFromWebpCtx2 (gdIOCtx * infile)
{
	int    width, height, ret;
	unsigned char   *filedata = NULL;
	unsigned char   *read, *temp;
	unsigned char   *Y = NULL;
	unsigned char   *U = NULL;
	unsigned char   *V = NULL;
	size_t size = 0, n;
	gdImagePtr im;
	WebPPicture * picture = NULL;
	WebPPicture pic;
	int ALPHA_IS_LAST = 1;

    uint8_t* argb;// = (const uint8_t*)picture->argb;
    uint8_t* r;// = ALPHA_IS_LAST ? argb + 2 : argb + 1;
    uint8_t* g;// = ALPHA_IS_LAST ? argb + 1 : argb + 2;
    uint8_t* b;// = ALPHA_IS_LAST ? argb + 0 : argb + 3;
    uint8_t* a;// = ALPHA_IS_LAST ? argb + 3 : argb + 0;
	int y = 0, x = 0;

	do {
		temp = gdRealloc(filedata, size+GD_WEBP_ALLOC_STEP);
		if (temp) {
			filedata = temp;
			read = temp + size;
		} else {
			if (filedata) {
				gdFree(filedata);
			}
			php_gd_error("WebP decode: realloc failed");
			return NULL;
		}

		n = gdGetBuf(read, GD_WEBP_ALLOC_STEP, infile);
		// differs from upstream where gdGetBuf return 0 instead of EOF
		if (n>0 && n!=EOF) {
			size += n;
		}
	} while (n>0 && n!=EOF);

	//--------------------------------------------------

	ret = WebPDecode(filedata, size, &Y, &U, &V, &width, &height);

	pic = main2(&width, &height);

// 	gdFree(filedata);
// 	if (ret != webp_success) {
// 		if (Y) free(Y);
// 		if (U) free(U);
// 		if (V) free(V);
// 		php_gd_error("WebP decode: fail to decode input data");
// 		return NULL;
// 	}
// 	im = gdImageCreateTrueColor(width, height);
// 	gd_YUV420toRGBA(Y, U, V, im);

	//--------------------------------------------------
	picture = &pic;
    argb = (const uint8_t*)picture->argb;
    r = ALPHA_IS_LAST ? argb + 2 : argb + 1;
    g = ALPHA_IS_LAST ? argb + 1 : argb + 2;
    b = ALPHA_IS_LAST ? argb + 0 : argb + 3;
    a = ALPHA_IS_LAST ? argb + 3 : argb + 0;

	//from PictureARGBToYUVA
    //picture->colorspace = WEBP_YUV420;
    //return ImportYUVAFromRGBA(r, g, b, a, 4, 4 * picture->argb_stride,
    //                          dithering, use_iterative_conversion, picture);

	for (y = 0; y < picture->height; ++y) 
	{
		for (x = 0; x < picture->width; ++x) 
		{
			//picture->argb
			printf("%d,%d,%d,\r\n", r,g,b);
		}
	
	
	}

	//里面的字节是怎么排的?
////	im->tpixels


	//--------------------------------------------------

	return im;
}
*/

//clq test 参考更简单一点的 python 接口
gdImagePtr gdImageCreateFromWebpCtx3 (gdIOCtx * infile)
{
	int    width, height, ret;
	unsigned char   *filedata = NULL;
	unsigned char   *read, *temp;
	unsigned char   *Y = NULL;
	unsigned char   *U = NULL;
	unsigned char   *V = NULL;
	size_t size = 0, n;
	gdImagePtr im;
	WebPPicture * picture = NULL;
	WebPPicture pic;
	int ALPHA_IS_LAST = 1;

    uint8_t* argb;// = (const uint8_t*)picture->argb;
//     uint8_t* r;// = ALPHA_IS_LAST ? argb + 2 : argb + 1;
//     uint8_t* g;// = ALPHA_IS_LAST ? argb + 1 : argb + 2;
//     uint8_t* b;// = ALPHA_IS_LAST ? argb + 0 : argb + 3;
//     uint8_t* a;// = ALPHA_IS_LAST ? argb + 3 : argb + 0;
	int y = 0, x = 0;

	uint8_t * out;
	long dataSize;
	long dataLeft;
	uint8_t * p;
	int color;
	//uint8_t r, g, b, a;
	int r, g, b, a;
	int col, row;
	int pos;

	do {
		temp = gdRealloc(filedata, size+GD_WEBP_ALLOC_STEP);
		if (temp) {
			filedata = temp;
			read = temp + size;
		} else {
			if (filedata) {
				gdFree(filedata);
			}
			php_gd_error("WebP decode: realloc failed");
			return NULL;
		}

		n = gdGetBuf(read, GD_WEBP_ALLOC_STEP, infile);
		/* differs from upstream where gdGetBuf return 0 instead of EOF */
		if (n>0 && n!=EOF) {
			size += n;
		}
	} while (n>0 && n!=EOF);

	//--------------------------------------------------
	//上面的代码只是从 infile 中读取全部文件内容而已

	//其实还有个 WebPDecodeARGB 函数
	out = WebPDecodeRGB((const uint8 *)filedata, size,&width,&height);

	if(out == NULL){
		printf("WebPDecodeRGB(%d)failed.\n",size);
		return 0;
	}
	
	printf("WebPDecodeRGB(%d)succeed：%dx%d WebP image decoded.\n",
		size,width,height);

	im = gdImageCreateTrueColor(width, height);

	dataSize = width * 3 * height; //如果是 alpha 的就是 dataSize = width * 4 * height;

	dataLeft = dataSize;
	p = out;

	pos = 0;
	
	//while(dataLeft)
	//while(dataLeft > 0)
	while(dataLeft >= 3) //内存安全起见,其实应该是这个
	{
		//color = gdImageColorAllocate(im, 255, 0, 0);
		//gdImageSetPixel(im, 0, 0, color);
		//gdImageSetPixel(im, 0, 1, color);
		//break;

		//memset(&RGB, 0, sizeof(RGB));

// 		RGB[0] = *(p + 2);
// 		RGB[1] = *(p + 1);
// 		RGB[2] = *(p);

//  		r = *(p + 2);
//  		g = *(p + 1);
//  		b = *(p);

 		b = *(p + 2);
 		g = *(p + 1);
 		r = *(p);

// 		pbmpdata[0] = RGB[0];
// 		pbmpdata[1] = RGB[1];
// 		pbmpdata[2] = RGB[2];
// 
// 		pbmpdata += 3; //如果是 32 位的位图就要是 4 //现在是 24 位

		//gd 的颜色没有 alpha ?//imagecolorallocatealpha() 的行为和 imagecolorallocate() 相同，但多了一个额外的透明度参数 alpha，其值从 0 到 127。0 表示完全不透
		color = gdImageColorAllocate(im, r, g, b);

		//col 就是x,width ,要按图片宽度计算
		row = pos / width;
		col = pos - row * width;

		color = gdImageColorAllocate(im, 255, 0, 0);

		gdImageSetPixel(im, col, row, color);
		color = gdImageColorAllocate(im, r, g, b);
		gdImageSetPixel(im, col, row, color);

		pos += 1;

		//--------------------------------------------------
		p += 3;
		dataLeft  -= 3;
	}


 	gdFree(filedata);
	//gdFree(temp);//好象等于 filedata 不用释放

	return im;

	//--------------------------------------------------


}



gdImagePtr gdImageCreateFromWebpCtx (gdIOCtx * infile)
{
	int    width, height, ret;
	unsigned char   *filedata = NULL;
	unsigned char   *read, *temp;
	unsigned char   *Y = NULL;
	unsigned char   *U = NULL;
	unsigned char   *V = NULL;
	size_t size = 0, n;
	gdImagePtr im;

	do {
		temp = gdRealloc(filedata, size+GD_WEBP_ALLOC_STEP);
		if (temp) {
			filedata = temp;
			read = temp + size;
		} else {
			if (filedata) {
				gdFree(filedata);
			}
			php_gd_error("WebP decode: realloc failed");
			return NULL;
		}

		n = gdGetBuf(read, GD_WEBP_ALLOC_STEP, infile);
		/* differs from upstream where gdGetBuf return 0 instead of EOF */
		if (n>0 && n!=EOF) {
			size += n;
		}
	} while (n>0 && n!=EOF);

	ret = WebPDecode(filedata, size, &Y, &U, &V, &width, &height);
	gdFree(filedata);
	if (ret != webp_success) {
		if (Y) free(Y);
		if (U) free(U);
		if (V) free(V);
		php_gd_error("WebP decode: fail to decode input data");
		return NULL;
	}
	im = gdImageCreateTrueColor(width, height);
////	gd_YUV420toRGBA(Y, U, V, im);
	return im;
}

void gdImageWebpEx (gdImagePtr im, FILE * outFile, int quantization)
{
	gdIOCtx *out = gdNewFileCtx(outFile);
	gdImageWebpCtx(im, out, quantization);
	out->gd_free(out);
}

void gdImageWebp (gdImagePtr im, FILE * outFile)
{
	gdIOCtx *out = gdNewFileCtx(outFile);
  	gdImageWebpCtx(im, out, -1);
	out->gd_free(out);
}

void * gdImageWebpPtr (gdImagePtr im, int *size)
{
	void *rv;
	gdIOCtx *out = gdNewDynamicCtx(2048, NULL);
	gdImageWebpCtx(im, out, -1);
	rv = gdDPExtractData(out, size);
	out->gd_free(out);

	return rv;
}

void * gdImageWebpPtrEx (gdImagePtr im, int *size, int quantization)
{
	void *rv;
	gdIOCtx *out = gdNewDynamicCtx(2048, NULL);
	gdImageWebpCtx(im, out, quantization);
	rv = gdDPExtractData(out, size);
	out->gd_free(out);
	return rv;
}

/*
 * Maps normalized QP (quality) to VP8 QP
 */
int mapQualityToVP8QP(int quality) {
#define MIN_QUALITY 0
#define MAX_QUALITY 100
#define MIN_VP8QP 1
#define MAX_VP8QP 63
	const float scale = MAX_VP8QP - MIN_VP8QP;
	const float vp8qp =
	scale * (MAX_QUALITY - quality) / (MAX_QUALITY - MIN_QUALITY) + MIN_VP8QP;
	if (quality < MIN_QUALITY || quality > MAX_QUALITY) {
		php_gd_error("Wrong quality value %d.", quality);
		return -1;
	}

	return (int)(vp8qp + 0.5);
}

/* This routine is based in part on code from Dale Lutz (Safe Software Inc.)
 *  and in part on demo code from Chapter 15 of "PNG: The Definitive Guide"
 *  (http://www.cdrom.com/pub/png/pngbook.html).
 */
void gdImageWebpCtx (gdImagePtr im, gdIOCtx * outfile, int quantization)
{
	int width = im->sx;
	int height = im->sy;
	int colors = im->colorsTotal;
	int *open = im->open;

	int  yuv_width, yuv_height, yuv_nbytes, ret;
	int vp8_quality;
	unsigned char *Y = NULL,
				  *U = NULL,
				  *V = NULL;
	unsigned char *filedata = NULL;

	/* Conversion to Y,U,V buffer */
    yuv_width = (width + 1) >> 1;
    yuv_height = (height + 1) >> 1;

	if (overflow2(width, height)) {
		return;
	}
	/* simplification possible, because WebP must not be larger than 16384**2 */
	if (overflow2(width * height, 2 * sizeof(unsigned char))) {
		return;
	}

    yuv_nbytes = width * height + 2 * yuv_width * yuv_height;

    if ((Y = (unsigned char *)gdCalloc(yuv_nbytes, sizeof(unsigned char))) == NULL) {
    	php_gd_error("gd-webp error: cannot allocate Y buffer");
        return;
    }
	vp8_quality = mapQualityToVP8QP(quantization);

    U = Y + width * height;
    V = U + yuv_width * yuv_height;
////    gd_RGBAToYUV420(im, Y, U, V);

	/* Encode Y,U,V and write data to file */
    ret = WebPEncode(Y, U, V, width, height, width, yuv_width, yuv_height, yuv_width,
                     vp8_quality, &filedata, &yuv_nbytes, NULL);
	gdFree(Y);

    if (ret != webp_success) {
    	if (filedata) {
    		free(filedata);
		}
		php_gd_error("gd-webp error: WebP Encoder failed");
		return;
    }

    gdPutBuf (filedata, yuv_nbytes, outfile);
    free(filedata);
}

#endif /* HAVE_LIBVPX */
