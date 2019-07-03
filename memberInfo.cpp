#include "memberInfo.h"

void MemberInfo::initMemberInfo(map<string,MemberInfo> &memberInfo)
{
	MemberInfo member1("马丁","普卡","6236609999",9860);
	memberInfo.insert(make_pair("6236609999",member1));
	MemberInfo member2("王立","金卡","6630009999",48860);
	memberInfo.insert(make_pair("6630009999",member2));
	MemberInfo member3("李想","白金卡","8230009999",98860);
	memberInfo.insert(make_pair("8230009999",member3));
	MemberInfo member4("张三","钻石卡","9230009999",198860);
	memberInfo.insert(make_pair("9230009999",member4));
}

string MemberInfo::getmemberName()
{
	return memberName;
}
string MemberInfo::getmemberCardLevel()
{
	return memberCardLevel;
}
void MemberInfo::setmemberCardLevel(string memberCardLevel)
{
	this->memberCardLevel=memberCardLevel;
}
string MemberInfo::getcardNO()
{
	return cardNO;
}
int MemberInfo::getmemberpoints()
{
	return memberpoints;
}
void MemberInfo::setmemberpoints(int memberpoints)
{
	this->memberpoints=memberpoints;
}

