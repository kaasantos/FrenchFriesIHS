#include<gb/gb.h>

void somVitoria(){
    NR10_REG = 0x67;
    NR11_REG = 0xCC;
    NR12_REG = 0x28;
    NR13_REG = 0x75;
    NR14_REG = 0x86;  
}
void somDerrota(){
    NR10_REG = 0x7F;
    NR11_REG = 0xD4;
    NR12_REG = 0x18;
    NR13_REG = 0x2F;
    NR14_REG = 0x86;  
}
void somAndar(){
    NR10_REG = 0x1A;
    NR11_REG = 0x80;
    NR12_REG = 0x22;
    NR13_REG = 0x9C;
    NR14_REG = 0x86; 
}
void somTiro(){
    NR10_REG = 0x3D;
    NR11_REG = 0x4A;
    NR12_REG = 0x24;
    NR13_REG = 0x5A;
    NR14_REG = 0xC6; 
}
void somVira(){
    NR30_REG = 0x80;
    NR31_REG = 0x03;
    NR32_REG = 0x60;
    NR33_REG = 0xBF;
    NR34_REG = 0xC6; 
}
void somViraVolta(){
    NR30_REG = 0x80;
    NR31_REG = 0x03;
    NR32_REG = 0x60;
    NR33_REG = 0x65;
    NR34_REG = 0xC6; 
}
void somSelect(){
    NR10_REG = 0x18;
    NR11_REG = 0x88;
    NR12_REG = 0x44;
    NR13_REG = 0x73;
    NR14_REG = 0x86; 
}