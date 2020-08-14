/*
 * File:   acuadori.c
 * Author: antop
 *
 * Created on March 1, 2019, 2:23 PM
 */


#include <xc.h>
#include <math.h>
#include "rn2483APP.h"
#include "acuadori.h"
#include "tmrAPP.h"
#include "I2C.h"
#include "mcc_generated_files/LoRaWAN/sw_timer.h"



#define PI 3.14159265
#define sinSamples 10
#define numCapSamples  200

static uint8_t stringValue[5]={0x00, 0x00, 0x00, 0x00, 0x00};
static uint8_t sensorsString[40] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static uint8_t clearString[40] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static uint8_t stringValueLength = 5;
static uint8_t sensorsStringLength = 10;
uint32_t upCnt = 0;
uint8_t clip = 0;
static uint16_t sinSignal[sinSamples];
//static uint16_t pulseSignal[2]={0x012C, 0x01C2};
static uint16_t pulseSignal[2]={0x0222, 0x0208};

void acuadoriApp(void)
{
    memcpy(sensorsString, clearString, 10);
    sensorsStringLength = 0;
    
    // Turn on the board and all mux
    GPIODigitalWrite(GPIO8, 0);
    
    // Turn on leaf sensor A, B=0, A=0
    GPIODigitalWrite(GPIO5, 0);    
    GPIODigitalWrite(GPIO0, 0); 
    rn2483_delaysec(1);
    leafSensAcquisition();
    strncat(sensorsString, "A", 1);
    strncat(sensorsString, stringValue, stringValueLength);
    sensorsStringLength += 1 + stringValueLength;
    
    // Turn on leaf sensor 2, B=0, A=1
    GPIODigitalWrite(GPIO5, 0);    
    GPIODigitalWrite(GPIO0, 1); 
    rn2483_delaysec(1);
    leafSensAcquisition();
    strncat(sensorsString, "B", 1);
    strncat(sensorsString, stringValue, stringValueLength);
    sensorsStringLength += 1 + stringValueLength;
    
    // Turn on acuadori clip, B=1, A=0
    GPIODigitalWrite(GPIO5, 1);    
    GPIODigitalWrite(GPIO0, 0);    

    clip = 1;
    // Read the temperature sensor and send it throw LoRa Network
    rn2483_delaysec(10);
    tempSensAcquisition();
    strncat(sensorsString, "T", 1);
    strncat(sensorsString, stringValue, stringValueLength);
    sensorsStringLength += 1 + stringValueLength;
    
    // Read the light transmission sensor and send it throw LoRa Network
    lightSensAcquisition();
    strncat(sensorsString, "L", 1);
    strncat(sensorsString, stringValue, stringValueLength);
    sensorsStringLength += 1 + stringValueLength;
    
    // Read the capacitance and send it throw LoRa Network
    impedenceAcquisition();
    //leafSensAcquisition();
    strncat(sensorsString, "C", 1);
    strncat(sensorsString, stringValue, stringValueLength);
    sensorsStringLength += 1 + stringValueLength;
    
    // Turn on acuadori clip, B=1, A=1                          //commentare queste righe per versione con una molletta
    GPIODigitalWrite(GPIO5, 1);    
    GPIODigitalWrite(GPIO0, 1); 
    clip = 2;
    rn2483_delaysec(10);
    tempSensAcquisition();
    strncat(sensorsString, "T", 1);
    strncat(sensorsString, stringValue, stringValueLength);
    sensorsStringLength += 1 + stringValueLength;
    
    // Read the light transmission sensor and send it throw LoRa Network
    lightSensAcquisition();
    strncat(sensorsString, "L", 1);
    strncat(sensorsString, stringValue, stringValueLength);
    sensorsStringLength += 1 + stringValueLength;
    
    // Read the capacitance and send it throw LoRa Network
    impedenceAcquisition();
    //leafSensAcquisition();
    strncat(sensorsString, "C", 1);
    strncat(sensorsString, stringValue, stringValueLength);
    sensorsStringLength += 1 + stringValueLength;                 //fino a qui
    
    // Turn off all the system
    GPIODigitalWrite(GPIO8, 1);
    upCnt = LORAWAN_GetUplinkCounter();
    sendValue();
    LORAWAN_SetUplinkCounter(upCnt);
    sendValue();
    
}

/* This function generates a sine function values.  
 * All sine values are saved in sinSignal array.    
*/
void sinGeneration(void){
    float rad;
    int16_t val;
    rad = 2*PI/sinSamples;
    for (uint8_t i=0; i<sinSamples; i++){
        val =  256 * sin(rad * i);
        sinSignal[i] =  val + 300;
    }
}

/* This function allow to send all sine sign values.    */
/* It sends only one period.                            */
//void sinGenStart(void){
//
//    i2c_start();
//    if(!i2c_sdaAddress(0x48, W)){
//        while(1){
//            for(uint8_t t=0; t<10; t++){
//
//                i2c_sendData(sinSignal[t]);
//                //i2c_sendData(0x03FF);
//
//            }
//        }
//    }
//
//    i2c_stop();
//}
    bool flag = false;
    uint8_t address = 0x48 << 1;
    adc_result_t result;

uint16_t capValues[numCapSamples];

void sinGenStart(void){
    
    for(uint16_t d=0; d<numCapSamples; d++){
        
        TMR5_StopTimer();
        TMR3_StartTimer();

        // Wait until SCL comes to HIGH state
        while(!(PORTE & _PORTE_RE0_MASK));

        // Set SDA LOW
         LATE &= ~_LATE_LE1_MASK;

        for(int8_t i = 7; i > -1; i--){
            if(flag){
                // Wait until SCL comes HIGH
                while(!(PORTE & _PORTE_RE0_MASK));
            }
            // Wait until SCL comes LOW
            while(PORTE & _PORTE_RE0_MASK);


            if(address & (1 << i)){
                // Set SDA HIGH
                LATE |= _LATE_LE1_MASK;

            }
            else{
                // Set SDA LOW
                LATE &= ~ _LATE_LE1_MASK;

            }
            flag = true;
        }
        while(!(PORTE & _PORTE_RE0_MASK));
        while(PORTE & _PORTE_RE0_MASK);
        //LATE |= _LATE_LE1_MASK;
        if(!i2c_waitACK() || 1){
    //        while(1){

                for(uint8_t t=0; t<2; t++){

                    i2c_sendData(pulseSignal[t]);
                    //i2c_sendData(0x03FF);

                }
                TMR3_StopTimer();
                
                for(int i=0; i<70; i++){
                    __delay_us(1);
                }
                
                
                // select the A/D channel
                ADCON0bits.CHS = GPIO2;    

                // Turn on the ADC module
                ADCON0bits.ADON = 1;

                // Start the conversion
                ADCON0bits.GO_nDONE = 1;

                // Wait for the conversion to finish
                while (ADCON0bits.GO_nDONE)
                {
                }

                // Conversion finished, return the result
                result = ((adc_result_t)((ADRESH << 8) + ADRESL));
                result>>=6;
                capValues[d] = result;
                TMR3_StartTimer();
            }

        i2c_stop();
        TMR3_StopTimer();
        TMR5_StartTimer();

    }
}

/* This function allow to acquise a temperature sensor  */
/* value.                                               */
void tempSensAcquisition(void){
    
    uint16_t value;
    uint16_t temp;
    
    value = GPIOAverageRead(GPIO1);
    temp = tempConversion(value);
    
    uint16ToString(temp, stringValue);
    pointAddition(stringValue);
    stringValueLength = adaptString(stringValue, 5);
    
//    acquisitionData(GPIO1, stringValue);
//    stringValueLength = adaptString(stringValue, 5);
    //sendValue();
}

uint16_t tempConversion(uint16_t adcValue){
    float val;
    uint16_t rTemp;
    float temp;
    val = 3.3 * adcValue/1023;
    val -= 0.02;
    temp = 499 * (val - 1.65) / (1.65 - 3.3); 
    val = temp;
    val /=100;
    temp = 0.074533 * log(val);
    temp++;
    temp = 298.15 / temp;
    temp -= 273.15;
    temp *= 10;
    
    switch(clip){
        case 1:
            /*Mote 1  */ 
            temp += 16;
            /*Mote 2  */ 
//            temp += 12;
            /*Mote 3  */ 
//            temp += 6;
            /*Mote 4  */ 
//            temp +=33;
            
        break;
        case 2:
            /*Mote 1  */ 
            temp += 18;
            /*Mote 2  */ 
//            temp += 16;
            /*Mote 3  */ 
//            temp += 10;
            /*Mote 4  */ 
//            temp +=18;
        break;
    }
    /*Motemain  */
//    temp += 50;
    /*Mote2     */
//    temp += 6;
    /*Mote3     */
//    temp += 6;
    /*Mote4     */
//    temp += 6;
    return temp;
}

/* This function allow to acquire a light sensor value. */
void lightSensAcquisition(void){
    
    // First of all, turn on the LED
    GPIODigitalWrite(GPIO4, 1);
    
    rn2483_delaysec(1);
    acquisitionData(GPIO3, stringValue);
    stringValueLength = adaptString(stringValue, 5);
    //sendValue();
    
    // Finally, turn off the LED
    GPIODigitalWrite(GPIO4, 0);
}

/* This function allow to acquire a leaf sensor value.  */
void leafSensAcquisition(void){
    acquisitionData(GPIO1, stringValue);
    stringValueLength = adaptString(stringValue, 5);
    //sendValue();
}

void impedenceAcquisition(void){
    sinGenStart();
    uint16ToString(averageMeasure(), stringValue);
    stringValueLength = adaptString(stringValue, 5);
    
}
//void impedenceAcquisition(void){
////    TMR1_StopTimer();
//    TMR5_StopTimer();
////    INTERRUPT_GlobalInterruptDisable();
////    // Enable the Peripheral Interrupts
////    INTERRUPT_PeripheralInterruptDisable();
////    
//    
////    RCONbits.IPEN = 1;
////    INTCONbits.GIEH = 1;
////    INTCONbits.GIEL = 1;
//    
//
//    TMR3_StartTimer();
//    
//    i2c_start();
//    
//    if(!i2c_sdaAddress(0x48, W)){
//      
//            
//        i2c_sendData(0x0208);
//            
//     
//    }
//
//    i2c_stop();
//    
//    acquisitionData(GPIO2, stringValue);
//    stringValueLength = adaptString(stringValue, 5);
//    
////    INTCONbits.GIEH = 0;
////    INTCONbits.GIEL = 0;
////    RCONbits.IPEN = 0;
////    INTERRUPT_GlobalInterruptEnable();
////    INTERRUPT_PeripheralInterruptEnable();
//    TMR3_StopTimer();
////    TMR1_StartTimer();
//    TMR5_StartTimer();
//    
//}

/* This function sends the sensorString string.         */
/* This string contains the values of the three sensors */
/* acquired by acuadoriApp function.                    */
/* The first try consists to send the string to the     */
/* gateway and if there were problems, the function     */
/* tries to send it until it receives a success respond.*/
void sendValue(void){
    
    uint8_t status = 1;
    bool firstSend = true;
    uint32_t result;
//    SwTimersClear(9);
    
    // Loop until we have sent the value
    while(status){
        LORAWAN_Mainloop();
        // If it's first sent or last sent went wrong, we must send already the value
        if(timer.sec > 10 || firstSend){
            firstSend = false;
            
            
//            result = LORAWAN_GetStatus();
            
            SwClearAllTimers();
            LORAWAN_Mainloop();
            // Send the value
            status = LORAWAN_Send(CNF, 200, sensorsString, sensorsStringLength);
            
//            //status = LORAWAN_Send(CNF, 200, "LORA", 4);
//            while(result != OK){
//                result = LORAWAN_GetStatus();
//                rn2483_delayms(100);
//                GPIODigitalToogle(GPIO10);
//                LORAWAN_Mainloop();
//            }
            // Toogle the green Led every time we send a value
            //GPIODigitalToogle(GPIO11);
            
            if(status == NETWORK_NOT_JOINED){
                break;
            }
            if (status){
                // There is an error on sending value
                //GPIODigitalWrite(GPIO10, 1);
                timerReset();
            }
            else{
                // The sending was successful
                //GPIODigitalWrite(GPIO10, 0);
            }

        }
    }
}

void pointAddition(uint8_t *element){
    for(uint8_t d = 1; d<4; d++){
        element[d-1] = element[d]; 
    }
    element[3] = 0x2E;
    
}

uint16_t averageMeasure(void){
    uint24_t value = 0; 
    for(uint16_t i=0; i<(numCapSamples); i++){
    value += capValues[i];
    }
    value/= numCapSamples;    
    return value;
}


