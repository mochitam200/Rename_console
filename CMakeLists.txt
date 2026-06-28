cmake_minimum_required(VERSION 3.12)
project(FileRenamer CXX)
# C++17標準を要求
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 実行ファイルの設定
add_executable(file_renamer main.cpp)