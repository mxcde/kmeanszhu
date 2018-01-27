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
	generateRandomCenter();
	Euclidean_distance();
	for (int i = 0; i <10; ++i)
	{
		if (labszr())
		{
			labszreo();
		}
		ComputerCenters();
		Euclidean_distance();
		
		for (int j = 0; j < k_value; j++)
		{    int k = 0;
			cout << "\n*****************" << j << "**********\n";
			for (int i = 0; i < data.size(); i++)
			{
				
				if (label[i] == j)
				{
					k++;
					//cout <<i<<":"<< filedata[i] << endl;;
				}
				
			}
			cout << "k:" << k << endl;
		}

		cout << "\n--------------------------" << endl;
	}
	outfile();
}

kmeans::~kmeans()
{

}
////  ŷʽ
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
	for (int k = 0; k < data.size(); ++k)  ////  data.size  ��ʾ���е� ���ݵ���
	{
		for (int j = 0; j <k_value; ++j) ////center.size ��ʾ����
		{
			centerDIS = 0;
			for (int i = 0; i <data[0].size(); ++i) ////  center[0].size  ��ʾά��
			{
				centerDIS += (center[j][i] - data[k][i])*(center[j][i] - data[k][i]);
			}
			comDIS[1] += centerDIS;
			centerdis.push_back(sqrtf(centerDIS));
		}
			
		vector<float>::iterator min = min_element(centerdis.begin(), centerdis.end());
		int pos=distance(centerdis.begin(), min); /// ʹ��label��ʶ data�����������ĸ���
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
////  ����
void kmeans::cosine_distance()
{

}

//���ھ�����������ǲ���ŷʽ���뻹�ǲ����������ƶȣ��ص����Ķ������ֵ����������άȡƽ�����ɡ�
void kmeans::ComputerCenters() ////      ���ĵļ���   
{
	Oldcenter =center; //  ��oldcenter ���и�ֵ
	vector<vector<float>>   centerdis;
	centerdis.resize(center.size());
	vector<float>  tmp;
	tmp.resize(center.size());
	center.clear();
	center.resize(Oldcenter.size());
	for (int j = 0; j < data[0].size(); ++j) ///  ά��  
    {
		tmp.clear();
		tmp.resize(center.size());
	for (int i = 0; i < data.size(); ++i) /// ����
	{		
		     tmp[label[i]]+= data[i][j];

	}
	for (int k = 0; k <center.size(); ++k)   /// ����  k
	{
		center[k].push_back(tmp[k]/labs[k]); ////������õ����ĵ��ŵ� center 
	}
    }
	 ///////////////////////////    �������ĵ�ƫ����
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
void kmeans::generateRandomCenter() /// �����������   ���ĵĳ�ʼ��
{
	srand((unsigned)time(NULL));
	random_device  rd;
	mt19937 gen(rd());
	for (int i = 0; i < k_value; ++i) ///  ��� k_value  ������
	{
		for (int j = 0; j < box.size(); ++j) ///  ���ÿ���� // ά��j
		{
			uniform_int_distribution<> dis(box[j][0], box[j][1]);
			center[i].push_back(float(dis(gen)*1.00000)); // ʹ��������� ÿһά�ȵ������Сֵ ֮��
			//center[i].push_back(float(dis(gen)*0.99999));
		}
	}

	return; 

 }
void kmeans::kppgenerateCenter()
{





}
/////////// ���ļ�
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
	vector<float> valuetmp; /// ��ʱ���ÿ������
	box.resize(data[0].size());
	for (int j = 0; j < data[0].size(); ++j)
	{
		for (int i = 0; i < data.size(); ++i)
		{
			valuetmp.push_back(data[i][j]);
		}
		float min = *min_element(valuetmp.begin(), valuetmp.end());
		float max = *max_element(valuetmp.begin(), valuetmp.end());
		box[j].push_back(min); ///  box  ��ŵ�һ�е���Сֵ
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
		for (int j = 0; j < data[0].size(); ++j) ///  ά��  
		{
			for (int i = 0; i < data.size(); ++i) /// ����
			{
				tmp[label[i]] += data[i][j];
				if (j == 0)
				{
					labs[label[i]]++;
				}
			}
			for (int k = 0; k <center.size(); ++k)   /// ����  k
			{
				center[k].push_back(tmp[k] / labs[k]); ////������õ����ĵ��ŵ� center 
			}
		}*/
		vector<float>    max_center;
		max_center.resize(data.size());  /// �洢���ص�����
		for (int j = 0; j < data[0].size(); ++j) ///  ά��  
		{
			for (int i = 0; i < data.size(); ++i) /// ����
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
			////////////////   ���������ĵ���Զ�ĵ�

			for (int j = 0; j < data[0].size(); ++j)
			{
				dist += (max_center[j] - data[i][j])*(max_center[j] - data[i][j]);
			}

			if (max_dist <= dist)
			{
				max_dist = dist;
				farthest_point = i; ///  ��¼��Զ��
			}
		}
		labs[max_k]--;
		labs[k]++;

		 //////////  ��  data[farthest] ��ŵ�center û�е��λ��
		label[farthest_point] = k;
	}

}
