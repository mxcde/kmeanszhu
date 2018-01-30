#include "kmeans.h"

kmeans::kmeans()
{
	filename = "iris.txt";
	k_value = 3;
	comDIS[0] = DBL_MAX;
	comDIS[1] = DBL_MAX;
	center.resize(k_value);
	labs.resize(k_value);
	
	readfile();
	
	label.resize(data.size());
	kppgenerateCenter();//generateRandomCenter();
	Euclidean_distance(); //cosine_distance();//Euclidean_distance();
	for (int i = 0; i < k_value; ++i)
	{
		cout << "******************* k:" << i << endl;
		cout << labs[i] << endl;
	}
	for (int i = 0; i < 10; ++i)
	{
		if (labszr())
		{
			labszreo();
		}
		ComputerCenters();
		Euclidean_distance(); //cosine_distance(); //Euclidean_distance(); 

		for (int i = 0; i < k_value; ++i)
		{
			cout << "******************* k:" << i << endl;
			cout << labs[i] << endl;
		}
		outfile();
	}
}

kmeans::~kmeans()
{

}
////  欧式
void kmeans::Euclidean_distance()
{
	labs.clear();
	labs.resize(k_value);
	float centerDIS = 0;
	vector<float> centerdis;
	for (int i = 0; i < center.size(); i++)
	{
		for (int j = 0; j < center[0].size(); ++j)
		{
			cout << center[i][j] << endl;
		}
	}
	int label_pos = 0;
	for (int k = 0; k < data.size(); ++k)  ////  data.size  表示所有的 数据点数
	{
		for (int j = 0; j <k_value; ++j) ////center.size 表示簇数
		{
			centerDIS = 0;
			for (int i = 0; i <data[0].size(); ++i) ////  center[0].size  表示维度
			{
				centerDIS += (center[j][i] - data[k][i])*(center[j][i] - data[k][i]);
			}
			comDIS[1] += centerDIS;
			centerdis.push_back(sqrtf(centerDIS));
		}
			
		vector<float>::iterator min = min_element(centerdis.begin(), centerdis.end());
		int pos=distance(centerdis.begin(), min); /// 使用label标识 data的数据属于哪个簇
		label[k] = pos;
		centerdis.clear();
		labs[label[k]]++;
	}
	/*
	if (comDIS[0] > comDIS[1])
	{
		
		SSE = comDIS[0] - comDIS[1];
	}*/

	
	
	return;
}
////  余弦
void kmeans::cosine_distance()
{

	labs.clear();
	labs.resize(k_value);
	double centerDISAB = 0;
	double centerDISA = 0;
	double centerDISB = 0;
	double cosDIS;
	vector<double> centerdis;
	for (int i = 0; i < center.size(); i++)
	{
		for (int j = 0; j < center[0].size(); ++j)
		{
			cout << center[i][j] << endl;
		}
	}
	int label_pos = 0;
	for (int k = 0; k < data.size(); ++k)  ////  data.size  表示所有的 数据点数
	{
		for (int j = 0; j < k_value; ++j) ////center.size 表示簇数
		{
			centerDISAB = 0;
			centerDISA = 0;
			centerDISB = 0;
			for (int i = 0; i < data[0].size(); ++i) ////  center[0].size  表示维度
			{
				centerDISAB += (center[j][i]*data[k][i]);
				centerDISA += center[j][i] * center[j][i];
				centerDISB += data[k][i] * data[k][i];
			}
			cosDIS = (centerDISAB) / (sqrtf(centerDISA)*sqrtf(centerDISB));
			centerdis.push_back(cosDIS);
		}

		vector<double>::iterator max = max_element(centerdis.begin(), centerdis.end());
		int pos = distance(centerdis.begin(), max); /// 使用label标识 data的数据属于哪个簇
		label[k] = pos;
		centerdis.clear();
		labs[label[k]]++;
	}

}

//对于距离度量不管是采用欧式距离还是采用余弦相似度，簇的质心都是其均值，即向量各维取平均即可。
void kmeans::ComputerCenters() ////      质心的计算   
{
	Oldcenter =center; //  对oldcenter 进行赋值
	vector<vector<float>>   centerdis;
	centerdis.resize(center.size());
	vector<float>  tmp;
	center.clear();
	center.resize(k_value);
	for (int j = 0; j < data[0].size(); ++j) ///  维度  
    {
		tmp.clear();
		tmp.resize(center.size());
	for (int i = 0; i < data.size(); ++i) /// 数据
	{		
		     tmp[label[i]]+= data[i][j];

	}
	for (int k = 0; k <k_value; ++k)   /// 带表  k
	{
		center[k].push_back(tmp[k]/labs[k]); ////将计算好的中心点存放到 center 
	}
    }
	 ///////////////////////////    计算质心的偏移量
	double dist = 0;
	max_center_shift = 0;
	for (int i = 0; i < k_value; ++i)
	{
		for (int j = 0; j < data[0].size(); ++j)
		{
			double t = Oldcenter[i][j] - center[i][j];
			dist += t*t;
		}
		max_center_shift = max(max_center_shift, dist);
	}
	cout << "max_shift:" << max_center_shift << endl;
	return;
}
void kmeans::generateRandomCenter() /// 生成随机质心   质心的初始化
{
	srand((unsigned)time(NULL));
	random_device  rd;
	mt19937 gen(rd());
	for (int i = 0; i < k_value; ++i) ///  随机 k_value  个质心
	{
		for (int j = 0; j < box.size(); ++j) ///  随机每个点 // 维数j
		{
			uniform_int_distribution<> dis(box[j][0], box[j][1]);
			center[i].push_back(float(dis(gen)*1.00000)); // 使得随机点在 每一维度的最大最小值 之间
			//center[i].push_back(float(dis(gen)*0.99999));
		}
	}

	return; 

 }
void kmeans::kppgenerateCenter()
{
	////////////////////   随机第一个点
	srand((unsigned)time(NULL));
	random_device  rd;
	mt19937 gen(rd());
	uniform_int_distribution<> FirstCenterNum(0,data.size());   
	int CenterNum = FirstCenterNum(gen);
	/*for (int i = 0; i < data[0].size(); ++i)
	{
		center[0].push_back(data[CenterNum][i]);
	}
	*/
	center[0]=data[CenterNum];///////////// firstcenter 


	//////////////////////////////    
	
	for (int i = 1; i < k_value; ++i)
	{
		dataPP.clear();
		dataPP.resize(data.size());
		getKPPdistence(i);
		float distCount = 0;
		float dataP = 0;
		for (int j = 0; j < data.size(); ++j)
		{
			distCount += dataPP[j][0];
		}
		for (int j = 0; j < data.size(); ++j)
		{
			dataP += dataPP[j][0] / distCount;
			dataPP[j].push_back(dataP);
		}

		uniform_int_distribution<> pp(0, 10);
		int ppsize = pp(gen);
		float centerPP = (float)ppsize / 10;
		int centerpos;
		for (int cen = 0; cen < data.size(); )
		{
			if (centerPP > dataPP[cen][1])
			{
				cen++;
			}
			else
			{
				centerpos = ++cen;
				break;
			}
		}
		center[i]=data[centerpos];
	}
}





void kmeans::getKPPdistence(int centersize)
{
	float DisPP = 0;
	vector<float>  centerdis;
	for (int k = 0; k < data.size(); ++k)  ////  data.size  表示所有的 数据点数
	{
		for (int j = 0; j <centersize; ++j) ////center.size 表示簇数
		{
			DisPP = 0;
			for (int i = 0; i < data[0].size(); ++i) ////  center[0].size  表示维度
			{
				DisPP += (center[j][i] - data[k][i])*(center[j][i] - data[k][i]);
			}
			centerdis.push_back(sqrtf(DisPP));
		}
		vector<float>::iterator min = min_element(centerdis.begin(), centerdis.end());
		float tmp = *min;
		dataPP[k].push_back(tmp);
		int pos = distance(centerdis.begin(), min); /// 使用label标识 data的数据属于哪个簇
		centerdis.clear();
	}
}

/////////// 读文件
void kmeans::readfile()
{
	ifstream File(filename);
	string  line;
	int div_pose = 0;

	vector<float> tmp;
	string str;

	while (getline(File,line))
	{
		filedata.push_back(line);
		tmp.clear();
 
		while (1)
		{
			div_pose = line.find(" ");
			if (div_pose < 0)
			{
				break;
			}
			str = line.substr(0, div_pose);
			float fl = stof(str);
			tmp.push_back(fl);
			line = line.substr(div_pose + 1, line.size());
		}

		tmp.push_back(stof(line));
		data.push_back(tmp);
  	}
	box_storage();
}

void kmeans::box_storage()
{
	vector<float> valuetmp; /// 临时存放每列数据
	box.resize(data[0].size());
	for (int j = 0; j < data[0].size(); ++j)
	{
		for (int i = 0; i < data.size(); ++i)
		{
			valuetmp.push_back(data[i][j]);
		}
		float min = *min_element(valuetmp.begin(), valuetmp.end());
		float max = *max_element(valuetmp.begin(), valuetmp.end());
		box[j].push_back(min); ///  box  存放第一列的最小值
		box[j].push_back(max);
	}
	return;
}
void kmeans::outfile()
{
	fstream outfilename("out.txt",ios::out);
	for (int k = 0; k < k_value; ++k)
	{
		outfilename << "k:" << k << "\n";
		for (int i = 0; i < data.size(); ++i)
		{
			if (label[i] == k)
			{
				outfilename << filedata[i]<<"\n";
			}
		}
	}



}
bool kmeans::labszr()
{
	for (int k = 0; k < k_value; ++k)
	{
		if (labs[k] == 0)
			return true;
	}
	return false;
}
// if some cluster appeared to be empty then:
//   1. find the biggest cluster
//   2. find the farthest from the center point in the biggest cluster
//   3. exclude the farthest point from the biggest cluster and form a new 1-point cluster.
void kmeans::labszreo()
{
	for (int k = 0; k < k_value; ++k)
	{
		if (labs[k] != 0)
			continue;
		int max_k = 0;
		for (int k1 = 1; k1 < k_value; ++k1)
		{
			if (labs[max_k] < labs[k1])
				max_k = k1;
		}
		/*
		for (int j = 0; j < data[0].size(); ++j) ///  维度  
		{
			for (int i = 0; i < data.size(); ++i) /// 数据
			{
				tmp[label[i]] += data[i][j];
				if (j == 0)
				{
					labs[label[i]]++;
				}
			}
			for (int k = 0; k <center.size(); ++k)   /// 带表  k
			{
				center[k].push_back(tmp[k] / labs[k]); ////将计算好的中心点存放到 center 
			}
		}*/
		vector<float>    max_center;
		max_center.resize(data.size());  /// 存储最大簇的中心
		for (int j = 0; j < data[0].size(); ++j) ///  维度  
		{
			for (int i = 0; i < data.size(); ++i) /// 数据
			{
				if (label[i] == max_k)
				{
					max_center[j] += data[i][j];
				}
			}
			max_center[j] = max_center[j] / labs[max_k];
		}
		float dist = 0;
		float max_dist = -1;
		int farthest_point;
		for (int i = 0; i < data.size(); ++i)
		{
			if (label[i] != max_k)
				continue;
			////////////////   计算离中心点最远的点

			for (int j = 0; j < data[0].size(); ++j)
			{
				dist += (max_center[j] - data[i][j])*(max_center[j] - data[i][j]);
			}

			if (max_dist <= dist)
			{
				max_dist = dist;
				farthest_point = i; ///  记录最远点
			}
		}
		labs[max_k]--;
		labs[k]++;

		 //////////  将  data[farthest] 存放到center 没有点的位置
		label[farthest_point] = k;
	}

}
