#ifndef __MEMBERINFO_H__
#define __MEMBERINFO_H__
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;
class MemberInfo {
	private:
		string memberName;//名字
		string memberCardLevel;//会员等级
		string cardNO;//卡号
		int memberpoints;//会员积分
	public:
		MemberInfo(){};
		MemberInfo(string memberName, string memberCardLevel, string cardNO, int memberpoints){
			this->memberName=memberName;
			this->memberCardLevel=memberCardLevel;
			this->cardNO=cardNO;
			this->memberpoints=memberpoints;
		};
		~MemberInfo(){}
		void initMemberInfo(map<string,MemberInfo> &memberInfo);
		string getmemberName();
		string getmemberCardLevel();
		void setmemberCardLevel(string memberCardLevel);
		string getcardNO();
		int getmemberpoints();
		void setmemberpoints(int memberpoints);
};

#endif
