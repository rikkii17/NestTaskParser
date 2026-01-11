#ifndef NSTT_PARSER_CONFIG-COMPONENT_H

    #define NSTT_PARSER_CONFIG-COMPONENT_H

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
        int int_data;
        char char_data;
        double double_data;
        char string_data[8192];
    } var;
    //データ型の決まっていないデータを保存するデータ型

#endif