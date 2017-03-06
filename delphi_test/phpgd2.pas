unit phpgd2;

interface

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

//����ĳ�����������ɫ
//PHP_FUNCTION(imagesetpixel)
procedure imagesetpixel(im:Integer; x:Integer; y:Integer; color:Integer); cdecl; external php_gd2;
//������Ϊ�� imagegetpixel
function imagecolorat(im:Integer; x:Integer; y:Integer):Integer; cdecl; external php_gd2;


//��һ��ͼ���е�һ�����������򿽱�����һ��ͼ���У�ƽ���ز�������ֵ����ˣ������ǣ���С��ͼ��Ĵ�С����Ȼ�����˼���������ȡ� 
function imagecopyresampled2(im_dst, im_src:Integer; dstX , dstY , srcX , srcY , dstW , dstH , srcW , srcH:Integer):Integer; //cdecl; external php_gd2;

//������һ����ɫ�� rgba ֵ//ע��Ӧ�������ָ����� 8 λ������,λ�����ԵĻ�Ӧ�û������//��������ԭ���� rgb ֵ,�����������
//GD_API void ex_color2rgb(gdImagePtr img, int color, uint8 * r8, uint8 * g8, uint8 * b8, uint8 * a8);
procedure ex_color2rgb(img:Integer; color:Integer; r8:PByte; g8:PByte; b8:PByte; a8:PByte); cdecl; external php_gd2;


implementation


//��һ��ͼ���е�һ�����������򿽱�����һ��ͼ���У�ƽ���ز�������ֵ����ˣ������ǣ���С��ͼ��Ĵ�С����Ȼ�����˼���������ȡ�
//����򵥵��㷨�ƺ��� php �� gdImageCopyResized ��//�������Ŵ�϶���û�����,��С�Ļ�,��ʵ��ȡһ�����ڵ�ֵ�Ϳ�����,����ȡ���ٸ��������ؿ���ֱ�Ӱ�������(��ȫû��Ҫʹ������˵�Ĳ�ֵ�㷨)
function imagecopyresampled2(im_dst, im_src:Integer; dstX , dstY , srcX , srcY , dstW , dstH , srcW , srcH:Integer):Integer; //cdecl; external php_gd2;
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
      ex_color2rgb(im_src, c, @r8, @g8, @b8, @a8);//�ܿ�

      //--------------------------------------------------
      //����������Ӧ����ԭͼ��ʲôλ��
      i2 := Trunc(i * srcW / w);
      j2 := Trunc(j * srcH / h);
      c := imagecolorat(im_src, i2, j2);
      ex_color2rgb(im_src, c, @r8, @g8, @b8, @a8);//�ܿ�

      //--------------------------------------------------

      c2 := imagecolorallocatealpha(im_dst, r8, g8, b8, a8);//�ܿ�

      imagesetpixel(im_dst, i, j, c);//�ܿ�

    end;

  end;



end;  



end.