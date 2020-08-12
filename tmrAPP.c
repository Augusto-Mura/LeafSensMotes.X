/*
 * File:   tmrAPP.c
 * Author: antop
 *
 * Created on 14 marzo 2019, 14.38
 */


#include <xc.h>
#include "tmrAPP.h"
#include "mcc_generated_files/mcc.h"

static uint16_t msCounter;
static uint16_t sCounter;
//timer_t timer = {0, 0, 0, 0, 0};

void timerTick(){
    msCounter++;
}

void timerTick16(){
    sCounter += 16;
}

void timerHandler(){
    timer.ms += msCounter;
    msCounter = 0;
    if(timer.ms/1000){
        timer.sec += timer.ms/1000;
        timer.ms %= 1000;
        
    }
    if (timer.sec/60){
        timer.min += timer.sec/60;
        timer.sec %= 60;
    }
    if (timer.min/60){
        timer.hour += timer.min/60;
        timer.min %= 60;
    }
    if(timer.hour/24){
        timer.day += timer.hour/24;
        timer.hour %= 24;
    }
}
void timerHandler16(){
    timer.sec += sCounter;
    sCounter = 0;
//    if(timer.ms/1000){
//        timer.sec += timer.ms/1000;
//        timer.ms %= 1000;
//        
//    }
    if (timer.sec/60){
        timer.min += timer.sec/60;
        timer.sec %= 60;
    }
    if (timer.min/60){
        timer.hour += timer.min/60;
        timer.min %= 60;
    }
    if(timer.hour/24){
        timer.day += timer.hour/24;
        timer.hour %= 24;
    }
}

void timerReset(){
    sCounter = 0;
    msCounter = 0;
    timer.ms = 0;
    timer.sec = 0;
    timer.min = 0;
    timer.hour = 0;
    timer.day = 0;
}