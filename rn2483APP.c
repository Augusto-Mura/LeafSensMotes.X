/*
 * File:   rn2483APP.c
 * Author: antop
 *
 * Created on March 1, 2019, 2:24 PM
 */


#include <xc.h>
#include "rn2483APP.h"
#include "mcc_generated_files/adc.h"
#include "mcc_generated_files/mcc.h"



void enableClockPeripherals (void){
    PMD0bits.TMR3MD = PER_ON;
    PMD2bits.ADCMD  = PER_ON;
    TMR3_Initialize();
    ADC_Initialize();
}


void disableClockPeripherals (void){
    PMD0bits.TMR3MD = PER_OFF;
    PMD2bits.ADCMD  = PER_OFF;
}

void rn2483_delayms(uint16_t length)
{
    uint16_t counter;
    for(counter = 0; counter < length; counter++)
    {
        __delay_ms(1);
    }
}
void rn2483_delaysec(uint16_t length)
{
    uint16_t counter;
    while(length){
        for(counter = 0; counter < 1000; counter++)
        {
            __delay_ms(1);
        }
        length--;
    }

}

/* This function allows to set analog or digital a RN2483 Pin.  */
/* The function parameters are GPIO which refers a PIC18LF46K22 */
/* pin, and mode which is "1" when we want to set the pin in    */
/* analog mode, or "0" in digital mode.                         */
void GPIOAnalogMode(uint8_t GPIO, uint8_t mode)
{
    switch(GPIO){
        case GPIO0:
            mode? ANSELA |= _ANSELA_ANSA0_MASK : ANSELA &= ~(_ANSELA_ANSA0_MASK);
        break;
        case GPIO1:
            mode? ANSELA |= _ANSELA_ANSA1_MASK : ANSELA &= ~(_ANSELA_ANSA1_MASK);
        break;
        case GPIO2:
            mode? ANSELA |= _ANSELA_ANSA2_MASK : ANSELA &= ~(_ANSELA_ANSA2_MASK);
        break;
        case GPIO3:
            mode? ANSELA |= _ANSELA_ANSA3_MASK : ANSELA &= ~(_ANSELA_ANSA3_MASK);
        break;
        case GPIO5:
            mode? ANSELA |= _ANSELA_ANSA5_MASK : ANSELA &= ~(_ANSELA_ANSA5_MASK);
        break;
        case GPIO6:
            mode? ANSELE |= _ANSELE_ANSE0_MASK : ANSELE &= ~(_ANSELE_ANSE0_MASK);
        break;
        case GPIO7:
            mode? ANSELE |= _ANSELE_ANSE1_MASK : ANSELE &= ~(_ANSELE_ANSE1_MASK);
        break;
        case GPIO8:
            mode? ANSELD |= _ANSELD_ANSD2_MASK : ANSELD &= ~(_ANSELD_ANSD2_MASK);
        break;
        case GPIO9:
            mode? ANSELE |= _ANSELE_ANSE2_MASK : ANSELE &= ~(_ANSELE_ANSE2_MASK);
        break;
        case GPIO10:
            mode? ANSELC |= _ANSELC_ANSC5_MASK : ANSELC &= ~(_ANSELC_ANSC5_MASK);
        break;
        case GPIO11:
            mode? ANSELD |= _ANSELD_ANSD5_MASK : ANSELD &= ~(_ANSELD_ANSD5_MASK);
        break;
    }
}


/* This function allows to set input or output a RN2483 Pin.    */
/* The function parameters are GPIO which refers a PIC18LF46K22 */
/* pin, and mode which is "1" when we want to set the pin like  */
/* an input, or "0" to output mode.                             */
void GPIOSet(uint8_t GPIO, uint8_t mode)
{
    switch(GPIO){
        case GPIO0:
            mode? TRISA |= (_TRISA_TRISA0_MASK) : TRISA &= ~(_TRISA_TRISA0_MASK);
        break;
        case GPIO1:
            mode? TRISA |= (_TRISA_TRISA1_MASK) : TRISA &= ~(_TRISA_TRISA1_MASK);
        break;
        case GPIO2:
            mode? TRISA |= (_TRISA_TRISA2_MASK) : TRISA &= ~(_TRISA_TRISA2_MASK);
        break;
        case GPIO3:
            mode? TRISA |= (_TRISA_TRISA3_MASK) : TRISA &= ~(_TRISA_TRISA3_MASK);
        break;
        case GPIO4:
            mode? TRISA |= (_TRISA_TRISA4_MASK) : TRISA &= ~(_TRISA_TRISA4_MASK);
        break;
        case GPIO5:
            mode? TRISA |= (_TRISA_TRISA5_MASK) : TRISA &= ~(_TRISA_TRISA5_MASK);
        break;
        case GPIO6:
            mode? TRISE |= (_TRISE_TRISE0_MASK) : TRISE &= ~(_TRISE_TRISE0_MASK);
        break;
        case GPIO7:
            mode? TRISE |= (_TRISE_TRISE1_MASK) : TRISE &= ~(_TRISE_TRISE1_MASK);
        break;
        case GPIO8:
            mode? TRISD |= (_TRISD_TRISD2_MASK) : TRISD &= ~(_TRISD_TRISD2_MASK);
        break;
        case GPIO9:
            mode? TRISE |= (_TRISE_TRISE2_MASK) : TRISE &= ~(_TRISE_TRISE2_MASK);
        break;
        case GPIO10:
            mode? TRISC |= (_TRISC_TRISC5_MASK) : TRISC &= ~(_TRISC_TRISC5_MASK);
        break;
        case GPIO11:
            mode? TRISD |= (_TRISD_TRISD5_MASK) : TRISD &= ~(_TRISD_TRISD5_MASK);
        break;
    }
}


/* This function write to a digital output pin a value.         */
/* The function parameters are GPIO which refers a PIC18LF46k22 */
/* pin and digiOut which is "1" if we want to write high status */
/* or "0" to low state.                                         */
void GPIODigitalWrite(uint8_t GPIO, uint8_t digOut){
    switch(GPIO){
        case GPIO0:
            digOut? LATA |= _LATA_LA0_MASK : LATA &= ~_LATA_LA0_MASK;
        break;
        case GPIO1:
            digOut? LATA |= _LATA_LA1_MASK : LATA &= ~_LATA_LA1_MASK;
        break;
        case GPIO2:
            digOut? LATA |= _LATA_LA2_MASK : LATA &= ~_LATA_LA2_MASK;
        break;
        case GPIO3:
            digOut? LATA |= _LATA_LA3_MASK : LATA &= ~_LATA_LA3_MASK;
        break;
        case GPIO4:
            digOut? LATA |= _LATA_LA4_MASK : LATA &= ~_LATA_LA4_MASK;
            break;
        case GPIO5:
            digOut? LATA |= _LATA_LA5_MASK : LATA &= ~_LATA_LA5_MASK;
        break;
        case GPIO6:
            digOut? LATE |= _LATE_LE0_MASK :  LATE &= ~_LATE_LE0_MASK;
        break;
        case GPIO7:
            digOut? LATE |= _LATE_LE1_MASK :  LATE &= ~_LATE_LE1_MASK;
        break;
        case GPIO8:
            digOut? LATD |= _LATD_LD2_MASK :  LATD &= ~_LATD_LD2_MASK;
        break;
        case GPIO9:
            digOut? LATE |= _LATE_LE2_MASK :  LATE &= ~_LATE_LE2_MASK;
        break;
        case GPIO10:
            digOut? LATC |= _LATC_LC5_MASK :  LATC &= ~_LATC_LC5_MASK;
        break;
        case GPIO11:
            digOut? LATD |= _LATD_LD5_MASK :  LATD &= ~_LATD_LD5_MASK;
        break;
    }
}

uint8_t GPIODigitalRead(uint8_t GPIO){
        switch(GPIO){
        case GPIO0:
            return ((PORTA & _PORTA_RA0_MASK) >> _PORTA_RA0_POSN);
        break;
        case GPIO1:
            return ((PORTA & _PORTA_RA1_MASK) >> _PORTA_RA1_POSN);
        break;
        case GPIO2:
            return ((PORTA & _PORTA_RA2_MASK) >> _PORTA_RA2_POSN);
        break;
        case GPIO3:
            return ((PORTA & _PORTA_RA3_MASK) >> _PORTA_RA3_POSN);
        break;
        case GPIO4:
            return ((PORTA & _PORTA_RA4_MASK) >> _PORTA_RA4_POSN);
            break;
        case GPIO5:
            return ((PORTA & _PORTA_RA5_MASK) >> _PORTA_RA5_POSN);
        break;
        case GPIO6:
            return ((PORTE & _PORTE_RE0_MASK) >> _PORTE_RE0_POSN);
        break;
        case GPIO7:
            return ((PORTE & _PORTE_RE1_MASK) >> _PORTE_RE1_POSN);
        break;
        case GPIO8:
            return ((PORTD & _PORTD_RD2_MASK) >> _PORTD_RD2_POSN);
        break;
        case GPIO9:
            return ((PORTE & _PORTE_RE2_MASK) >> _PORTE_RE2_POSN);
        break;
        case GPIO10:
            return ((PORTC & _PORTC_RC5_MASK) >> _PORTC_RC5_POSN);
        break;
        case GPIO11:
            return ((PORTD & _PORTD_RD5_MASK) >> _PORTD_RD5_POSN);
        break;
    }
}

void GPIODigitalToogle(uint8_t GPIO){
    switch(GPIO){
        case GPIO0:
            LATA ^= _LATA_LA0_MASK; 
        break;
        case GPIO1:
            LATA ^= _LATA_LA1_MASK;
        break;
        case GPIO2:
            LATA ^= _LATA_LA2_MASK;
        break;
        case GPIO3:
            LATA ^= _LATA_LA3_MASK;
        break;
        case GPIO4:
            LATA ^= _LATA_LA4_MASK;
            break;
        case GPIO5:
            LATA ^= _LATA_LA5_MASK;
        break;
        case GPIO6:
            LATE ^= _LATE_LE0_MASK;
        break;
        case GPIO7:
            LATE ^= _LATE_LE1_MASK;
        break;
        case GPIO8:
            LATD ^= _LATD_LD2_MASK;
        break;
        case GPIO9:
            LATE ^= _LATE_LE2_MASK;
        break;
        case GPIO10:
            LATC ^= _LATC_LC5_MASK;
        break;
        case GPIO11:
            LATD ^= _LATD_LD5_MASK;
        break;
    }
}

/* The following function converts a 16 bit integer to a string */
/* value.                                                       */
void uint16ToString(uint16_t value, uint8_t *output)
{
    uint16_t position = 0;
    
//    output[position + 9] = '0' + (value % 10);
//    value /= 10;
//    output[position + 8] = '0' + (value % 10);
//    value /= 10;
//    output[position + 7] = '0' + (value % 10);
//    value /= 10;
//    output[position + 6] = '0' + (value % 10);
//    value /= 10;
//    output[position + 5] = '0' + (value % 10);
//    value /= 10;
    output[position + 4] = '0' + (value % 10);
    value /= 10;
    output[position + 3] = '0' + (value % 10);
    value /= 10;
    output[position + 2] = '0' + (value % 10);
    value /= 10;
    output[position + 1] = '0' + (value % 10);
    value /= 10;
    output[position] = '0' + (value % 10);
}



#define NumberOfSamples 1000
/* The following function allow to read a number of time an     */
/* analog input and return the average.                         */
uint16_t GPIOAverageRead(uint8_t GPIO)
{
    uint24_t finalValue = 0; 
    
    for(uint16_t i=0; i<(NumberOfSamples); i++){
        finalValue += GPIOAnalogRead(GPIO);
    }
    finalValue/= NumberOfSamples;    
    return finalValue;
}

/* The following function allow to read a GPIO's analog value   */
/* and to convert it to a string form.                          */
void acquisitionData(uint8_t GPIO, uint8_t *string)
{
    uint16ToString(GPIOAverageRead(GPIO), string);
    //LORAWAN_Send(UNCNF, 2, "GPIO1 Acquised", 14);
}

/* This function returns the value of an analog reading from a  */
/* GPIO pin.                                                    */
uint16_t GPIOAnalogRead(uint8_t GPIO)
{
    adc_result_t result;
    
    result =  ADC_GetConversion(GPIO);
    //LORAWAN_Send(UNCNF, 2, "GPIO1 Readed", 12);
    return result;
}

/* This function is used to initialize all GPIOs like IO mode   */
/* or analog/digital mode.                                      */
void GPIOInit(){
    /*  GPIO0 = ACUADORI MUX Control A (DIGITAL OUTPUT)
        GPIO1 = ACUADORI Temperature Sensor (ANALOG INPUT)
        GPIO2 = ACUADORI Impedence Sensor (ANALOG INPUT)
        GPIO3 = ACUADORI Light Sensor (ANALOG INPUT)
        GPIO4 = ACUADORI Light led switch (DIGITAL OUTPUT)
        GPIO5 = ACUADORI MUX Control A (DIGITAL OUTPUT)
        GPIO6 = ACUADORI I2C Clock SCL (DIGITAL OUTPUT)
        GPIO7 = ACUADORI I2C Serial Data SDA (DIGITAL OUTPUT)
        GPIO8 = ACUADORI Power Switch (DIGITAL OUTPUT)
        GPIO10 = MOTE Orange LED
        GPIO11 = MOTE Green LED
    */
    GPIOSet(GPIO0, 0);
    GPIOSet(GPIO1, 1);
    GPIOSet(GPIO2, 1);
    GPIOSet(GPIO3, 1);
    GPIOSet(GPIO4, 0);
    GPIOSet(GPIO5, 0);
    GPIOSet(GPIO6, 0);
    GPIOSet(GPIO7, 0);
    GPIOSet(GPIO8, 0);
    GPIOSet(GPIO10, 0);
    GPIOSet(GPIO11, 0);
    
    
    GPIOAnalogMode(GPIO0, 0);
    GPIOAnalogMode(GPIO1, 1);
    GPIOAnalogMode(GPIO2, 1);
    GPIOAnalogMode(GPIO3, 1);
    GPIOAnalogMode(GPIO4, 0);
    GPIOAnalogMode(GPIO5, 0);
    GPIOAnalogMode(GPIO6, 0);
    GPIOAnalogMode(GPIO7, 0);
    GPIOAnalogMode(GPIO8, 0);
    GPIOAnalogMode(GPIO10, 0);
    GPIOAnalogMode(GPIO11, 0);
    
    GPIODigitalWrite(GPIO0, 0);
    GPIODigitalWrite(GPIO4, 0);
    GPIODigitalWrite(GPIO5, 0);
    GPIODigitalWrite(GPIO8, 1);
}

    uint8_t adaptString(uint8_t *string, uint8_t length){
  uint8_t deleteElem = 0;
  bool flag = false;
  
  for(uint8_t i = 0; i<length; i++){
    if(string[i]== 0x30 && !flag){
      deleteElem++;
    }
    else{
      string[i-deleteElem] = string[i];
      flag=true;
    }
  }
  // Check if all values are zero
  if (deleteElem == length){
      return 1;
  }
  return length-deleteElem;
}

uint8_t isJoined(){
    uint32_t value; 
    uint8_t joined; 
    value = LORAWAN_GetStatus();
    joined = value & 0x10;
    return joined; 
}

void rn2483_IdleInitialization(void){
    //Disable Watchdog timer 
    WDTCON = 0;
//    INTERRUPT_GlobalInterruptDisable();
//    INTERRUPT_PeripheralInterruptDisable();
//    OSCCON &= ~_OSCCON_IDLEN_MASK;
    OSCCON |= _OSCCON_IDLEN_MASK;

}

uint8_t rn2483_GoToIdle(void){
//    INTERRUPT_GlobalInterruptDisable();
    
    //ADC interrupt disable
//    PIE1bits.ADIE = 0;
    INTCON3bits.INT1IE = 0;
    INTCON3bits.INT2IE = 0;
    INTCONbits.RBIE = 0;
//    TMR1_StopTimer();
    PIE1bits.TMR1IE = 0;
//    INTERRUPT_GlobalInterruptEnable();
    //Set IDLE mode
    
//   OSCCON |= _OSCCON_IDLEN_MASK;
    
    //Enter in IDLE mode
    __asm(" sleep");
    NOP();
    
//    INTERRUPT_GlobalInterruptDisable();
    
    PIE1bits.TMR1IE = 1;
//    TMR1_StartTimer();
    INTCON3bits.INT1IE = 1;
    INTCON3bits.INT2IE = 1;
    INTCONbits.RBIE = 1;
    
    
    //ADC interrupt enable
//    PIE1bits.ADIE = 1;
    
//    INTERRUPT_GlobalInterruptEnable();

    
}

void resetAllChannels(void){
    
    for(int i=0; i<4; i++){
        LORAWAN_SetChannelIdStatus(i, DISABLED);
    }
    
    for(int i=0; i<4; i++){
        LORAWAN_SetChannelIdStatus(i, ENABLED);
    }
    
}
/**
 End of File
*/