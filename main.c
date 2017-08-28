#include"SysCtrl.h"
#include"GPIO.h"
#include"Delay.h"
#include"lcdEKE.h"
#include"Sound.h"


int main(void){
/* local data types for main file        */		
SensorRead_t read ;
	
/*      System initialization             */	
	
// connect clock
   clock_Enable_PORT(Clock_PortC);
   clock_Enable_PORT(Clock_PortE);
	 clock_Enable_PORT(Clock_PortD);
//LCD and PORTE initialization.
	 LCD_Init();
	
//Sound Sensor initialization. 
	 GPIO_PortC_Init();
//LDR portD
	 GPIO_PortD_Init();
	
/* Main GUI for LCD                      */	
	 goToRowColumn(1,1);
	 LCD_string((U8_t*)"Light:");
	 goToRowColumn(2,1);
	 LCD_string((U8_t*)"Sound:");	
	while(1){
//Sound System	
		read=Check_SoundSensor();
		if(read==DETECTED){
			goToRowColumn(2,7);
      LCD_string((U8_t*)"detected");
			//buzzer ON
			GPIO_PORTC_DATA|=(1<<PC4);
			delayMsec(500);
			GPIO_PORTC_DATA&=~(1<<PC4);
      //PI-LED RED			
		  GPIO_PORTC_DATA|=(1<<PC6);
			GPIO_PORTC_DATA&=~(1<<PC7);
      			
		}
		else if(read==SAFE){
			//PI-LED yellow	
		  GPIO_PORTC_DATA|=(1<<PC7);
			GPIO_PORTC_DATA&=~(1<<PC6);
			goToRowColumn(2,7);
      LCD_string((U8_t*)"SAFE      ");			
		}
		else{
			//System Failed
			GPIO_PORTC_DATA&=~((1<<PC7)|(1<<PC6));
			goToRowColumn(2,7);
      LCD_string((U8_t*)"SysFailed");
		}
			
//LDR for light
		if(!(GPIO_PORTD_DATA &(1<<PD1))){
			GPIO_PORTD_DATA|=(1<<PD2)|(1<<PD3);	
      goToRowColumn(1,7);
      LCD_string((U8_t*)"ON ! ");			
		}
		else{
			GPIO_PORTD_DATA&=~((1<<PD2)|(1<<PD3));
			goToRowColumn(1,7);
      LCD_string((U8_t*)"OFF !");
			
		}
	}
	
}
