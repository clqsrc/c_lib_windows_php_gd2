#include <stdio.h>

//�� exe ��Ҫ������������� gd �� 
#define IN_EXE


#include "c_lib_windows_gd.h"
#include "utf8.h"
#include <string.h>

//ע�� gcc windows �汾��������ʱ��д���� -l php_gd2 ������ -l php_gd2.lib ,��ʡ�Ե���׺��,���Ϸ����Ǵ���� 

int main(int argc, char *argv[])
{
  int r,color;
  
  printf("Press enter to continue ...");
  
  gdImagePtr im = imagecreatefromjpeg("c:\\1.jpg");
  
  //imageantialias(im, 1);//�о����Ǻܿ���,�ᵼ�� imagesetthickness �� alpha ʧ��,�о��������� alpha ��ɫ���,����������ͨ�Ļ�,Ȼ������ aa ģʽ���

  imagesetthickness(im, 3);
  color = imagecolorallocatealpha(im, 255, 0, 0, 100);
  imageline(im, 0, 0, 100, 100, color);

  imagefilledellipse(im,  0, 0, 100, 100, color);

//  color := imagecolorallocatealpha(im, 255, 0, 0, 110);
//  imagefilledellipse(im,  200, 200, 98, 98, color);
//  color := imagecolorallocatealpha(im, 255, 0, 0, 80);
//  imagefilledellipse(im,  200, 200, 96, 96, color);
  color = imagecolorallocatealpha(im, 255, 0, 0, 50);
  imagefilledellipse(im,  200, 200, 94, 94, color);

  //��һ�� aa �߽��Բ//cr �ǰ뾶?
  color = imagecolorallocatealpha(im, 255, 0, 0, 100);
  //ex_imageSmoothCircle(im, 200, 200, 50, color);
  ////ex_imageSmoothCircle(im, 190,  90,  125, color);//ok
  ex_imageSmoothCircle_alpha(im, 190,  90,  125, color);

  color = imagecolorallocatealpha(im, 255, 0, 0, 0);
  imagestring(im, 1, 0, 0, "aaa", color);
  imagestring(im, 5, 250, 250, "aaa����", color); //Ĭ�������ǳ��������ĵ�

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

  //���ı����� utf8 �� 
  //imagettftext(im, 20, 0, 4, 40, color, "simkai.ttf", "123abc���ĺ�");//������ѡ��ı��������ǿ��壬����ѡ��ϵͳ�ֿ��д��ڵ���
  
  char tobuf[255];// = {0};
  memset(tobuf, 0, 255);
  
  //int tolen = convert("UTF-8//IGNORE","gb2312", (char *)&tobuf[0], tobuf.size(), (char *)content.c_str(), content.length());
  //int tolen = convert("UTF-8//IGNORE","gb2312", (char *)&tobuf[0], 255, "123abc���ĺ�", strlen("123abc���ĺ�"));
  int tolen = convert("gb2312//IGNORE","UTF-8", (char *)&tobuf[0], 255, "123abc���ĺ�", strlen("123abc���ĺ�"));
  if (tolen < 0)
  {
    printf("Error\n");
  }else tobuf[tolen] = '\0';

  imagettftext(im, 20, 0, 4, 40, color, "simkai.ttf", tobuf);//������ѡ��ı��������ǿ��壬����ѡ��ϵͳ�ֿ��д��ڵ���

  r = imagepng(im, "d:\\2.png");
  imagedestroy(im);
  //ShowMessage(IntToStr(r));  
  
  getchar();	
  return 0;

}//


