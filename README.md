# lpslither

スリザーリンクの問題をIPソルバで解かせるための変換プログラム
（とそのビジュアライザ）です．

## お願い

かなり雑なC++（という名のC）で書きました．
バグがあっても私は責任を負いません．保守もしません．

商用利用は不可です．学校の課題の回答としてこれをそのまま送るのは不可です．
それ以外は良識の範囲内で自由に使ってください．
ただし，このソースを利用したということをどこかに含めてくれると私が
少し幸せになります．

## 使い方

```
$ make
$ ./lpslither < sample.dat > sample.lp
```
で（超簡単な）サンプルの問題を整数計画問題に直します．

適当なIPソルバで実行し，その結果を`sample.sol`に書いたとすると，
```
$ ./visualizer sample.dat sample.sol
+-+-+-+-+-+
|3 . . . 3|
+-+-+-+-+-+
```
というふうに結果を見ることができます．
（私はGurobiでしか動作を確認していません）

問題ファイルの形式は次の方式を採用しています．
```
H W
[問題の盤面]
```
`H`は盤面の高さ，`W`は幅を指定します．
問題の盤面の内容は，数字の書いてあるところにその数字を，
空白のマスには`.`を書きます．
技術的な理由で，`3`がない盤面には対応していません．

## 整数計画問題化の方針

あとで気が向いたら書く
