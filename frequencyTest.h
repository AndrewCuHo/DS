/*
 * frequencyTest.h
 *
 *  Created on: 2019Äê8ÔÂ5ÈÕ
 *      Author: 09050220
 */

#ifndef FREQUENCYTEST_H_
#define FREQUENCYTEST_H_


#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "ad9850.h"
#include "msp_ad.h"

extern double nowFrq;
extern uint32_t adValue[];
extern uint32_t amp[],ampDB[];
extern uint32_t adValueAss[];
extern uint32_t step;

void ftstart();
void ftcompute();


#endif /* FREQUENCYTEST_H_ */
