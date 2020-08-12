/*
 * File:   I2C.c
 * Author: antop
 *
 * Created on March 15, 2019, 2:38 PM
 */


#include <xc.h>
#include "mcc_generated_files/tmr3.h"
#include "rn2483APP.h"
#include "I2C.h"
#include "mcc_generated_files/mcc.h"


#define I2CDELAY    1

    static uint8_t high;
    static uint8_t low;
    static bool flag;
    static uint8_t nACK;
    
void i2c_start(void)
{
    // Set SDA HIGH
    LATE |= _LATE_LE1_MASK;
    
    // Wait until SCL comes to HIGH state
    while(!(PORTE & _PORTE_RE0_MASK));

    // Set SDA LOW
     LATE &= ~_LATE_LE1_MASK;
     


}

void i2c_stop(void)
{
    resetSDA();
    while(!GPIODigitalRead(SCL));
    //i2c_usdelay(I2CDELAY);
    setSDA();
    i2c_usdelay(I2CDELAY);
    while(GPIODigitalRead(SCL));

}

// Da sdaWrite e sdaAddress ne tolgo fuori un altra funzione a 
// basso livello che mi permette di andare a scrivere solamente
// i valori sul terminale SDA

uint8_t i2c_sdaWrite(uint8_t data){
    
    flag = false;
    
    for(int8_t i = 7; i > -1; i--){
        if(flag){
            while(!(PORTE & _PORTE_RE0_MASK));
        }
        while(PORTE & _PORTE_RE0_MASK);
       
        if(data & (1 << i)){
            LATE |= _LATE_LE1_MASK;
        }
        else{
            LATE &= ~_LATE_LE1_MASK;
        }
        flag = true;
    }
    while(!(PORTE & _PORTE_RE0_MASK));
    while(PORTE & _PORTE_RE0_MASK);
    return i2c_waitACK();
}

uint8_t i2c_sdaAddress(uint8_t address, bool RnW){
    
    flag = false;
    address <<= 1;
    if (RnW){
        address |= 0x01;
    }
    
    for(int8_t i = 7; i > -1; i--){
        if(flag){
            // Wait until SCL comes 
            while(!(PORTE & _PORTE_RE0_MASK));
        }
        // Wait until SCL comes LOW
        while(PORTE & _PORTE_RE0_MASK);
        
        //i2c_usdelay(I2CDELAY);
        if(address & (1 << i)){
            // Set SDA HIGH
            LATE |= _LATE_LE1_MASK;
            //i2c_usdelay(I2CDELAY);
        }
        else{
            // Set SDA LOW
            LATE &= ~ _LATE_LE1_MASK;
            //i2c_usdelay(I2CDELAY);
        }
        flag = true;
    }
    while(!(PORTE & _PORTE_RE0_MASK));
    while(PORTE & _PORTE_RE0_MASK);
    return i2c_waitACK();
}



uint8_t i2c_waitACK(){
    
    // Set SDA HIGH
    //LATE |= _LATE_LE1_MASK;
    
    // Set SDA as INPUT
    TRISE |= (_TRISE_TRISE1_MASK);
    
    // Wait until SCL comes HIGH
    while(!(PORTE & _PORTE_RE0_MASK));
    
    // Read nACK from SDA
    //nACK = (PORTE & _PORTE_RE1_MASK) >> _PORTE_RE1_POSN;
    nACK = (PORTE & _PORTE_RE1_MASK);
    
    TRISE &= ~(_TRISE_TRISE1_MASK);
    
    while(PORTE & _PORTE_RE0_MASK);
    
    return nACK;
}

uint8_t i2c_sendData(uint16_t data){

    data <<= 2;
    data &= 0x0FFC;
    high = data >>8;
    low = data & 0x00FF;
    i2c_sdaWrite(high);
    i2c_sdaWrite(low);
    
}

void i2c_sclStop(void){
    TMR3_StopTimer();
    TMR3_Reload();
}

void i2c_sclStart(void){
    TMR3_StartTimer();
}


void i2c_usdelay(uint16_t time){
    for (int i=0; i< time; i++){
        __delay_us(1);
    }
}

void setSDA(){
    GPIODigitalWrite(SDA, 1);
}
void setSCL(){
    GPIODigitalWrite(SCL, 1);
}

void resetSDA(){
    GPIODigitalWrite(SDA, 0);
}
void resetSCL(){
    GPIODigitalWrite(SCL, 0);
}
