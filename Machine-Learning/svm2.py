# -*- coding: utf-8 -*-
"""
Created on Tue Apr  6 18:58:25 2021

@author: fly
"""
import os
import numpy as np
from sklearn import svm
from sklearn.model_selection import train_test_split
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis as LDA


def loaddata(path):
    filenames = os.listdir(path)
    num = len(filenames)
    dataset = np.zeros((num, 1024))
    labels = np.zeros((num))
    index = 0
    for filename in filenames:
        filepath = path + '/' + filename
        with open(filepath, 'r') as f:
            for i in range(32):
                fr = f.readline()
                for j in range(32):
                    dataset[index, i*32+j] = int(fr[j])
            f.close()
        labels[index] = filename.split('_')[0]
        index += 1
    return dataset, labels


def pca(data):
    m = data.shape[0]
    means = np.mean(data, axis=0)
    meandata = data-means
    cov_mat = (meandata.T*meandata)/(m-1)
    eigVals, eigVects = np.linalg.eig(cov_mat)
    eigValInd = np.argsort(eigVals)
    k = 0
    s = sum(eigVals)
    total = 0
    while(total/s < 0.99):
        k += 1
        total += eigVals[eigValInd[-k]]
    eigValInd = eigValInd[:-(k+1):-1]
    redEigVects = eigVects[:, eigValInd]
    lowdatamat = meandata*redEigVects
    return lowdatamat.real


def lda(x, y):
    model = LDA(solver='svd')
    sklearn_x = model.fit(x, y).transform(x)
    return sklearn_x


def mysvm(x, y, ga):
    p = 70
    x_train, x_test, y_train, y_test = train_test_split(
        x, y, random_state=1, train_size=p/100)
    print("训练集数据占比 %d%%" % p)
    clf1 = svm.SVC(C=1, kernel='rbf', gamma=ga)
    clf1.fit(x_train, y_train.ravel())
    print("高斯核分类准确率：%f" % clf1.score(x_test, y_test))
    clf2 = svm.SVC(C=1, kernel="linear")
    clf2.fit(x_train, y_train.ravel())
    print("线性分类准确率：%f" % clf2.score(x_test, y_test))
    clf3 = svm.SVC(C=1, kernel='poly')
    clf3.fit(x_train, y_train.ravel())
    print("多项式核分类准确率：%f" % clf3.score(x_test, y_test))


if __name__ == '__main__':
    path = "C:/Users/fly/Desktop/机器学习/实验四/trainingDigits"
    data, labels = loaddata(path)
    #lowdata = pca(np.mat(data))
    #mysvm(lowdata, labels, ga=0.002)
    lowdata = lda(data, labels)
    mysvm(lowdata, labels, 0.1)
