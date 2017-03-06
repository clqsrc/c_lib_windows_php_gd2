
//#include "gd.h"


//引出 dll 函数而已//可简单参考 php_gd.h

#ifndef _C_LIB_WINDOWS_GD_H_
#define _C_LIB_WINDOWS_GD_H_

//直接用 C 的调用规范好了,反正 delphi 的支持也很简单

#ifdef IN_EXE
#	define GD_API
#else
#	define GD_API __declspec(dllexport)
#endif

#ifdef IN_EXE
	typedef void * gdImagePtr;
#else
#	include "gd.h"
#endif

//如果实在要 stdcall 的话
// #define USE_STDCALL
// #ifdef USE_STDCALL
// #	define GD_API __stdcall __declspec(dllexport) 
// #endif

//--------------------------------------------------
//以下为函数列表,其实只是 C 语言的接口需要

typedef unsigned char uint8;

GD_API gdImagePtr imagecreatefromjpeg(char * filename);
GD_API gdImagePtr imagecreatefrompng(char * filename);
GD_API int imagepng(gdImagePtr im, char * outfilename);
//  bool imageantialias ( resource $image , bool $enabled )
// 对线段和多边形启用快速画图抗锯齿方法。不支持 alpha 部分。使用直接混色操作。仅用于真彩色图像。
// 不支持线宽和风格。
// 使用抗锯齿和透明背景色可能出现未预期的结果。混色方法把背景色当成任何其它颜色使用。缺乏 alpha 部分的支持导致不允许基于 alpha 抗锯齿
GD_API int imageantialias(gdImagePtr im, int alias);
//画线
GD_API void imageline(gdImagePtr im, int x1, int y1, int x2, int y2, int color);
//分配颜色 imagecolorallocatealpha() 的行为和 imagecolorallocate() 相同，但多了一个额外的透明度参数 alpha，其值从 0 到 127。0 表示完全不透明，127 表示完全透明。
GD_API int imagecolorallocatealpha(gdImagePtr im, int red , int green , int blue , int alpha);
//clq 从实现源码上看其实就是取颜色值,只是如果不是真彩图片的话会取调色盘的颜色罢了
GD_API int imagecolorexactalpha (gdImagePtr im, int r, int g, int b, int a);

//将一幅图像中的一块正方形区域拷贝到另一个图像中，平滑地插入像素值，因此，尤其是，减小了图像的大小而仍然保持了极大的清晰度。 
GD_API int imagecopyresampled(gdImagePtr im_dst, gdImagePtr im_src, int dstX , int dstY , int srcX , int srcY , int dstW , int dstH , int srcW , int srcH);

//设置画线的宽度,不过似乎不是每个绘图函数下都起作用
GD_API void imagesetthickness(gdImagePtr im, long thick);
//画一椭圆并填充到指定的 image 
GD_API void imagefilledellipse(gdImagePtr im, int cx , int cy , int width , int height , int color);
//设置某个点的像素颜色
//PHP_FUNCTION(imagesetpixel)
GD_API void imagesetpixel(gdImagePtr im, int x, int y, int color);
//可以认为是 imagegetpixel
GD_API int imagecolorat(gdImagePtr im, int x, int y);

//解析出一个颜色的 rgba 值//注意应该输出的指针就是 8 位的整数,位数不对的话应该会乱码的//尽量保存原来的 rgb 值,少用这个函数
GD_API void ex_color2rgb(gdImagePtr img, int color, uint8 * r8, uint8 * g8, uint8 * b8, uint8 * a8);
//画一个 aa 边界的圆//cr 是半径?
GD_API void ex_imageSmoothCircle(gdImagePtr img, int cx, int cy, int cr, int color);
//按 imageSmoothCircle 算法做的支持 alpha 通道
GD_API void ex_imageSmoothCircle_alpha(gdImagePtr img, int cx, int cy, int cr, int color) ;

//imagedestroy() 释放与 image 关联的内存
GD_API void imagedestroy(gdImagePtr im);
//clq 调用这个函数后最后接着调用 imagesavealpha,这样才能存出透明的 png 图片
//新建一个真彩色图像
GD_API gdImagePtr imagecreatetruecolor(long x_size, long y_size);
//设置标记以在保存 PNG 图像时保存完整的 alpha 通道信息（与单一透明色相反）。
//要使用本函数，必须将 alphablending 清位（imagealphablending($im, false)）。 //指的是不要使用混色模式,直接使用 alpha 值
GD_API void imagesavealpha(gdImagePtr im, int save);
// imagealphablending() 允许在真彩色图像上使用两种不同的绘画模式。
// 在混色（blending）模式下，alpha 通道色彩成分提供给所有的绘画函数，例如 imagesetpixel() 决定底层的颜色应在何种程度上被允许照射透过。作为结果，GD 自动将该点现有的颜色和画笔颜色混合，并将结果储存在图像中。结果的像素是不透明的。
// 在非混色模式下，画笔颜色连同其 alpha 通道信息一起被拷贝，替换掉目标像素。混色模式在画调色板图像时不可用。
// 如果 blendmode 为 TRUE，则启用混色模式，否则关闭。成功时返回 TRUE， 或者在失败时返回 FALSE
//clq 还是有点难懂的,总之操作透明的 png 得不到想要的结果时可以切换下试试//默认是打开的
GD_API void imagealphablending(gdImagePtr im, int blend);

//图片宽,高
GD_API int imagesx(gdImagePtr im);
GD_API int imagesy(gdImagePtr im);

//如果 font 是 1，2，3，4 或 5，则使用内置字体,否则使用 imageloadfont() 装载字体
GD_API void imagestring(gdImagePtr image, int _font, int x, int y, char * str, int color);

//imagettftext — 用 TrueType 字体向图像
//imagefttext — 使用 FreeType 2 字体将文本写入图像写入文本//size 字体大小, angle 角度(一般是0)
GD_API char * imagettftext(gdImagePtr im, double size, double angle , int x , int y , int color , char * fontfile, char * text);

//imagefill() 在 image 图像的坐标 x，y（图像左上角为 0, 0）处用 color 颜色执行区域填充（即与 x, y 点颜色相同且相邻的点都会被填充）
//clq 这个的效果和画图这样的软件相似,是会弄掉这个像素点周围的所有相似的像素点,如果要与其他类似的 api 差不多的背景填充,应该用 imagefilledrectangle
GD_API void imagefill(gdImagePtr im, int x, int y, int color);

//imagefilledrectangle() 在 image 图像中画一个用 color 颜色填充了的矩形，其左上角坐标为 x1，y1，右下角坐标为 x2，y2。0, 0 是图像的最左上角。 
GD_API void imagefilledrectangle (gdImagePtr im, int x1, int y1, int x2, int y2, int color);



#endif /* _C_LIB_WINDOWS_GD_H_ */

