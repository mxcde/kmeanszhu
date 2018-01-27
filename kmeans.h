#pragma once
#include "utili.h"
class kmeans
{
public:
	kmeans();
	~kmeans();

protected:
	void 	Euclidean_distance(); // 欧式距离
	void    cosine_distance(); // 余弦距离
protected:
	void    ComputerCenters();

protected:
	void generateRandomCenter(); //  生成随机质心
	void kppgenerateCenter();

protected:
	void readfile();             //  读取数据文件
	void box_storage();        // box  存储
	void outfile();
protected:
	bool labszr();
	void labszreo();   ////   当labs里面出现数量为0时，存在质心未分配点,需要为其再分配质心


private:
	int k_value;                    // K值
	vector<string>        filedata; //存储文件中的文本数据
	vector<vector<float>> data; // 存储文件中的数据（float）
	vector<vector<float>> center; //存储质心位置  
	vector<vector<float>> Oldcenter;  // 记录上一次质心  和这次所得质心比较   迭代截止条件之一 
	vector<vector<float>> allcenters; // 存储每次迭代的质心
	vector<int>  label;  //labels表示每一个样本的类的标签，是一个整数，从0开始的索引整数, 是簇数.
	vector<vector<float>> box; // 存储每一列的最大最小值
	vector<int> labs; /// 记录每簇的数据量
	string filename;           // 文件名
	double     comDIS[2];
	double  SSE;    ///  代价函数  记录着新的质心和
    // 迭代的终止条件
	double     max_center_shift; ////  质心不在发生变化（可以设定质心的最小的一个变化值）

	//  质心的选择方式 1. 随机  2.人为选择  3. Kpp算法









};
