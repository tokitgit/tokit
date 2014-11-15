本目录说明
=====

本目录下是go源码

之前采用c++编写tokit工具，发现唯一的瓶颈在于读取excel文件的速度，但经过反复试用，并没有找到比较方便操作excel的c++工具库，有的速度快但根本不支持excel中的公式，如libxl，有的功能全面但速度奇慢，如ole，最后决定把libxl和ole结合使用，导致载入未采用公式的excel文件很快，耗时基本小于0.1秒，载入采用公式的excel文件耗时整体在0.5秒左右，但仍然很不满意

现在用golang重写tokit工具，由于采用了开源xlsx库，载入含公式的excel文件耗时基本在0.35秒以下，效果不错，所以之后的版本发布将以go为准

本目录下的文件夹分别是：
* go-colortext: 开源库，用于转换控制台输出文字的颜色，https://github.com/daviddengcn/go-colortext/tree/master/
* mahonia: 开源转码库，娶自https://code.google.com/p/mahonia/
* xlsx: 读取excel 2007格式文件的开源库，见https://github.com/tealeg/xlsx
* tokit: 本项目的golang源码，使用到了以上开源库