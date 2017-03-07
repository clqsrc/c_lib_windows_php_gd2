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
// ��֧���߿�ͷ��
// ʹ�ÿ���ݺ�͸������ɫ���ܳ���δԤ�ڵĽ������ɫ�����ѱ���ɫ�����κ�������ɫʹ�á�ȱ�� alpha ���ֵ�֧�ֵ��²�������� alpha �����
function imageantialias(im:Integer; alias{enabled=1}:Integer):Integer; cdecl; external php_gd2;

//imagecopyresampled http://php.net/imageantialias �и�����˵�������� imagecopyresampled ����ͼ��,�������Զ��� aa Ч��

//������ɫ imagecolorallocatealpha() ����Ϊ�� imagecolorallocate() ��ͬ��������һ�������͸���Ȳ��� alpha����ֵ�� 0 �� 127��0 ��ʾ��ȫ��͸����127 ��ʾ��ȫ͸����
function imagecolorallocatealpha(im:Integer; red:Integer; green:Integer; blue:Integer; alpha:Integer):Integer; cdecl; external php_gd2;
//����
procedure imageline(im:Integer; x1:Integer; y1:Integer; x2:Integer; y2:Integer; color:Integer); cdecl; external php_gd2;
//���û��ߵĿ��,�����ƺ�����ÿ����ͼ�����¶�������
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


//�� "aaline�ֹ�����" һ��,�㷨˼�붼���� "�����ͼ��ѧԭ��ʵ����C��������.pdf" ,����������ļ򻯰汾�㷨//��Ȼ�Ǽ�Ч���Ѿ�������


//��һ��ͼ���е�һ�����������򿽱�����һ��ͼ���У�ƽ���ز�������ֵ����ˣ������ǣ���С��ͼ��Ĵ�С����Ȼ�����˼���������ȡ�
//����򵥵��㷨�ƺ��� php �� gdImageCopyResized ��//�������Ŵ�϶���û�����,��С�Ļ�,��ʵ��ȡһ�����ڵ�ֵ�Ϳ�����,����ȡ���ٸ��������ؿ���ֱ�Ӱ�������(��ȫû��Ҫʹ������˵�Ĳ�ֵ�㷨)

function imagecopyresampled2(im_dst, im_src:Integer; dstX , dstY , srcX , srcY , dstW , dstH , srcW , srcH:Integer):Integer; //cdecl; external php_gd2;
var
  w,h:integer;
  i,j:integer;
  i2,j2:integer;
  c, c2:Integer;
  r8, g8, b8, a8:Byte;

  pix_count:Integer;//������С�˶��ٱ�,����Ҫȡ���ڵĶ��ٸ����ص�//�и�Ǳ�ڵ� bug, �����С�÷ǳ���ͻ��� rgb �ϲ������,�������Ժ����������
  pix_count_square:Integer;//ƽ����//ֻ��Ϊ�Ż�����


  //����һ���������ֵ//ȡ4�����ƽ��ֵ//���ǹ̶�ȡ 4 ������㷨,Ч����Ҳ������
  function GetAAPixel(x,y:Integer):Integer;
  var
    xsrc,ysrc:Integer;
    r, g, b, a:Integer;//rgb ֵ���ܺ�

    xadd,yadd:Integer; //ȡ���ٸ����ֵ���㵱ǰ�����
    xsrc2,ysrc2:Integer;//����Խ��
    //pix_count:Integer;//������С�˶��ٱ�,����Ҫȡ���ڵĶ��ٸ����ص�//�и�Ǳ�ڵ� bug, �����С�÷ǳ���ͻ��� rgb �ϲ������,�������Ժ����������
    //pix_count_square:Integer;//ƽ����//ֻ��Ϊ�Ż�����
  begin
    r := 0; g := 0; b := 0; a := 0;

    //����������Ӧ����ԭͼ��ʲôλ��
    xsrc := Trunc(x * srcW / w);
    ysrc := Trunc(y * srcH / h);

    //--------------------------------------------------
    //Ϊ�Ż��ٶ�,����Ӧ�÷��ں�������
//    pix_count := srcW div dstW;//��ʵӦ���ø�����,��������̫����
//
//    if pix_count<1 then pix_count := 1;
//    //if pix_count<2 then pix_count := 2; //���Ҫ�Ŵ��Ч���õ�,���������
//
//    pix_count_square := pix_count * pix_count;
    //--------------------------------------------------

    for xadd := 0 to pix_count-1 do
    begin
      for yadd := 0 to pix_count-1 do
      begin
        xsrc2 := xsrc + xadd; ysrc2 := ysrc + yadd;//����Խ��
        if xsrc2>srcW-1 then xsrc2 := srcW-1;
        if ysrc2>srcH-1 then ysrc2 := srcH-1;

        c := imagecolorat(im_src, xsrc2, ysrc2);
        ex_color2rgb(im_src, c, @r8, @g8, @b8, @a8);//�ܿ�

        r := r + r8; g := g + g8; b := b + b8; a := a + a8;

      end;

    end;

//    c := imagecolorat(im_src, xsrc, ysrc);
//    ex_color2rgb(im_src, c, @r8, @g8, @b8, @a8);//�ܿ�
//
//    r := r + r8; g := g + g8; b := b + b8; a := a + a8;

    //c2 := imagecolorallocatealpha(im_dst, r, g, b, a);//�ܿ�
    //c2 := imagecolorallocatealpha(im_dst, r div 4, g div 4, b div 4, a div 4);//�ܿ�
    c2 := imagecolorallocatealpha(im_dst, r div pix_count_square, g div pix_count_square, b div pix_count_square, a div pix_count_square);//�ܿ�

    Result := c2;
  end;

begin
  Result := 1;

  w := imagesx(im_dst);
  h := imagesy(im_dst);

  //--------------------------------------------------
  //Ϊ�Ż��ٶ�,����Ӧ�÷��ں�������
  pix_count := srcW div dstW;//��ʵӦ���ø�����,��������̫����

  if pix_count<1 then pix_count := 1;
  if pix_count<2 then pix_count := 2; //���Ҫ�Ŵ��Ч���õ�,���������

  pix_count_square := pix_count * pix_count;
  //--------------------------------------------------


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

      //c2 := imagecolorallocatealpha(im_dst, r8, g8, b8, a8);//�ܿ�
      c2 := GetAAPixel(i, j);

      imagesetpixel(im_dst, i, j, c2);//�ܿ�

    end;

  end;



end;


//ȡ�������ؼ���ƽ��ֵ(��Ϊ��ƽ��,����ʵ������4�����ص�ƽ��ֵ),��������Ҫ�󲻸ߵĵط�
function imagecopyresampled2_2(im_dst, im_src:Integer; dstX , dstY , srcX , srcY , dstW , dstH , srcW , srcH:Integer):Integer; //cdecl; external php_gd2;
var
  w,h:integer;
  i,j:integer;
  i2,j2:integer;
  c, c2:Integer;
  r8, g8, b8, a8:Byte;

  //����һ���������ֵ//ȡ4�����ƽ��ֵ//���ǹ̶�ȡ 4 ������㷨,Ч����Ҳ������
  function GetAAPixel(x,y:Integer):Integer;
  var
    xsrc,ysrc:Integer;
    r, g, b, a:Integer;//rgb ֵ���ܺ�

    xadd,yadd:Integer; //ȡ���ٸ����ֵ���㵱ǰ�����
    xsrc2,ysrc2:Integer;//����Խ��
  begin
    r := 0; g := 0; b := 0; a := 0;

    //����������Ӧ����ԭͼ��ʲôλ��
    xsrc := Trunc(x * srcW / w);
    ysrc := Trunc(y * srcH / h);

    for xadd := 0 to 2-1 do
    begin
      for yadd := 0 to 2-1 do
      begin
        xsrc2 := xsrc + xadd; ysrc2 := ysrc + yadd;//����Խ��
        if xsrc2>srcW-1 then xsrc2 := srcW-1;
        if ysrc2>srcH-1 then ysrc2 := srcH-1;

        c := imagecolorat(im_src, xsrc2, ysrc2);
        ex_color2rgb(im_src, c, @r8, @g8, @b8, @a8);//�ܿ�

        r := r + r8; g := g + g8; b := b + b8; a := a + a8;

      end;

    end;

//    c := imagecolorat(im_src, xsrc, ysrc);
//    ex_color2rgb(im_src, c, @r8, @g8, @b8, @a8);//�ܿ�
//
//    r := r + r8; g := g + g8; b := b + b8; a := a + a8;

    //c2 := imagecolorallocatealpha(im_dst, r, g, b, a);//�ܿ�
    c2 := imagecolorallocatealpha(im_dst, r div 4, g div 4, b div 4, a div 4);//�ܿ�

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
      ex_color2rgb(im_src, c, @r8, @g8, @b8, @a8);//�ܿ�

      //--------------------------------------------------
      //����������Ӧ����ԭͼ��ʲôλ��
      i2 := Trunc(i * srcW / w);
      j2 := Trunc(j * srcH / h);
      c := imagecolorat(im_src, i2, j2);
      ex_color2rgb(im_src, c, @r8, @g8, @b8, @a8);//�ܿ�

      //--------------------------------------------------

      //c2 := imagecolorallocatealpha(im_dst, r8, g8, b8, a8);//�ܿ�
      c2 := GetAAPixel(i, j);

      imagesetpixel(im_dst, i, j, c2);//�ܿ�

    end;

  end;



end;

//��һ��,�ܿ���㷨//ֻ�Ǽ򵥵�ȡ��������,��С�Ļ��ᶪʧ����ֵ,���������Ŵ���û�����
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
