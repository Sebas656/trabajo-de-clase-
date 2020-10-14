/*
 * File:   newmain.c
 * Author: DIEGO
 *
 * Created on 18 de septiembre de 2020, 10:06 AM
 */

#include <xc.h>
#define _XTAL_FREQ 8000000
int a = -1,n = 0,s = 0,mm = 0,du = 0,dd = 0,e = 0;
float tem = 0.0;

void display(int a,int b){
    int t = 0;  
    if(PORTDbits.RD7 == 1){
        INTCONbits.GIE      = 0;
        INTCONbits.PEIE     = 0;
        du  = 0;
        dd  = 0;
        a   = -1;
        n   = 0;
        s   = 0;
        mm  = 1;
        tem = 0.0;
        while(PORTDbits.RD7==1);
    }
    
    ADCON0bits.GO_DONE  = 1;
    LATB                = 0b11111110;
    LATB                = 0b11111101;
    LATB                = 0b11111011;  
    LATAbits.LA4        = 1;
    while(t<50){
        PORTD = a;
        t++;
    }
    t=0;
    LATAbits.LA4 = 0;
    LATAbits.LA5 = 1;
    while(t<50){
        LATD = b;
        t++;
    }
    t = 0;
    LATAbits.LA5 = 0;
    if(tem >= 60 ){
            LATAbits.LA3 = 1;
        }
        else{
            LATAbits.LA3 = 0;
    }
    if(s == 1 ){
            LATAbits.LA2 = 1;
        }
        else{
            LATAbits.LA2 = 0;
    }
}

void mantenimiento(){
    if(mm == 1){  
        for(int u = 0; u < 3; u++){
            LATAbits.LA1 = 1;
            LATAbits.LA2 = 1;
            LATAbits.LA3 = 1;
            __delay_ms(500);
            LATAbits.LA1 = 0;
            LATAbits.LA2 = 0;
            LATAbits.LA3 = 0;
            __delay_ms(500);
        }
        for(int q = 1; q <= 9; q++){
            while(e <= 500){
                display(q,q);
                e++;
            }
            e = 0;
        }
        INTCONbits.GIE  = 1;
        INTCONbits.PEIE = 1;
        mm = 0;
    }
}

void main(void) {
    OSCCONbits.IRCF   = 0b111; //Configura oscilador interno (FOSC = 8Mhz)
    OSCCONbits.SCS    = 0b10;   // Oscilador del sistema = Fosc interno
    
    TRISA             = 0b00000001;
    TRISB             = 0b11110000;
    TRISD             = 0b10000000;
    
    PORTA             = 0;
    PORTB             = 0b00001111;
    PORTD             = 0;
    
    ADCON1            = 0b00001110; // se deja el voltaje de referencia vss y vdd se habilita el puerto AN0
    ADCON0            = 0b00000000; 
    ADCON2            = 0b10010001;
    ADCON0bits.ADON   = 1;
 
    INTCONbits.GIE    = 1;
    INTCONbits.PEIE   = 1;  
    PIE1bits.ADIE     = 1;  //HABILITA LA INTERRUPCIONES DEL CONVERTIDOR
    PIR1bits.ADIF     = 0;  //BANDERA ABAJO
    INTCONbits.RBIE   = 1;  //HABILITA LA INTERRUCIONES DEL PUERTO B
    INTCONbits.RBIF   = 0;  //BANDERA ABAJO
    INTCON2bits.nRBPU = 0;  //HABILITA LAS PULL-APP
    
    while(1){  
        
        display(du,dd); 
        mantenimiento();

        LATAbits.LA1 = 1;
        if(n == 1 && a >= 0 && a <= 9){
            du = a;
            a=-1;
        }   
        if(n == 2 && a >= 0 && a <= 9){
            dd = a;
            a=-1;
        }
        if(n >= 2 && a == 10){
            LATAbits.LA1 = 0;
            for(du; du >= 0; du--){
                for(dd; dd >= 0; dd--){
                    while(e <= 500){
                        display(du,dd);
                        while(s == 1 || tem == 60){
                            display(11,10);
                        }
                        e++;
                    }
                    e = 0;
                }
                dd = 9;
            }
            du = 0;
            dd = 0;
            a  = -1;
            n  = 0; 
        }
    }
    return;
}

void __interrupt() isr(void){
    if(PIR1bits.ADIF){
        int rg = 0;
        rg=(ADRESH<<8)+ADRESL;
        tem = (rg*5)/10.24;
        PIR1bits.ADIF = 0;    
    }
    
    if(INTCONbits.RBIF){ 
        a = -1;
        if(PORTBbits.RB0        ==  0){
            if(PORTBbits.RB4    ==  0){a = 1;}
            if(PORTBbits.RB5    ==  0){a = 4;}
            if(PORTBbits.RB6    ==  0){a = 7;}
            if(PORTBbits.RB7    ==  0){a = 10;}
        }
        if(PORTBbits.RB1        ==  0){
            if(PORTBbits.RB4    ==  0){a = 2;}
            if(PORTBbits.RB5    ==  0){a = 5;}
            if(PORTBbits.RB6    ==  0){a = 8;}
            if(PORTBbits.RB7    ==  0){a = 0;}
        }
        if(PORTBbits.RB2        ==  0){
            if(PORTBbits.RB4    ==  0){a = 3;}
            if(PORTBbits.RB5    ==  0){a = 6;}
            if(PORTBbits.RB6    ==  0){a = 9;}
            if(PORTBbits.RB7    ==  0){s = 1;}
        }

        while(PORTBbits.RB4 == 0||PORTBbits.RB5 == 0||PORTBbits.RB6 == 0||PORTBbits.RB7 == 0);

        if(a > -1 && a <= 9){
            n++;
        }
        if(a == 10){
            s = 0;
        }
        INTCONbits.RBIF = 0;
    }
}
