cmake_minimum_required(VERSION 4.2)
project(GardeningSimulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(GardeningSimulator main.cpp
        Player.cpp
        Player.h
        Menu.cpp
        Menu.h
        Potato.cpp
        Potato.h
        Tomato.cpp
        Tomato.h
        Store.cpp
        Store.h
        Plant.cpp
        Plant.h
        Shovel.cpp
        Shovel.h
        Plot.cpp
        Plot.h)
