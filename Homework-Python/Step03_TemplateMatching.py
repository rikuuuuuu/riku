#!/usr/bin/env python
# coding: utf-8

# ## Step03_TemplateMatching
# 
# テストサンプルを１枚ずつ読み出してマッチングする
# 混同行列と各クラスの認識率を表示する

# In[2]:


from skimage import io
import numpy as np


# In[3]:


TrainingSampleNum = 2000 # 学習サンプル総数
TestSampleNum = 10000 # テストサンプル総数
ClassNum = 10 # クラス数（今回は10）
ImageSize = 28 # 画像サイズ（今回は縦横ともに28）
TrainingDataFile = './Images/TrainingSamples/{0:1d}-{1:04d}.png'
TestDataFile = './Images/TestSamples/{0:1d}-{1:04d}.png'
OutFile = './Images/OutSamples/gray_{0:1d}-{1:04d}.png'


# In[4]:


# LoadTemplates
def LoadTemplates():
    labels = np.zeros(TrainingSampleNum, dtype=np.uint8)
    templates = np.zeros((TrainingSampleNum, ImageSize, ImageSize), dtype=np.int16)

    i = 0
    for label in range(0, ClassNum):
        for sample in range(0, TrainingSampleNum // ClassNum):
            filename = TrainingDataFile.format(label, sample)
            templates[i,:,:] = io.imread(filename).astype(np.int16)
            labels[i] = label
            i += 1

    return templates, labels


# In[5]:


# CalcDistance
# 今回は L1 距離を算出
def CalcDistance(target, template):
    buf = np.fabs(target - template)    
    return np.sum(buf)


# In[6]:


# ReturnMatchLabel
def ReturnMatchLabel(target, templates, labels):
    min_dis = CalcDistance(target, templates[0,:,:])
    match_label = labels[0]
    for i in range(0, TrainingSampleNum):
        
        dis = CalcDistance(target, templates[i,:,:])
        if min_dis > dis:
            min_dis = dis
            match_label = labels[i]
            
    return match_label


# In[7]:


# TemplateMatching 
def TemplateMatching(templates, labels):

    results = np.zeros((ClassNum, ClassNum))
    each_class_num = TestSampleNum // ClassNum
    
    for label in range(0, ClassNum):
        for sample in range(0, each_class_num):
            filename = TestDataFile.format(label, sample)
            t_img = io.imread(filename).astype(np.int16)
            match_label = ReturnMatchLabel(t_img, templates, labels)
            results [label, match_label] += 1
        print("{0:1d}: {1:.4f}".format(label, results[label,label] / each_class_num))

    print("= Confusion matrix ===========")
    for t_label in range(0,ClassNum):

        for m_label in range(0,ClassNum):
            print("{:04g}, ".format(results[t_label,m_label]), end="")
        print("")

    print("= Total Recognition accuracy ===========")
    total_correct_num = 0
    for t_label in range(0, ClassNum):
        total_correct_num += results[t_label, t_label]
    print("TOTAL: {}".format(total_correct_num / TestSampleNum))


# In[8]:


# main ルーチン

templates, labels = LoadTemplates()
TemplateMatching(templates, labels)


# In[ ]:




