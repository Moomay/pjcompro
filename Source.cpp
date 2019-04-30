// itshowtime.cpp : Defines the entry point for the application.
//

//#include "framework.h"
//#include "itshowtime.h"
#include "windows.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
struct calendar_info {
	char id[14];
	char dmy[12];
	char day[3];
	char month[3];
	char year[5];
	char time[6];
	char event[256];
	char loca[11];
};

#define generatePull 5
#define aboutComand 6
#define generatePush 7
#define generateClear 8
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void addControll(HWND);
void addMenus(HWND);
void registerDialogClass(HINSTANCE);
void displayDialog(HWND);
void loadImages();
void readfile();
HMENU hMenu;
HWND hEdit;
HWND hEvent;
HWND hTime;
HWND hOut;
HWND hLocate;
HWND hDate;
HWND hLogo;

HBITMAP hLogoImage;
char buffer[19][255];
char data_out[4845];
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, PWSTR pCmdLine, int nCmdShow)
{
	// Register the window class.
	const wchar_t CLASS_NAME[] = L"myWindowClass";
	WNDCLASS wc = { 0 };
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = "myWindowClass";
	


	if (!RegisterClass(&wc))
	{
		return -1;
	}
	//registerDialogClass(hInstance);

	CreateWindowW(L"myWindowClass", L"It showtime app", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 450, 800
		, NULL, NULL, NULL, NULL); //16:9
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_COMMAND:
		switch (wParam)
		{
		case 1:
			MessageBeep(MB_OK);
			break;
		case 3:
			DestroyWindow(hwnd);
			break;
		case 4:
			MessageBeep(MB_OK);
			wchar_t text[100];
			GetWindowTextW(hEdit, text, 100);
			SetWindowTextW(hwnd, text);
			break;
		case generatePull:
			readfile();
			SetWindowText(hOut, data_out);
			strcpy(data_out, ""); //reset data_out
			break;
		case generatePush:
			FILE* fd, *cr;
			char eVent[256], tIme[20], out[2000], dAte[11], lOcation[100];
			
			GetWindowText(hEvent, eVent, 256);
			GetWindowText(hTime, tIme, 20);
			GetWindowText(hDate, dAte, 11);
			GetWindowText(hLocate, lOcation, 100);
			SetWindowText(hEvent, "");
			SetWindowText(hTime, "");
			SetWindowText(hDate, "");
			SetWindowText(hLocate, "");
			strcpy_s(out, dAte);
			strcat_s(out, ",");
			strcat_s(out, tIme);
			strcat_s(out, ",");
			strcat_s(out, eVent);
			strcat_s(out, ",");
			strcat_s(out, lOcation);
			strcat_s(out, "\n");
			fd = fopen("text.txt", "a+");
			fprintf(fd,out);
			fclose(fd);
			break;
		case generateClear:
			FILE* fl;
			fl = fopen("text.txt", "w");
			fprintf(fl, "");
			fclose(fl);
			break;
		case aboutComand:
			MessageBox(NULL, "It showtime Team", "About", MB_OK | MB_ICONASTERISK);
			break;
		}
	

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;


	case WM_CREATE:
		loadImages();
		displayDialog(hwnd);
		addMenus(hwnd);
		addControll(hwnd);
		
		
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);

}
void addMenus(HWND hWnd)
{
	hMenu = CreateMenu();
	HMENU hHelpMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
	HMENU hSubMenu = CreateMenu();
	/* Dead code wait for function
	//AppendMenu(hSubMenu, MF_STRING, 1, "Supmenu");
	//AppendMenu(hFileMenu, MF_STRING, 1, "NEW");
	//AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu, "Open");
	//AppendMenu(hFileMenu, MF_STRING, 4, "Change Title");
	*/
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hFileMenu, MF_STRING, 3, "Exit");
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hHelpMenu, "Help");
	AppendMenu(hHelpMenu, MF_STRING, aboutComand, "About");


	SetMenu(hWnd, hMenu);
}

void addControll(HWND hWnd)
{
	/*
	CreateWindowW(L"static", L"EnterText:", WS_VISIBLE | WS_CHILD | WS_BORDER| SS_CENTER, 200, 100, 100, 50
		, hWnd, NULL, NULL, NULL);
	hEdit = CreateWindowW(L"Edit", L"ffffff", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 200, 152, 100, 50, hWnd, NULL, NULL, NULL);
	*/
	CreateWindowW(L"static", L"Event :", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER , 100, 150, 98, 38, hWnd, NULL, NULL, NULL, NULL);
	hEvent = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 150, 150, 38, hWnd, NULL, NULL, NULL, NULL);

	CreateWindowW(L"static", L"time :", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 100, 190, 98, 38, hWnd, NULL, NULL, NULL, NULL);
	hTime = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 190, 150, 38, hWnd, NULL, NULL, NULL, NULL);

	CreateWindowW(L"static", L"Date :", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 100, 230, 98, 38, hWnd, NULL, NULL, NULL, NULL);
	hDate = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 230, 80, 38, hWnd, NULL, NULL, NULL, NULL);

	CreateWindowW(L"static", L"Location :", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 100, 270, 98, 38, hWnd, NULL, NULL, NULL, NULL);
	hLocate = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 270, 150, 38, hWnd, NULL, NULL, NULL, NULL);

	CreateWindowW(L"button", L"Pull", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 340, 98, 38, hWnd, (HMENU)generatePull, NULL, NULL, NULL);
	CreateWindowW(L"button", L"Push", WS_VISIBLE | WS_CHILD | WS_BORDER, 50, 340, 98, 38, hWnd, (HMENU)generatePush, NULL, NULL, NULL);
	CreateWindowW(L"button", L"Clear", WS_VISIBLE | WS_CHILD | WS_BORDER, 250, 340, 98, 38, hWnd, (HMENU)generateClear, NULL, NULL, NULL);
	hOut = CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER , 50, 400, 350, 300, hWnd, NULL, NULL, NULL, NULL);
	hLogo = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 175, 20, 100, 100, hWnd, NULL, NULL, NULL, NULL);
	SendMessageW(hLogo, STM_SETIMAGE, IMAGE_BITMAP,(LPARAM) hLogoImage);
}
LRESULT CALLBACK DialogProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}

void registerDialogClass(HINSTANCE hInst)
{

	WNDCLASS dialog = { 0 };
	dialog.hbrBackground = (HBRUSH)COLOR_WINDOW;
	dialog.hCursor = LoadCursor(NULL, IDC_ARROW);
	dialog.lpfnWndProc = DialogProcedure;
	dialog.hInstance = hInst;
	dialog.lpszClassName = "myDialogClass";

	RegisterClass(&dialog);
}
void displayDialog(HWND hWnd)
{
	CreateWindowW(L"myDialogClass", L"", WS_VISIBLE
		| WS_OVERLAPPEDWINDOW, 400, 400, 200, 200, hWnd, NULL, NULL, NULL, NULL);
}
void loadImages()
{
	hLogoImage = (HBITMAP)LoadImageW(NULL, L"icon.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}
void readfile()
{
	int line = 5;
	int i, j;

	struct calendar_info info[18];
	struct calendar_info temp;
	FILE* fp, * ca;
	int numL;
	char numstr[30];
	ca = fopen("numline.txt", "r");
	fgets(numstr, 30, ca);
	numL = atoi(numstr);
	fclose(ca);
	fp = fopen("text.txt", "r");
	//ล้างบัพเฟอร์
	for (int i = 0; i < 18; i++) 
	{
		strcpy(buffer[i], "");
	}
	//get data in flie
	for (int i = 0; i < 18; i++) 
	{
		fgets(buffer[i], 255, fp);
	}
	/*for (j = 0; j < line; j++) {
		char* token = buffer[j];
		token = strtok(buffer[j], ",");
		for (i = 0; i < 4; i++) {
			switch (i) {
			case 0:
				strcpy(info[j].dmy, token);
				break;
			case 1:
				strcpy(info[j].time, token);
				break;
			case 2:
				strcpy(info[j].event, token);
				break;
			case 3:
				strcpy(info[j].loca, token);
				break;
			}
			token = strtok(NULL, ",");
		}
	}
	for (j = 0; j < line; j++) {
		char* token = info[j].dmy;
		token = strtok(info[j].dmy, "/");
		for (i = 0; i < 3; i++) {
			switch (i) {
			case 0:
				strcpy(info[j].day, token);
				break;
			case 1:
				strcpy(info[j].month, token);
				break;
			case 2:
				strcpy(info[j].year, token);
				break;
			}
			token = strtok(NULL, "/");
		}
	}
	for (j = 0; j < line; j++) {
		strcpy(info[j].id, info[j].year);
		strcat(info[j].id, info[j].month);
		strcat(info[j].id, info[j].day);
		strcat(info[j].id, info[j].time);
		//printf("%s\n", info[j].id);
	}
	//printf("\n");
	for (i = 0; i < line - 1; i++) {
		for (j = 0; j < line - 1; j++) {
			if (strcmp(info[j].id, info[j + 1].id) > 0) {
				temp = info[j];
				info[j] = info[j + 1];
				info[j + 1] = temp;
			}
		}
	}*/
	//เอามาต่อกัน
	for (int i = 0; i < 18; i++)
	{
		strcat(data_out, buffer[i]);
	}
	fclose(fp);
}
