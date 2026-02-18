#include <stdio.h>
#include <stdlib.h>
//標準系の関数を使用するライブラリ
#include <string.h>
//string系の扱いライブラリ
#include "nstt_helper.h"
//helperのヘッダーファイル

int create_nest_task_data(Nest_task_data **out_task) {
    /* 引数チェック */
    if (out_task == NULL) {
        return NSTT_ERR_INVALID_ARGUMENT; 
    }

    /* メモリ確保 */
    Nest_task_data *new_task = (Nest_task_data *)malloc(sizeof(Nest_task_data));
    if (new_task == NULL) {
        return NSTT_ERR_MALLOC_FAIL; 
    }

    /* データの初期化（ゴミデータを消去） */
    memset(new_task->task_name, 0, sizeof(new_task->task_name));
    memset(new_task->memo, 0, sizeof(new_task->memo));
    new_task->importance_level = 0;
    new_task->option_head = NULL;

    //ネットワークの初期化
    new_task->parent = NULL;
    new_task->children = NULL;
    new_task->next = NULL;
    new_task->prev = NULL;

    /* 生成したポインタを引数の先に格納 */
    *out_task = new_task;

    return NSTT_SUCCESS_OK;
}

int append_child_task(Nest_task_data *parent, Nest_task_data *child) {
    if (parent == NULL || child == NULL) {
        return NSTT_ERR_INVALID_ARGUMENT;
    }

    child->parent = parent;

    if (parent->children == NULL) {
        /* 同一レイヤに何もない場合、最初の子として登録 */
        parent->children = child;
    } else {
        /* 同一レイヤのリストの末尾を探す */
        Nest_task_data *current = parent->children;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = child;
        child->prev = current;
    }

    return NSTT_SUCCESS_OK;
}

int add_option_data(Nest_task_data *task, const char *word, var content) {
    if (task == NULL || word == NULL) {
        return NSTT_ERR_INVALID_ARGUMENT;
    }

    Option_data *new_opt = (Option_data *)malloc(sizeof(Option_data));
    if (new_opt == NULL) {
        return NSTT_ERR_MALLOC_FAIL;
    }

    /* 文字列の終端考慮*/
    strncpy(new_opt->option_word, word, sizeof(new_opt->option_word) - 1);
    new_opt->option_word[sizeof(new_opt->option_word) - 1] = '\0';
    
    new_opt->option_content = content;
    new_opt->next_data = NULL;
    new_opt->previous_data = NULL;

    /* リストの先頭挿入 */
    if (task->option_head != NULL) {
        new_opt->next_data = task->option_head;
        task->option_head->previous_data = new_opt;
    }
    task->option_head = new_opt;

    return NSTT_SUCCESS_OK;
}