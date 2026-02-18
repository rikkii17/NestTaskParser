#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "nstt_parser.h"
#include "nstt_helper.h"

// 前後の空白を削除する補助関数
static char* trim_space(char* str);


int nstt_parse_file(const char *filename, Nest_task_data **out_root) {
    if (filename == NULL || out_root == NULL) return NSTT_ERR_INVALID_ARGUMENT;

    FILE *fp = fopen(filename, "r");
    if (!fp) return NSTT_ERR_FILE_OPEN;

    nstt_Parser_Context ctx = {0, 0, NULL, NULL};
    char line[4096];
    int res = NSTT_SUCCESS_OK;

    while (fgets(line, sizeof(line), fp)) {
        ctx.current_line++;
        char *trimmed = trim_space(line);
        if (strlen(trimmed) == 0) continue;

        //タスク名の抽出 ($taskname)
        if (trimmed[0] == '$') {
            Nest_task_data *new_task = NULL;
            res = create_nest_task_data(&new_task);
            if (res != NSTT_SUCCESS_OK) break;

            // $ の直後から空白か { までをコピー
            char *name_start = trimmed + 1;
            char *name_end = strpbrk(name_start, " {");
            size_t len = name_end ? (size_t)(name_end - name_start) : strlen(name_start);
            strncpy(new_task->task_name, name_start, len);
            new_task->task_name[len] = '\0';

            if (ctx.root == NULL) {
                ctx.root = new_task;
            } else if (ctx.current_task != NULL) {
                // 現在のタスクの子として追加
                append_child_task(ctx.current_task, new_task);
            }
            ctx.current_task = new_task;
        }

        //ネスト開始 ({)
        if (strchr(trimmed, '{')) {
            ctx.nesting_level++;
            // 既に current_task は生成されているはずなので、特にポインタ操作はなし
        }

        //プロパティ解析
        if (strstr(trimmed, "deadline:")) {
            char *val = strchr(trimmed, ':') + 1;
            parse_deadline_string(val, &ctx.current_task->deadline_time);
        } else if (strstr(trimmed, "importance:")) {
            char *val = strchr(trimmed, ':') + 1;
            ctx.current_task->importance_level = (unsigned char)atoi(val);
        } else if (strstr(trimmed, "need_time:")) {
            char *val = strchr(trimmed, ':') + 1;
            parse_time_string(val, &ctx.current_task->need_time);
        } else if (strstr(trimmed, "worked_time:")) {
            char *val = strchr(trimmed, ':') + 1;
            parse_time_string(val, &ctx.current_task->worked_time);
        } else if (strstr(trimmed, "memo:")) {
            char *start = strchr(trimmed, '"');
            char *end = strrchr(trimmed, '"');
            if (start && end && start != end) {
                size_t len = (size_t)(end - start - 1);
                if (len >= sizeof(ctx.current_task->memo)) len = sizeof(ctx.current_task->memo) - 1;
                strncpy(ctx.current_task->memo, start + 1, len);
                ctx.current_task->memo[len] = '\0';
            }
        }

        //ネスト終了 (})
        if (strchr(trimmed, '}')) {
            ctx.nesting_level--;
            if (ctx.current_task->parent != NULL) {
                ctx.current_task = ctx.current_task->parent;
            }
        }
    }

    if (ctx.nesting_level != 0) res = NSTT_ERR_SYNTAX_BRACE_MISMATCH;

    fclose(fp);
    if (res == NSTT_SUCCESS_OK) {
        *out_root = ctx.root;
    }
    return res;
}

/* 指定した名前のタスクをツリー内から再帰的に探索する内部関数 */
static Nest_task_data* find_task_by_name_recursive(Nest_task_data *current, const char *name) {
    if (current == NULL) return NULL;

    // 自分の名前をチェック
    if (strcmp(current->task_name, name) == 0) {
        return current;
    }

    // 子要素を再帰的にチェック
    Nest_task_data *found = find_task_by_name_recursive(current->children, name);
    if (found != NULL) return found;

    // 兄弟要素（同じ階層の次）を再帰的にチェック
    return find_task_by_name_recursive(current->next, name);
}

/*特定のタスク名をサーチして、そのノードのポインタを返す */
int nstt_get_task_by_name(Nest_task_data *root, const char *name, Nest_task_data **out_task) {
    if (root == NULL || name == NULL || out_task == NULL) {
        return NSTT_ERR_INVALID_ARGUMENT;
    }

    Nest_task_data *result = find_task_by_name_recursive(root, name);
    
    if (result != NULL) {
        *out_task = result;
        return NSTT_SUCCESS_OK;
    }

    return NSTT_ERR_UNABLE_ERROR; // 見つからない場合
}



static char* trim_space(char* str) {
    char* end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return str;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
    return str;
}