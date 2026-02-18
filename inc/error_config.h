#ifndef ERROR_CONFIG_H
    #define ERROR_CONFIG_H
        #define NSTT_INFO_FILE_END                101  // ファイルの終端に到達
        #define NSTT_WARN_EXTRA_CONTENT           102  // パース成功だが定義外のデータあり

    // 【 0 】完全な正常終了
        #define NSTT_SUCCESS_OK                    0   // 正常終了

    // 【負数】エラー（Critical Errors）

    // 100s: System & Resources
        #define NSTT_ERR_FILE_OPEN               -101  // ファイルオープン失敗
        #define NSTT_ERR_MALLOC_FAIL             -102  // メモリ確保失敗

    // 200s: Syntax Analysis
        #define NSTT_ERR_SYNTAX_BRACE_MISMATCH   -201  // 中括弧 {} の対応が不正
        #define NSTT_ERR_SYNTAX_INVALID_KEY      -202  // 不正なキーワード（$や<の欠落など）
        #define NSTT_ERR_SYNTAX_MISSING_SEMICOLON -203 // セミコロン忘れ
        #define NSTT_ERR_SYNTAX_MISSING_COLON    -204  // コロン分けが不正
        

    // 300s: Value Validation
        #define NSTT_ERR_VAL_OUT_OF_RANGE        -301  // 数値が範囲外 
        #define NSTT_ERR_VAL_INVALID_DATE        -302  // 日付形式が不正
        #define NSTT_ERR_VAL_INVALID_TIME        -303  // 時間形式が不正
        #define NSTT_ERR_INVALID_ARGUMENT        -304  // 引数が不正

    // 400s: Types & Options
        #define NSTT_ERR_TYPE_UNKNOWN            -401  // 未知の型指定
        #define NSTT_ERR_TYPE_MISMATCH           -402  // 型と内容の不整合

    
    //1000s Unable to identify error
        #define NSTT_ERR_UNABLE_ERROR      -1000   //不明なエラー

#endif