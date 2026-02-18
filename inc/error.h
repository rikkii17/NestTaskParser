#ifndef ERROR_H
    #define ERROR_H

    // 【正数】成功 + 情報（Warning / Info）
    #define NSTT_SUCCESS_WITH_EXTRA_CONTENT    2  // パースは成功したが、定義外の文字列が含まれていた
    #define NSTT_SUCCESS_FILE_END              1  // ファイルの終端に到達して正常終了

    // 【 0 】完全な正常終了
    #define NSTT_SUCCESS_OK                    0  // 異常なし

    // 【負数】エラー（Critical Errors）
    #define NSTT_ERR_FILE_OPEN                -1  // ファイルオープン失敗
    #define NSTT_ERR_MALLOC_FAIL              -2  // メモリ確保失敗
    #define NSTT_ERR_SYNTAX_BRACE_MISMATCH    -10 // 中括弧 {} の対応が不正
    #define NSTT_ERR_SYNTAX_INVALID_KEY       -11 // 不正なキーワード
    #define NSTT_ERR_SYNTAX_MISSING_SEMICOLON -12 // セミコロン忘れ
    #define NSTT_ERR_VALUE_OUT_OF_RANGE       -20 // 重要度(1-255)などの値が範囲外
    #define NSTT_ERR_INVALID_DATE_FORMAT      -30 // 日付の形式が不正
    #define NSTT_ERR_INVALID_TIME_FORMAT      -31 // 時間の形式が不正
    #define NSTT_ERR_UNKNOWN_TYPE             -40 // オプションの型指定が不明

#endif