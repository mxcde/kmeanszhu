#pragma once
#include "utili.h"
class kmeans
{
public:
	kmeans();
	~kmeans();

protected:
	void 	Euclidean_distance(); // ŷʽ����
	void    cosine_distance(); // ���Ҿ���
protected:
	void    ComputerCenters();

protected:
	void generateRandomCenter(); //  �����������
	void kppgenerateCenter();

protected:
	void readfile();             //  ��ȡ�����ļ�
	void box_storage();        // box  �洢
	void outfile();
protected:
	bool labszr();
	void labszreo();   ////   ��labs�����������Ϊ0ʱ����������δ�����,��ҪΪ���ٷ�������


private:
	int k_value;                    // Kֵ
	vector<string>        filedata; //�洢�ļ��е��ı�����
	vector<vector<float>> data; // �洢�ļ��е����ݣ�float��
	vector<vector<float>> center; //�洢����λ��  
	vector<vector<float>> Oldcenter;  // ��¼��һ������  ������������ıȽ�   ������ֹ����֮һ 
	vector<vector<float>> allcenters; // �洢ÿ�ε���������
	vector<int>  label;  //labels��ʾÿһ����������ı�ǩ����һ����������0��ʼ����������, �Ǵ���.
	vector<vector<float>> box; // �洢ÿһ�е������Сֵ
	vector<int> labs; /// ��¼ÿ�ص�������
	string filename;           // �ļ���
	double     comDIS[2];
	double  SSE;    ///  ���ۺ���  ��¼���µ����ĺ�
    // ��������ֹ����
	double     max_center_shift; ////  ���Ĳ��ڷ����仯�������趨���ĵ���С��һ���仯ֵ��

	//  ���ĵ�ѡ��ʽ 1. ���  2.��Ϊѡ��  3. Kpp�㷨









};
