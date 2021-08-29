# -*- coding: utf-8 -*-
"""
Created on Tue Mar 23 16:32:35 2021

@author: fly
"""
import numpy as np
import matplotlib.pyplot as plt
import random


# 数据导入demo
def loadDataSet(fileName):  # general function to parse tab -delimited floats
    dataMat = []  # assume last column is target value
    fr = open(fileName)
    for line in fr.readlines():
        curLine = line.strip().split()
        fltLine = list(map(float, curLine))  # map all elements to float()
        dataMat.append(fltLine)
    return dataMat


# 距离计算demo
def distEclud(vecA, vecB):
    return np.linalg.norm(vecA-vecB, ord=2)


# 生成随机质心demo
def randCent(dataSet, k):
    n = dataSet.shape[1]
    centroids = np.mat(np.zeros([k, n]))  # create centroid mat
    for j in range(n):  # create random cluster centers, within bounds of each dimension
        minJ = min(dataSet[:, j])
        rangeJ = float(max(dataSet[:, j]) - minJ)
        centroids[:, j] = np.mat(minJ + rangeJ * np.random.rand(k, 1))
    return centroids


# 生成新的质心
def creatnewCent(dataSet, labels, k):
    n = dataSet.shape[1]
    centroids = np.mat(np.zeros([k, n]))
    for i in range(k):
        cuindex = np.array(np.where(labels == i)).flatten()
        cu = dataSet[cuindex, :]
        for j in range(n):
            centroids[i, j] = np.mean(cu[:, j])
    return centroids


# 绘制Kmeans结果
def paint(dataSet, labels, k):
    for i in range(k):
        cuindex = np.array(np.where(labels == i)).flatten()
        cu = dataSet[cuindex, :]
        plt.scatter(cu[:, 0], cu[:, 1], c=randomcolor())


# 生成随机颜色
def randomcolor():
    colorArr = ['1', '2', '3', '4', '5', '6', '7',
                '8', '9', 'A', 'B', 'C', 'D', 'E', 'F']
    color = ''
    for i in range(6):
        color += colorArr[random.randint(0, 14)]
    return '#'+color


# 计算WSS
def kwss(dataSet, centroids, labels, k):
    s = 0
    ks = 0
    for i in range(k):
        cuindex = np.array(np.where(labels == i)).flatten()
        cu = dataSet[cuindex, :]
        if (centroids[i] != np.NaN).all:
            for j in range(cu.shape[0]):
                ks += (distEclud(cu[j, :], centroids[i]))**2
        s += ks
        ks = 0
    return s


# K均值聚类
def kMeans(dataSet, k):
    m = dataSet.shape[0]
    cent = randCent(dataSet, k)
    lastlab = np.zeros(m)
    labels = np.zeros(m)
    dist = []
    maxtimes = 500
    x = 1
    while True:
        for i in range(m):
            for j in range(k):
                dist.append(distEclud(dataSet[i, :], cent[j, :]))
            mindist = min(dist)
            labels[i] = dist.index(mindist)
            dist = []
        if np.all(lastlab == labels) or x >= maxtimes:
            centroids = cent
            clusterAssment = labels
            break
        cent = creatnewCent(dataSet, labels, k)
        lastlab = np.array(labels)
        x += 1
    return centroids, clusterAssment  # 返回质心 聚类结果


if __name__ == '__main__':
    dataSet = np.array(loadDataSet("xiguadata3.txt"))[:, 1:]
    x = []
    y = []
    for k in range(7, 8):
        centroids, clusterAssment = kMeans(dataSet, k)
        paint(dataSet, clusterAssment, k)
        x.append(k)
        y.append(kwss(dataSet, centroids, clusterAssment, k))
    #plt.plot(x, y)
