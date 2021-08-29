# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import numpy as np
import numpy.matlib  # 子包不单独导入

# 数组创建及操作

# 1 - 使用 numpy 生成（0，1）随机数组，长度为 24
ranx = np.random.rand(24)

# 2 - 将得到的数组 reshape 成为 3*8 的矩阵形式
ranm1 = ranx.reshape(3, 8)

# 3 - 将 2 中的矩阵展平为一维数组
zhanp2 = ranm1.flatten()
zhanp1 = np.ravel(ranm1)

# 4 - 将 3 中的数组 reshape 成为 4*6 的矩阵形式
ranm2 = zhanp1.reshape(4, 6)

# 5 - 截取 4 中矩阵的前 3 行，第 2 到第 6 列，得到 3*5 的矩阵
ranm3 = ranm2[0:3, 1:6]

# 6 - 输出 5 矩阵中大于 0.5 的元素的值及其行列值
for i in range(3):
    for j in range(5):
        if ranm3[i][j] > 0.5:
            print("%f , (%d , %d)" % (ranm3[i][j], i+1, j+1))


# 矩阵计算

# 1 - 创建全 0 数组 a，形状为 4x4；
a = np.matlib.zeros((4, 4))

# 2 - 创建 1-12 间隔为 1 的数组 b，形状为 4x3；
b = np.arange(1, 13, 1).reshape(4, 3)  # 左闭右开

# 3 - 创建对角矩阵 c，形状为 3x4。
c = np.matlib.eye(3, 4)

# 4 - 使用矩阵 b，c 完成矩阵相乘计算,得到 4 x 4 矩阵。
d = b * c

# 5 - 将相乘得到的 4 x 4 矩阵拷贝到矩阵 a。
a = d

# 二维有序数组查找
x = [
    [1, 4, 7, 11, 15],
    [2, 5, 8, 12, 19],
    [3, 6, 9, 16, 22],
    [10, 13, 14, 17, 24],
    [18, 21, 23, 26, 30]
]

n = 24


def searchm(x, a):
    t = np.array(x)
    (m, n) = t.shape

    i = 0
    j = m-1
    while i < n and j > 0:
        if t[i][j] == a:
            print("True (%d,%d)" % (i+1, j+1))
            return True
        if t[i][j] < a:
            i += 1
        else:
            j -= 1
    print("false")
    return False


searchm(x, n)
