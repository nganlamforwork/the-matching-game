#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <conio.h>
#include <Random>
#pragma comment(lib, "Winmm.lib")

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define AQUA 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_AQUA 11
#define LIGHT_RED 12
#define LIGHT_PURPLE 13
#define LIGHT_YELLOW 14
#define BRIGHT_WHITE 15

using namespace std;

class Common
{
private:
	static HWND consoleWindow;    //Con trỏ xử lí cửa sổ console
	static HANDLE consoleOutput;  //Con trỏ xử lí output console
public:
	Common() {}
	~Common() {}
	static void setUpConsole();               //Thiết lập cửa sổ console
	static void gotoXY(int, int);			  //Di chuyển con trỏ đến vị trí x,y
	static void setAndCenterWindow();         //Căn giữa và thiết lập độ phân giải màn hình console
	static void setConsoleColor(int, int);    //Thiết lập màu chữ và và màu nền
	static void hideScrollBars();             //Ẩn thanh cuộn
	static void setConsoleTitle();            //Cài đặt tiêu đề console
	static void disableMaximize();            //Vô hiệu hóa phóng to màn hình
	static void showCursor(bool);             //Ẩn hoặc hiện con trỏ
	static void setFontInfo();                //Cài đặt font chữ
	static void clearConsole();               //Xóa màn hình console
	static void disableMouseInput();          //Vô hiệu hóa chuột trong console
	static int getConsoleInput();             //Lấy lệnh từ bàn phím
	static void playSound(int);               //Phát âm thanh
};

int getRandomInt(int begin, int end);         //Hàm lấy số nguyên ngẫu nhiên