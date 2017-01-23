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

//clq ������������������ŵ��� imagesavealpha,�������ܴ��͸���� png ͼƬ
//�½�һ�����ɫͼ��
function imagecreatetruecolor(x_size:Integer; y_size:Integer):Integer; cdecl; external php_gd2;

function imagepng(im:Integer; outfilename:PAnsiChar): Integer; cdecl; external php_gd2;

//���ñ�����ڱ��� PNG ͼ��ʱ���������� alpha ͨ����Ϣ���뵥һ͸��ɫ�෴����
//Ҫʹ�ñ����������뽫 alphablending ��λ��imagealphablending($im, false)���� //ָ���ǲ�Ҫʹ�û�ɫģʽ,ֱ��ʹ�� alpha ֵ
procedure imagesavealpha(im:Integer; save:Integer); cdecl; external php_gd2;

// imagealphablending() ���������ɫͼ����ʹ�����ֲ�ͬ�Ļ滭ģʽ��
// �ڻ�ɫ��blending��ģʽ�£�alpha ͨ��ɫ�ʳɷ��ṩ�����еĻ滭���������� imagesetpixel() �����ײ����ɫӦ�ں��̶ֳ��ϱ���������͸������Ϊ�����GD �Զ����õ����е���ɫ�ͻ�����ɫ��ϣ��������������ͼ���С�����������ǲ�͸���ġ�
// �ڷǻ�ɫģʽ�£�������ɫ��ͬ�� alpha ͨ����Ϣһ�𱻿������滻��Ŀ�����ء���ɫģʽ�ڻ���ɫ��ͼ��ʱ�����á�
// ��� blendmode Ϊ TRUE�������û�ɫģʽ������رա��ɹ�ʱ���� TRUE�� ������ʧ��ʱ���� FALSE
//clq �����е��Ѷ���,��֮����͸���� png �ò�����Ҫ�Ľ��ʱ�����л�������//Ĭ���Ǵ򿪵�
procedure imagealphablending(im:Integer; blend:Integer); cdecl; external php_gd2;

//  bool imageantialias ( resource $image , bool $enabled )
// ���߶κͶ�������ÿ��ٻ�ͼ����ݷ�������֧�� alpha ���֡�ʹ��ֱ�ӻ�ɫ���������������ɫͼ��
// ��֧���߿��ͷ��
// ʹ�ÿ���ݺ�͸������ɫ���ܳ���δԤ�ڵĽ������ɫ�����ѱ���ɫ�����κ�������ɫʹ�á�ȱ�� alpha ���ֵ�֧�ֵ��²��������� alpha �����
function imageantialias(im:Integer; alias{enabled=1}:Integer):Integer; cdecl; external php_gd2;

//imagecopyresampled http://php.net/imageantialias �и�����˵�������� imagecopyresampled ����ͼ��,�������Զ��� aa Ч��

//������ɫ imagecolorallocatealpha() ����Ϊ�� imagecolorallocate() ��ͬ��������һ�������͸���Ȳ��� alpha����ֵ�� 0 �� 127��0 ��ʾ��ȫ��͸����127 ��ʾ��ȫ͸����
function imagecolorallocatealpha(im:Integer; red:Integer; green:Integer; blue:Integer; alpha:Integer):Integer; cdecl; external php_gd2;
//����
procedure imageline(im:Integer; x1:Integer; y1:Integer; x2:Integer; y2:Integer; color:Integer); cdecl; external php_gd2;
//���û��ߵĿ���,�����ƺ�����ÿ����ͼ�����¶�������
procedure imagesetthickness(im:Integer; thick:Integer); cdecl; external php_gd2;
//��һ��Բ����䵽ָ���� image//cx,cy Ӧ����Բ�ĵ�λ�� 
procedure imagefilledellipse(im:Integer; cx:Integer; cy:Integer; width:Integer; height:Integer; color:Integer); cdecl; external php_gd2;

//��һ�� aa �߽��Բ//cr �ǰ뾶?
procedure ex_imageSmoothCircle(im:Integer; cx:Integer; cy:Integer; cr:Integer; color:Integer); cdecl; external php_gd2;
//�� imageSmoothCircle �㷨����֧�� alpha ͨ��
procedure ex_imageSmoothCircle_alpha(im:Integer; cx:Integer; cy:Integer; cr:Integer; color:Integer); cdecl; external php_gd2;
//imagedestroy() �ͷ��� image �������ڴ�
procedure imagedestroy(im:Integer); cdecl; external php_gd2;
//��� font �� 1��2��3��4 �� 5����ʹ����������,����ʹ�� imageloadfont() װ������
procedure imagestring(im:Integer; _font:Integer; x:Integer; y:Integer; str:PAnsiChar; color:Integer); cdecl; external php_gd2;

//imagettftext �� �� TrueType ������ͼ��
//imagefttext �� ʹ�� FreeType 2 ���彫�ı�д��ͼ��д���ı�//size �����С, angle �Ƕ�(һ����0)
function imagettftext(im:Integer; size:Double; angle:Double; x:Integer; y:Integer; color:Integer; fontfile:PAnsiChar; text:PAnsiChar):PAnsiChar; cdecl; external php_gd2;

//ͼƬ��,��
function imagesx(im:Integer):Integer; cdecl; external php_gd2;
function imagesy(im:Integer):Integer; cdecl; external php_gd2;

//��һ��ͼ���е�һ�����������򿽱�����һ��ͼ���У�ƽ���ز�������ֵ����ˣ������ǣ���С��ͼ��Ĵ�С����Ȼ�����˼���������ȡ� 
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
  //imageantialias(im, 1);//�о����Ǻܿ���,�ᵼ�� imagesetthickness �� alpha ʧ��,�о��������� alpha ��ɫ���,����������ͨ�Ļ�,Ȼ������ aa ģʽ���

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

  //��һ�� aa �߽��Բ//cr �ǰ뾶?
  color := imagecolorallocatealpha(im, 255, 0, 0, 100);
  //ex_imageSmoothCircle(im, 200, 200, 50, color);
  ////ex_imageSmoothCircle(im, 190,  90,  125, color);//ok
  ex_imageSmoothCircle_alpha(im, 190,  90,  125, color);

  color := imagecolorallocatealpha(im, 255, 0, 0, 0);
  imagestring(im, 1, 0, 0, 'aaa', color);
  imagestring(im, 5, 250, 250, 'aaa����', color); //Ĭ�������ǳ��������ĵ�

//2
//	//��PHP��ͼ�κ�����������Ұ��㡱
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
//	ImageTTFText($im,20,0,4,40,$yellow,"simkai.ttf",$cur_count);//������ѡ��ı��������ǿ��壬����ѡ��ϵͳ�ֿ��д��ڵ���

  ImageTTFText(im, 20, 0, 4, 40, color, 'simkai.ttf', PAnsiChar(AnsiToUtf8('123abc���ĺ�')));//������ѡ��ı��������ǿ��壬����ѡ��ϵͳ�ֿ��д��ڵ���


  r := imagepng(im, 'd:\1.png');
  imagedestroy(im);
  ShowMessage(IntToStr(r));
end;

(*

<?PHP
/*
 *$sourePic:ԭͼ·��
 * $smallFileName:Сͼ����
 * $width:Сͼ��
 * $heigh:Сͼ��
 * ת��ע�� www.chhua.com*/
function pngthumb($sourePic,$smallFileName,$width,$heigh){
    $image=imagecreatefrompng($sourePic);//PNG
            imagesavealpha($image,true);//�������Ҫ ��˼�ǲ�Ҫ����$sourePicͼ���͸��ɫ;
            $BigWidth=imagesx($image);//��ͼ����
            $BigHeigh=imagesy($image);//��ͼ�߶�
            $thumb = imagecreatetruecolor($width,$heigh);
            imagealphablending($thumb,false);//�������Ҫ,��˼�ǲ��ϲ���ɫ,ֱ����$imgͼ����ɫ�滻,����͸��ɫ;
            imagesavealpha($thumb,true);//�������Ҫ,��˼�ǲ�Ҫ����$thumbͼ���͸��ɫ;
            if(imagecopyresampled($thumb,$image,0,0,0,0,$width,$heigh,$BigWidth,$BigHeigh)){
            imagepng($thumb,$smallFileName);}
            return $smallFileName;//����Сͼ·�� ת��ע�� www.chhua.com
}
  
pngthumb("a.png", "c.png", 300, 300);//����
?>

*)

procedure pngthumb(sourePic:string; smallFileName:string; dwidth:Integer; dheigh:Integer);
var
  image, thumb:Integer; //ͼƬ
  BigWidth, BigHeigh:Integer;
begin

    image := imagecreatefrompng(PAnsiChar(sourePic));//PNG
            imagesavealpha(image, 1);//true);//�������Ҫ ��˼�ǲ�Ҫ����$sourePicͼ���͸��ɫ;
            BigWidth := imagesx(image);//��ͼ����
            BigHeigh :=imagesy(image);//��ͼ�߶�
            thumb := imagecreatetruecolor(dwidth, dheigh);
            imagealphablending(thumb, 0);//false);//�������Ҫ,��˼�ǲ��ϲ���ɫ,ֱ����$imgͼ����ɫ�滻,����͸��ɫ;
            imagesavealpha(thumb, 1);//true);//�������Ҫ,��˼�ǲ�Ҫ����$thumbͼ���͸��ɫ;
            if(imagecopyresampled(thumb,image,0,0,0,0,dwidth,dheigh,BigWidth,BigHeigh) = 1) then
            imagepng(thumb, PAnsiChar(smallFileName));

            //return $smallFileName;//����Сͼ·�� ת��ע�� www.chhua.com



end;


procedure TForm1.Button2Click(Sender: TObject);
begin
  //
  pngthumb(ExtractFilePath(Application.ExeName)+'1.png', ExtractFilePath(Application.ExeName)+'2.png', 50, 50);

end;

end.