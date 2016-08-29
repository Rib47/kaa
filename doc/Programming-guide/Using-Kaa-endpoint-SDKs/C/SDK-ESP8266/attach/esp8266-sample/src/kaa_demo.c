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

#include <stddef.h>
#include <kaa/kaa_error.h>
#include <kaa/kaa_context.h>
#include <kaa/platform/kaa_client.h>

static void loop_fn(void *context)
{
    printf("Hello, Kaa!\r\n");

    kaa_client_stop(context);
}

int main(void)
{
    printf("Initializing Kaa client\r\n");

    kaa_client_t *kaa_client;

    kaa_error_t error_code = kaa_client_create(&kaa_client, NULL);
    if (error_code) {
        printf("Failed to create Kaa client\r\n");
        return 1;
    }

    error_code = kaa_client_start(kaa_client, loop_fn, (void*)kaa_client, 0);
    if (error_code) {
        printf("Failed to start Kaa main loop\r\n");
        return 1;
    }

    kaa_client_destroy(kaa_client);
    return 0;
}
