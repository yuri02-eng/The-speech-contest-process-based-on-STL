#include<iostream>
#include "speechManager.h"
int main() {
	SpeechManager sm;
	//for (const auto& it : sm.m_Speaker) {
	//	std::cout << "选手编号：" << it.first << "\t选手姓名" << it.second.m_Name << "\t选手分数" << it.second.m_Score[0]<<std::endl;
	//}
	int choice=0;
	while (true) {
		sm.show_Menu();
		cout << "请输入您的选择：" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			sm.startSpeech();
			break;
		case 2:
			sm.showRecord();
			break;
		case 3:
			sm.clearRecord();
			break;
		case 0:
			sm.exitSystem();
			break;
		default:
			system("cls");
			break;
		}
	}
	return 0;
}