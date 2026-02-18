#ifndef NSTT_PARSER_CONFIG-COMPONENT_H

    #define NSTT_PARSER_CONFIG-COMPONENT_H

    #include"nstt_parser.h"

    //データ型識別用のdefine
    #define NSTT_TYPE_NONE   0
    #define NSTT_TYPE_INT    1
    #define NSTT_TYPE_CHAR   2
    #define NSTT_TYPE_DOUBLE 3
    #define NSTT_TYPE_STRING 4



    typedef struct _Date{
        short int year;
        short int month;
        short int day;
        //とりあえずshort intで定義。汎用性や安全性を考えてintに変更する可能性あり。
    } Date;
    //日付を定義しるためのデータ型。

    typedef struct _Time{
        short int hour;
        short int minute;
        short int second;
    } Time;
    //時間を時間・分・秒単位までで保存することのできるデータ型

    typedef struct _Variable{
        unsigned char data_type;
        /*
            * 0: NONE   未定義
            * 1: INT    整数型
            * 2: CHAR   bytecode
            * 3: DOUBLE 浮動小数点
            * 4: STRING 文字列: max 8192 bytes
        */

        int int_data;
        char char_data;
        double double_data;
        char string_data[8192];
    } var;
    //データ型の決まっていないデータを保存するデータ型

#endif