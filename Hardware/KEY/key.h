#ifndef __KEY_H

#define __KEY_H
#include "stm32f10x.h"
 #include <stdbool.h>
void Key_Init(void);
bool EXTI_Flag(void);
#endif