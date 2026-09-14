cmake_minimum_required(VERSION 3.20)
project(LibrarySystem)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(LibrarySystem
    src/main.cpp
    src/Item.cpp
    src/Book.cpp
    src/Member.cpp
    src/BorrowRecord.cpp
    src/ItemCollection.cpp
    src/Library.cpp
    src/Date.cpp
)

target_include_directories(LibrarySystem PRIVATE include)