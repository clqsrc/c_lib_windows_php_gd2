
#include "c_lib_windows_gd.h"

//�ο� http://php.net/imageantialias ��Щ����չ

// function ImageEllipseAA( &$img, $x, $y, $w, $h,$color,$segments=70)
// {
//     $w=$w/2;
//     $h=$h/2;
//     $jump=2*M_PI/$segments;
//     $oldx=$x+sin(-$jump)*$w;
//     $oldy=$y+cos(-$jump)*$h;
//     for($i=0;$i<2*(M_PI);$i+=$jump)
//     {
//         $newx=$x+sin($i)*$w;
//         $newy=$y+cos($i)*$h;
//         ImageLine($img,$newx,$newy,$oldx,$oldy,$color);
//         $oldx=$newx;
//         $oldy=$newy;
//     }
// }


//�ο� http://php.net/manual/zh/function.imageantialias.php ������Խ��
// function imageSmoothCircle( &$img, $cx, $cy, $cr, $color ) {
//         $ir = $cr;
//         $ix = 0;
//         $iy = $ir;
//         $ig = 2 * $ir - 3;
//         $idgr = -6;
//         $idgd = 4 * $ir - 10;
//         $fill = imageColorExactAlpha( $img, $color[ 'R' ], $color[ 'G' ], $color[ 'B' ], 0 );
//         imageLine( $img, $cx + $cr - 1, $cy, $cx, $cy, $fill );
//         imageLine( $img, $cx - $cr + 1, $cy, $cx - 1, $cy, $fill );
//         imageLine( $img, $cx, $cy + $cr - 1, $cx, $cy + 1, $fill );
//         imageLine( $img, $cx, $cy - $cr + 1, $cx, $cy - 1, $fill );
//         $draw = imageColorExactAlpha( $img, $color[ 'R' ], $color[ 'G' ], $color[ 'B' ], 42 );
//         imageSetPixel( $img, $cx + $cr, $cy, $draw );
//         imageSetPixel( $img, $cx - $cr, $cy, $draw );
//         imageSetPixel( $img, $cx, $cy + $cr, $draw );
//         imageSetPixel( $img, $cx, $cy - $cr, $draw );
//         while ( $ix <= $iy - 2 ) {
//             if ( $ig < 0 ) {
//                 $ig += $idgd;
//                 $idgd -= 8;
//                 $iy--;
//             } else {
//                 $ig += $idgr;
//                 $idgd -= 4;
//             }
//             $idgr -= 4;
//             $ix++;
//             imageLine( $img, $cx + $ix, $cy + $iy - 1, $cx + $ix, $cy + $ix, $fill );
//             imageLine( $img, $cx + $ix, $cy - $iy + 1, $cx + $ix, $cy - $ix, $fill );
//             imageLine( $img, $cx - $ix, $cy + $iy - 1, $cx - $ix, $cy + $ix, $fill );
//             imageLine( $img, $cx - $ix, $cy - $iy + 1, $cx - $ix, $cy - $ix, $fill );
//             imageLine( $img, $cx + $iy - 1, $cy + $ix, $cx + $ix, $cy + $ix, $fill );
//             imageLine( $img, $cx + $iy - 1, $cy - $ix, $cx + $ix, $cy - $ix, $fill );
//             imageLine( $img, $cx - $iy + 1, $cy + $ix, $cx - $ix, $cy + $ix, $fill );
//             imageLine( $img, $cx - $iy + 1, $cy - $ix, $cx - $ix, $cy - $ix, $fill );
//             $filled = 0;
//             for ( $xx = $ix - 0.45; $xx < $ix + 0.5; $xx += 0.2 ) {
//                 for ( $yy = $iy - 0.45; $yy < $iy + 0.5; $yy += 0.2 ) {
//                     if ( sqrt( pow( $xx, 2 ) + pow( $yy, 2 ) ) < $cr ) $filled += 4;
//                 }
//             }
//             $draw = imageColorExactAlpha( $img, $color[ 'R' ], $color[ 'G' ], $color[ 'B' ], ( 100 - $filled ) );
//             imageSetPixel( $img, $cx + $ix, $cy + $iy, $draw );
//             imageSetPixel( $img, $cx + $ix, $cy - $iy, $draw );
//             imageSetPixel( $img, $cx - $ix, $cy + $iy, $draw );
//             imageSetPixel( $img, $cx - $ix, $cy - $iy, $draw );
//             imageSetPixel( $img, $cx + $iy, $cy + $ix, $draw );
//             imageSetPixel( $img, $cx + $iy, $cy - $ix, $draw );
//             imageSetPixel( $img, $cx - $iy, $cy + $ix, $draw );
//             imageSetPixel( $img, $cx - $iy, $cy - $ix, $draw );
//         }
//     }
// 
//     $img = imageCreateTrueColor( 320, 240 );
// 
//     imageSmoothCircle( $img, 160, 120, 100, array( 'R' => 0xCC, 'G' => 0x33, 'B' => 0x00 ) );
//     imageSmoothCircle( $img, 170, 110,  75, array( 'R' => 0xDD, 'G' => 0x66, 'B' => 0x00 ) );
//     imageSmoothCircle( $img, 180, 100,  50, array( 'R' => 0xEE, 'G' => 0x99, 'B' => 0x00 ) );
//     imageSmoothCircle( $img, 190,  90,  25, array( 'R' => 0xFF, 'G' => 0xCC, 'B' => 0x00 ) );
// 
//     header( 'Content-Type: image/png' );
//     imagePNG( $img 



//�ο� http://php.net/manual/zh/function.imagecolorat.php
//��� PHP ����ʱ������ GD �� 2.0 ����ߵİ汾����ͼ�������ɫͼ���򱾺������������ظõ�� RGB ֵ������λ��������ȡ�ú죬�̣������Գɷֵ�ֵ�� 
//����˵ֻ�����ͼ������������
// Example #1 ȡ�ø��Ե� RGB ֵ
// <?php
// $im = ImageCreateFromPng("rockym.png");
// $rgb = ImageColorAt($im, 100, 100);
// $r = ($rgb >> 16) & 0xFF;
// $g = ($rgb >> 8) & 0xFF;
// $b = $rgb & 0xFF;
// ?>
//ע��Ӧ�������ָ����� 8 λ������,λ�����ԵĻ�Ӧ�û������
GD_API void ex_color2rgb(gdImagePtr img, int color, uint8 * r8, uint8 * g8, uint8 * b8, uint8 * a8) 
{
	int rgb = color;
	int a = (rgb >> 24) & 0xFF; //�� gdTrueColorAlpha Դ��������������
	int r = (rgb >> 16) & 0xFF;
	int g = (rgb >> 8) & 0xFF;
	int b = rgb & 0xFF; 

	* r8 = r;
	* g8 = g;
	* b8 = b;

	* a8 = a;
}


//cr �ǰ뾶?
///*
GD_API void ex_imageSmoothCircle(gdImagePtr img, int cx, int cy, int cr, int color) 
{
    int ir = cr;
    int ix = 0;
    int iy = ir;
    int ig = 2 * ir - 3;
    int idgr = -6;
    int idgd = 4 * ir - 10;
    //int fill = 0;//imagecolorexactalpha( $img, $color[ 'R' ], $color[ 'G' ], $color[ 'B' ], 0 );

//	$a = 100; //clq add alpha ��ɫ//��ʵ������㷨����˼,�ں���� 42 �� 100 �� alpha ����ֵ��Ӧ�ú����Ҫ������ɫ�е� alpha ֵ�ٵȱ�������,����������Ч���Ѿ��ܺ���

	uint8 r8, g8, b8, a8;

	//�⼸��Ӧ�ö�����ɫ
	int fill,draw,filled;
	//int xx,yy;
	double xx,yy;//clq �����и�������,����������

	//��������ɫ�е� rgba
	ex_color2rgb(img, color, &r8, &g8, &b8, &a8);

	fill = imagecolorexactalpha(img, r8, g8, b8, 0 );

    imageline(img, cx + cr - 1, cy, cx, cy, fill );
    imageline(img, cx - cr + 1, cy, cx - 1, cy, fill );
    imageline(img, cx, cy + cr - 1, cx, cy + 1, fill );
    imageline(img, cx, cy - cr + 1, cx, cy - 1, fill );
    draw = imagecolorexactalpha(img, r8, g8, b8, 42 );
    imagesetpixel(img, cx + cr, cy, draw );
    imagesetpixel(img, cx - cr, cy, draw );
    imagesetpixel(img, cx, cy + cr, draw );
    imagesetpixel(img, cx, cy - cr, draw );
    while ( ix <= iy - 2 ) {
        if ( ig < 0 ) {
            ig += idgd;
            idgd -= 8;
            iy--;
        } else {
            ig += idgr;
            idgd -= 4;
        }
        idgr -= 4;
        ix++;

        imageline( img, cx + ix, cy + iy - 1, cx + ix, cy + ix, fill );
        imageline( img, cx + ix, cy - iy + 1, cx + ix, cy - ix, fill );
        imageline( img, cx - ix, cy + iy - 1, cx - ix, cy + ix, fill );
        imageline( img, cx - ix, cy - iy + 1, cx - ix, cy - ix, fill );
        imageline( img, cx + iy - 1, cy + ix, cx + ix, cy + ix, fill );
        imageline( img, cx + iy - 1, cy - ix, cx + ix, cy - ix, fill );
        imageline( img, cx - iy + 1, cy + ix, cx - ix, cy + ix, fill );
        imageline( img, cx - iy + 1, cy - ix, cx - ix, cy - ix, fill );
        filled = 0;
        for ( xx = ix - 0.45; xx < ix + 0.5; xx += 0.2 ) {
            for ( yy = iy - 0.45; yy < iy + 0.5; yy += 0.2 ) {
                if ( sqrt( pow( xx, 2 ) + pow( yy, 2 ) ) < cr ) filled += 4;
            }
        }
        draw = imagecolorexactalpha( img, r8, g8, b8, ( 100 - filled ) );
        imagesetpixel( img, cx + ix, cy + iy, draw );//continue;//����Բ�����
        imagesetpixel( img, cx + ix, cy - iy, draw );
        imagesetpixel( img, cx - ix, cy + iy, draw );
        imagesetpixel( img, cx - ix, cy - iy, draw );
        imagesetpixel( img, cx + iy, cy + ix, draw );
        imagesetpixel( img, cx + iy, cy - ix, draw );
        imagesetpixel( img, cx - iy, cy + ix, draw );
        imagesetpixel( img, cx - iy, cy - ix, draw );
    }		

}//

//�� imageSmoothCircle �㷨����֧�� alpha ͨ��
GD_API void ex_imageSmoothCircle_alpha(gdImagePtr img, int cx, int cy, int cr, int color) 
{
    int ir = cr;
    int ix = 0;
    int iy = ir;
    int ig = 2 * ir - 3;
    int idgr = -6;
    int idgd = 4 * ir - 10;
    //int fill = 0;//imagecolorexactalpha( $img, $color[ 'R' ], $color[ 'G' ], $color[ 'B' ], 0 );

//	$a = 100; //clq add alpha ��ɫ//��ʵ������㷨����˼,�ں���� 42 �� 100 �� alpha ����ֵ��Ӧ�ú����Ҫ������ɫ�е� alpha ֵ�ٵȱ�������,����������Ч���Ѿ��ܺ���

	uint8 r8, g8, b8, a8;

	//�⼸��Ӧ�ö�����ɫ
	int fill,draw,filled;
	//int xx,yy;
	double xx,yy;//clq �����и�������,����������

	//��������ɫ�е� rgba
	ex_color2rgb(img, color, &r8, &g8, &b8, &a8);

	////fill = imagecolorexactalpha(img, r8, g8, b8, 0 );
	fill = imagecolorexactalpha(img, r8, g8, b8, a8 );

    imageline(img, cx + cr - 1, cy, cx, cy, fill );
    imageline(img, cx - cr + 1, cy, cx - 1, cy, fill );
    imageline(img, cx, cy + cr - 1, cx, cy + 1, fill );
    imageline(img, cx, cy - cr + 1, cx, cy - 1, fill );

    ////draw = imagecolorexactalpha(img, r8, g8, b8, 42 );
    //$draw = imageColorExactAlpha( $img, $color[ 'R' ], $color[ 'G' ], $color[ 'B' ], 42+$a );//����Ҳ����,�ᳬ�� 127 �����ֵ�������²�͸����//��Ϊ gd ��� alpha ȡֵ��Χ���� 0-127
    draw = imagecolorexactalpha(img, r8, g8, b8, min(127, 42+a8) );

    imagesetpixel(img, cx + cr, cy, draw );
    imagesetpixel(img, cx - cr, cy, draw );
    imagesetpixel(img, cx, cy + cr, draw );
    imagesetpixel(img, cx, cy - cr, draw );
    while ( ix <= iy - 2 ) {
        if ( ig < 0 ) {
            ig += idgd;
            idgd -= 8;
            iy--;
        } else {
            ig += idgr;
            idgd -= 4;
        }
        idgr -= 4;
        ix++;

        //imageline( img, cx + ix, cy + iy - 1, cx + ix, cy + ix, fill );//�����������
		if (ix < iy - 2)//������������ұߵĵ�
		imageline( img, cx + ix, cy + iy - 1, cx + ix, cy + ix+1, fill );//�����������

        //imageline( img, cx + ix, cy - iy + 1, cx + ix, cy - ix, fill );
		if (ix < iy - 2)//������������ұߵĵ�
		imageline( img, cx + ix, cy - iy + 1, cx + ix, cy - ix-1, fill );

        //imageline( img, cx - ix, cy + iy - 1, cx - ix, cy + ix, fill );
		if (ix < iy - 2)//������������ұߵĵ�
		imageline( img, cx - ix, cy + iy - 1, cx - ix, cy + ix+1, fill );

        //imageline( img, cx - ix, cy - iy + 1, cx - ix, cy - ix, fill );
		if (ix < iy - 2)//������������ұߵĵ�
		imageline( img, cx - ix, cy - iy + 1, cx - ix, cy - ix-1, fill );

        imageline( img, cx + iy - 1, cy + ix, cx + ix, cy + ix, fill );//������ĺ���
        imageline( img, cx + iy - 1, cy - ix, cx + ix, cy - ix, fill );
        imageline( img, cx - iy + 1, cy + ix, cx - ix, cy + ix, fill );
        imageline( img, cx - iy + 1, cy - ix, cx - ix, cy - ix, fill );
        filled = 0;
        for ( xx = ix - 0.45; xx < ix + 0.5; xx += 0.2 ) {
            for ( yy = iy - 0.45; yy < iy + 0.5; yy += 0.2 ) {
                if ( sqrt( pow( xx, 2 ) + pow( yy, 2 ) ) < cr ) filled += 4;
            }
        }
        ////draw = imagecolorexactalpha( img, r8, g8, b8, ( 100 - filled ) );
		//$draw = imageColorExactAlpha( $img, $color[ 'R' ], $color[ 'G' ], $color[ 'B' ], ( 100 - $filled )+$a );//����Ҳ����,�ᳬ�� 127 �����ֵ�������²�͸����
        draw = imagecolorexactalpha( img, r8, g8, b8, min(127, ( 100 - filled )+a8) );//continue;

        imagesetpixel( img, cx + ix, cy + iy, draw );//continue;//����Բ�����
        imagesetpixel( img, cx + ix, cy - iy, draw );
        imagesetpixel( img, cx - ix, cy + iy, draw );
        imagesetpixel( img, cx - ix, cy - iy, draw );
        imagesetpixel( img, cx + iy, cy + ix, draw );
        imagesetpixel( img, cx + iy, cy - ix, draw );
        imagesetpixel( img, cx - iy, cy + ix, draw );
        imagesetpixel( img, cx - iy, cy - ix, draw );
    }		

}//


//*/
