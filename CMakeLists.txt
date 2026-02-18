cmake_minimum_required(VERSION 3.10)
project(NestTaskParser C)

# C11標準を使用
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# ソースファイルの取得
file(GLOB SOURCES "src/*.c")

# ライブラリとしてビルド（parser本体）
add_library(nstt_parser ${SOURCES})

# インクルードパスの設定
# target_include_directories を使うことで、このライブラリをリンクする側にも
# 自動的に inc フォルダの場所が伝わるようになるよ。
target_include_directories(nstt_parser 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)