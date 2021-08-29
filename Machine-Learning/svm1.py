# -*- coding: utf-8 -*-
"""
Created on Tue Mar 30 18:54:03 2021

@author: fly
"""

from sklearn import svm
import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
from matplotlib import colors
from sklearn.model_selection import train_test_split
from sklearn import datasets


def load_data():
    iris = datasets.load_iris()
    return iris["data"], iris["target"]


def mysvm(x, y):
    x_train, x_test, y_train, y_test = train_test_split(
        x, y, random_state=1, train_size=0.82)
    clf1 = svm.SVC(C=0.4, kernel="linear", decision_function_shape="ovr")
    clf1.fit(x_train, y_train.ravel())
    print("线性分类准确率：%f" % clf1.score(x_test, y_test))
    draw(clf1, x)
    clf2 = svm.SVC(C=0.8, kernel='rbf', gamma=20,
                   decision_function_shape='ovr')
    clf2.fit(x_train, y_train.ravel())
    print("高斯核分类准确率：%f" % clf2.score(x_test, y_test))
    draw(clf2, x)


def draw(clf, x):
    x1_min, x1_max = x[:, 0].min(), x[:, 0].max()  # 第 0 列的范围
    x2_min, x2_max = x[:, 1].min(), x[:, 1].max()  # 第 1 列的范围
    x1, x2 = np.mgrid[x1_min:x1_max:200j, x2_min:x2_max:200j]  # 生成网格采样点
    grid_test = np.stack((x1.flat, x2.flat), axis=1)  # 测试点
    # 设置默认字体
    mpl.rcParams['font.sans-serif'] = [u'SimHei']
    mpl.rcParams['axes.unicode_minus'] = False
    # 绘制
    cm_light = colors.ListedColormap(['#A0FFA0', '#FFA0A0', '#A0A0FF'])
    cm_dark = colors.ListedColormap(['g', 'r', 'b'])
    grid_hat = clf.predict(grid_test)  # 预测分类值
    grid_hat = grid_hat.reshape(x1.shape)  # 使之与输入的形状相同
    plt.pcolormesh(x1, x2, grid_hat, shading='auto', cmap=cm_light)
    plt.scatter(x[:, 0], x[:, 1], c=labels,
                edgecolors='k', s=50, cmap=cm_dark)
    plt.xlabel(u'花萼长度', fontsize=13)
    plt.ylabel(u'花萼宽度', fontsize=13)
    plt.xlim(x1_min, x1_max)
    plt.ylim(x2_min, x2_max)
    plt.title(u'鸢尾花 SVM 二特征分类', fontsize=15)
    plt.show()


if __name__ == '__main__':
    dataset, labels = load_data()
    mysvm(dataset[:, :2], labels)
