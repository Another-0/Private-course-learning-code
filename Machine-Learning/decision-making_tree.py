import numpy as np
from math import log
import operator
import copy
from matplotlib.font_manager import FontProperties
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split


"""
函数说明：计算给定数据集的经验熵（香农熵）
Parameters：
 dataSet：数据集
Returns：
 shannonEnt：经验熵
"""


def calcShannonEnt(dataSet):
    shannonEnt = 0
    m = dataSet.shape[0]
    pdata = dataSet[:, -1].ravel()
    labcount = {}
    for i in pdata:
        if i not in labcount.keys():
            labcount[i] = 0
        labcount[i] += 1
    for v in labcount.values():
        pk = v/m
        shannonEnt -= pk*log(pk, 2)
    return shannonEnt  # 返回经验熵


"""
函数说明：创建数据集
Parameters：无
Returns：
 dataSet：数据集
 labels：分类属性
"""


def createDataSet():
    # 数据集需要按照实验要求替换为指定数据集
    datas = []
    labels = {1: [1, 2, 3], 2: [1, 2], 3: [1, 2], 4: [1, 2]}
    with open('lenses.data', 'r') as f:
        for line in f.readlines():
            line = [int(i) for i in line.split()]
            datas.append(line)
        f.close()
    dataSet = np.array(datas)
    return dataSet, labels


"""
函数说明：划分数据集为训练数据集和测试数据集
Paramaters:
    dataSet:待划分的数据集
return：
    trainData:训练数据集
    testData：测试数据集u
"""


def classfiy(dataSet):
    trainData, testData = train_test_split(
        dataSet, test_size=0.25, random_state=12)
    return trainData, testData


"""
函数说明：按照给定特征划分数据集
Parameters：
 dataSet:待划分的数据集
 axis：划分数据集的特征
 value：需要返回的特征值
Returns：
 返回划分后的数据集
"""


def splitDataSet(dataSet, axis, value):
    retDataSet = dataSet[dataSet[:, axis] == value]
    retDataSet = np.delete(retDataSet, axis, axis=1)
    # 返回划分后的数据集
    return retDataSet


def chooseBestFeatureToSplit(dataSet):
    # 这里调用 calcShannonEnt 函数来计算熵
    EntD = calcShannonEnt(dataSet)
    Gains = []
    (m, n) = dataSet.shape
    for axis in range(1, n-1):
        values = np.unique(dataSet[:, axis])
        s = 0
        for value in values:
            retDataSet = splitDataSet(dataSet, axis, value)
            EntDv = calcShannonEnt(retDataSet)
            mv = retDataSet.shape[0]
            s += mv*EntDv/m
        Gains.append(EntD - s)
    print(Gains)
    index = np.argsort(Gains)
    bestFeature = index[-1]+1
    # 返回信息增益最大特征的索引值
    return bestFeature


"""
函数说明：统计 classList 中出现次数最多的元素（类标签）
Parameters：
 classList：类标签列表
 s:选择输出最多元素标签还是元素数目
Returns：
 sortedClassCount[0][s]：出现次数最多的元素（类标签）
"""


def majorityCnt(classList, s):
    classCount = {}
    # 统计 classList 中每个元素出现的次数
    for vote in classList:
        if vote not in classCount.keys():
            classCount[vote] = 0
        classCount[vote] += 1
        # 根据字典的值降序排列
    sortedClassCount = sorted(
        classCount.items(), key=operator.itemgetter(1), reverse=True)
    return sortedClassCount[0][s]


"""
函数说明：创建决策树
Parameters:
 dataSet：训练数据集
 labels：分类属性标签
 featLabels：存储选择的最优特征标签
Returns：
 myTree：决策树
"""


def createTree(dataSet, labels, featLabels):
    myTree = {}
    tempLabels = copy.deepcopy(labels)
    # 样本属于同一类
    if np.all(dataSet[:, -1] == dataSet[0, -1]):
        return dataSet[0, -1]
    # 属性集为空或者数据集在样本集上取值相同
    if tempLabels == {} or np.unique(dataSet[:, 1:-1], axis=0).shape[0] == 1:
        label = majorityCnt(dataSet[:, -1], 0)
        return label

    # 预剪枝判断
    bestFeature = chooseBestFeatureToSplit(dataSet)
    feature = list(tempLabels.keys())[bestFeature-1]
    prep = majorityCnt(dataSet[:, -1], 1)/dataSet.shape[0]
    nowp = 0
    tempLabels_p = copy.deepcopy(tempLabels)
    tempLabels_p.pop(feature)
    indexdata = np.unique(dataSet[:, bestFeature])
    for value in indexdata:
        retDataSet = splitDataSet(dataSet, bestFeature, value)
        nowp += majorityCnt(dataSet[:, -1], 1)/dataSet.shape[0]
    if prep >= nowp:
        print("剪枝")
        return majorityCnt(dataSet[:, -1], 0)

    # 迭代划分
    upTree = {feature: myTree}
    tempLabels.pop(feature)
    for value in indexdata:
        retDataSet = splitDataSet(dataSet, bestFeature, value)
        myTree[value] = createTree(retDataSet, tempLabels, featLabels)
    featLabels.append(feature)
    return upTree


"""
函数说明：获取决策树叶子节点的数目
Parameters：
 myTree：决策树
Returns：
 numLeafs：决策树的叶子节点的数目
"""


def getNumLeafs(myTree):
    numLeafs = 0
    firstStr = next(iter(myTree))
    secondDict = myTree[firstStr]
    for key in secondDict.keys():
        if type(secondDict[key]).__name__ == 'dict':
            numLeafs += getNumLeafs(secondDict[key])
        else:
            numLeafs += 1
    return numLeafs


"""
函数说明:获取决策树的层数
Parameters:
 myTree:决策树
Returns:
 maxDepth:决策树的层数
"""


def getTreeDepth(myTree):
    maxDepth = 0  # 初始化决策树深度
    # python3 中myTree.keys()返回的是dict_keys, 不在是list, 所 以 不 能 使 用 myTree.keys()[0] 的方法获取结点属性，可以使用list(myTree.keys())[0]
    firstStr = next(iter(myTree))
    secondDict = myTree[firstStr]  # 获取下一个字典
    for key in secondDict.keys():
        if type(secondDict[key]).__name__ == 'dict':  # 测试该结点是否为字典，如果不是字典，代表此结点为叶子结点
            thisDepth = 1 + getTreeDepth(secondDict[key])
        else:
            thisDepth = 1
        if thisDepth > maxDepth:
            maxDepth = thisDepth  # 更新层数
    return maxDepth


"""
函数说明:绘制结点
Parameters:
 nodeTxt - 结点名
 centerPt - 文本位置
 parentPt - 标注的箭头位置
 nodeType - 结点格式
Returns:
 无
"""


def plotNode(nodeTxt, centerPt, parentPt, nodeType):
    arrow_args = dict(arrowstyle="<-")  # 定义箭头格式
    font = FontProperties(
        fname=r"c:\windows\fonts\simsun.ttc", size=14)  # 设置中文字体
    createPlot.ax1.annotate(nodeTxt, xy=parentPt, xycoords='axes fraction',  # 绘制结点
                            xytext=centerPt, textcoords='axes fraction',
                            va="center", ha="center", bbox=nodeType, arrowprops=arrow_args, FontProperties=font)


"""
函数说明:标注有向边属性值
Parameters:
 cntrPt、parentPt - 用于计算标注位置
 txtString - 标注的内容
Returns:
无
"""


def plotMidText(cntrPt, parentPt, txtString):
    xMid = (parentPt[0]-cntrPt[0])/2.0 + cntrPt[0]  # 计算标注位置
    yMid = (parentPt[1]-cntrPt[1])/2.0 + cntrPt[1]
    createPlot.ax1.text(xMid, yMid, txtString, va="center",
                        ha="center", rotation=30)


"""
函数说明:绘制决策树
Parameters:
 myTree - 决策树(字典)
 parentPt - 标注的内容
 nodeTxt - 结点名
Returns:
 无
"""


def plotTree(myTree, parentPt, nodeTxt):
    decisionNode = dict(boxstyle="sawtooth", fc="0.8")  # 设置结点格式
    leafNode = dict(boxstyle="round4", fc="0.8")  # 设置叶结点格式
    numLeafs = getNumLeafs(myTree)  # 获取决策树叶结点数目，决定了树的宽度
    depth = getTreeDepth(myTree)  # 获取决策树层数
    firstStr = next(iter(myTree))  # 下个字典
    cntrPt = (plotTree.xOff + (1.0 + float(numLeafs)) /
              2.0/plotTree.totalW, plotTree.yOff)  # 中心位置
    plotMidText(cntrPt, parentPt, nodeTxt)  # 标注有向边属性值
    plotNode(firstStr, cntrPt, parentPt, decisionNode)  # 绘制结点
    secondDict = myTree[firstStr]  # 下一个字典，也就是继续绘制子结点
    plotTree.yOff = plotTree.yOff - 1.0/plotTree.totalD  # y 偏移
    for key in secondDict.keys():
        if type(secondDict[key]).__name__ == 'dict':
            # 测试该结点是否为字典，如果不是字典，代表此结点为叶子结点
            plotTree(secondDict[key], cntrPt, str(key))  # 不是叶结点，递归调用继续绘制
        else:
           # 如果是叶结点，绘制叶结点，并标注有向边属性值
            plotTree.xOff = plotTree.xOff + 1.0/plotTree.totalW
            plotNode(secondDict[key], (plotTree.xOff,
                     plotTree.yOff), cntrPt, leafNode)
            plotMidText((plotTree.xOff, plotTree.yOff), cntrPt, str(key))
    plotTree.yOff = plotTree.yOff + 1.0/plotTree.totalD


"""
函数说明:创建绘制面板
Parameters:
 inTree - 决策树(字典)
Returns:
 无
"""


def createPlot(inTree):
    fig = plt.figure(1, facecolor='white')  # 创建 fig
    fig.clf()  # 清空 fig
    axprops = dict(xticks=[], yticks=[])
    createPlot.ax1 = plt.subplot(111, frameon=False, **axprops)  # 去掉 x、y 轴
    plotTree.totalW = float(getNumLeafs(inTree))  # 获取决策树叶结点数目
    plotTree.totalD = float(getTreeDepth(inTree))  # 获取决策树层数
    plotTree.xOff = -0.5/plotTree.totalW
    plotTree.yOff = 1.0  # x 偏移
    plotTree(inTree, (0.5, 1.0), '')  # 绘制决策树
    plt.show()


"""
函数说明：测试决策树
Parameters:
    myTree:决策树字典
    testData：测试数据集
Returns：
    无
"""


def testTree(myTree, testData):
    m = testData.shape[0]
    s = 0
    for i in range(m):
        notfind = 0
        tempTree = myTree
        while type(tempTree).__name__ == 'dict':
            arr = list(tempTree.keys())[0]
            tempTree = tempTree[arr]
            arrvalue = testData[i, arr]
            if arrvalue not in tempTree.keys():
                notfind = 1
                break
            else:
                tempTree = tempTree[arrvalue]
        if notfind == 0 and tempTree == testData[i, -1]:
            s += 1
    p = s/m*100
    print("决策树分类准确率：%.2f" % p)


if __name__ == '__main__':
    dataSet, labels = createDataSet()
    trainData, testData = classfiy(dataSet)
    featLabels = []
    myTree = createTree(trainData, labels, featLabels)
    createPlot(myTree)
    testTree(myTree, testData)
