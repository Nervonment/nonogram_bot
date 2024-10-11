# Nonogram bot

一个自动求解 [Nonogram 网站](https://cn.puzzle-nonograms.com/) 上的题目的机器人.

## 用法

1. 在 [config.txt](/config.txt) 中依次填写题目的等级, 宽度, 长度和你的邮箱. (如果你是第一次使用这个网站, 请前往 [这里](https://cn.puzzle-nonograms.com/hallsubmit.php) 注册, 记得勾选 "Robot account - for testing automatic solvers".)   
下面是题目等级和宽度与长度的对照表:

    |等级|宽度|长度|
    |-|-|-|
    |0|5|5|
    |1|10|10|
    |2|15|15|
    |3|20|20|
    |4|25|25|

1. 运行 `./build.sh` 和 `./run.sh`.

## 其他

你可能会问我为什么不直接全部用 Rust 写. 因为获取题目和发送解答的代码来自于 https://gitlab.com/MHYCWasTaken/h2so4/-/tree/dabiao?ref_type=heads, 我懒得翻译成 Rust, 就直接抄过来用了.