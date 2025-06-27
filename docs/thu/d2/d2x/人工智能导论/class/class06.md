第6周课程

卷积和全连接神经网络

## 全连接网络




# 卷积网络



## 习题

![alt text](image.png)



## 池化
一种降维的方法

平均池化和最大化池化

## LetNet

yang lecun发明的

Impact:
LeNet was one of the first CNN architectures to show the power of deep learning, particularly in computer vision tasks.

It laid the foundation for more advanced architectures like AlexNet, VGG, and ResNet, which have achieved remarkable success in image classification, object detection, and other areas of deep learning.

## VGG-16

为什么使用64，128这样的数字
和计算机体系结构有关，二进制为基础

in VGG-16,the picture is 224x224x3,but the input of the network is 224x224x64,why

So, in short, the 224x224x64 is not the input image size, but the output from the first convolutional layer after processing the initial input image of 224x224x3. The 64 represents the number of filters applied in the first convolution layer, which generate 64 different feature maps.

So, in short, the 224x224x64 is not the input image size, but the output from the first convolutional layer after processing the initial input image of 224x224x3. The 64 represents the number of filters applied in the first convolution layer, which generate 64 different feature maps.


## 神经网络遇到的两大问题

### 梯度消失问题

#### GOOGLENET


GoogLeNet 的L大写，用来致敬LeNet
引入了梯度消失层

#### ResNet

在1000层以内都没有梯度消失问题

为什么不能设计一个激活函数，梯度大于1？
梯度大于1就是指数增长，会爆炸



### 过拟合问题
#### Dropout
Dropout is a regularization technique used in neural networks to prevent overfitting. It works by randomly setting a fraction of the input units to zero at each update during training time, which helps to break the co-adaptation of neurons. This means that the model cannot rely on any specific neuron, and must learn more robust features that are useful in conjunction with many different random subsets of the other neurons.

期权
#### 期权
期权是一种金融衍生工具，赋予持有者在特定时间以特定价格买入或卖出标的资产的权利，但没有义务。期权广泛应用于风险管理和投资策略中。
期权的主要类型包括看涨期权（Call Option）和看跌期权（Put Option）。看涨期权允许持有者在到期日或之前以执行价格购买标的资产，而看跌期权则允许持有者以执行价格出售标的资产。
公式
期权的价值通常由两个部分组成：内在价值和时间价值。内在价值是指期权在当前市场条件下的实际价值，而时间价值则反映了期权到期前可能获得的额外收益。
期权定价模型，如Black-Scholes模型，提供了一种计算期权理论价值
的方法，考虑了标的资产价格、执行价格、无风险利率、波动率和到期时间等因素。
期权的数学公式如下：
- 内在价值（Call Option） = max(0, S - K)
- 内在价值（Put Option） = max(0, K - S)    
- 时间价值 = 期权价格 - 内在价值


