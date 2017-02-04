#include <stdio.h>

//在 exe 中要定义这个再引用 gd 库 
#define IN_EXE


#include "c_lib_windows_gd.h"
#include "utf8.h"
#include <string.h>

//注意 gcc windows 版本在引入库的时候写的是 -l php_gd2 而不是 -l php_gd2.lib ,即省略掉后缀名,加上反而是错误的 

int main(int argc, char *argv[])
{
  int r,color;
  
  printf("Press enter to continue ...");
  
  gdImagePtr im = imagecreatefromjpeg("c:\\1.jpg");
  
  //imageantialias(im, 1);//感觉不是很靠谱,会导致 imagesetthickness 和 alpha 失败,感觉还不如用 alpha 颜色描边,或者先用普通的画,然后再用 aa 模式描边

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

  //画一个 aa 边界的圆//cr 是半径?
  color = imagecolorallocatealpha(im, 255, 0, 0, 100);
  //ex_imageSmoothCircle(im, 200, 200, 50, color);
  ////ex_imageSmoothCircle(im, 190,  90,  125, color);//ok
  ex_imageSmoothCircle_alpha(im, 190,  90,  125, color);

  color = imagecolorallocatealpha(im, 255, 0, 0, 0);
  imagestring(im, 1, 0, 0, "aaa", color);
  imagestring(im, 5, 250, 250, "aaa中文", color); //默认字体是出不来中文的

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

  //中文必须是 utf8 的 
  //imagettftext(im, 20, 0, 4, 40, color, "simkai.ttf", "123abc中文好");//我这里选择的本地字体是楷体，必须选择系统字库中存在的字
  
  char tobuf[255];// = {0};
  memset(tobuf, 0, 255);
  
  //int tolen = convert("UTF-8//IGNORE","gb2312", (char *)&tobuf[0], tobuf.size(), (char *)content.c_str(), content.length());
  //int tolen = convert("UTF-8//IGNORE","gb2312", (char *)&tobuf[0], 255, "123abc中文好", strlen("123abc中文好"));
  int tolen = convert("gb2312//IGNORE","UTF-8", (char *)&tobuf[0], 255, "123abc中文好", strlen("123abc中文好"));
  if (tolen < 0)
  {
    printf("Error\n");
  }else tobuf[tolen] = '\0';

  imagettftext(im, 20, 0, 4, 40, color, "simkai.ttf", tobuf);//我这里选择的本地字体是楷体，必须选择系统字库中存在的字

  r = imagepng(im, "d:\\2.png");
  imagedestroy(im);
  //ShowMessage(IntToStr(r));  
  
  getchar();	
  return 0;

}//


