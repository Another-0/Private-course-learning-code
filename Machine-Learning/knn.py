# -*- coding: utf-8 -*-
"""
Created on Mon Mar 15 17:17:48 2021

@author: fly
"""
import numpy as np
import csv
# KNN DEMO
# 数据归一化处理


def autoNorm(dataSet):
    minVals = dataSet.min(0)
    maxVals = dataSet.max(0)
    ranges = maxVals - minVals
    m = dataSet.shape[0]
    normDataSet = dataSet - np.tile(minVals, (1, m))
    # print normDataSet
    normDataSet = normDataSet / np.tile(ranges, (1, m))
    # print normDataSet
    return normDataSet, ranges, minVals


# 测试数据归一化


def normTest(dataSet, ranges, minVals):
    return (dataSet-minVals)/ranges

# 计算马氏距离


def covariance(X, Y):
    n = np.shape(X)[0]
    X, Y = np.array(X), np.array(Y)
    meanX, meanY = np.mean(X), np.mean(Y)
    cov = sum(np.multiply(X - meanX, Y - meanY)) / (n - 1)
    return cov


def calc_covmat1(samples):
 # 方法 1：根据协方差公式和协方差矩阵的概念计算协方差矩阵
    S = samples  # 样本集
    na = np.shape(S)[1]  # 特征 attr 总数
    covmat1 = np.full((na, na), fill_value=0.)  # 保存协方差矩阵
    for i in range(na):
        for j in range(na):
            covmat1[i, j] = covariance(S[:, i], S[:, j])
    return covmat1


def mashidis(x, dataset):
    n = x.shape[0]
    x = x.reshape([1, n])
    s = calc_covmat1(dataset)
    s = np.linalg.inv(s)
    y = np.dot(x, s)
    y = np.dot(y, x.T)
    return y[0][0]**0.5


# 分类 主体部分根据实验要求自行完成


def classify(test, dataSet, labels, k):
    # 数据预处理，归一化处理
    (m, n) = dataSet.shape
    """
    for i in range(1, n):
        dataSet[:, i], ranges, minVals = autoNorm(dataSet[:, i])
        test[i-1] = normTest(test[i-1], ranges, minVals)
    """

    # 计算距离
    dis = np.zeros([m, 4])
    dis[:, 0] = dataSet[:, 0]
    for i in range(m):
        # 欧式距离
        dis[i, 1] = np.linalg.norm(test-dataSet[i, 1:n])
        # 曼哈顿距离
        dis[i, 2] = np.linalg.norm(test-dataSet[i, 1:n], ord=1)
        # 马氏距离
        dis[i, 3] = mashidis(test-dataSet[i, 1:n], dataSet[:, 1:n])

    # 从距离中选择K个最近的,判断标签,打印结果
    mindis1 = findnn(dis[:, [0, 1]], k)
    lab1 = classifylabels(mindis1[:, 0], labels)
    print("测试数据：", test)
    print("在 K = %d 的情况下：" % k)
    print("欧式距离判断标签为 "+lab1)

    mindis2 = findnn(dis[:, [0, 2]], k)
    lab2 = classifylabels(mindis2[:, 0], labels)
    print("曼哈顿距离判断标签为 "+lab2)

    mindis3 = findnn(dis[:, [0, 3]], k)
    lab3 = classifylabels(mindis3[:, 0], labels)
    print("马氏距离判断标签为 "+lab3, end="\n\n")


# 挑选K个近邻
def findnn(dis, k):
    minn = dis[0:k, :]
    maxd = minn[:, 1].max()
    maxx = np.where(minn[:, 1] == maxd)
    for i in range(k, dis.shape[0]):
        if dis[i, 1] < maxd:
            minn[maxx, :] = dis[i, :]
            maxd = minn[:, 1].max()
            maxx = np.where(minn[:, 1] == maxd)
    return minn


# 判断标签
def classifylabels(dis, labels):
    labs = {}
    maxl = 0
    for i in range(dis.shape[0]):
        index = int(dis[i]-1)
        label = labels[index]
        if label in labs:
            labs[label] += 1
        else:
            labs[label] = 1
        maxl = labs[label] if labs[label] > maxl else maxl
    lab = list(labs.keys())[list(labs.values()).index(maxl)]
    return lab


if __name__ == '__main__':
    # 西瓜数据集
    xigua = [[1, 0.697, 0.460],
             [2, 0.774, 0.376],
             [3, 0.634, 0.264],
             [4, 0.608, 0.318],
             [5, 0.556, 0.215],
             [6, 0.403, 0.237],
             [7, 0.481, 0.149],
             [8, 0.437, 0.211],
             [9, 0.666, 0.091],
             [10, 0.243, 0.267],
             [11, 0.245, 0.057],
             [12, 0.343, 0.099],
             [13, 0.639, 0.161],
             [14, 0.657, 0.198],
             [15, 0.360, 0.370],
             [16, 0.593, 0.042],
             [17, 0.719, 0.103]]

    xigua_labels = ["是", "是", "是", "是", "是", "是", "是",
                    "是", "否", "否", "否", "否", "否", "否", "否", "否", "否"]
    """
    xigua = np.array(xigua)
    xigua_labels = np.array(xigua_labels)
    testdata = xigua[10, 1:3]
    xiguadata = xigua[[1, 3, 5, 7, 9, 11, 13, 15, 16], :]
    for k in range(3, 9, 2):
        classify(testdata, xiguadata, xigua_labels, k)
    """
    # iris数据集

    """
    with open('Iris.csv', 'r') as f:
        read = csv.reader(f)
        result = np.array(list(read))
        result = result[1:, :]
        irisdata = result[:, 0:5].astype(np.float64)
        irislabels = result[:, 5]
        testiria = irisdata[100, 1:]
        for k in range(11, 41, 10):
            classify(testiria, irisdata, irislabels, k)
    """
