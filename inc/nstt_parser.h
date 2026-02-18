#ifndef NSTT_PARSER_H
    #define NSTT_PARSER_H


    #include"nstt_parser_config-component.h"
    #include"nstt_parser_config.h" 
    #include"nstt_parser_internal.h"
    #include"error.h"
    #include"error_config.h"

    
int nstt_parse_file(const char *filename, Nest_task_data **out_root);
    /* * 指定されたNSTTファイルを解析し、データ構造を構築する
 * 引数1: ファイルパス
 * 引数2: 生成されたルートタスクのポインタを格納する変数
 * 戻り値: NSTT_SUCCESS_OK(0) またはエラーコード
 */

static Nest_task_data* find_task_by_name_recursive(Nest_task_data *current, const char *name);

int nstt_get_task_by_name(Nest_task_data *root, const char *name, Nest_task_data **out_task);

#endif    