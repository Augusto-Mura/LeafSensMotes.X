
//#include <stdio.h>
//#include <stdlib.h>
//#include <xc.h>
#include "mcc_generated_files/mcc.h"

#include "rn2483APP.h"
#include "tmrAPP.h"
#include "acuadori.h"
#include "I2C.h"
#include "mcc_generated_files/LoRaWAN/lorawan_eu.h"
#include <math.h>

/* FOR OTAA ACTIVATION: DevEui, AppEui, AppKey  */
/* FOR ABP ACTIVATION: nwSKey, appSKey, devAddr */

/* MOTE MAIN    */
//uint8_t appKey[16] = {0x7f, 0xb8, 0x0d, 0x9d, 0x46, 0x4A, 0x57, 0x3f, 0xef, 
//    0x68, 0x0e, 0x55, 0xae, 0xc4, 0x52, 0x9a};
//uint8_t deviceEui[8] = {0xB9, 0x96, 0x8F, 0x87, 0x84, 0x48, 0x8c, 0x2c};

/* MOTE 2       */
//uint8_t appKey[16] = {0x7f, 0xb8, 0x0d, 0x9d, 0x46, 0x4A, 0x57, 0x3f, 0xef, 
//    0x68, 0x0e, 0x55, 0xae, 0xc4, 0x52, 0x9b};
//uint8_t deviceEui[8] = {0xB9, 0x96, 0x8F, 0x87, 0x84, 0x48, 0x8c, 0x2d};

/* MOTE 3       */
//uint8_t appKey[16] = {0x2a, 0x98, 0xd0, 0x7d, 0xb4, 0xea, 0xf2, 0x35, 0x04,
//    0x02, 0x57, 0x5d, 0x7c, 0xff, 0xeb, 0x16};
//uint8_t deviceEui[8] = {0xB3, 0x43, 0xFF, 0xCF, 0x5D, 0xFF, 0xE2, 0x66};

/* MOTE 4       */
//uint8_t appKey[16] = {0x4d, 0x49, 0xb5, 0x62, 0x1c, 0x5f, 0xf5, 0x24, 0x78, 
//    0xbe, 0x95, 0x9e, 0x86, 0xd3, 0x02, 0x8e};
//uint8_t deviceEui[8] = {0xc6, 0x51, 0xf7, 0x3a, 0xe7, 0xa8, 0x6f, 0xa4};

/* CA 1   */
//uint8_t appKey[16] = {0xa4, 0xf9, 0x6e, 0x0b, 0x22, 0x24, 0x11, 0xd0, 0x76,
//    0xa9, 0xb9, 0x27, 0xbd, 0x32, 0xb9, 0xbe};
//uint8_t deviceEui[8] = {0x59, 0xe9, 0xde, 0xfa, 0x32, 0x15, 0x48, 0x3e};

/* CA 2   */
//uint8_t appKey[16] = {0x58, 0x87, 0x6c, 0xc0, 0xff, 0x90, 0xa4, 0x8e, 0x02,
//    0xab, 0x2a, 0xee, 0x61, 0xd1, 0x23, 0xce};
//uint8_t deviceEui[8] = {0xcf, 0x5e, 0x97, 0x15, 0xbc, 0x33, 0xd6, 0xa3};

/* CA 3   */
//uint8_t appKey[16] = {0x2a, 0xf6, 0x90, 0xfa, 0x58, 0x34, 0xf5, 0xc3, 0x1f,
//    0xa4, 0x32, 0xf7, 0x01, 0x74, 0xd9, 0x41};
//uint8_t deviceEui[8] = {0x7f, 0x24, 0xfa, 0x39, 0x0a, 0x79, 0x02, 0x8f};

/* CA 4   */
//uint8_t appKey[16] = {0x86, 0x76, 0x1f, 0xb2, 0x56, 0xd1, 0x44, 0x08, 0x99,
//    0x9e, 0x36, 0x01, 0xf5, 0xde, 0x23, 0x30};
//uint8_t deviceEui[8] = {0xfa, 0x48, 0xb9, 0xc6, 0x63, 0xee, 0x7c, 0x14};

/* POWER MOTE*/
uint8_t appKey[16] = {0x58, 0xfd, 0xd5, 0x36, 0x9f, 0x84, 0x6d, 0xfa, 0x90, 
    0x16, 0x5b, 0x5f, 0x8e, 0x4d, 0x81, 0xf8};
uint8_t deviceEui[8] = {0xe4, 0x43, 0x5f, 0x66, 0xbf, 0x8a, 0x57, 0x6d};

uint8_t appEui[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

uint8_t string[5]={0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t stringLength = 5;


bool joined = false;
bool firstSend;
uint32_t value;


void RxData(uint8_t* pData, uint8_t dataLength, OpStatus_t status) {
}

void RxJoinResponse(bool status) {
    
    if (status == ACCEPTED){
//        GPIODigitalWrite(GPIO10, 0);
//        GPIODigitalWrite(GPIO11, 0);
        joined = true;
    } 
    else {
        joined = false;
    }   
}


 

void main(void) {
    // Initialize the device
    SYSTEM_Initialize();
    GPIOInit();
    GPIODigitalWrite(GPIO11, 1);
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable
    // the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to
    // enable the Global and Peripheral Interrupts
    // Use the following macros to:
    // Enable high priority global interrupts
    //INTERRUPT_GlobalInterruptHighEnable();
    // Enable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowEnable();
    // Disable high priority global interrupts
    //INTERRUPT_GlobalInterruptHighDisable();
    // Disable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowDisable();
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();
    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();
    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    LORAWAN_Init(RxData, RxJoinResponse);
//    LORAWAN_SetClass(CLASS_C);
//    
    /* ABP ACTIVATION   */
//    LORAWAN_SetNetworkSessionKey(nwkSKey);
//    LORAWAN_SetApplicationSessionKey(appSKey);
//    LORAWAN_SetDeviceAddress(devAddr);
    
    /* OTAA ACTIVATION  */
    LORAWAN_SetApplicationKey(appKey);
    LORAWAN_SetApplicationEui(appEui);
    LORAWAN_SetDeviceEui(deviceEui);
    
    /* LORAWAN JOIN     */
    LORAWAN_Join(OTAA);
    

    
    /* Select IDLE mode when sleep() is called*/
    OSCCONbits.IDLEN = 1;
    
    //sinGeneration();
    
    /* Start timer      */
    TMR5_StartTimer();
    timerReset();
    
    /* Set the firstSend flag */
    firstSend = true;
//    rn2483_IdleInitialization();
    while (1) {
       
        /* PROCEDURA PER LA RIDUZIONE DEL CONSUMO ENERGETICO*/
        /* La mia idea è quella di far entrare il sistema in 
         * nello stato di IDLE (quindi CPU off ma Periferiche On
         * ogni qualvolta si debba aspettare che passi un'ora. 
         * Quindi dopo il primo invio, il dispositivo dovrà
         * contare per un'ora intera prima di poter rinviare il 
         * dato successivo. Se la CPU è comunque clockata, questo
         * comporta un consumo maggiore di corrente quando realmente 
         * non serve. Infatti nell'aspettare un'ora il dispositivo dovrebbe
         * solamente contare i millisecondi.
         * L'algoritmo che ho intenzione di implementare consiste quindi
         * nell'andare a richiamare la PRI_IDLE mode appena viene 
         * compiuto il primo invio. Si uscirà da questa modalità
         * non appena si ha un interrupt e quindi ogni volta che il 
         * timer conta un ms. Dunque appena viene completata la 
         * routine il firmware dovrà far rientrare il dispositivo
         * nella modalità PRI_IDLE.
         */
//        rn2483_GoToIdle();

        LORAWAN_Mainloop();
        
       //timer.hour == 1
        if (isJoined() && (timer.hour >= 1 || firstSend)){
            GPIODigitalWrite(GPIO10, 0);
            GPIODigitalWrite(GPIO11, 0);

            firstSend = false;
            enableClockPeripherals();
            acuadoriApp();  
            disableClockPeripherals();
            GPIOSet(GPIO1, 0);              //for power-saving purpose set all GPIOs as outputs
            GPIOSet(GPIO2, 0);
            GPIOSet(GPIO3, 0);
            GPIODigitalWrite(GPIO1, 0);
            GPIODigitalWrite(GPIO2, 0);
            GPIODigitalWrite(GPIO3, 0);
            timerReset();
        }
         
        else if (timer.sec >= 16 && !isJoined()){
            
                /* Da sistemare per determinare quale problema genera 
                   l'interruzione del join dopo tre richieste.         */
                LORAWAN_Reset (ISM_EU868);
                LORAWAN_SetApplicationKey(appKey);
                LORAWAN_SetApplicationEui(appEui);
                LORAWAN_SetDeviceEui(deviceEui);
                LORAWAN_Join(OTAA);  
                GPIODigitalToogle(GPIO10);
                timerReset();  
        }
        
        Sleep();
        Nop();
        Nop();
        
    }
}


