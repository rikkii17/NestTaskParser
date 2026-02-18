#ifndef NSTT_INTERNAL_H
    #define NSTT_INTERNAL_H

    #include"nstt_parser.h"

    // パーサーの現在状態管理用の構造体
    typedef struct _nstt_Parser_Context {
        int current_line;       // エラー箇所特定
        int nesting_level;      // 現在のネスト深さ
        Nest_task_data *root;   // ツリーの根
        Nest_task_data *current_task; // 現在パース中のタスク
    } nstt_Parser_Context;