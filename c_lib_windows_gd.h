
//#include "gd.h"


//���� dll ��������//�ɼ򵥲ο� php_gd.h

#ifndef _C_LIB_WINDOWS_GD_H_
#define _C_LIB_WINDOWS_GD_H_

//ֱ���� C �ĵ��ù淶����,���� delphi ��֧��Ҳ�ܼ�

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

//���ʵ��Ҫ stdcall �Ļ�
// #define USE_STDCALL
// #ifdef USE_STDCALL
// #	define GD_API __stdcall __declspec(dllexport) 
// #endif

//--------------------------------------------------
//����Ϊ�����б�,��ʵֻ�� C ���ԵĽӿ���Ҫ

typedef unsigned char uint8;

GD_API gdImagePtr imagecreatefromjpeg(char * filename);
GD_API gdImagePtr imagecreatefrompng(char * filename);
GD_API int imagepng(gdImagePtr im, char * outfilename);
//  bool imageantialias ( resource $image , bool $enabled )
// ���߶κͶ�������ÿ��ٻ�ͼ����ݷ�������֧�� alpha ���֡�ʹ��ֱ�ӻ�ɫ���������������ɫͼ��
// ��֧���߿�ͷ��
// ʹ�ÿ���ݺ�͸������ɫ���ܳ���δԤ�ڵĽ������ɫ�����ѱ���ɫ�����κ�������ɫʹ�á�ȱ�� alpha ���ֵ�֧�ֵ��²�������� alpha �����
GD_API int imageantialias(gdImagePtr im, int alias);
//����
GD_API void imageline(gdImagePtr im, int x1, int y1, int x2, int y2, int color);
//������ɫ imagecolorallocatealpha() ����Ϊ�� imagecolorallocate() ��ͬ��������һ�������͸���Ȳ��� alpha����ֵ�� 0 �� 127��0 ��ʾ��ȫ��͸����127 ��ʾ��ȫ͸����
GD_API int imagecolorallocatealpha(gdImagePtr im, int red , int green , int blue , int alpha);
//clq ��ʵ��Դ���Ͽ���ʵ����ȡ��ɫֵ,ֻ������������ͼƬ�Ļ���ȡ��ɫ�̵���ɫ����
GD_API int imagecolorexactalpha (gdImagePtr im, int r, int g, int b, int a);

//��һ��ͼ���е�һ�����������򿽱�����һ��ͼ���У�ƽ���ز�������ֵ����ˣ������ǣ���С��ͼ��Ĵ�С����Ȼ�����˼���������ȡ� 
GD_API int imagecopyresampled(gdImagePtr im_dst, gdImagePtr im_src, int dstX , int dstY , int srcX , int srcY , int dstW , int dstH , int srcW , int srcH);

//���û��ߵĿ��,�����ƺ�����ÿ����ͼ�����¶�������
GD_API void imagesetthickness(gdImagePtr im, long thick);
//��һ��Բ����䵽ָ���� image 
GD_API void imagefilledellipse(gdImagePtr im, int cx , int cy , int width , int height , int color);
//����ĳ�����������ɫ
//PHP_FUNCTION(imagesetpixel)
GD_API void imagesetpixel(gdImagePtr im, int x, int y, int color);
//������Ϊ�� imagegetpixel
GD_API int imagecolorat(gdImagePtr im, int x, int y);

//������һ����ɫ�� rgba ֵ//ע��Ӧ�������ָ����� 8 λ������,λ�����ԵĻ�Ӧ�û������//��������ԭ���� rgb ֵ,�����������
GD_API void ex_color2rgb(gdImagePtr img, int color, uint8 * r8, uint8 * g8, uint8 * b8, uint8 * a8);
//��һ�� aa �߽��Բ//cr �ǰ뾶?
GD_API void ex_imageSmoothCircle(gdImagePtr img, int cx, int cy, int cr, int color);
//�� imageSmoothCircle �㷨����֧�� alpha ͨ��
GD_API void ex_imageSmoothCircle_alpha(gdImagePtr img, int cx, int cy, int cr, int color) ;

//imagedestroy() �ͷ��� image �������ڴ�
GD_API void imagedestroy(gdImagePtr im);
//clq ������������������ŵ��� imagesavealpha,�������ܴ��͸���� png ͼƬ
//�½�һ�����ɫͼ��
GD_API gdImagePtr imagecreatetruecolor(long x_size, long y_size);
//���ñ�����ڱ��� PNG ͼ��ʱ���������� alpha ͨ����Ϣ���뵥һ͸��ɫ�෴����
//Ҫʹ�ñ����������뽫 alphablending ��λ��imagealphablending($im, false)���� //ָ���ǲ�Ҫʹ�û�ɫģʽ,ֱ��ʹ�� alpha ֵ
GD_API void imagesavealpha(gdImagePtr im, int save);
// imagealphablending() ���������ɫͼ����ʹ�����ֲ�ͬ�Ļ滭ģʽ��
// �ڻ�ɫ��blending��ģʽ�£�alpha ͨ��ɫ�ʳɷ��ṩ�����еĻ滭���������� imagesetpixel() �����ײ����ɫӦ�ں��̶ֳ��ϱ���������͸������Ϊ�����GD �Զ����õ����е���ɫ�ͻ�����ɫ��ϣ��������������ͼ���С�����������ǲ�͸���ġ�
// �ڷǻ�ɫģʽ�£�������ɫ��ͬ�� alpha ͨ����Ϣһ�𱻿������滻��Ŀ�����ء���ɫģʽ�ڻ���ɫ��ͼ��ʱ�����á�
// ��� blendmode Ϊ TRUE�������û�ɫģʽ������رա��ɹ�ʱ���� TRUE�� ������ʧ��ʱ���� FALSE
//clq �����е��Ѷ���,��֮����͸���� png �ò�����Ҫ�Ľ��ʱ�����л�������//Ĭ���Ǵ򿪵�
GD_API void imagealphablending(gdImagePtr im, int blend);

//ͼƬ��,��
GD_API int imagesx(gdImagePtr im);
GD_API int imagesy(gdImagePtr im);

//��� font �� 1��2��3��4 �� 5����ʹ����������,����ʹ�� imageloadfont() װ������
GD_API void imagestring(gdImagePtr image, int _font, int x, int y, char * str, int color);

//imagettftext �� �� TrueType ������ͼ��
//imagefttext �� ʹ�� FreeType 2 ���彫�ı�д��ͼ��д���ı�//size �����С, angle �Ƕ�(һ����0)
GD_API char * imagettftext(gdImagePtr im, double size, double angle , int x , int y , int color , char * fontfile, char * text);

//imagefill() �� image ͼ������� x��y��ͼ�����Ͻ�Ϊ 0, 0������ color ��ɫִ��������䣨���� x, y ����ɫ��ͬ�����ڵĵ㶼�ᱻ��䣩
//clq �����Ч���ͻ�ͼ�������������,�ǻ�Ū��������ص���Χ���������Ƶ����ص�,���Ҫ���������Ƶ� api ���ı������,Ӧ���� imagefilledrectangle
GD_API void imagefill(gdImagePtr im, int x, int y, int color);

//imagefilledrectangle() �� image ͼ���л�һ���� color ��ɫ����˵ľ��Σ������Ͻ�����Ϊ x1��y1�����½�����Ϊ x2��y2��0, 0 ��ͼ��������Ͻǡ� 
GD_API void imagefilledrectangle (gdImagePtr im, int x1, int y1, int x2, int y2, int color);



#endif /* _C_LIB_WINDOWS_GD_H_ */

