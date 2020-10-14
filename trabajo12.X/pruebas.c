#define _XTAL_FREQ 4000000
#include <xc.h>
void main() {
    
    ADCON1bits.PCFG = 0X0F;                                                     //SE CONFIGURA TODAS LAS ENTRADA CON CON CONVERTIDOSRES COMO DIGITALES
    TRISA = 0b00000100;                                                         //EL PUERTO A ESTA COMO SALIDA EXCEPTO A2 
    TRISB = 0;                                                                  //EL PUERTO C ESTA COMO SALIDA
    TRISC = 0;                                                                  //EL PUERTO C ESTA COMO SALIDA
    TRISD = 0;                                                                  //EL PUERTO D ESTA COMO SALIDA
    PORTB = 0b00000000;                                                          //SE INICIALIZA EL PUERTO B EN NIVEL BAJO
    PORTC = 0b00000000;                                                          //SE INICIALIZA EL PUERTO C EN NIVEL BAJO
    PORTD = 0b00000000;                                                          //SE INICIALIZA EL PUERTO D EN NIVEL BAJO
    int x=0,i=1,e=1,y;
    
    while(1){
        if(PORTAbits.RA2==1){  
            x++;
            __delay_ms(500);
            if(x==5){
                x=0;
            }
        }
        
        if(x==1){
            PORTCbits.RC0=1;
            for(PORTD = 1; PORTD != 0 ; PORTD <<= 1)
                {
                __delay_ms(500);                       
                if(PORTD==128)
                    {
                    for(PORTD = 128; PORTD > 0 ; PORTD >>= 1)
                        {   
                        __delay_ms(500);
                    }
                }                
            }
        }
        
        if(x==2){
            PORTCbits.RC1=1;
            for(y=0;y<=8;y++){
                while(i<=y){
                    e*=2;
                    i++;
                }
                PORTB=e-1;
                __delay_ms(500);
            }
            i=0;
            for(int w=0;w<=7;w++){
                e/=2;
                PORTB=e-1;
                __delay_ms(500);    
            }
            PORTB=0;
        }        
           
        if(x==3){
            PORTCbits.RC2=1;
            PORTA = 0b00000000;
            __delay_ms(1000);  
            PORTA = 0b00000010;
            __delay_ms(1000);  
            PORTA = 0b00001000;
            __delay_ms(1000);  
            PORTA = 0b00001010;
            __delay_ms(1000);  
            PORTA = 0b00010000;
            __delay_ms(1000);  
            PORTA = 0b00010010;
            __delay_ms(1000);  
            PORTA = 0b00011000;
            __delay_ms(1000);  
            PORTA = 0b00011010;
            __delay_ms(1000);  
            PORTA = 0b00100000;
            __delay_ms(1000);  
            PORTA = 0b00100010;
            __delay_ms(1000);  
            PORTA = 0b00101000;
            __delay_ms(1000);  
            PORTA = 0b00101010;
            __delay_ms(1000);  
            PORTA = 0b00110000;
            __delay_ms(1000);  
            PORTA = 0b00110010;
            __delay_ms(1000);  
            PORTA = 0b00111000;
            __delay_ms(1000);  
            PORTA = 0b00111010;
            __delay_ms(1000); 
            PORTA = 0b00000000;
        }
        
        if(x==4){
            PORTCbits.RC4=1;
            PORTAbits.RA0=1;
            __delay_ms(500);
            PORTAbits.RA0=0;
            __delay_ms(500);
        }
        
        PORTCbits.RC0=0;
        PORTCbits.RC1=0;
        PORTCbits.RC2=0;
        PORTCbits.RC4=0; 
    }
    
    return;
}
    



 

