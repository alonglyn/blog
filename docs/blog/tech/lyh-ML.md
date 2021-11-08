# 李宏毅机器学习视频课程

[b站链接](https://www.bilibili.com/video/BV1Wv411h7kN?p=34)
[]# chapter2

﻿
第二节 机器学习任务攻略 P10 - 14:49
﻿






模型训练出来，的验证集效果不好。

第一，首先考虑的是模型本身， 是不是model bias， 也即模型（结构）不够合适。（function set 太小）

第二，或者是优化问题， 即模型不能优化到更低的function set。（即便存在）



我们可以用一些简单的模型，比如svm。 这些模型往往能保证 有一个很低的loss。

如果深度模型的loss。比这些高。

那就要考虑从以上两个角度去优化。



﻿
类神经网络训练不起来怎么办(二) 批次 (batch... P12 - 14:17
﻿

由于在GPU上运算， batch越大其实一个epoch的时间是会更短的。

但是batch越大， optimization的效果就会越差。因此在validation上的准确率没有小batch好。





﻿
类神经网络训练不起来怎么办(二) 批次 (batch... P12 - 18:27
﻿




Flat Minima  和Sharp Minima。

我们认为flat的minima，更容易在Validation上得到更好的结果。





大小Batch的总结






当然也有针对大batch的优化方法。

﻿
类神经网络训练不起来怎么办(二) 批次 (batch... P12 - 22:38
﻿






## Adam梯度下降。 动态的 Learning rate + momentum。

﻿
类神经网络训练不起来怎么办(三) 自动调整学习率... P13 - 23:00
﻿






## learning rate schedual。 decay or warm up

﻿
类神经网络训练不起来怎么办(三) 自动调整学习率... P13 - 29:31
﻿




warm up 类似TCP的快重启。



## 总结

﻿
类神经网络训练不起来怎么办(三) 自动调整学习率... P13 - 36:20
﻿






# batch_normalization.

为什么需要做正则





# self-attention  



一个比较经典的任务是 seq2seq 的任务即输入和输出序列的长度是一样的。（例如， 对于一段句子的词性标注, Sequence Labeling， 标记一段句子中一个）



语音辨识的时候， 由于向量序列的长度L非常大。 而在计算attention的时候会有L*L复杂度的计算量。所以我们常常会做trunk(也就是每个位置的attention矩阵只考虑window_size的大小）





On the Relationship between Self-Attention and Convolutional Layers 用数学方法证明了其实CNN就是Self-Attention的一个子集





self-A vs RNN. 



RNN 是一个记忆网络， 把上一步的输出作为隐藏层输入到下一个向量的处理中。

RNN 是基于顺序的， 会受到方向和顺序的影响，不能并行。

而self-attention则可以做到这一点。



self-attiontion也可以完全



这就说明了 自注意力的出现self-attention is all your need. 



# Transformer



Seq2Seq



很多NLP问题都可以强行 用Seq2Seq Model train起来。





