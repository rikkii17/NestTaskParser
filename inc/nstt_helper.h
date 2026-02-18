#ifndef NSTT_HELPER_H
#define NSTT_HELPER_H

#include "nstt_parser_config.h"
//パーサー系のデータ型定義ヘッダー
#include "error_config.h"
//エラーコードの管理ヘッダー

/*変数構造体の生成系*/

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

 /*パース系のコード*/

static int get_next_val(const char **str, short int *result);
/* * 文字列から次の '.' までの数値を読み取り、ポインタを進める内部補助
 *　引数1: 解析前の文字列
 *　引数2: 解析の結果得られた整数値
 * 戻り値: NSTT_SUCCESS_OK(0) またはエラーコード
*/
int parse_date_string(const char *str, Date *out_date);
/* * 日付文字列(yyyy.mm.dd)をDate構造体に変換する
 * 引数1: 解析対象の文字列 ("2025.09.02" など)
 * 引数2: 結果を格納するDate構造体のポインタ
 * 戻り値: NSTT_SUCCESS_OK(0) またはエラーコード
 */

int parse_time_string(const char *str, Time *out_time);
/* * 時間文字列(h.min.ss)をTime構造体に変換する
 * 引数1: 解析対象の文字列 ("1.30.00" など)
 * 引数2: 結果を格納するTime構造体のポインタ
 * 戻り値: NSTT_SUCCESS_OK(0) またはエラーコード
 */

int parse_deadline_string(const char *str, Deadline_time *out_deadline);
/* * デッドライン文字列(yyyy.mm.dd.hh.minmin)をDeadline_time構造体に変換する
 * 引数1: 解析対象の文字列 ("2025.09.02.14.30" など)
 * 引数2: 結果を格納するDeadline_time構造体のポインタ
 * 戻り値: NSTT_SUCCESS_OK(0) またはエラーコード
 */

 //ツリー操作用の関数

int add_child_task(Nest_task_data *parent, Nest_task_data *child);

 /* * 指定したタスクを、親タスクの子リストの末尾に追加する
 * 引数1: 親となるタスクのポインタ
 * 引数2: 追加したい子タスクのポインタ
 * 戻り値: NSTT_SUCCESS_OK(0) またはエラーコード
 */

int get_root_task(Nest_task_data *current, Nest_task_data **out_root);
/* * 指定したタスクの「一番上の親（ルート）」を探して返す
 * 引数1: 起点となるタスクのポインタ
 * 引数2: ルートタスクのポインタを格納する変数へのポインタ
 * 戻り値: NSTT_SUCCESS_OK(0) またはエラーコード
 */

#endif