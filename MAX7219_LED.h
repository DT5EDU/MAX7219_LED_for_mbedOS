#include "mbed.h"
#include "cstdint"

#define DECODEMODE 		0X09	//编码模式
#define INTENSITY  		0X0A	//亮度
#define SCANLIMT		0x0B	//扫描寄存器个数
#define SHUTDOWN   		0X0C	//关闭寄存器


namespace DT5EDU{
    class MAX7219_LCDs{
        public:
            
            void Init(int _num);

            void Show_Single_Pattern(uint8_t pixel[]);
            void Show_Number(uint8_t display[]);
            void Show_Single_Number(int n);

            
        private:
            void write_byte(uint8_t data);
            void write_command(uint8_t add,uint8_t data);
            int num;
            
    };
}