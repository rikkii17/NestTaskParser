NestTaskParser (NSTT Parser)NestTaskParserは、階層構造（ネスト）を持つタスク定義ファイル（.nstt形式）を効率的に解析し、C言語の構造体としてメモリ上に動的展開するための軽量なパーサーライブラリだよ。1. プロジェクト概要このプロジェクトは、単純なリスト形式では管理しきれない「プロジェクト > サブプロジェクト > 具体的なタスク」といった複雑な親子関係を持つタスク群を、直感的なテキスト形式で定義し、プログラムから容易に制御できるように設計されているんだ。開発言語: C11（標準的なC言語の機能を活用）ビルドシステム: CMake（マルチプラットフォームに対応）主な機能:再帰的なタスク階層のパース: 無制限に近い深さのネスト構造を、親・子・兄弟の関係性を維持したまま解析。標準パラメータの自動変換: 期限（Deadline）、重要度（Importance）、工数（Time）などの文字列を、プログラムで計算可能な数値型へ自動変換。柔軟な拡張オプション: <option_word>(型名):内容; という形式で、ユーザー独自のカスタムデータをタスクに付与可能。強力な検索機能: ルートからツリー全体を再帰的に巡回し、特定のタスク名を持つノードを高速に特定。2. NSTT ファイルフォーマットの詳細.nsttファイルは、視認性と編集のしやすさを両立した独自フォーマットだよ。タスク名の宣言には $ を使い、そのプロパティや子タスクは {} 内に記述するルールになっているんだ。$メインプロジェクト
{
    deadline:2025.12.31.23.59;    // yyyy.mm.dd.hh.minmin 形式
    importance:100;               // 1-255 の重要度
    need_time:10.30.00;           // 10時間30分00秒の予定工数
    worked_time:02.15.00;         // すでに2時間15分作業済み
    memo:"プロジェクト全体の概要をここに記載します";

    $設計フェーズ
    {
        deadline:2025.10.15.18.00;
        importance:255;
        <budget>(INT):50000;      // 拡張オプションの例
        
        $基本設計図の作成
        {
            importance:200;
            need_time:05.00.00;
        }
    }
}
3. 実装の深掘り柔軟なデータ構造 (The Hybrid Tree Structure)内部では Nest_task_data 構造体が中心となり、ツリー構造と双方向リストを組み合わせたハイブリッドな管理を行っているよ。垂直方向 (Hierarchy): parent と children ポインタにより、親タスクと最初の子タスクを繋ぐ。水平方向 (Sibling): next と prev ポインタにより、同じ階層にあるタスク同士を双方向リストとして管理。この構造により、「あるタスクの全子要素を走査する」「親に遡ってステータスを更新する」といった処理が、ポインタを辿るだけで非常に高速に行えるのが特徴なんだ。解析アルゴリズムと堅牢性nstt_parser.c の解析エンジンは、行指向のステートマシンとして動作するよ。行の正規化: fgets で取得した生データから trim_space を用いてインデントや改行を除去し、純粋な命令語のみを抽出。コンテキスト管理: nstt_Parser_Context が現在の解析行数やネストの深さを常に監視。これにより、中括弧の閉じ忘れなどの構文エラーを即座に検知できるよ。動的バインディング: 解析中に新しいタスクを見つけると、即座にヒープ領域にメモリを確保。append_child_task 関数が、現在のコンテキストに基づいて適切な親子関係のリンクを自動的に生成するんだ。厳密な型チェック: 日付や時間は単なる文字列としてではなく、short int 型のメンバを持つ構造体へ変換される。この際、秒が60以上になっていないかなどの論理チェックも行っているよ。4. 使い方 (Usage Guide)基本的なパースの流れファイルからデータを読み込み、メモリ上のツリー構造にアクセスする最も標準的な実装例だよ。#include <stdio.h>
#include "nstt_parser.h"

int main() {
    Nest_task_data *root = NULL;
    
    // ファイルを解析してメモリ上に展開
    int result = nstt_parse_file("project_plan.nstt", &root);

    if (result == NSTT_SUCCESS_OK) {
        printf("解析成功！ルートタスク名: %s\n", root->task_name);
        
        // 階層を辿る例：最初の子要素の名前を表示
        if (root->children) {
            printf("最初の子タスク: %s\n", root->children->task_name);
        }
    } else {
        // エラーコードに基づいて詳細なメッセージを表示可能
        fprintf(stderr, "パースエラーが発生しました (ErrorCode: %d)\n", result);
    }
    
    return 0;
}
再帰検索によるタスク特定膨大なタスクツリーの中から、特定の名前を持つタスクを探し出す方法だよ。検索は深さ優先で再帰的に行われるんだ。Nest_task_data *found_task = NULL;
const char *search_name = "基本設計図の作成";

// root配下から再帰的に検索
int search_res = nstt_get_task_by_name(root, search_name, &found_task);

if (search_res == NSTT_SUCCESS_OK && found_task != NULL) {
    printf("タスク発見: %s\n", found_task->task_name);
    printf("工数: %02d:%02d:%02d\n", 
           found_task->need_time.hour, 
           found_task->need_time.minute, 
           found_task->need_time.second);
}
5. ビルドと導入環境CMakeを利用して、既存のプロジェクトに簡単に組み込むことができるよ。# ビルドディレクトリの作成とコンパイル
mkdir build && cd build
cmake ..
make
出力: 静的ライブラリ libnstt_parser.a依存関係: 標準Cライブラリのみを使用しているため、組み込み環境などでも動作させやすい設計だよ。6. 詳細エラーコード表トラブルシューティングの際は、戻り値を以下の表と照らし合わせてね（inc/error_config.h に詳細が定義されているよ）。エラーコード定数名発生原因の例-101NSTT_ERR_FILE_OPENファイルパスが間違っている、または権限がない。-102NSTT_ERR_MALLOC_FAILメモリ不足により構造体の生成に失敗。-201NSTT_ERR_SYNTAX_BRACE_MISMATCH{ に対して } が足りない、または多すぎる。-301NSTT_ERR_VAL_OUT_OF_RANGE分や秒に 60 以上の値が指定されているなど。-302NSTT_ERR_VAL_INVALID_DATE日付のフォーマット（ドット区切り）が正しくない。Produced by NestTaskParser Project.高機能かつ軽量なタスク解析ソリューションを提供します。