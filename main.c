/*
 * main.c
 *
 *  Created on: 25.01.2014
 *      Author: Michail Kurochkin
 */

#include <stdio.h>
#include "init_hw.h"
#include "config.h"

int
main(void)
{
    init_hw();
    printf("Init - ok\r\n");

    for (;;) {

    }
}

