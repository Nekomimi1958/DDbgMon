# Dual Debug Monitor (DDbgMon.exe)

## 概要

プロセスIDを指定して、そのデバッグ出力(OutputDebugString)を表示します。

## 使い方

対象アプリケーションのクラス名(Class)やタイトルバーテキスト(Text)を入力して[Find Process]ボタンを押すと、それにマッチするプロセスID(PID)を取得できます。  
あるいは、[Find Process]ボタンの上にあるターゲットアイコンをドラッグして、対象アプリケーションのウィンドウを選びます。  

プロセスIDが指定できたら、[Start]ボタンを押してください。  
OutputDebugString の内容が右側のリストに表示されます。  
[Pause/Resume]ボタンで休止/再開、[Ptop]ボタンで監視を終了します。  

## オプション設定

[Option]タブで表示などに関する設定を行えます。  
