#ifndef NSTT_PARSER_CONFIG_H
#define NSTT_PARSER_CONFIG_H

#include "nstt_parser_config-component.h"

// 前方定義
typedef struct _Option_data Option_data;
typedef struct _Nest_task_data Nest_task_data;

// 期限管理用構造体
typedef struct _Deadline_time {
    Date deadline_date;
    short int hour;
    short int minute;
} Deadline_time;

// オプションデータ
struct _Option_data {
    char option_word[256]; // <option_word> を保持
    var option_content;
    Option_data *next_data;
    Option_data *previous_data;
};

// メインタスク構造体
struct _Nest_task_data {
    // コンテンツ
    char task_name[1024];
    Deadline_time deadline_time;
    unsigned char importance_level; 
    Time need_time;
    Time worked_time;
    char memo[4096];
    Option_data *option_head; // オプションリストの先頭ポインタに変更

    // リスト・ツリー構造
    Nest_task_data *parent;    // 上の階層へのポインタ
    Nest_task_data *children;  // 下の階層へのポインタ
    Nest_task_data *next;      // 同階層の次のタスク
    Nest_task_data *prev;      // 同階層の前のタスク
};

#endif