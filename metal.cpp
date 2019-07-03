#include "metal.h"

void MetalInfo::initConfig(map<string,MetalInfo> &metalInfoMap)
{
	MetalInfo metalNO1("世园会五十国钱币册","001001","册",998.00,1.00,0);
	metalInfoMap.insert(make_pair("001001",metalNO1));
	MetalInfo metalNO2("2019北京世园会纪念银章大全40g","001002","盒",1380.00,0.9,0);
	metalInfoMap.insert(make_pair("001002",metalNO2));
	MetalInfo metalNO3("招财进宝","003001","条",1580.00,0.95,0);
	metalInfoMap.insert(make_pair("003001",metalNO3)); 
	MetalInfo metalNO4("水晶之恋","003002","条",980.00,1,1);
	metalInfoMap.insert(make_pair("003002",metalNO4));
	MetalInfo metalNO5("中国经典钱币套装","002002","套",998.00,1,2);
	metalInfoMap.insert(make_pair("002002",metalNO5));
	MetalInfo metalNO6("守扩之羽比翼双飞4.8g","002001","条",1080.00,0.95,1);
	metalInfoMap.insert(make_pair("002001",metalNO6));
	MetalInfo metalNO7("中国银象棋12g","002003","套",698.00,0.9,2);
	metalInfoMap.insert(make_pair("002003",metalNO7));
}

string MetalInfo::getMetalName()
{
	return metalName;
}
string MetalInfo::getmetalOrderId()
{
	return metalOrderId;
}
string MetalInfo::getmetalUnit()
{
	return metalUnit;
}
double MetalInfo::getmetalPrice()
{
	return metalPrice;
}
double MetalInfo::getdiscount()
{
	return discount;
}
int MetalInfo::getreduceType()
{
	return reduceType;
}
