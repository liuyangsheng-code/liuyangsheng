#include <json/json.h>
#include "metal.h"
#include "memberInfo.h"
#include <string.h>
#include <sstream>

using namespace std;

#define JSONCONFIGNAME "sample_command.json"
#define TITLE "方鼎银行贵金属购买凭证\n\n"

map<string,MetalInfo> metalInfoMap;
map<int,int> reduceInfoMap;
map<int,string> levelMap;
int getCardLevel(int points)
{
	int level=1;
	if(points <10000)
		level = 1;
	else if(points*1.5>=10000 && points*1.5<50000)
		level = 2;
	else if(points*1.8>=10000 && points*1.8<50000)
		level = 3;
	else if(points*2>=10000 && points*2<50000)
		level = 4;
	return level;
}
int calculateLevelIsUp(int addPoints, MemberInfo memberInfo, int &newLevel)
{
	int curentPoints = memberInfo.getmemberpoints();
	int oldLevel = getCardLevel(curentPoints);
	int totalPoints = curentPoints + addPoints;
	int level = getCardLevel(totalPoints);
	newLevel=level;
	if(level> oldLevel)
		return 1;
	return 0;
}
//计算单个产品的优惠后的价钱
void calculateProduct(MetalInfo metalInfo, int amount, double singleTotalPrice, double &reducePirce)
{
	double discount=metalInfo.getdiscount();	
	int reduceType=metalInfo.getreduceType();
	//折扣优惠金额
	double discountPrice = singleTotalPrice * (1-discount);
	//cout <<singleTotalPrice <<"==="<<discountPrice<<endl;
	//满减优惠金额
	double fullReducePrice = 0.0;
	switch(reduceType)
	{
		case 0:
			break;
		case 1:
			if(amount == 3)
				fullReducePrice = metalInfo.getmetalPrice()/2;
			else if(amount > 3)
				fullReducePrice = metalInfo.getmetalPrice();
			break;
		case 2:
			if(singleTotalPrice >= 1000.00 && singleTotalPrice <2000.00)
				fullReducePrice = reduceInfoMap[1000];
			else if(singleTotalPrice >=2000.00 && singleTotalPrice <3000.00)
				fullReducePrice = reduceInfoMap[2000];
			else if(singleTotalPrice >=3000.00)
				fullReducePrice = reduceInfoMap[3000];
			break;
		default:
			break;
	}
	//cout <<"==="<<fullReducePrice<<endl;
	reducePirce=fullReducePrice;
	if(discountPrice > fullReducePrice)
		reducePirce = discountPrice;
	return;
}

//开始转换
int doConvert(map<string,MemberInfo> memberInfoMap)  
{  
	Json::Reader reader;  
	Json::Value root;  
	//从文件中读取，保证当前文件有test.json文件  
	ifstream in(JSONCONFIGNAME, ios::binary);  
	if( !in.is_open() )    
	{   
		cout << "Error opening file\n";   
		return -1;   
	}  
	if(!reader.parse(in,root))  
	{  
		cout << "parse error\n" << endl;      
		in.close();  
		return -1;   
	}
	//读取根节点信息  
	string orderId = root["orderId"].asString();  
	string cardNO= root["memberId"].asString();  
	string createTime= root["createTime"].asString();  
	//int age = root["age"].asInt();  
	//bool sex_is_male = root["sex_is_male"].asBool();  
	MemberInfo memberInfo = memberInfoMap[cardNO];
	FILE *fd = fopen(cardNO.c_str(), "a+");
	if (fd == NULL) 
	{
		printf("fd is NULL and open file fail\n");
		return -1;
	}
	fwrite(TITLE, strlen(TITLE), 1, fd);
	char tempStr[2048]={0};
	snprintf(tempStr, sizeof(tempStr), "销售单号：%s 日期：%s\n", orderId.c_str(),createTime.c_str());
	fwrite(tempStr, strlen(tempStr), 1, fd);
	memset(tempStr,0,sizeof(tempStr));

	//读取购买数组信息  
	string product;
	int amount;
	double totalPrice = 0.00;
	string printStr="商品及数量\t单价\t金额\n";
	std::stringstream discountPriceInfo;//优惠清单信息
	discountPriceInfo << "优惠清单：\n";
	double reducePirce=0.0;
	double totalReducePirce=0.0;
	//snprintf(tempStr, sizeof(tempStr), "商品及数量\t单价\t金额\n");
	for(unsigned int i = 0; i < root["items"].size(); i++)  
	{  
		product = root["items"][i]["product"].asString();  
		amount = root["items"][i]["amount"].asInt();  
		double singleTotalPrice=metalInfoMap[product].getmetalPrice()*amount;//购买的单个产品的总价
		totalPrice+=singleTotalPrice;
		std::stringstream stream;
		stream<<'('<<product<<')'+metalInfoMap[product].getMetalName()<<'x'<<amount<<','<<
				metalInfoMap[product].getmetalPrice()<<','<<singleTotalPrice<<'\n';

		printStr = printStr + stream.str();
		calculateProduct(metalInfoMap[product], amount, singleTotalPrice, reducePirce);
		if(reducePirce > 0)
			discountPriceInfo <<'('<<product<<')'<<metalInfoMap[product].getMetalName()<<": -"<<reducePirce<<'\n';
		
		totalReducePirce+=reducePirce;
		//snprintf(tempStr+strlen(tempStr), sizeof(tempStr+strlen(tempStr)), "(%s)%sx%d,%lf,%lf \n",product.c_str(),
		//snprintf(Point, 2048, "(%s)%sx%d,%lf,%lf \n",product.c_str(),
		//		metalInfoMap[product].getMetalName().c_str(),amount,
		//		metalInfoMap[product].getmetalPrice(),
		//		metalInfoMap[product].getmetalPrice()*amount);
	}  
	std::stringstream stream;
	stream<<totalPrice;
	printStr=printStr+"合计："+stream.str()+'\n';
	discountPriceInfo << "优惠合计:" << totalReducePirce<<"\n\n";
	discountPriceInfo <<"应收合计：" << totalPrice-totalReducePirce;
	//discountPriceInfo << root["payments"]["type"].asString()<<'\n';
	//缺少打印收款信息
	//discountPriceInfo <<"\n收款：\n" << root["discountCards"].asString()<<'\n';
	discountPriceInfo <<"\n客户等级与积分：\n" << "新增积分:"<<totalPrice-totalReducePirce;
	int newLevel = 0;
	if(1==calculateLevelIsUp(totalPrice-totalReducePirce,memberInfo,newLevel))
	{
		discountPriceInfo <<"恭喜您升级为"<<levelMap[newLevel] << "客户！\n";
	}
	discountPriceInfo<<"客户卡号:"<<cardNO.c_str()<<" 会员姓名："<<memberInfo.getmemberName().c_str()<<
		" 客户等级："<<levelMap[newLevel].c_str()<<" 累计积分："<<memberInfo.getmemberpoints()+totalPrice-totalReducePirce;
	printStr=printStr+'\n'+discountPriceInfo.str();

	fwrite(printStr.c_str(), strlen(printStr.c_str()), 1, fd);
	//cout << printStr<< '\n';  
	//cout << endl;  
	fclose(fd);
	in.close();  
}  
//初始化满减信息
void initReduceInfo()
{
	reduceInfoMap[1000]=10;
	reduceInfoMap[2000]=30;
	reduceInfoMap[3000]=350;

	levelMap[1]="普卡";
	levelMap[2]="金卡";
	levelMap[3]="白金卡";
	levelMap[4]="钻石卡";
}
int main()
{
	//初始化满减信息
	initReduceInfo();
	//初始化产品信息
	MetalInfo metalInfo;
	metalInfo.initConfig(metalInfoMap);
	//cout << metalInfoMap["001001"].getMetalName()<<endl;
	//cout << metalInfoMap["001001"].getmetalUnit()<<endl;

	//初始化会员信息
	MemberInfo memberInfo;
	map<string,MemberInfo> memberInfoMap;
	memberInfo.initMemberInfo(memberInfoMap);
	//cout << memberInfoMap["6236609999"].getmemberName()<<endl;
	//cout << memberInfoMap["6236609999"].getcardNO()<<endl;
	doConvert(memberInfoMap);  
	return 0;
}
