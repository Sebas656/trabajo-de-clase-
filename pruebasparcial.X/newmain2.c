/*
 * File:   newmain2.c
 * Author: El Elipse
 *
 * Created on 10 de septiembre de 2020, 01:08 AM
 */


#include <xc.h>
#define _XTAL_FREQ 8000000
#define B PORTAbits.RA1    //RA1 para asignar valor
#define C PORTAbits.RA2    //RA2 para asignar valor
#define D PORTAbits.RA3    //RA3 para asignar valor

float temp(){
    int rg=0;
    float fa=0.0,tem=0.0;
    ADCON0bits.GO_DONE=1;
    while(ADCON0bits.GO_DONE){
        rg=(ADRESH<<8)+ADRESL;
        tem =(rg*5)/10.24;  
        fa=(tem*1.8)+32;
        return fa;
    }
}

void main(void) {
    OSCCONbits.IRCF = 0b111; //Configura oscilador interno (FOSC = 8Mhz)
    OSCCONbits.SCS = 0b10;   // Oscilador del sistema = Fosc interno
    
    TRISA = 15;
    TRISD = 0;
    PORTA = 0;
    PORTD = 0;
    
    ADCON1 = 0b00001110; // se deja el voltaje de referencia vss y vdd se habilita el puerto AN0
    ADCON0 = 0b00000000; 
    ADCON2 = 0b10010001;
    ADCON0bits.ADON = 1;
    
    int A= 0;
    
   // double tem=0.0,fa=0.0;
    while(1){
        if(temp()>=176){
            PORTAbits.RA4 = 1;
            A=1;
        }
        else{
            PORTAbits.RA4 =0;
            A=0;
        }
        
        if((A&&B&&C&&!D) || (!A&&B&&!C&&D) || (!A&&!B&&C&&!D) || (A&&!B&&!C)){
            PORTAbits.RA4 = 1;
        }
        else{
            PORTAbits.RA4 =0;
        }
    }        
    return;
}