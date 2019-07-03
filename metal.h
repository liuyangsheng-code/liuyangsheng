#ifndef __METAL_H__
#define __METAL_H__
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;
class MetalInfo {
	private:
		string metalName;//名字
		string metalOrderId;//编号
		string metalUnit;//单位
		double metalPrice;//价格
		double discount; //折扣
		int reduceType;//0:没有满减,1:满3件减,2:满多少钱后减
	public:
		MetalInfo(){};
		MetalInfo(string metalName, string metalOrderId, string metalUnit, double metalPrice, double discount, int reduceType){
			this->metalName=metalName;
			this->metalOrderId=metalOrderId;
			this->metalUnit=metalUnit;
			this->metalPrice=metalPrice;
			this->discount=discount;
			this->reduceType=reduceType;
		};
		~MetalInfo(){}
		void initConfig(map<string,MetalInfo> &metalInfoMap);
		string getMetalName();
		string getmetalOrderId();
		string getmetalUnit();
		double getmetalPrice();
		double getdiscount();
		int getreduceType();
		//map<string, MetalInfo> metalInfoMap;
};

#endif
