# OreIdentifier-Alpha-0.1

# 公共信息：  
10.4-21:50 本文档记录所有人的分工信息。  
10.4-22.30 矿石在图像的固定位置（可能有少许偏移）  

# 分工1：  
人数：2人 @李君宠 @王天瑞  
传入：	相机原始图像  
传出：	黑白图像，其中原始图像的黑颜色的轮廓为1，其他颜色为0  
实现方法：  

# 分工2：  
人数：1人 @王子瑜  
传入：	黑白图像，其中原始图像的黑颜色的轮廓为1，其他颜色为0  
传出：	识别出是顶面、底面还是侧面  
		如果是顶面或底面则输出：[自己定义]  
		如果是侧面则输出：  
			vector<vector<Point>> _contours;  
			vector<int> _six_index, _square_index;  
实现方法：  

# 分工3：  
人数：2人 @赵宇新 @蒋航  
传入：     
	  vector<vector<Point>> _contours;  
	  vector<int> _six_index, _square_index;  
传出：	侧面的方向：[自己定义]  
实现方法：  
