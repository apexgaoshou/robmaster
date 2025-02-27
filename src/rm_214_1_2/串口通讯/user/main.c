#include "stm32f10x.h"
#include "Delay.h"
#include "LED.H"
#include "KEY.H"
#include "OLED.H"
#include "SERIAL.H"

void HMI_send_string(char* name, char* showdata)
{
    // printf("t0.txt=\"%d\"\xff\xff\xff", num);
    printf("%s=\"%s\"\xff\xff\xff", name, showdata);
}
void HMI_send_number(char* name, int num)
{
    // printf("t0.txt=\"%d\"\xff\xff\xff", num);
    printf("%s=%d\xff\xff\xff", name, num);
}
void HMI_send_float(char* name, float num)
{
    // printf("t0.txt=\"%d\"\xff\xff\xff", num);
    printf("%s=%d\xff\xff\xff", name, (int)(num * 100));
}

int main(void)
{

	
	SERIALINIT();
	
	int testnum=114;
	SERIALSENDDATA(0x41);
	
	uint8_t myarray[]={0x42,0x43,0x44,0x45};
	
	//SENDARRAY(myarray,4);
	
	
while(1){
	//printf("AA");
	//Delay_ms(1000);
	//SERIALSENDDATA(0x57);
	
	
}}
