# Histogram Equalization<br />
##### 이미지 Enhancement 방법의 한가지다.<br />
## Algorithm<br />
###1. Compute Histogram<br />
##### 각 픽셀의 값이 몇개 있는지 기록한다. (0~255)<br />
###2. Calculate Normalized Sum of Histogram<br />
##### 수식에 따라서 계산하고 LUT를 만든다.<br />
###3. Transform Input Image to Output Image<br />
##### LUT를 이용하여 이미지를 출력한다.
