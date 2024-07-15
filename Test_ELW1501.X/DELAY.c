/*
 * File:   DELAY.c
 * Author: t.douillet
 *
 * Created on July 2, 2024, 10:05 AM
 */


#include "xc.h"
#include "DELAY.h"

void Delay(unsigned int msec)
{
   while(msec > 0)
   {
       __delay_ms(1);
      msec--;
    }
}

void Delay_us(unsigned int usec)
{
   while(usec > 0)
   {
       __delay_us(1);
      usec--;
    }
}
