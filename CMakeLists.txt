cmake_minimum_required(VERSION 3.12.3)
project(untitled)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER "/Library/Developer/CommandLineTools/usr/bin/g++")

add_executable(1 osnovy/1semestr/first.cpp)
add_executable(2 osnovy/1semestr/second.cpp)
add_executable(3_a osnovy/1semestr/third_a.cpp osnovy/1semestr/third_a.h)
add_executable(3_b osnovy/1semestr/third_b.cpp osnovy/1semestr/third_b.h)
add_executable(3_c osnovy/1semestr/third_c.cpp osnovy/1semestr/third_c.h)
add_executable(4 osnovy/1semestr/forth.cpp)
add_executable(5 osnovy/1semestr/fifth.cpp)
add_executable(sort osnovy/1semestr/sort.cpp)
add_executable(algo1 algo/algo_3.cpp)
add_executable(os_1 os/os_1.c)
add_executable(os_3 os/os_3.c)
add_executable(os_4 os/os_4.c)
add_executable(os_3.2 os/os_3_2.c)
add_executable(os_2 os/os_2.c)
# Note: when running some main function, need to specify here all classes should be linked (?)
add_executable(oop oop/oop.cpp oop/1/Function.cpp)
add_executable(oop_kursova oop/kusr_examp/marina.cpp oop/kursova/kursova.cpp )
add_executable(oop_test oop/kusr_examp/test.cpp)
add_executable(oop_2 oop/2/lab_2.cpp oop/2/Date.cpp oop/2/Enterprise.cpp oop/2/IOProcessor.cpp)
add_executable(oop_3
        oop/3/Person.cpp
        oop/3/lab3.cpp
        oop/3/Position.cpp
        oop/3/Employee.cpp
        oop/3/Manager.cpp
        oop/2/Date.cpp
        oop/3/Showable.cpp
        )
add_executable(oop_4
        oop/4/Fuel.cpp
        oop/4/Operator.cpp
        oop/4/Checkout.cpp
        oop/4/DailyBalance.cpp
        oop/4/Container.h
        oop/2/Date.cpp
        oop/4/lab4.cpp
        )



#add_executable(6_test osnovy/1semestr/six_example.cpp)
