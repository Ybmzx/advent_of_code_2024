# Advent of Code 2024
Advent of Code 2024 个人解题代码, 质量堪忧, 不建议参考.

语言: 部分 C++, 部分 Typescript(Deno).

## 每日记录

day01: 简单模拟, 个人难度评级: D

day02: 还是模拟, part02 一开始试图使用 $O(n)$ 的方法解, 但是想烦了就摆了, 个人难度评级: 反正没有时间限制所以 D 吧.

day03: 正则魔法! 个人难度评级: D

day04: 比前两天简单. 个人难度评级: D

day05: 调了半天都没调好才发现思路错了. 个人难度评级: C

day06: 个人难度评级: C

day07: 个人难度评级: D

day08: 个人难度评级: D

day09: 个人难度评级: C

day10: 简单 dfs/bfs, part1 一开始做错了, 然后发现这个错的程序是 part2 的答案, 个人难度评级: C

day11: 研究了半天, 没想到用 map 就能解决... 个人难度评级: C

day12: part1 bfs, part2 把两种方向的边分别排序, 然后判断数组中相邻的边是不是连着的就行了, 个人难度评级: C

day13: 解二元一次方程组, 个人难度评级: D

day14: part01 没什么好说的, part02 有点意义不明, 光说找圣诞树也没说圣诞树长什么样, 到论坛上看了下, 圣诞树大概是这样的:
```
###############################
#                             #
#                             #
#                             #
#                             #
#              #              #
#             ###             #
#            #####            #
#           #######           #
#          #########          #
#            #####            #
#           #######           #
#          #########          #
#         ###########         #
#        #############        #
#          #########          #
#         ###########         #
#        #############        #
#       ###############       #
#      #################      #
#        #############        #
#       ###############       #
#      #################      #
#     ###################     #
#    #####################    #
#             ###             #
#             ###             #
#             ###             #
#                             #
#                             #
#                             #
#                             #
###############################
```
可以发现顶上有 31 个连续的机器人, 所以直接找连续出现 31 个机器人的情况就行了, 不过这种方法也比较容易被卡, 个人难度评级: ***?***

day15: 大模拟, 调各种细节人都麻了. 个人难度评级: C

day16: 开始上难度了, 没反应过来用 dijkstra, 琢磨了好久. 个人难度评级: B

day17: p1模拟, p2 先枚举 A 为不同值的每种情况, 然后通过瞪眼法找到规律, 如果 $A = x$ 时输出为 $y$, 则 $A \in [x \times 8, (x + 1) \times 8)$ 时输出以 $y$ 结尾, $A = x$ 时输出为 $y, z$, 则 $A \in [x \times 8, (x + 1) \times 8)$ 时输出同样以 $y, z$ 结尾, 具体正确性我也没有验证, 不过我的样例是通过了, 个人难度评级: C

day18: p1 bfs, p2 建并查集倒着加边, 看这两点什么时候父节点相同, 因为没搞清坐标调了好久. 暴力也可以, 开 O2 下只花了 1.5 秒. 个人难度评级: B.

day19: 很经典的单词拆分dp. 个人难度评级: B.
