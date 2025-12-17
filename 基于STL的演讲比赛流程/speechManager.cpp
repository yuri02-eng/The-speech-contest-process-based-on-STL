#include"speechManager.h"
#include <algorithm>  // 包含 shuffle
#include <random>     // 包含随机数引擎
#include <vector>
#include <deque>
#include <numeric>
#include <iomanip>
#include <map>
#include <fstream>
SpeechManager::SpeechManager(){
    initSpeech();
    createSpeaker();
    loadRecord();
}
void SpeechManager::show_Menu()
{
    cout << "*********************************************************************" << endl;
    cout << "**********                 欢迎参加演讲比赛                 **********" << endl;
    cout << "**********                 1.开始演讲比赛                   **********" << endl;
    cout << "**********                 2.查看往届记录                   **********" << endl;
    cout << "**********                 3.清空比赛记录                   **********" << endl;
    cout << "**********                 0.退出比赛程序                   **********" << endl;
    cout << "*********************************************************************" << endl;
    cout << endl;
}
void SpeechManager::exitSystem() {
    cout << "期待与您的下次相遇" << endl;
    system("pause");
    exit(0);
}
void SpeechManager::initSpeech() {
    v1.clear();
    v2.clear();
    vVictory.clear();
    m_Speaker.clear();
    m_Index = 0;
    m_Record.clear();
}
void SpeechManager::createSpeaker() {
    string nameSeed = "ABCDEFGHIJKL";
    for (int i = 0; i < nameSeed.size(); i++) {
        // 创建选手姓名
        string name = "选手";
        name += nameSeed[i];

        // 创建选手对象并初始化
        Speaker sp(name);

        // 初始化选手分数
        for (int j = 0; j < 2; j++) {
            sp.m_Score[j] = 0.0;
        }

        // 生成选手编号（从10001开始）
        int playerId = 10001 + i;

        // 将选手编号存入向量
        v1.push_back(playerId);

        // 将选手编号和对应的选手对象存入map
        m_Speaker.insert(make_pair(playerId, sp));
    }

    //cout << "成功创建了 " << nameSeed.size() << " 名选手" << endl;
}
void SpeechManager::startSpeech() {
    //第一轮开始比赛
    //1.抽签
    speechDraw();
    //2.比赛
    speechContest();
    //3.显示晋级结果
    showScore();
    //第二轮
    m_Index++;
    //1.抽签
    speechDraw();
    //2.比赛
    speechContest();
    //3.显示最终结果
    showScore();
    //4.保存结果
    saveRecord();
    cout << "本届比赛结束" << endl;
    initSpeech();
    createSpeaker();
    loadRecord();
    system("pause");
    system("cls");
}
void SpeechManager::speechDraw() {
    cout << "第<<" << m_Index+1 << "<<轮比赛开始" << endl;
    cout << "----------------------------------------" << endl;
    std::random_device rd;
    std::mt19937 g(rd());
    if (m_Index == 0) {
        // 方法1：使用随机设备种子
        std::shuffle(v1.begin(), v1.end(), g);
        for (const auto& it : v1) {
                cout << it << " ";
            }
        cout << endl;
    }
    else {
        std::shuffle(v2.begin(), v2.end(), g);
        for (const auto& it : v2) {
            cout << it << " ";
        }
        cout << endl;
    }
    cout << "--------------------------------" << endl;
    system("pause");
    cout << endl;
}
void SpeechManager::speechContest() {
    cout << "------------第<<" << m_Index + 1 << "<<轮比赛正式开始-------------" << endl;
    vector<int>v_Src;
    //准备临时容器 存放小组程序
    multimap<double, int, greater<double>> groupScore;
    int num = 0;
    if (m_Index == 0) {
        v_Src = v1;
    }
    else {
        v_Src = v2;
    }
    for (const auto& it : v_Src){
        ++num;
        deque<double> d;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(60.0, 100.0);

        for (int i = 0; i < 10; i++) {
            double score = dis(gen);
            d.push_back(score);
        }
        sort(d.begin(), d.end(), greater<double>());
        d.pop_front();
        d.pop_back();
        double sum = accumulate(d.begin(), d.end(), 0);
        double avg = sum / static_cast<double>(d.size());
        //cout << "编号：" << it << "姓名：" << m_Speaker[it].m_Name << "获取平均分 " << avg;
        //m_Speaker.insert(make_pair(avg,))
        m_Speaker[it].m_Score[m_Index] = avg;
        groupScore.insert(make_pair(avg, it));
        if (num % 6 == 0) {
            cout << "第" << num / 6 << "次 的比赛名次" << endl;
            for (const auto& it : groupScore) {
                cout << "编号是" << it.second << "姓名" << m_Speaker[it.second].m_Name << "成绩是"<< m_Speaker[it.second].m_Score[m_Index] <<endl;
            }
            int count = 0;
            for (const auto& it : groupScore) {
                if (m_Index == 0) {
                    v2.push_back(it.second);
                }
                else {
                    vVictory.push_back(it.second);
                }
                ++count;
                if (count== 3) {
                    break;
                }
            }
            groupScore.clear();
            cout << endl;
        } 
    }
    cout << "---------------第" << m_Index + 1 << "轮比赛结束----------------" << endl;
    cout << endl;
}
void SpeechManager::showScore(){
    cout << "-------------第" << m_Index+1 << "轮的晋级信息-------------" << endl;
    vector<int> v;
    if (m_Index == 0) {
        v = v2;
    }
    else {
        v = vVictory;
    }
    for (const auto& it : v) {
        cout << "选手编号：" << it << "姓名" << m_Speaker[it].m_Name << "分数" << m_Speaker[it].m_Score[m_Index] << endl;
    }
    cout << endl;
    system("pause");
    system("cls");
}
void SpeechManager::saveRecord() {
    ofstream ofs;
    ofs.open("speech.csv",ios::out|ios::app);
    for (const auto& it : vVictory) {
        ofs << it << "," << m_Speaker[it].m_Score[1] << ",";

    }
    ofs << endl;
    ofs.close();
    cout << "记录已经保存" << endl;
    fileIsEmpty = false;
}
void SpeechManager::loadRecord() {
    ifstream ifs("speech.csv",ios::in);
    if (!ifs.is_open()) {
        fileIsEmpty = true;
        cout << "文件不存在" << endl;
        ifs.close();
        return;
    }
    char ch;
    ifs >> ch;
    if (ifs.eof()) {
        cout << "文件为空" << endl;
        fileIsEmpty = true;
        ifs.close();
        return;
    }
    fileIsEmpty = false;
    ifs.putback(ch);
    string data;
    int index = 0;
    while (ifs >> data) {
        /*cout << data << endl;*/
        vector<string> v;
        int pos = -1;
		int start = 0;
        while (true) {
            pos = data.find(",", start);
            if (pos == -1) {
                break;
            }
            else {
                string temp = data.substr(start, pos - start);
                //cout << temp << endl;
                start = pos + 1;
                v.push_back(std::move(temp));
            }
        }
        this->m_Record.insert(make_pair(index, v));
        ++index;
    }
    ifs.close();
    //for (const auto& it : m_Record) {
    //    cout << it.first+1 << "冠军编号：" << it.second[0] << "分数：" << it.second[1] << endl;
    //}
}
void SpeechManager::showRecord() {
    if (fileIsEmpty) {
        cout << "文件不存在或记录为空！" << endl;
    }
    else {
        for (const auto& it : m_Record) {
            cout << "-------------第" << it.first + 1 << "届比赛信息如下：--------------" << endl;
            cout << "冠军编号：" << it.second[0] << "分数：" << it.second[1] << endl;
            cout << "亚军编号：" << it.second[2] << "分数：" << it.second[3] << endl;
            cout << "季军编号：" << it.second[4] << "分数：" << it.second[5] << endl;
        }
    }
    system("pause");
    system("cls");
}
void SpeechManager::clearRecord() {
    cout << "确认清空？" << endl;
    cout << "1.确认" << endl;
    cout << "2.返回" << endl;
    int select = 0;
    cin >> select;
    if (select == 1) {
        ofstream ofs("speech.csv", ios::trunc);
        ofs.close();
        initSpeech();
        createSpeaker();
        loadRecord();
        cout << "清空成功！" << endl;
    }
    system("cls");
}
SpeechManager::~SpeechManager(){
}