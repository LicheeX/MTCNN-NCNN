# MTCNN-NCNN 
Face detection and landmark implementation with mtcnn based on ncnn framework.

### Note

1. This project is modified from https://github.com/Longqi-S/ncnn-mtcnn.git;    
2. I compiled ncnn on RK3399, ubuntu 16.04,if you use other platform, replace ncnn include files and libncnn.a;
3. mkdir bin    

## Quick Start

```
mkdir bin
mkdir build

cd build
cmake ..
make

```
if you use other platform, compile ncnn project first and replace releated include files and libncnn.a in this project. (https://github.com/Tencent/ncnn.git)

 
### Result
![image](https://github.com/LicheeX/MTCNN-NCNN/blob/master/result.jpg)

