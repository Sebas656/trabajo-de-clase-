/*
 * File:   practicandoparcila.c
 * Author: El Elipse
 *
 * Created on 6 de septiembre de 2020, 05:31 PM
 */


#include <xc.h>

void main(void) {
    TRISB = 0b00011000 ;
    TRISDbits.TRISD3 = 0 ;
     
    while(1){ 
        if(PORTBbits.RB3 == 0){
             (PORTDbits.RD3 = 1 );
                        
        }
        }    

    return;
    
   
}
