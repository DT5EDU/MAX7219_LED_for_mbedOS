#include "MAX7219_LED.h"
#include <cstdint>


DigitalOut _DIN(D3);
DigitalOut _CS(D4);
DigitalOut _CLK(D5);

const uint8_t numbers[10][8]={
	 {0x0f,0x09,0x09,0x09,0x09,0x09,0x0f,0x00},//0
	 {0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x00},//1
	 {0x0f,0x01,0x01,0x0f,0x08,0x08,0x0f,0x00},//2
	 {0x0f,0x01,0x01,0x0f,0x01,0x01,0x0f,0x00},//3
	 {0x09,0x09,0x09,0x0f,0x01,0x01,0x01,0x00},//4
	 {0x0f,0x08,0x08,0x0f,0x01,0x01,0x0f,0x00},//5
	 {0x0f,0x08,0x08,0x0f,0x09,0x09,0x0f,0x00},//6
	 {0x0f,0x01,0x01,0x01,0x01,0x01,0x01,0x00},//7
	 {0x0f,0x09,0x09,0x0f,0x09,0x09,0x0f,0x00},//8
	 {0x0f,0x09,0x09,0x0f,0x01,0x01,0x0f,0x00}//9
 };


void DT5EDU::MAX7219_LCDs::write_byte(uint8_t data){
    _CS=0;
    for(uint8_t i=8;i>0;i--){
        _CLK=0;
        if(data&0x80) _DIN=1;
        else _DIN=0;
        data<<=1;
        _CLK=1;
    }
}


void DT5EDU::MAX7219_LCDs::write_command(uint8_t add,uint8_t data){
    write_byte(add);
    write_byte(data);
}


void DT5EDU::MAX7219_LCDs::Init(int _num){   
    num=_num;
    uint8_t i=0;
    for(i=0;i<num;i++) write_command(DECODEMODE,0);
    _CS=1;_CS=0;
    for(i=0;i<num;i++) write_command(INTENSITY,0x01);
    _CS=1;_CS=0;
    for(i=0;i<num;i++) write_command(SCANLIMT,0x07);
    _CS=1;_CS=0;
    for(i=0;i<num;i++) write_command(SHUTDOWN, 0x01);
    _CS=1;
}//参数为你LCD屏幕的数量

void DT5EDU::MAX7219_LCDs::Show_Single_Pattern(uint8_t pixel[]){
    for(uint8_t i=1;i<=8;i++){
        _CS=0;
        write_byte(i);
        write_byte(pixel[i-1]);
        _CS=1;
    }
}//接受一个uint8_t类型,有八个元素的数组的数组,其与像素的关系详见README

void DT5EDU::MAX7219_LCDs::Show_Number(uint8_t display[]){
    for(uint8_t i=1;i<=8;i++){
        _CS=0;
        for(int j=1;j<=num;j++){
            write_byte(i);
            write_byte(numbers[display[j-1]][i-1]);
        }
        _CS=1;
    }
}
//display[]为一个uint8_t类型的数组。在反向里面填入分别在每块LCD上显示的数字

void DT5EDU::MAX7219_LCDs::Show_Single_Number(int n){
    for(uint8_t i=1;i<=8;i++){
        _CS=0;
        write_byte(i);
        write_byte(numbers[n][i-1]);
        _CS=1;
    }

}
//在一块LCD上显示数字，可能会影响其他LCD（倘若多于一块）