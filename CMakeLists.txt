cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr)

project(selog)
include_directories(inc)
target_sources(app PRIVATE 
                    src/main.c
                    src/sensor.c
                    src/user_shell.c)
