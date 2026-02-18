#ifndef NSTT_HELPER_H
#define NSTT_HELPER_H

#include "nstt_parser_config.h"
//パーサー系のデータ型定義ヘッダー
#include "error_config.h"
//エラーコードの管理ヘッダー

int create_nest_task_data(Nest_task_data **out_task);
/* * 新しいタスク構造体をメモリ確保して初期化する
 * 引数1: 生成された構造体のポインタを格納するためのポインタ
 * 戻り値: NSTT_SUCCESS_OK(0) またはエラーコード(負数)
 */
 
int append_child_task(Nest_task_data *parent, Nest_task_data *child);
/* * 親タスクに子タスクを追加する
 * 引数1: 親となるタスクのポインタ
 * 引数2: 追加する子タスクのポインタ
 * 戻り値: NSTT_SUCCESS_OK(0) またはエラーコード(負数)
*/

int add_option_data(Nest_task_data *task, const char *word, var content);
/* * タスクにオプションデータを追加する
 * 引数1: 対象のタスクのポインタ
 * 引数2: オプション名（文字列）
 * 引数3: 格納するデータ構造体
 * 戻り値: NSTT_SUCCESS_OK(0) またはエラーコード(負数)
 */

#endif