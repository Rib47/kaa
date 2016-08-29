/*
 * Copyright 2014-2016 CyberVision, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "uart.h"

extern int main(void);
    
static void main_task(void *pvParameters)
{
    (void)pvParameters;
    main();
    for (;;);
}

void user_init(void)
{
    uart_init_new();
    UART_SetBaudrate(UART0, 115200);
    UART_SetPrintPort(UART0);
    
    portBASE_TYPE error = xTaskCreate(main_task, "main_task", 512, NULL, 2, NULL );
    if (error < 0) {
        printf("Error creating main_task! Error code: %ld\r\n", error);
    }
}
