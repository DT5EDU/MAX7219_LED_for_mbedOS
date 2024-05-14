# MAX7219_LED_for_mbedOS

适用于基于MAX7219的8*8LED点阵屏。

# 使用方法：
## 文件位置
放在与main同目录下就行
## 电路连接
默认以D3为DIN，D4为CS，D5为CLK。
你可以在`MAX7219_LED.cpp`中修改引脚。
## 预处理
在include之后添加
```
using namespace DT5EDU;
```
## 定义
```
MAX7219_LCDs a;
a.Init(4);//Init函数的参数为你串联的点阵屏的总数量
```
这两行代码是程序运行必须的。需要被放在main函数的初始位置。
## 调用
本库提供了以下几个显示函数：（是少了点，毕竟是手搓的，将就用）
### 带Single的函数适用于单块点阵屏。多块点阵屏可能会出现重复，缺失等错误
```
void Show_Single_Pattern(uint8_t pixel[]);
void Show_Number(uint8_t display[]);
void Show_Single_Number(int n);
```
参数`pixel[]`是一个含八个元素的uint8_t类型的数组。可以以0和1在代码中绘制你需要的图案。例如：
```
uint8_t Pattern[8]={
    0b00110011,
    0b00110011,
    0b11001100,
    0b11001100,
    0b00110011,
    0b00110011,
    0b11001100,
    0b11001100
};
```
0b为二进制前缀，照着抄就行了。后面的01即为你所绘制的图案。
### 注意：由于代码特性，01绘制的图案是水平镜像的，这一点需要注意。
`void Show_Number(uint8_t display[]);`函数需要一个数组，每一个元素为0-9的任意数字。可以用于多块点阵屏情况，且数组的元素数量必须与点阵屏保持一致。同时显示的顺序与点阵屏顺序相反，例如数组为{0,1},则显示出来的为1 0。  
  
`void Show_Single_Number(int n);`适用于单块点阵屏，n即为所需要显示的数字（0-9）.

## 自己编写函数
除此之外，也支持自己编写显示函数以适配自己的需求。
在.cpp文件内，可以发现传入数据的：首先拉低CS的电平，传入地址，此后传入一个八位的整数，其二进制值代表了操作的像素。然后拉高CS电平（锁存），即完成传入一行的写入。  
因此，一个标准的显示过程为：
```
for(int i=1;i<=8;i++){
  CS=0;
  a.write_byte(i);//写入地址
  a.write_byte(data);//data是八位整数，有多少块点阵屏就在一个循环内循环多少次a.write_byte(data);
  CS=1;
}

```
# 最重要的事情
## 关注待兼诗歌剧谢谢喵~
