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
    strncpy_s(new_opt->option_word, sizeof(new_opt->option_word), word, _TRUNCATE);
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



int get_next_val(const char **str, short int *result) {
    int val = 0;
    int digit_count = 0;

    while (**str >= '0' && **str <= '9') {
        val = val * 10 + (**str - '0');
        (*str)++;
        digit_count++;
    }

    if (digit_count == 0) return -1; /* 数値が存在しなかった場合 */
    *result = (short int)val;

    if (**str == '.') {
        (*str)++; /* ドットが存在する場合それは無視する*/
    }
    return NSTT_SUCCESS_OK;
}

int parse_date_string(const char *str, Date *out_date) {
    if (str == NULL || out_date == NULL) return NSTT_ERR_VAL_INVALID_DATE;

    const char *p = str;
    
    /* 年・月・日の順にてて解析 */
    if (get_next_val(&p, &out_date->year) != 0) return NSTT_ERR_VAL_INVALID_DATE;
    if (get_next_val(&p, &out_date->month) != 0) return NSTT_ERR_VAL_INVALID_DATE;
    if (get_next_val(&p, &out_date->day) != 0) return NSTT_ERR_VAL_INVALID_DATE;

    /* バリデーションエラーの検出*/
    if (out_date->month < 1 || out_date->month > 12 || out_date->day < 1 || out_date->day > 31) {
        return NSTT_ERR_VAL_OUT_OF_RANGE;
    }

    return NSTT_SUCCESS_OK;
}

int parse_time_string(const char *str, Time *out_time) {
    //引数エラーの検出
    if (str == NULL || out_time == NULL) return NSTT_ERR_VAL_INVALID_TIME;

    const char *p = str;

    /* 時・分・秒の順にて解析 */
    if (get_next_val(&p, &out_time->hour) != 0) return NSTT_ERR_VAL_INVALID_TIME;
    if (get_next_val(&p, &out_time->minute) != 0) return NSTT_ERR_VAL_INVALID_TIME;
    if (get_next_val(&p, &out_time->second) != 0) return NSTT_ERR_VAL_INVALID_TIME;

    /*バリデーションエラーの検出*/
    if (out_time->minute >= 60 || out_time->second >= 60) {
        return NSTT_ERR_VAL_OUT_OF_RANGE;
    }

    return NSTT_SUCCESS_OK;
}

int parse_deadline_string(const char *str, Deadline_time *out_deadline) {
    //引数エラーの検出
    if (str == NULL || out_deadline == NULL) return NSTT_ERR_VAL_INVALID_DATE;

    const char *p = str;

    //yyyy.mm.dd 部分の解析処理
    if (get_next_val(&p, &out_deadline->deadline_date.year) != 0) return NSTT_ERR_VAL_INVALID_DATE;
    if (get_next_val(&p, &out_deadline->deadline_date.month) != 0) return NSTT_ERR_VAL_INVALID_DATE;
    if (get_next_val(&p, &out_deadline->deadline_date.day) != 0) return NSTT_ERR_VAL_INVALID_DATE;

    /* hh.minmin 部分の解析処理 */
    if (get_next_val(&p, &out_deadline->hour) != 0) return NSTT_ERR_VAL_INVALID_TIME;
    if (get_next_val(&p, &out_deadline->minute) != 0) return NSTT_ERR_VAL_INVALID_TIME;

    return NSTT_SUCCESS_OK;
}



int add_child_task(Nest_task_data *parent, Nest_task_data *child) {
    if (parent == NULL || child == NULL) return NSTT_ERR_INVALID_ARGUMENT;

    child->parent = parent;

    /* まだ子が一人もいない場合 */
    if (parent->children == NULL) {
        parent->children = child;
    } 
    /* すでに子がいる場合、兄弟リスト(next)の末尾を探す */
    else {
        Nest_task_data *p = parent->children;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = child;
        child->prev = p;
    }

    return NSTT_SUCCESS_OK;
}

int get_root_task(Nest_task_data *current, Nest_task_data **out_root) {
    if (current == NULL || out_root == NULL) return NSTT_ERR_INVALID_ARGUMENT; 

    Nest_task_data *p = current;
    while (p->parent != NULL) {
        p = p->parent;
    }
    *out_root = p;

    return NSTT_SUCCESS_OK;
}

