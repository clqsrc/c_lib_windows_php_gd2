
#include "c_lib_windows_gd.h"

//参考 http://php.net/imageantialias 做些简单扩展

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


//参考 http://php.net/manual/zh/function.imageantialias.php 可能有越界
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



//参考 http://php.net/manual/zh/function.imagecolorat.php
//如果 PHP 编译时加上了 GD 库 2.0 或更高的版本并且图像是真彩色图像，则本函数以整数返回该点的 RGB 值。用移位加掩码来取得红，绿，蓝各自成分的值： 
//就是说只有真彩图才能这样处理
// Example #1 取得各自的 RGB 值
// <?php
// $im = ImageCreateFromPng("rockym.png");
// $rgb = ImageColorAt($im, 100, 100);
// $r = ($rgb >> 16) & 0xFF;
// $g = ($rgb >> 8) & 0xFF;
// $b = $rgb & 0xFF;
// ?>
//注意应该输出的指针就是 8 位的整数,位数不对的话应该会乱码的
GD_API void ex_color2rgb(gdImagePtr img, int color, uint8 * r8, uint8 * g8, uint8 * b8, uint8 * a8) 
{
	int rgb = color;
	int a = (rgb >> 24) & 0xFF; //从 gdTrueColorAlpha 源码来看是这样的
	int r = (rgb >> 16) & 0xFF;
	int g = (rgb >> 8) & 0xFF;
	int b = rgb & 0xFF; 

	* r8 = r;
	* g8 = g;
	* b8 = b;

	* a8 = a;
}


//cr 是半径?
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

//	$a = 100; //clq add alpha 颜色//其实按这个算法的意思,在后面的 42 和 100 的 alpha 修正值还应该和这个要画的颜色中的 alpha 值再等比例计算,不过这样的效果已经很好了

	uint8 r8, g8, b8, a8;

	//这几个应该都是颜色
	int fill,draw,filled;
	//int xx,yy;
	double xx,yy;//clq 后面有浮点运算,不能用整数

	//解析出颜色中的 rgba
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
        imagesetpixel( img, cx + ix, cy + iy, draw );//continue;//就是圆形外框
        imagesetpixel( img, cx + ix, cy - iy, draw );
        imagesetpixel( img, cx - ix, cy + iy, draw );
        imagesetpixel( img, cx - ix, cy - iy, draw );
        imagesetpixel( img, cx + iy, cy + ix, draw );
        imagesetpixel( img, cx + iy, cy - ix, draw );
        imagesetpixel( img, cx - iy, cy + ix, draw );
        imagesetpixel( img, cx - iy, cy - ix, draw );
    }		

}//

//按 imageSmoothCircle 算法做的支持 alpha 通道
GD_API void ex_imageSmoothCircle_alpha(gdImagePtr img, int cx, int cy, int cr, int color) 
{
    int ir = cr;
    int ix = 0;
    int iy = ir;
    int ig = 2 * ir - 3;
    int idgr = -6;
    int idgd = 4 * ir - 10;
    //int fill = 0;//imagecolorexactalpha( $img, $color[ 'R' ], $color[ 'G' ], $color[ 'B' ], 0 );

//	$a = 100; //clq add alpha 颜色//其实按这个算法的意思,在后面的 42 和 100 的 alpha 修正值还应该和这个要画的颜色中的 alpha 值再等比例计算,不过这样的效果已经很好了

	uint8 r8, g8, b8, a8;

	//这几个应该都是颜色
	int fill,draw,filled;
	//int xx,yy;
	double xx,yy;//clq 后面有浮点运算,不能用整数

	//解析出颜色中的 rgba
	ex_color2rgb(img, color, &r8, &g8, &b8, &a8);

	////fill = imagecolorexactalpha(img, r8, g8, b8, 0 );
	fill = imagecolorexactalpha(img, r8, g8, b8, a8 );

    imageline(img, cx + cr - 1, cy, cx, cy, fill );
    imageline(img, cx - cr + 1, cy, cx - 1, cy, fill );
    imageline(img, cx, cy + cr - 1, cx, cy + 1, fill );
    imageline(img, cx, cy - cr + 1, cx, cy - 1, fill );

    ////draw = imagecolorexactalpha(img, r8, g8, b8, 42 );
    //$draw = imageColorExactAlpha( $img, $color[ 'R' ], $color[ 'G' ], $color[ 'B' ], 42+$a );//这样也不行,会超过 127 的最大值反而导致不透明了//因为 gd 库的 alpha 取值范围就是 0-127
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

        //imageline( img, cx + ix, cy + iy - 1, cx + ix, cy + ix, fill );//这个画的竖线
		if (ix < iy - 2)//修正多出来的右边的点
		imageline( img, cx + ix, cy + iy - 1, cx + ix, cy + ix+1, fill );//这个画的竖线

        //imageline( img, cx + ix, cy - iy + 1, cx + ix, cy - ix, fill );
		if (ix < iy - 2)//修正多出来的右边的点
		imageline( img, cx + ix, cy - iy + 1, cx + ix, cy - ix-1, fill );

        //imageline( img, cx - ix, cy + iy - 1, cx - ix, cy + ix, fill );
		if (ix < iy - 2)//修正多出来的右边的点
		imageline( img, cx - ix, cy + iy - 1, cx - ix, cy + ix+1, fill );

        //imageline( img, cx - ix, cy - iy + 1, cx - ix, cy - ix, fill );
		if (ix < iy - 2)//修正多出来的右边的点
		imageline( img, cx - ix, cy - iy + 1, cx - ix, cy - ix-1, fill );

        imageline( img, cx + iy - 1, cy + ix, cx + ix, cy + ix, fill );//这个画的横线
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
		//$draw = imageColorExactAlpha( $img, $color[ 'R' ], $color[ 'G' ], $color[ 'B' ], ( 100 - $filled )+$a );//这样也不行,会超过 127 的最大值反而导致不透明了
        draw = imagecolorexactalpha( img, r8, g8, b8, min(127, ( 100 - filled )+a8) );//continue;

        imagesetpixel( img, cx + ix, cy + iy, draw );//continue;//就是圆形外框
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
