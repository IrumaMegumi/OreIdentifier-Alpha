# OreIdentifier-Alpha-0.1

分工1：  
人数：2人 @李君宠 @王天瑞  
传入：	图像  
传出：	仅包含矿石上形状的黑白图像，其中原始图像的黑颜色为1，其他颜色为0  
实现方法：  

分工2：  
人数：1人 @王子瑜  
传入：	仅包含矿石上形状的黑白图像，其中原始图像的黑颜色为1，其他颜色为0  
传出：	识别出是顶面、底面还是侧面  
	如果是侧面则输出：[自己定义]  
	如果是侧面则输出：  
		所有轮廓（比如使用OpenCV教程中的vector<vector<Point>>和vector<Vec4i> Chapter7.cpp）  
		vector<int>：四边形或六边形对应的序号  
		vector<int>：是四边形还是六边形（比如四边形为1，六边形为0）  
实现方法：  

分工3：  
人数：2人 @赵宇新 @蒋航  
传入：	所有轮廓（比如使用OpenCV教程中的vector<vector<Point>>和vector<Vec4i> Chapter7.cpp）  
	vector<int>：四边形或六边形对应的序号  
	vector<int>：是四边形还是六边形（比如四边形为1，六边形为0）  
传出：	侧面的方向：[自己定义]  
实现方法：  

