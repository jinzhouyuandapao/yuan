#include"stdafx.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
using namespace std;

void main()
{
	bool countc = false;           //统计字符
	bool countw = false;           //统计单词数
	bool countl = false;           //统计行
	bool fuco = false;             //输出到指定文件
	char input[20] = { '\0' };    
	char output[20] = { '\0' };    
	char orders[30];                    //储存用户输入指令
	cin.get(orders, 30);
	int i;
	for (i = 0; i < 30; i++)
	{                            
		if (orders[i] >= 'a'&&orders[i] <= 'z' || orders[i] >= 'A'&&orders[i] <= 'Z') {
			for (int j = 0; j < 20; j++) {
				input[j] = orders[i + j];
				if (orders[i + j] == ' ' || orders[i + j] == '\n' || orders[i + j] == '\0') { i = i + j; break; }
			}
		}
		if (orders[i] == '-') {        
			if (orders[i + 1] == 'c') {
				countc = true; i++;
			}
			else if (orders[i + 1] == 'w') {
				countw = true; i++;
			}
			else if (orders[i + 1] == 'l') {
				countl = true; i++;
			}
			else if (orders[i + 1] == 'o') {
				if ((countc || countw || countl) == false) { cout << "先确定统计目标再输出到指定文件" << endl; break; }
				else {
					fuco = true; i = i + 3;
					for (int j = 0; j < 20; j++) {//读取输出文件名
						output[j] = orders[i + j];
						if (orders[i + j] == ' ' || orders[i + j] == '\n' || orders[i + j] == '\0') { i = i + j; break; }
					}
				}
			}
			else {
				cout << "未定义标识符" << endl; break;
			}
		}
	}
	
	FILE *p;
	p = NULL;
	errno_t err;
	if (fuco) {                    //指定文件输出
		ofstream fout(output);
		if (countc) {                
			err = fopen_s(&p, input, "r");
			int c_count = 0;
			char ch;
			while (!feof(p)) {
				ch = fgetc(p); c_count++;
			}
			fclose(p);
			fout << input << "，字符数：" << c_count << endl;
		}

		if (countw) {                
			err = fopen_s(&p, input, "r");
			int w_count = 0;
			char ch;
			bool flag = false;
			while (!feof(p)) {
				ch = fgetc(p);
			
				if (ch >= 'a'&&ch <= 'z' || ch >= 'A'&&ch <= 'Z' || ch >= '0'&&ch <= '9' || ch == '&' || ch == '-' || ch == '_' || ch == '^')
					flag = true;
				else {
					if (flag)
					{
						flag = false;
						w_count++;
					}
				}
			}
			fclose(p);
			fout << input << "，单词数：" << w_count << endl;
		}

		if (countl) {                
			err = fopen_s(&p, input, "r");
			int l_count = 1;
			char ch;
			while (!feof(p)) {
				ch = fgetc(p);
				if (ch == '\n') l_count++;
			}
			fclose(p);
			fout << input << "，行数：" << l_count << endl;
		}
	}
	else {                        //控制台输出
		if (countc) {
			err = fopen_s(&p, input, "r");
			int c_count = 0;
			char ch;
			while (!feof(p)) {
				ch = fgetc(p); c_count++;
			}
			fclose(p);
			cout << input << "，字符数：" << c_count << endl;
		}

		if (countw) {
			err = fopen_s(&p, input, "r");
			int w_count = 0;
			char ch;
			bool flag = false;
			while (!feof(p)) {
				ch = fgetc(p);
				
				if (ch >= 'a'&&ch <= 'z' || ch >= 'A'&&ch <= 'Z' || ch >= '0'&&ch <= '9' || ch == '&' || ch == '-' || ch == '_' || ch == '^')
					flag = true;
				else {
					if (flag)
					{
						flag = false;
						w_count++;
					}
				}
			}
			fclose(p);
			cout << input << "，单词数：" << w_count << endl;
		}

		if (countl) {
			err = fopen_s(&p, input, "r");
			int l_count = 1;
			char ch;
			while (!feof(p)) {
				ch = fgetc(p);
				if (ch == '\n') l_count++;
			}
			fclose(p);
			cout << input << "，行数：" << l_count << endl;
		}
	}
	system("pause");
}