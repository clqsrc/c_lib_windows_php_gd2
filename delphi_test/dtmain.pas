unit dtmain;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm1 = class(TForm)
    Button1: TButton;
    Button2: TButton;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

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




var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
var
  im:Integer;
  r,color:Integer;
begin
  im := imagecreatefromjpeg('c:\1.jpg');
  //imageantialias(im, 1);//感觉不是很靠谱,会导致 imagesetthickness 和 alpha 失败,感觉还不如用 alpha 颜色描边,或者先用普通的画,然后再用 aa 模式描边

  imagesetthickness(im, 3);
  color := imagecolorallocatealpha(im, 255, 0, 0, 100);
  imageline(im, 0, 0, 100, 100, color);

  imagefilledellipse(im,  0, 0, 100, 100, color);

//  color := imagecolorallocatealpha(im, 255, 0, 0, 110);
//  imagefilledellipse(im,  200, 200, 98, 98, color);
//  color := imagecolorallocatealpha(im, 255, 0, 0, 80);
//  imagefilledellipse(im,  200, 200, 96, 96, color);
  color := imagecolorallocatealpha(im, 255, 0, 0, 50);
  imagefilledellipse(im,  200, 200, 94, 94, color);

  //画一个 aa 边界的圆//cr 是半径?
  color := imagecolorallocatealpha(im, 255, 0, 0, 100);
  //ex_imageSmoothCircle(im, 200, 200, 50, color);
  ////ex_imageSmoothCircle(im, 190,  90,  125, color);//ok
  ex_imageSmoothCircle_alpha(im, 190,  90,  125, color);

  color := imagecolorallocatealpha(im, 255, 0, 0, 0);
  imagestring(im, 1, 0, 0, 'aaa', color);
  imagestring(im, 5, 250, 250, 'aaa中文', color); //默认字体是出不来中文的

//2
//	//在PHP的图形函数中输出“我爱你”
//03
//	$cur_count=chr(0xE6).chr(0x88).chr(0x91).chr(0xE7).chr(0x88).chr(0xB1).chr(0xE4).chr(0xBD).chr(0xA0).chr(0xEF).chr(0xBC).chr(0x81) ;
//04
//	Header("Content-type: image/gif");
//05
//	$im = imagecreate(156,116);
//06
//	$black = ImageColorAllocate($im, 0,0,0);
//07
//	$blue = ImageColorAllocate($im, 0,0,255);
//08
//	$white = ImageColorAllocate($im, 255,255,255);
//09
//	$yellow = ImageColorAllocate($im, 255,255,0);
//10
//	ImageTTFText($im,20,0,4,40,$yellow,"simkai.ttf",$cur_count);//我这里选择的本地字体是楷体，必须选择系统字库中存在的字

  //在某些版本操作系统下,字体文件在和主程序在同一个文件夹,否则画不出字
  ImageTTFText(im, 20, 0, 4, 40, color, 'simkai.ttf', PAnsiChar(AnsiToUtf8('123abc中文好')));//我这里选择的本地字体是楷体，必须选择系统字库中存在的字


  r := imagepng(im, 'd:\1.png');
  imagedestroy(im);
  ShowMessage(IntToStr(r));
end;

(*

<?PHP
/*
 *$sourePic:原图路径
 * $smallFileName:小图名称
 * $width:小图宽
 * $heigh:小图高
 * 转载注明 www.chhua.com*/
function pngthumb($sourePic,$smallFileName,$width,$heigh){
    $image=imagecreatefrompng($sourePic);//PNG
            imagesavealpha($image,true);//这里很重要 意思是不要丢了$sourePic图像的透明色;
            $BigWidth=imagesx($image);//大图宽度
            $BigHeigh=imagesy($image);//大图高度
            $thumb = imagecreatetruecolor($width,$heigh);
            imagealphablending($thumb,false);//这里很重要,意思是不合并颜色,直接用$img图像颜色替换,包括透明色;
            imagesavealpha($thumb,true);//这里很重要,意思是不要丢了$thumb图像的透明色;
            if(imagecopyresampled($thumb,$image,0,0,0,0,$width,$heigh,$BigWidth,$BigHeigh)){
            imagepng($thumb,$smallFileName);}
            return $smallFileName;//返回小图路径 转载注明 www.chhua.com
}
  
pngthumb("a.png", "c.png", 300, 300);//调用
?>

*)

procedure pngthumb(sourePic:string; smallFileName:string; dwidth:Integer; dheigh:Integer);
var
  image, thumb:Integer; //图片
  BigWidth, BigHeigh:Integer;
begin

    image := imagecreatefrompng(PAnsiChar(sourePic));//PNG
            imagesavealpha(image, 1);//true);//这里很重要 意思是不要丢了$sourePic图像的透明色;
            BigWidth := imagesx(image);//大图宽度
            BigHeigh :=imagesy(image);//大图高度
            thumb := imagecreatetruecolor(dwidth, dheigh);
            imagealphablending(thumb, 0);//false);//这里很重要,意思是不合并颜色,直接用$img图像颜色替换,包括透明色;
            imagesavealpha(thumb, 1);//true);//这里很重要,意思是不要丢了$thumb图像的透明色;
            if(imagecopyresampled(thumb,image,0,0,0,0,dwidth,dheigh,BigWidth,BigHeigh) = 1) then
            imagepng(thumb, PAnsiChar(smallFileName));

            //return $smallFileName;//返回小图路径 转载注明 www.chhua.com



end;


procedure TForm1.Button2Click(Sender: TObject);
begin
  //
  pngthumb(ExtractFilePath(Application.ExeName)+'1.png', ExtractFilePath(Application.ExeName)+'2.png', 50, 50);

end;

end.
