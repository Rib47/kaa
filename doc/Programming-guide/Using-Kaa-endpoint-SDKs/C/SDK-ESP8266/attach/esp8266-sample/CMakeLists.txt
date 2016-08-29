#
# Copyright 2014-2016 CyberVision, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

cmake_minimum_required(VERSION 3.0.2)

project(kaa_demo C)

# Add Kaa SDK directory
add_subdirectory(kaa)

# Add source files
add_library(kaa_demo_s STATIC user/user_main.c driver/uart.c src/kaa_demo.c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

if(NOT DEFINED ESP_RTOS_SDK)
    set(ESP_RTOS_SDK /opt/Espressif/esp-rtos-sdk)
endif()

# specify include directories
target_include_directories(kaa_demo_s PUBLIC driver)
target_include_directories(kaa_demo_s PUBLIC .)
target_include_directories(kaa_demo_s PUBLIC
                           ${ESP_RTOS_SDK}/extra_include
                           ${ESP_RTOS_SDK}/include
                           ${ESP_RTOS_SDK}/include/lwip
                           ${ESP_RTOS_SDK}/include/lwip/ipv4
                           ${ESP_RTOS_SDK}/include/lwip/ipv6
                           ${ESP_RTOS_SDK}/include/espressif/
                           )

exec_program(xtensa-lx106-elf-gcc .
            ARGS -print-libgcc-file-name
            OUTPUT_VARIABLE ESP8266_LIBGCC
            )

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/ld)

target_link_libraries(kaa_demo_s PUBLIC
                      kaac
                      ${ESP_RTOS_SDK}/lib/libfreertos.a
                      ${ESP_RTOS_SDK}/lib/libhal.a
                      ${ESP_RTOS_SDK}/lib/libpp.a
                      ${ESP_RTOS_SDK}/lib/libphy.a
                      ${ESP_RTOS_SDK}/lib/libnet80211.a
                      ${ESP_RTOS_SDK}/lib/libwpa.a
                      ${ESP_RTOS_SDK}/lib/liblwip.a
                      ${ESP_RTOS_SDK}/lib/libmain.a
                      ${ESP_RTOS_SDK}/lib/libssl.a
                      ${ESP_RTOS_SDK}/lib/libhal.a
                      ${ESP8266_LIBGCC}
                      -Teagle.app.v6.ld
                      )

file(WRITE ${CMAKE_BINARY_DIR}/blank.c "")
add_executable(kaa_demo ${CMAKE_BINARY_DIR}/blank.c)

target_link_libraries(kaa_demo kaa_demo_s)
