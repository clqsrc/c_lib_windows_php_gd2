unit phpgd2;

interface

const
  php_gd2    = 'php_gd2.dll';

function imagecreatefromjpeg(filename:PAnsiChar): Integer; cdecl; external php_gd2 name 'imagecreatefromjpeg';
function imagecreatefrompng(filename:PAnsiChar): Integer; cdecl; external php_gd2;

//clq 调用这个函数后最后接着调用 imagesavealpha,这样才能存出透明的 png 图片
//新建一个真彩色图像
function imagecreatetruecolor(x_size:Integer; y_size:Integer):Integer; cdecl; external php_gd2;

function imagepng(im:Integer; outfilename:PAnsiChar): Integer; cdecl; external php_gd2;

//设置标记以在保存 PNG 图像时保存完整的 alpha 通道信息（与单一透明色相反）。
//要使用本函数，必须将 alphablending 清位（imagealphablending($im, false)）。 //指的是不要使用混色模式,直接使用 alpha 值
procedure imagesavealpha(im:Integer; save:Integer); cdecl; external php_gd2;

// imagealphablending() 允许在真彩色图像上使用两种不同的绘画模式。
// 在混色（blending）模式下，alpha 通道色彩成分提供给所有的绘画函数，例如 imagesetpixel() 决定底层的颜色应在何种程度上被允许照射透过。作为结果，GD 自动将该点现有的颜色和画笔颜色混合，并将结果储存在图像中。结果的像素是不透明的。
// 在非混色模式下，画笔颜色连同其 alpha 通道信息一起被拷贝，替换掉目标像素。混色模式在画调色板图像时不可用。
// 如果 blendmode 为 TRUE，则启用混色模式，否则关闭。成功时返回 TRUE， 或者在失败时返回 FALSE
//clq 还是有点难懂的,总之操作透明的 png 得不到想要的结果时可以切换下试试//默认是打开的
procedure imagealphablending(im:Integer; blend:Integer); cdecl; external php_gd2;

//  bool imageantialias ( resource $image , bool $enabled )
// 对线段和多边形启用快速画图抗锯齿方法。不支持 alpha 部分。使用直接混色操作。仅用于真彩色图像。
// 不支持线宽和风格。
// 使用抗锯齿和透明背景色可能出现未预期的结果。混色方法把背景色当成任何其它颜色使用。缺乏 alpha 部分的支持导致不允许基于 alpha 抗锯齿
function imageantialias(im:Integer; alias{enabled=1}:Integer):Integer; cdecl; external php_gd2;

//imagecopyresampled http://php.net/imageantialias 有个例子说明可以用 imagecopyresampled 复制图像,这样会自动有 aa 效果

//分配颜色 imagecolorallocatealpha() 的行为和 imagecolorallocate() 相同，但多了一个额外的透明度参数 alpha，其值从 0 到 127。0 表示完全不透明，127 表示完全透明。
function imagecolorallocatealpha(im:Integer; red:Integer; green:Integer; blue:Integer; alpha:Integer):Integer; cdecl; external php_gd2;
//画线
procedure imageline(im:Integer; x1:Integer; y1:Integer; x2:Integer; y2:Integer; color:Integer); cdecl; external php_gd2;
//设置画线的宽度,不过似乎不是每个绘图函数下都起作用
procedure imagesetthickness(im:Integer; thick:Integer); cdecl; external php_gd2;
//画一椭圆并填充到指定的 image//cx,cy 应该是圆心的位置 
procedure imagefilledellipse(im:Integer; cx:Integer; cy:Integer; width:Integer; height:Integer; color:Integer); cdecl; external php_gd2;

//画一个 aa 边界的圆//cr 是半径?
procedure ex_imageSmoothCircle(im:Integer; cx:Integer; cy:Integer; cr:Integer; color:Integer); cdecl; external php_gd2;
//按 imageSmoothCircle 算法做的支持 alpha 通道
procedure ex_imageSmoothCircle_alpha(im:Integer; cx:Integer; cy:Integer; cr:Integer; color:Integer); cdecl; external php_gd2;
//imagedestroy() 释放与 image 关联的内存
procedure imagedestroy(im:Integer); cdecl; external php_gd2;
//如果 font 是 1，2，3，4 或 5，则使用内置字体,否则使用 imageloadfont() 装载字体
procedure imagestring(im:Integer; _font:Integer; x:Integer; y:Integer; str:PAnsiChar; color:Integer); cdecl; external php_gd2;

//imagettftext — 用 TrueType 字体向图像
//imagefttext — 使用 FreeType 2 字体将文本写入图像写入文本//size 字体大小, angle 角度(一般是0)
function imagettftext(im:Integer; size:Double; angle:Double; x:Integer; y:Integer; color:Integer; fontfile:PAnsiChar; text:PAnsiChar):PAnsiChar; cdecl; external php_gd2;

//图片宽,高
function imagesx(im:Integer):Integer; cdecl; external php_gd2;
function imagesy(im:Integer):Integer; cdecl; external php_gd2;

//将一幅图像中的一块正方形区域拷贝到另一个图像中，平滑地插入像素值，因此，尤其是，减小了图像的大小而仍然保持了极大的清晰度。 
function imagecopyresampled(im_dst, im_src:Integer; dstX , dstY , srcX , srcY , dstW , dstH , srcW , srcH:Integer):Integer; cdecl; external php_gd2;

//设置某个点的像素颜色
//PHP_FUNCTION(imagesetpixel)
procedure imagesetpixel(im:Integer; x:Integer; y:Integer; color:Integer); cdecl; external php_gd2;
//可以认为是 imagegetpixel
function imagecolorat(im:Integer; x:Integer; y:Integer):Integer; cdecl; external php_gd2;


//将一幅图像中的一块正方形区域拷贝到另一个图像中，平滑地插入像素值，因此，尤其是，减小了图像的大小而仍然保持了极大的清晰度。 
function imagecopyresampled2(im_dst, im_src:Integer; dstX , dstY , srcX , srcY , dstW , dstH , srcW , srcH:Integer):Integer; //cdecl; external php_gd2;

//解析出一个颜色的 rgba 值//注意应该输出的指针就是 8 位的整数,位数不对的话应该会乱码的//尽量保存原来的 rgb 值,少用这个函数
//GD_API void ex_color2rgb(gdImagePtr img, int color, uint8 * r8, uint8 * g8, uint8 * b8, uint8 * a8);
procedure ex_color2rgb(img:Integer; color:Integer; r8:PByte; g8:PByte; b8:PByte; a8:PByte); cdecl; external php_gd2;


implementation


//与 "aaline手工画线" 一样,算法思想都来自 "计算机图形学原理及实践—C语言描述.pdf" ,基本上是其的简化版本算法//虽然是简化效果已经不错了


//将一幅图像中的一块正方形区域拷贝到另一个图像中，平滑地插入像素值，因此，尤其是，减小了图像的大小而仍然保持了极大的清晰度。
//这个简单的算法似乎比 php 的 gdImageCopyResized 好//用来做放大肯定是没问题的,缩小的话,其实再取一下相邻的值就可以了,至于取多少个相邻像素可以直接按像素来(完全没必要使用网上说的插值算法)

function imagecopyresampled2(im_dst, im_src:Integer; dstX , dstY , srcX , srcY , dstW , dstH , srcW , srcH:Integer):Integer; //cdecl; external php_gd2;
var
  w,h:integer;
  i,j:integer;
  i2,j2:integer;
  c, c2:Integer;
  r8, g8, b8, a8:Byte;

  pix_count:Integer;//计算缩小了多少倍,就是要取相邻的多少个像素点//有个潜在的 bug, 如果缩小得非常多就会在 rgb 合并是溢出,不过可以忽略这种情况
  pix_count_square:Integer;//平方数//只是为优化而已


  //计算一个点的像素值//取4个点的平均值//这是固定取 4 个点的算法,效果倒也还可以
  function GetAAPixel(x,y:Integer):Integer;
  var
    xsrc,ysrc:Integer;
    r, g, b, a:Integer;//rgb 值的总和

    xadd,yadd:Integer; //取多少个点的值来算当前这个点
    xsrc2,ysrc2:Integer;//避免越界
    //pix_count:Integer;//计算缩小了多少倍,就是要取相邻的多少个像素点//有个潜在的 bug, 如果缩小得非常多就会在 rgb 合并是溢出,不过可以忽略这种情况
    //pix_count_square:Integer;//平方数//只是为优化而已
  begin
    r := 0; g := 0; b := 0; a := 0;

    //算出这个代表应该是原图的什么位置
    xsrc := Trunc(x * srcW / w);
    ysrc := Trunc(y * srcH / h);

    //--------------------------------------------------
    //为优化速度,计算应该放在函数体外
//    pix_count := srcW div dstW;//其实应该用浮点数,但是那样太慢了
//
//    if pix_count<1 then pix_count := 1;
//    //if pix_count<2 then pix_count := 2; //如果要放大的效果好点,可以用这个
//
//    pix_count_square := pix_count * pix_count;
    //--------------------------------------------------

    for xadd := 0 to pix_count-1 do
    begin
      for yadd := 0 to pix_count-1 do
      begin
        xsrc2 := xsrc + xadd; ysrc2 := ysrc + yadd;//避免越界
        if xsrc2>srcW-1 then xsrc2 := srcW-1;
        if ysrc2>srcH-1 then ysrc2 := srcH-1;

        c := imagecolorat(im_src, xsrc2, ysrc2);
        ex_color2rgb(im_src, c, @r8, @g8, @b8, @a8);//很快

        r := r + r8; g := g + g8; b := b + b8; a := a + a8;

      end;

    end;

//    c := imagecolorat(im_src, xsrc, ysrc);
//    ex_color2rgb(im_src, c, @r8, @g8, @b8, @a8);//很快
//
//    r := r + r8; g := g + g8; b := b + b8; a := a + a8;

    //c2 := imagecolorallocatealpha(im_dst, r, g, b, a);//很快
    //c2 := imagecolorallocatealpha(im_dst, r div 4, g div 4, b div 4, a div 4);//很快
    c2 := imagecolorallocatealpha(im_dst, r div pix_count_square, g div pix_count_square, b div pix_count_square, a div pix_count_square);//很快

    Result := c2;
  end;

begin
  Result := 1;

  w := imagesx(im_dst);
  h := imagesy(im_dst);

  //--------------------------------------------------
  //为优化速度,计算应该放在函数体外
  pix_count := srcW div dstW;//其实应该用浮点数,但是那样太慢了

  if pix_count<1 then pix_count := 1;
  if pix_count<2 then pix_count := 2; //如果要放大的效果好点,可以用这个

  pix_count_square := pix_count * pix_count;
  //--------------------------------------------------


  for i := 0 to w-1 do
  begin

    for j := 0 to h-1  do
    begin
      c := imagecolorat(im_src, i, j);
      ex_color2rgb(im_src, c, @r8, @g8, @b8, @a8);//很快

      //--------------------------------------------------
      //算出这个代表应该是原图的什么位置
      i2 := Trunc(i * srcW / w);
      j2 := Trunc(j * srcH / h);
      c := imagecolorat(im_src, i2, j2);
      ex_color2rgb(im_src, c, @r8, @g8, @b8, @a8);//很快

      //--------------------------------------------------

      //c2 := imagecolorallocatealpha(im_dst, r8, g8, b8, a8);//很快
      c2 := GetAAPixel(i, j);

      imagesetpixel(im_dst, i, j, c2);//很快

    end;

  end;



end;


//取两个像素计算平均值(因为是平面,所以实际上是4个像素的平均值),可以用在要求不高的地方
function imagecopyresampled2_2(im_dst, im_src:Integer; dstX , dstY , srcX , srcY , dstW , dstH , srcW , srcH:Integer):Integer; //cdecl; external php_gd2;
var
  w,h:integer;
  i,j:integer;
  i2,j2:integer;
  c, c2:Integer;
  r8, g8, b8, a8:Byte;

  //计算一个点的像素值//取4个点的平均值//这是固定取 4 个点的算法,效果倒也还可以
  function GetAAPixel(x,y:Integer):Integer;
  var
    xsrc,ysrc:Integer;
    r, g, b, a:Integer;//rgb 值的总和

    xadd,yadd:Integer; //取多少个点的值来算当前这个点
    xsrc2,ysrc2:Integer;//避免越界
  begin
    r := 0; g := 0; b := 0; a := 0;

    //算出这个代表应该是原图的什么位置
    xsrc := Trunc(x * srcW / w);
    ysrc := Trunc(y * srcH / h);

    for xadd := 0 to 2-1 do
    begin
      for yadd := 0 to 2-1 do
      begin
        xsrc2 := xsrc + xadd; ysrc2 := ysrc + yadd;//避免越界
        if xsrc2>srcW-1 then xsrc2 := srcW-1;
        if ysrc2>srcH-1 then ysrc2 := srcH-1;

        c := imagecolorat(im_src, xsrc2, ysrc2);
        ex_color2rgb(im_src, c, @r8, @g8, @b8, @a8);//很快

        r := r + r8; g := g + g8; b := b + b8; a := a + a8;

      end;

    end;

//    c := imagecolorat(im_src, xsrc, ysrc);
//    ex_color2rgb(im_src, c, @r8, @g8, @b8, @a8);//很快
//
//    r := r + r8; g := g + g8; b := b + b8; a := a + a8;

    //c2 := imagecolorallocatealpha(im_dst, r, g, b, a);//很快
    c2 := imagecolorallocatealpha(im_dst, r div 4, g div 4, b div 4, a div 4);//很快

    Result := c2;
  end;

begin
  Result := 1;

  w := imagesx(im_dst);
  h := imagesy(im_dst);

  for i := 0 to w-1 do
  begin

    for j := 0 to h-1  do
    begin
      c := imagecolorat(im_src, i, j);
      ex_color2rgb(im_src, c, @r8, @g8, @b8, @a8);//很快

      //--------------------------------------------------
      //算出这个代表应该是原图的什么位置
      i2 := Trunc(i * srcW / w);
      j2 := Trunc(j * srcH / h);
      c := imagecolorat(im_src, i2, j2);
      ex_color2rgb(im_src, c, @r8, @g8, @b8, @a8);//很快

      //--------------------------------------------------

      //c2 := imagecolorallocatealpha(im_dst, r8, g8, b8, a8);//很快
      c2 := GetAAPixel(i, j);

      imagesetpixel(im_dst, i, j, c2);//很快

    end;

  end;



end;

//第一个,很快的算法//只是简单地取坐标像素,缩小的话会丢失像素值,不过用来放大是没问题的
function imagecopyresampled2_1(im_dst, im_src:Integer; dstX , dstY , srcX , srcY , dstW , dstH , srcW , srcH:Integer):Integer; //cdecl; external php_gd2;
var
  w,h:integer;
  i,j:integer;
  i2,j2:integer;
  c, c2:Integer;
  r8, g8, b8, a8:Byte;

begin
  Result := 1;

  w := imagesx(im_dst);
  h := imagesy(im_dst);

  for i := 0 to w-1 do
  begin

    for j := 0 to h-1  do
    begin
      c := imagecolorat(im_src, i, j);
      ex_color2rgb(im_src, c, @r8, @g8, @b8, @a8);//很快

      //--------------------------------------------------
      //算出这个代表应该是原图的什么位置
      i2 := Trunc(i * srcW / w);
      j2 := Trunc(j * srcH / h);
      c := imagecolorat(im_src, i2, j2);
      ex_color2rgb(im_src, c, @r8, @g8, @b8, @a8);//很快

      //--------------------------------------------------

      c2 := imagecolorallocatealpha(im_dst, r8, g8, b8, a8);//很快

      imagesetpixel(im_dst, i, j, c);//很快

    end;

  end;



end;  




end.
