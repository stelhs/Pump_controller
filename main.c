/*
 * main.c
 *
 *  Created on: 25.01.2014
 *      Author: Michail Kurochkin
 */

#include <stdio.h>
#include "init_hw.h"
#include "machine.h"
#include "config.h"

int
main(void)
{
    int rc;

    init_hw();
    printf("Init - ok\r\n");

    for (;;) {

    }
}

