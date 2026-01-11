#ifndef NSTT_PARSER_CONFIG_H
    #define NSTT_PARSER_CONFIG_H

    #include"nstt_parser_config-component.h"

    typedef struct _Nest_task_data_struct{
        //コンテンツ部
        char task_name[1024];
        Deadline_time deadline_time;
        char importance_level;
        Time need_time;
        Time worked_time;
        char memo[4096];
        Option_data option_data;

        //リスト部
        Nest_task_data *above_data;
        Nest_task_data *under_data;
        Nest_task_data *next_data;
        Nest_task_data *previous_data;

    } Nest_task_data;
    //ネストタスクデータを一括で保存することのできる構造体

    typedef struct _Deadline_time{
        Date deadline_date;
        short int hour;
        short int minute;
    } Deadline_time;
    //デッドラインを保存するための構造体

    typedef struct _Option_data{
        var option_content;
        Option_data *next_data;
        Option_data *previous_data;
    } Option_data;

    



    

#endif