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




var
  Form1: TForm1;

implementation

uses phpgd2;

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
  i:Integer;
  ttt:Integer;
begin

    image := imagecreatefrompng(PAnsiChar(sourePic));//PNG
            imagesavealpha(image, 1);//true);//这里很重要 意思是不要丢了$sourePic图像的透明色;
            BigWidth := imagesx(image);//大图宽度
            BigHeigh :=imagesy(image);//大图高度
            thumb := imagecreatetruecolor(dwidth, dheigh);
            imagealphablending(thumb, 0);//false);//这里很重要,意思是不合并颜色,直接用$img图像颜色替换,包括透明色;
            imagesavealpha(thumb, 1);//true);//这里很重要,意思是不要丢了$thumb图像的透明色;
            //imagecopyresampled(thumb,image,0,0,0,0,dwidth,dheigh,BigWidth,BigHeigh); //明显有点慢,设置像素本身还是很快的
            imagecopyresampled2(thumb,image,0,0,0,0,dwidth,dheigh,BigWidth,BigHeigh); //说明是算法本身而不是 gd 库的性能有问题

            //for i := 0 to 90 do
            for i := 0 to 9 do
            begin
              imagecopyresampled2(thumb,image,0,0,0,0,dwidth,dheigh,BigWidth,BigHeigh);
            end;

            //--------------------------------------------------
//            ttt := imagecreatetruecolor(dwidth*4, dheigh*4); //aa4 算法
//            imagecopyresampled2(ttt,image,0,0,0,0,dwidth*4,dheigh*4,BigWidth,BigHeigh);
//
//            imagecopyresampled2(thumb,ttt,0,0,0,0,dwidth,dheigh,dwidth*4,dheigh*4);

            //--------------------------------------------------

            if(imagecopyresampled2(thumb,image,0,0,0,0,dwidth,dheigh,BigWidth,BigHeigh) = 1) then
            imagepng(thumb, PAnsiChar(smallFileName));

            //return $smallFileName;//返回小图路径 转载注明 www.chhua.com



end;


procedure TForm1.Button2Click(Sender: TObject);
begin
  //
  //pngthumb(ExtractFilePath(Application.ExeName)+'11.png', ExtractFilePath(Application.ExeName)+'2.png', 50, 50);
  //pngthumb(ExtractFilePath(Application.ExeName)+'1.png', ExtractFilePath(Application.ExeName)+'2.png', 800, 800);
  //pngthumb(ExtractFilePath(Application.ExeName)+'1.png', ExtractFilePath(Application.ExeName)+'2.png', 2000, 2000);
//  pngthumb(ExtractFilePath(Application.ExeName)+'1.png', ExtractFilePath(Application.ExeName)+'2.png', 650, 650);

  //对小图片的性能不佳的话,可以放大后再缩小
  pngthumb(ExtractFilePath(Application.ExeName)+'11.png', ExtractFilePath(Application.ExeName)+'22.png', 5000, 5000);//放大目标大小的 100 倍//从实际来看不必要 10 倍就可以了
  pngthumb(ExtractFilePath(Application.ExeName)+'11.png', ExtractFilePath(Application.ExeName)+'22.png', 500, 500);//放大目标大小的 10 倍
  pngthumb(ExtractFilePath(Application.ExeName)+'22.png', ExtractFilePath(Application.ExeName)+'2.png', 50, 50);

end;

end.
