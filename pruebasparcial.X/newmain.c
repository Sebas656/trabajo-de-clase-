/*
 * File:   newmain.c
 * Author: El Elipse
 *
 * Created on 8 de septiembre de 2020, 09:11 PM
 */
#include <xc.h>
#define _XTAL_FREQ 8000000
#include <math.h>

void main(void) {
    OSCCONbits.IRCF = 0b111; //Configura oscilador interno (FOSC = 8Mhz)
    OSCCONbits.SCS = 0b10;   // Oscilador del sistema = Fosc interno
    
    TRISA=1;
    TRISD = 0;
    TRISC=0;
    PORTA = 0;
    PORTD = 0;
    PORTC = 0;
    
    ADCON1 = 0b00001110; // se deja el voltaje de referencia vss y vdd se habilita el puerto AN0
    ADCON0 = 0b00000000; 
    ADCON2 = 0b10010001;
    ADCON0bits.ADON = 1;
    int rg=0,peu=0,ped=0,d=0;
    double  total=0.0,tot=0.0;
    while(1){
        ADCON0bits.GO_DONE=1;
        while(ADCON0bits.GO_DONE){
            rg=(ADRESH<<8)+ADRESL;
            if(rg>=512){
               PORTAbit2s.RA4 = 1;
            }
                else{
                    PORTAbits.RA4 = 0;
            }
            total=(rg*5)/1023;         
            tot=((rg*50)/1023);     
            peu=(int)total;
            ped=(int)tot;
            d=ped-peu*10;
            PORTCbits.RC6 =1;
            PORTD=peu;
            __delay_us(1000);
            PORTCbits.RC6 =0;
            PORTCbits.RC7 =1;
            PORTD=d;
            __delay_us(1000);
            PORTCbits.RC7 =0;
       }        
    }
    return;
}
