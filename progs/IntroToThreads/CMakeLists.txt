cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

set(PROJECT_NAME IntroToMultiThreading)
project(${PROJECT_NAME}) 

set(LES1 ./src/Lesson1.cpp ./include/Lesson1.h)
set(LES2 ./src/Lesson2.cpp ./include/Lesson2.h)
set(LES3 ./src/Lesson3.cpp ./include/Lesson3.h)
set(LES4 ./src/Lesson4.cpp ./include/Lesson4.h)
set(LES5 ./src/Lesson5.cpp ./include/Lesson5.h)
set(LES6 ./src/Lesson6.cpp ./include/Lesson6.h)
set(LES7 ./src/Lesson7.cpp ./include/Lesson7.h)
set(LES8 ./src/Lesson8.cpp ./include/Lesson8.h)
set(LES9 ./src/Lesson9.cpp ./include/Lesson9.h)
set(MYTIMER ./src/Timer.cpp ./include/Timer.h)

add_executable(${PROJECT_NAME} 
        main.cpp ./include/Lessons.h 
        ${LES1} ${LES2} ${LES3} ${LES4} ${LES5} ${LES6} ${LES7} ${LES8} ${LES9} 
        ${MYTIMER})