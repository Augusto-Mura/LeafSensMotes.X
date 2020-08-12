/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef RNHEADER
#define	RNHEADER

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

// GPIO DEFINITION 
#define GPIO0 0x00
#define GPIO1 0x01
#define GPIO2 0x02
#define GPIO3 0x03
#define GPIO4 0xFF
#define GPIO5 0x04
#define GPIO6 0x05
#define GPIO7 0x06
#define GPIO8 0x16
#define GPIO9 0x07
#define GPIO10 0x11
#define GPIO11 0x19

#define ANAL 1
#define DIG 0

void GPIOInit(void);
void GPIOAnalogMode(uint8_t GPIO, uint8_t mode);
void GPIOSet(uint8_t GPIO, uint8_t mode);
uint16_t GPIOAnalogRead(uint8_t GPIO);
void GPIODigitalWrite(uint8_t GPIO, uint8_t digOut);
uint8_t GPIODigitalRead(uint8_t GPIO);
void GPIODigitalToogle(uint8_t GPIO);
void acquisitionData(uint8_t GPIO, uint8_t *string);
void uint16ToString(uint16_t value, uint8_t *output);
void rn2483_delayms(uint16_t length);
void rn2483_delaysec(uint16_t length);
uint8_t adaptString(uint8_t *string, uint8_t length);
uint16_t GPIOAverageRead(uint8_t GPIO);
uint8_t isJoined(void);
uint8_t rn2483_GoToIdle(void);
void rn2483_IdleInitialization(void);
void resetAllChannels(void);


#endif	/* XC_HEADER_TEMPLATE_H */

