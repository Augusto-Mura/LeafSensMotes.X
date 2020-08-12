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

void i2c_start(void)
{
    // Stop clock
    setSDA();
    i2c_usdelay(I2CDELAY);
    while(!GPIODigitalRead(SCL));
    i2c_usdelay(I2CDELAY);
    resetSDA();
    i2c_usdelay(I2CDELAY);

}

void i2c_stop(void)
{
    resetSDA();
    while(!GPIODigitalRead(SCL));
    i2c_usdelay(I2CDELAY);
    setSDA();
    i2c_usdelay(I2CDELAY);
    while(GPIODigitalRead(SCL));

}

// Da sdaWrite e sdaAddress ne tolgo fuori un altra funzione a 
// basso livello che mi permette di andare a scrivere solamente
// i valori sul terminale SDA

uint8_t i2c_sdaWrite(uint8_t data){
    
    bool flag = false;
    
    for(int8_t i = 7; i > -1; i--){
        if(flag){
            while(!GPIODigitalRead(SCL));
        }
        while(GPIODigitalRead(SCL));
        i2c_usdelay(I2CDELAY);
        if(data & (1 << i)){
            GPIODigitalWrite(SDA, 1);
        }
        else{
            GPIODigitalWrite(SDA, 0);
        }
        flag = true;
    }
    while(!GPIODigitalRead(SCL));
    while(GPIODigitalRead(SCL));
    return i2c_waitACK();
}

uint8_t i2c_sdaAddress(uint8_t address, bool RnW){
    
    bool flag = false;
    address <<= 1;
    if (RnW){
        address |= 0x01;
    }
    
    for(int8_t i = 7; i > -1; i--){
        if(flag){
            while(!GPIODigitalRead(SCL));
        }
        while(GPIODigitalRead(SCL));
        i2c_usdelay(I2CDELAY);
        if(address & (1 << i)){
            GPIODigitalWrite(SDA, 1);
        }
        else{
            GPIODigitalWrite(SDA, 0);
        }
        flag = true;
    }
    while(!GPIODigitalRead(SCL));
    while(GPIODigitalRead(SCL));
    return i2c_waitACK();
}

static uint8_t nACK;

uint8_t i2c_waitACK(){
    
    setSDA();
    GPIOSet(SDA, 1);
    //while(1);
    while(!GPIODigitalRead(SCL));
    i2c_usdelay(I2CDELAY);
    
    nACK = GPIODigitalRead(SDA);
    
    GPIOSet(SDA, 0);
    while(GPIODigitalRead(SCL));
    i2c_usdelay(I2CDELAY);
    return nACK;
}

uint8_t i2c_sendData(uint16_t data){
    uint8_t high;
    uint8_t low;
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
