# c_lib_windows_php_gd2
php扩展php_gd2改写为C的库(windows版)

大部分都只是简单的改写一下就可以用了,用法都可以直接参考 php 的手册.只是逐步实现我需要用到的函数,需要的网友可以自己参考其中的改写方式加入
自己需要的 php 对应函数接口.

这其中有个比较特别的:webp图片的解码,原实现相当的繁琐,我另外换用了 libwebp(版本libwebp-0.5.1) 来实现,需要编码的网友也可参考自己实现.
代码基于的php版本为 php-5.6.29-src 的 windows 编译版.

--------------------------------------------------

目前实现的为缩放和画线. 详细见 c_lib_windows_gd.h
