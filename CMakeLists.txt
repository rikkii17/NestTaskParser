cmake_minimum_required(VERSION 3.10)
project(NestTaskParser C)

# C11標準を使用
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# インクルードディレクトリの指定 (incフォルダ)
include_directories(inc)

# ソースファイルの取得
file(GLOB SOURCES "src/*.c")

# ライブラリとしてビルド（parser本体）
add_library(nstt_parser ${SOURCES})