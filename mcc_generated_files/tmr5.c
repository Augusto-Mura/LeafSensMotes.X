/**
  TMR5 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    tmr5.c

  @Summary
    This is the generated driver implementation file for the TMR5 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides APIs for TMR5.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC18LF46K22
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.00
        MPLAB 	          :  MPLAB X 5.10
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "../rn2483APP.h"
#include "tmr5.h"
#include "../tmrAPP.h"

/**
  Section: Global Variable Definitions
*/
volatile uint16_t timer5ReloadVal;
void (*TMR5_InterruptHandler)(void);

/**
  Section: TMR5 APIs
*/

void TMR5_Initialize(void)
{
    //Set the Timer to the options selected in the GUI

    //T5GSS T5G_pin; TMR5GE disabled; T5GTM disabled; T5GPOL low; T5GGO done; T5GSPM disabled; 
    T5GCON = 0x00;

    //TMR5H 254; 
    TMR5H = 0xFE;

    //TMR5L 12; 
    TMR5L = 0x0C;

    // Load the TMR value to reload variable
    timer5ReloadVal=TMR5;

    // Clearing IF flag before enabling the interrupt.
    PIR5bits.TMR5IF = 0;

    // Enabling TMR5 interrupt.
    PIE5bits.TMR5IE = 1;

    IPR5bits.TMR5IP = 0;
    
    // Set Default Interrupt Handler
    TMR5_SetInterruptHandler(TMR5_InterruptTicker);

    // T5CKPS 1:8; T5SOSCEN disabled; T5SYNC do_not_synchronize; TMR5CS FOSC/4; TMR5ON enabled; T5RD16 disabled; 
    T5CON = 0x35;
}

void TMR5_StartTimer(void)
{
    // Start the Timer by writing to TMRxON bit
    T5CONbits.TMR5ON = 1;
    
}

void TMR5_StopTimer(void)
{
    // Stop the Timer by writing to TMRxON bit
    T5CONbits.TMR5ON = 0;
    
    
}

uint16_t TMR5_ReadTimer(void)
{
    uint16_t readVal;
    uint8_t readValHigh;
    uint8_t readValLow;
    
    T5CONbits.T5RD16 = 1;
	
    readValLow = TMR5L;
    readValHigh = TMR5H;
    
    readVal = ((uint16_t)readValHigh << 8) | readValLow;

    return readVal;
}

void TMR5_WriteTimer(uint16_t timerVal)
{
    if (T5CONbits.T5SYNC == 1)
    {
        // Stop the Timer by writing to TMRxON bit
        T5CONbits.TMR5ON = 0;

        // Write to the Timer5 register
        TMR5H = (timerVal >> 8);
        TMR5L = (uint8_t) timerVal;

        // Start the Timer after writing to the register
        T5CONbits.TMR5ON =1;
    }
    else
    {
        // Write to the Timer5 register
        TMR5H = (timerVal >> 8);
        TMR5L = (uint8_t) timerVal;
    }
}

void TMR5_Reload(void)
{
    TMR5_WriteTimer(timer5ReloadVal);
}

void TMR5_StartSinglePulseAcquisition(void)
{
    T5GCONbits.T5GGO = 1;
}

uint8_t TMR5_CheckGateValueStatus(void)
{
    return T5GCONbits.T5GVAL;
}

void TMR5_ISR(void)
{

    // Clear the TMR5 interrupt flag
    PIR5bits.TMR5IF = 0;
    TMR5_WriteTimer(timer5ReloadVal);

    if(TMR5_InterruptHandler)
    {
        TMR5_InterruptHandler();
    }
}


void TMR5_SetInterruptHandler(void (* InterruptHandler)(void)){
    TMR5_InterruptHandler = InterruptHandler;
}

void TMR5_InterruptTicker(void){
    timerTick();
    timerHandler();
}


/**
 End of File
*/
