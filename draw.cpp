// draw.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "draw.h"
#include <deque>
#include <vector>

#define MAX_LOADSTRING 100
#define TMR_1 1
#define TMR_2 2
#define TMR_3 3
#define ID_RBUTTON1 201
#define ID_BUTTON1 202
#define ID_BUTTON2 203
#define ID_BUTTON3 204
#define ID_BUTTON4 205
#define ID_BUTTON5 206
#define ID_BUTTON6 207
#define ID_BUTTON7 208
#define ID_BUTTON8 209
#define ID_BUTTON9 210
#define ID_BUTTON10 211
#define ID_BUTTON11 212
#define ID_BUTTON12 213
#define ID_BUTTON13 214
#define ID_BUTTON14 215
#define ID_BUTTON15 216
#define ID_BUTTON16 217
#define ID_BUTTON17 218
#define ID_BUTTON18 219
#define ID_BUTTON19 220
#define ID_BUTTON20 221


// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

struct kolejka 
{
	int prog1;
	int prog2;
	bool kierunek;
};

kolejka nowa;

INT value;
HWND hwndButton, hStatic;
std::deque<kolejka>Poczekalnia;												//kolejka przechowujaca pasazerow czekajacych na winde
std::deque<int>Winda;														//kolejka przechowujaca informacje gdzie pasazerowie w windzie chca trafic
std::deque<int>gdzie;														//kolejka przechowujaca informacje gdzie winda ma pojechac

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
RECT drawArea1 = { 396, 100, 464, 560 };



void MyOnPaint(HDC hdc)
{
	
	Graphics graphics(hdc);
	Pen pen(Color(255,0,0,255));
	Pen pen1(Color(255, 0, 0, 0));
	Pen pen2(Color(255, 123, 69, 0));
	graphics.DrawLine(&pen2,0,550,395,550);
	graphics.DrawLine(&pen2, 465, 450, 760, 450);
	graphics.DrawLine(&pen2, 0, 350, 395,350 );
	graphics.DrawLine(&pen2, 465, 250, 760, 250);
	graphics.DrawLine(&pen2, 0, 150, 395, 150);
	graphics.DrawRectangle(&pen1, 395, 95 , 70 , 490);


	graphics.DrawRectangle(&pen,400,500-value,60, 50);
}

int OnCreate(HWND hWnd)
{
   //SetTimer(hWnd, TMR_1, 25, 0);
   return 0;
}



int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	value= 10;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAW));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken);

	return (int) msg.wParam;
}

void repaintWindow(HWND hWnd, HDC &hdc, PAINTSTRUCT &ps, RECT *drawArea)
{
	if (drawArea == NULL)
		InvalidateRect(hWnd, NULL, TRUE);
	else
		InvalidateRect(hWnd, drawArea, TRUE);
	hdc = BeginPaint(hWnd, &ps);
	MyOnPaint(hdc);
	EndPaint(hWnd, &ps);
}




//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAW));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_DRAW);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   hwndButton = CreateWindow(TEXT("button"),
	   TEXT("3"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   0, 0,
	   20, 20,
	   hWnd,
	   (HMENU)ID_BUTTON1,
	   hInstance,
	   NULL);

   hwndButton = CreateWindow(TEXT("button"),
	   TEXT("2"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   0, 20,
	   20, 20,
	   hWnd,
	   (HMENU)ID_BUTTON2,
	   hInstance,
	   NULL);

   hwndButton = CreateWindow(TEXT("button"),
	   TEXT("1"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   0, 40,
	   20, 20,
	   hWnd,
	   (HMENU)ID_BUTTON3,
	   hInstance,
	   NULL);

   hwndButton = CreateWindow(TEXT("button"),
	   TEXT("0"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   0, 60,
	   20, 20,
	   hWnd,
	   (HMENU)ID_BUTTON4,
	   hInstance,
	   NULL);

   hwndButton = CreateWindow(TEXT("button"),
	   TEXT("4"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   740, 150,
	   20, 20,
	   hWnd,
	   (HMENU)ID_BUTTON5,
	   hInstance,
	   NULL);

   hwndButton = CreateWindow(TEXT("button"),
	   TEXT("2"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   740, 170,
	   20, 20,
	   hWnd,
	   (HMENU)ID_BUTTON6,
	   hInstance,
	   NULL);

   hwndButton = CreateWindow(TEXT("button"),
	   TEXT("1"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   740, 190,
	   20, 20,
	   hWnd,
	   (HMENU)ID_BUTTON7,
	   hInstance,
	   NULL);

   hwndButton = CreateWindow(TEXT("button"),
	   TEXT("0"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   740, 210,
	   20, 20,
	   hWnd,
	   (HMENU)ID_BUTTON8,
	   hInstance,
	   NULL);

   hwndButton = CreateWindow(TEXT("button"),
	   TEXT("4"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   0, 240,
	   20, 20,
	   hWnd,
	   (HMENU)ID_BUTTON9,
	   hInstance,
	   NULL);

   hwndButton = CreateWindow(TEXT("button"),
	   TEXT("3"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   0, 260,
	   20, 20,
	   hWnd,
	   (HMENU)ID_BUTTON10,
	   hInstance,
	   NULL);

   hwndButton = CreateWindow(TEXT("button"),
	   TEXT("1"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   0, 280,
	   20, 20,
	   hWnd,
	   (HMENU)ID_BUTTON11,
	   hInstance,
	   NULL);

   hwndButton = CreateWindow(TEXT("button"),
	   TEXT("0"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   0, 300,
	   20, 20,
	   hWnd,
	   (HMENU)ID_BUTTON12,
	   hInstance,
	   NULL);

   hwndButton = CreateWindow(TEXT("button"),
	   TEXT("4"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   740, 350,
	   20, 20,
	   hWnd,
	   (HMENU)ID_BUTTON13,
	   hInstance,
	   NULL);

   hwndButton = CreateWindow(TEXT("button"),
	   TEXT("3"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   740, 370,
	   20, 20,
	   hWnd,
	   (HMENU)ID_BUTTON14,
	   hInstance,
	   NULL);

   hwndButton = CreateWindow(TEXT("button"),
	   TEXT("2"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   740, 390,
	   20, 20,
	   hWnd,
	   (HMENU)ID_BUTTON15,
	   hInstance,
	   NULL);

   hwndButton = CreateWindow(TEXT("button"),
	   TEXT("0"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   740, 410,
	   20, 20,
	   hWnd,
	   (HMENU)ID_BUTTON16,
	   hInstance,
	   NULL);

   hwndButton = CreateWindow(TEXT("button"),
	   TEXT("4"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   0, 460,
	   20, 20,
	   hWnd,
	   (HMENU)ID_BUTTON17,
	   hInstance,
	   NULL);

   hwndButton = CreateWindow(TEXT("button"),
	   TEXT("3"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   0, 480,
	   20, 20,
	   hWnd,
	   (HMENU)ID_BUTTON18,
	   hInstance,
	   NULL);

   hwndButton = CreateWindow(TEXT("button"),
	   TEXT("2"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   0, 500,
	   20, 20,
	   hWnd,
	   (HMENU)ID_BUTTON19,
	   hInstance,
	   NULL);

   hwndButton = CreateWindow(TEXT("button"),
	   TEXT("1"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   0, 520,
	   20, 20,
	   hWnd,
	   (HMENU)ID_BUTTON20,
	   hInstance,
	   NULL);
   hwndButton = CreateWindowExA(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_CENTER, 920, 122, 150, 20, hWnd, NULL, NULL, NULL);
   SetWindowTextA(hwndButton, "Masa pasazerow:");

   OnCreate(hWnd);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
//funkcja odpowiedzialna za wyswietlanie aktualnej masy pasazerow
void pasazerowie(HWND hWnd)
{
	char bufor[1024];
	sprintf(bufor, "%d", 70 * Winda.size());							//zapisanie aktualnej masy do bufora
	hStatic = CreateWindowExA(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_CENTER, 990, 152, 30, 20, hWnd, NULL, NULL, NULL);
	SetWindowTextA(hStatic, bufor);
}
//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	//OnCreate(hWnd,wParam,lParam);
	//OnTimer(hWnd,wParam,lParam);

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_BUTTON1:
			nowa.prog1 = 400;													//skad jedziemy
			nowa.prog2 = 300;													//dokad jedziemy
			nowa.kierunek = true;							//true - na dol, false - do gory
			Poczekalnia.push_back(nowa);
			if (Poczekalnia.size() == 1 && Winda.size() == 0)
			{
				gdzie.push_back(nowa.prog1);
				SetTimer(hWnd, TMR_1, 25, 0);
			}
			break;
		case ID_BUTTON2:
			nowa.prog1 = 400;
			nowa.prog2 = 200;
			nowa.kierunek = true;
			Poczekalnia.push_back(nowa);
			if (Poczekalnia.size() == 1 && Winda.size() == 0)
			{
				gdzie.push_back(nowa.prog1);
				SetTimer(hWnd, TMR_1, 25, 0);
			}
			break;
		case ID_BUTTON3:
			nowa.prog1 = 400;
			nowa.prog2 = 100;
			nowa.kierunek = true;
			Poczekalnia.push_back(nowa);
			if (Poczekalnia.size() == 1 && Winda.size() == 0)
			{
				gdzie.push_back(nowa.prog1);
				SetTimer(hWnd, TMR_1, 25, 0);
			}
			break;
		case ID_BUTTON4:
			nowa.prog1 = 400;
			nowa.prog2 = 0;
			nowa.kierunek = true;
			Poczekalnia.push_back(nowa);
			if (Poczekalnia.size() == 1 && Winda.size() == 0)
			{
				gdzie.push_back(nowa.prog1);
				SetTimer(hWnd, TMR_1, 25, 0);
			}
			break;
		case ID_BUTTON5:
			nowa.prog1 = 300;
			nowa.prog2 = 400;
			nowa.kierunek = false;
			Poczekalnia.push_back(nowa);
			if (Poczekalnia.size() == 1 && Winda.size() == 0)
			{
				gdzie.push_back(nowa.prog1);
				SetTimer(hWnd, TMR_1, 25, 0);
			}
			break;
		case ID_BUTTON6:
			nowa.prog1 = 300;
			nowa.prog2 = 200;
			nowa.kierunek = true;
			Poczekalnia.push_back(nowa);
			if (Poczekalnia.size() == 1 && Winda.size() == 0)
			{
				gdzie.push_back(nowa.prog1);
				SetTimer(hWnd, TMR_1, 25, 0);
			}
			break;
		case ID_BUTTON7:
			nowa.prog1 = 300;
			nowa.prog2 = 100;
			nowa.kierunek = true;
			Poczekalnia.push_back(nowa);
			if (Poczekalnia.size() == 1 && Winda.size() == 0)
			{
				gdzie.push_back(nowa.prog1);
				SetTimer(hWnd, TMR_1, 25, 0);
			}
			break;
		case ID_BUTTON8:
			nowa.prog1 = 300;
			nowa.prog2 = 0;
			nowa.kierunek = true;
			Poczekalnia.push_back(nowa);
			if (Poczekalnia.size() == 1 && Winda.size() == 0)
			{
				gdzie.push_back(nowa.prog1);
				SetTimer(hWnd, TMR_1, 25, 0);
			}
			break;
		case ID_BUTTON9:
			nowa.prog1 = 200;
			nowa.prog2 = 400;
			nowa.kierunek = false;
			Poczekalnia.push_back(nowa);
			if (Poczekalnia.size() == 1 && Winda.size() == 0)
			{
				gdzie.push_back(nowa.prog1);
				SetTimer(hWnd, TMR_1, 25, 0);
			}
			break;
		case ID_BUTTON10:
			nowa.prog1 = 200;
			nowa.prog2 = 300;
			nowa.kierunek = false;
			Poczekalnia.push_back(nowa);
			if (Poczekalnia.size() == 1 && Winda.size() == 0)
			{
				gdzie.push_back(nowa.prog1);
				SetTimer(hWnd, TMR_1, 25, 0);
			}
			break;
		case ID_BUTTON11:
			nowa.prog1 = 200;
			nowa.prog2 = 100;
			nowa.kierunek = true;
			Poczekalnia.push_back(nowa);
			if (Poczekalnia.size() == 1 && Winda.size() == 0)
			{
				gdzie.push_back(nowa.prog1);
				SetTimer(hWnd, TMR_1, 25, 0);
			}
			break;
		case ID_BUTTON12:
			nowa.prog1 = 200;
			nowa.prog2 = 0;
			nowa.kierunek = true;
			Poczekalnia.push_back(nowa);
			if (Poczekalnia.size() == 1 && Winda.size() == 0)
			{
				gdzie.push_back(nowa.prog1);
				SetTimer(hWnd, TMR_1, 25, 0);
			}
			break;
		case ID_BUTTON13:
			nowa.prog1 = 100;
			nowa.prog2 = 400;
			nowa.kierunek = false;
			Poczekalnia.push_back(nowa);
			if (Poczekalnia.size() == 1 && Winda.size() == 0)
			{
				gdzie.push_back(nowa.prog1);
				SetTimer(hWnd, TMR_1, 25, 0);
			}
			break;
		case ID_BUTTON14:
			nowa.prog1 = 100;
			nowa.prog2 = 300;
			nowa.kierunek = false;
			Poczekalnia.push_back(nowa);
			if (Poczekalnia.size() == 1 && Winda.size() == 0)
			{
				gdzie.push_back(nowa.prog1);
				SetTimer(hWnd, TMR_1, 25, 0);
			}			break;
		case ID_BUTTON15:
			nowa.prog1 = 100;
			nowa.prog2 = 200;
			nowa.kierunek = false;
			Poczekalnia.push_back(nowa);
			if (Poczekalnia.size() == 1 && Winda.size() == 0)
			{
				gdzie.push_back(nowa.prog1);
				SetTimer(hWnd, TMR_1, 25, 0);
			}
			break;
		case ID_BUTTON16:
			nowa.prog1 = 100;
			nowa.prog2 = 0;
			nowa.kierunek = true;
			Poczekalnia.push_back(nowa);
			if (Poczekalnia.size() == 1 && Winda.size() == 0)
			{
				gdzie.push_back(nowa.prog1);
				SetTimer(hWnd, TMR_1, 25, 0);
			}
			break;
		case ID_BUTTON17:
			nowa.prog1 = 000;
			nowa.prog2 = 400;
			nowa.kierunek = false;
			Poczekalnia.push_back(nowa);
			if (Poczekalnia.size() == 1 && Winda.size() == 0)
			{
				gdzie.push_back(nowa.prog1);
				SetTimer(hWnd, TMR_1, 25, 0);
			}
			break;
		case ID_BUTTON18:
			nowa.prog1 = 000;
			nowa.prog2 = 300;
			nowa.kierunek = false;
			Poczekalnia.push_back(nowa);
			if (Poczekalnia.size() == 1 && Winda.size() == 0)
			{
				gdzie.push_back(nowa.prog1);
				SetTimer(hWnd, TMR_1, 25, 0);
			}
			break;
		case ID_BUTTON19:
			nowa.prog1 = 000;
			nowa.prog2 = 200;
			nowa.kierunek = false;
			Poczekalnia.push_back(nowa);
			if (Poczekalnia.size() == 1 && Winda.size() == 0)
			{
				gdzie.push_back(nowa.prog1);
				SetTimer(hWnd, TMR_1, 25, 0);
			}
			break;
		case ID_BUTTON20:
			nowa.prog1 = 000;
			nowa.prog2 = 100;
			nowa.kierunek = false;
			Poczekalnia.push_back(nowa);
			if (Poczekalnia.size() == 1 && Winda.size() == 0)
			{
				gdzie.push_back(nowa.prog1);
				SetTimer(hWnd, TMR_1, 25, 0);
			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		MyOnPaint(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_TIMER:
		switch (wParam)
		{
		case TMR_1:
			if (gdzie.size() != 0)
			{
				if (value <= gdzie.front()) {
					value++;
					//jesli ktos chce wsiasc po drodze
					for (int i = 0; i < Poczekalnia.size(); i++)
						if (Poczekalnia[i].prog1 < gdzie.front() && Poczekalnia[i].kierunek == false && value < Poczekalnia[i].prog1)
							if (Poczekalnia[i].prog1 != gdzie.front())
								gdzie.push_front(Poczekalnia[i].prog1);						//nowe pietro docelowe
					

					if (value >= gdzie.front())											//jesli dojechalismy na pietro docelowe
					{
						KillTimer(hWnd, TMR_1);
						Sleep(1000);
						
						int ile = Winda.size();											//wszyscy ktorzy mieli tu wysiasc, wysiadaja
						for(int j = 0; j < ile; j++)
							for (int i = 0; i < Winda.size(); i++)
								if (Winda[i] == gdzie.front())
									Winda.erase(Winda.begin() + i);

						ile = Poczekalnia.size();
						for (int j = 0; j < ile; j++)
							for (int i = 0; i < Poczekalnia.size(); i++)
							{
								if (Poczekalnia[i].prog1 == gdzie.front() && Winda.size() == 0)
								{
									Winda.push_back(Poczekalnia[i].prog2);
									Poczekalnia.erase(Poczekalnia.begin() + i);
								}
								else if (Poczekalnia[i].prog1 == gdzie.front() && ((Poczekalnia[i].prog2 <= gdzie.front() && Winda[0] <= gdzie.front())
									|| (Poczekalnia[i].prog2 >= gdzie.front() && Winda[0] >= gdzie.front())))
								{
									Winda.push_back(Poczekalnia[i].prog2);
									Poczekalnia.erase(Poczekalnia.begin() + i);
								}
							}

						pasazerowie(hWnd);
						if (gdzie.size() != 0)
							gdzie.pop_front();

						  if(gdzie.size() != 0)
							SetTimer(hWnd, TMR_1, 25, 0);				
						  else if (gdzie.size() == 0)
							  SetTimer(hWnd, TMR_2, 25, 0);
						 else  if (Poczekalnia.size() != 0)
						 {
							 gdzie.push_front(Poczekalnia.front().prog1);
							 SetTimer(hWnd, TMR_1, 25, 0);
						 }

					}
					repaintWindow(hWnd, hdc, ps, &drawArea1);
				}
				
				 else if (value >= gdzie.front()) {
					value--;
					//jesli ktos chce wsiasc po drodze
					for (int i = 0; i < Poczekalnia.size(); i++)
						if (Poczekalnia[i].prog1 > gdzie.front() && Poczekalnia[i].kierunek == true && value > Poczekalnia[i].prog1)
							if (Poczekalnia[i].prog1 != gdzie.front())
								gdzie.push_front(Poczekalnia[i].prog1);						//nowe pietro docelowe

					if (value <= gdzie.front())											//jesli dojechalismy na pietro docelowe
					{
						KillTimer(hWnd, TMR_1);
						Sleep(1000);
										 
						int ile = Winda.size();											//wszyscy ktorzy mieli tu wysiasc, wysiadaja
						for (int j = 0; j < ile; j++)
							for (int i = 0; i < Winda.size(); i++)
								if (Winda[i] == gdzie.front())
									Winda.erase(Winda.begin() + i);		

						ile = Poczekalnia.size();
						for (int j = 0; j < ile; j++)
							for (int i = 0; i < Poczekalnia.size(); i++)
							{
								if (Poczekalnia[i].prog1 == gdzie.front() && Winda.size() == 0)
								{
									Winda.push_back(Poczekalnia[i].prog2);
									Poczekalnia.erase(Poczekalnia.begin() + i);
								}
								else if (Poczekalnia[i].prog1 == gdzie.front() && ((Poczekalnia[i].prog2 <= gdzie.front() && Winda[0] <= gdzie.front())
									|| (Poczekalnia[i].prog2 >= gdzie.front() && Winda[0] >= gdzie.front())))
								{
									Winda.push_back(Poczekalnia[i].prog2);
									Poczekalnia.erase(Poczekalnia.begin() + i);
								}
							}
						
						pasazerowie(hWnd);
						if(gdzie.size() != 0)
							gdzie.pop_front();

						if (gdzie.size() != 0)
							SetTimer(hWnd, TMR_1, 25, 0);
						else if (gdzie.size() == 0)
							SetTimer(hWnd, TMR_2, 25, 0);
						else if(Poczekalnia.size() != 0)
						{
							gdzie.push_front(Poczekalnia.front().prog1);
							SetTimer(hWnd, TMR_1, 25, 0);
						}
					}
					repaintWindow(hWnd, hdc, ps, &drawArea1);
				}
			}

			break;

		case TMR_2:
			if (Winda.size() != 0)
			{
				if (value >= Winda.front()) {
					value--;
					//jesli ktos chce wsiasc po drodze
					for (int i = 0; i < Poczekalnia.size(); i++)
						if (Poczekalnia[i].prog1 > Winda.front() && Poczekalnia[i].kierunek == true && value > Poczekalnia[i].prog1)
						{
							gdzie.push_front(Poczekalnia[i].prog1);
							KillTimer(hWnd, TMR_2);
							SetTimer(hWnd, TMR_1, 25, 0);
						}

					for (int i = 0; i < Winda.size(); i++)
						if (Winda[i] > Winda.front() && value > Winda[i])
							Winda.push_front(Winda[i]);


					if (value <= Winda.front())										//jesli dojechalismy na pietro docelowe
					{
						KillTimer(hWnd, TMR_2);
						Sleep(1000);
						int miejsce = Winda.front();
						if (Winda.size() != 0)										//wszyscy ktorzy mieli tu wysiasc, wysiadaja
						{
							int doUsuniecia = Winda.front();
							int ile = Winda.size();
							for (int j = 0; j < ile; j++)
								for (int i = 0; i < Winda.size(); i++)
									if (Winda[i] == doUsuniecia)
										Winda.erase(Winda.begin() + i);
						} 

						int ile = Poczekalnia.size();
						for (int j = 0; j < ile; j++)
							for (int i = 0; i < Poczekalnia.size(); i++)
							{
								if (Poczekalnia[i].prog1 == miejsce && Winda.size() == 0)
								{
									Winda.push_back(Poczekalnia[i].prog2);
									Poczekalnia.erase(Poczekalnia.begin() + i);
								}
								else if (Poczekalnia[i].prog1 == miejsce && ((Poczekalnia[i].prog2 <= miejsce && Winda[0] <= miejsce)
									|| (Poczekalnia[i].prog2 >= miejsce && Winda[0] >= miejsce)))
								{
									Winda.push_back(Poczekalnia[i].prog2);
									Poczekalnia.erase(Poczekalnia.begin() + i);
								}
							}

						pasazerowie(hWnd);

						if(Winda.size() != 0)
							SetTimer(hWnd, TMR_2, 25, 0);
						else if(gdzie.size() != 0)
							SetTimer(hWnd, TMR_1, 25, 0);
						else if(Poczekalnia.size() != 0)
						{
							gdzie.push_front(Poczekalnia.front().prog1);
							SetTimer(hWnd, TMR_1, 25, 0);
						}
					}

					repaintWindow(hWnd, hdc, ps, &drawArea1);
				}

				else if (value <= Winda.front()) {
					value++;
					//jesli ktos chce wsiasc po drodze
					for (int i = 0; i < Poczekalnia.size(); i++)
						if (Poczekalnia[i].prog1 < Winda.front() && Poczekalnia[i].kierunek == false && value < Poczekalnia[i].prog1)
						{
							gdzie.push_front(Poczekalnia[i].prog1);
							KillTimer(hWnd, TMR_2);
							SetTimer(hWnd, TMR_1, 25, 0);
						}

					for (int i = 0; i < Winda.size(); i++)
						if (Winda[i] < Winda.front() && value < Winda[i])
							Winda.push_front(Winda[i]);

					if (value >= Winda.front())											//jesli dojechalismy na pietro docelowe
					{
						KillTimer(hWnd, TMR_2);
						Sleep(1000);
						int miejsce = Winda.front();

						if (Winda.size() != 0)											//wszyscy ktorzy mieli tu wysiasc, wysiadaja
						{
							int doUsuniecia = Winda.front(); 
							int ile = Winda.size();
							for (int j = 0; j < ile; j++)
								for (int i = 0; i < Winda.size(); i++)
									if (Winda[i] == doUsuniecia)
										Winda.erase(Winda.begin() + i);
						}

						int ile = Poczekalnia.size();
						for (int j = 0; j < ile; j++)
							for (int i = 0; i < Poczekalnia.size(); i++)
							{
								if (Poczekalnia[i].prog1 == miejsce && Winda.size() == 0)
								{
									Winda.push_back(Poczekalnia[i].prog2);
									Poczekalnia.erase(Poczekalnia.begin() + i);
								}
								else if (Poczekalnia[i].prog1 == miejsce && ((Poczekalnia[i].prog2 <= miejsce && Winda[0] <= miejsce)
									|| (Poczekalnia[i].prog2 >= miejsce && Winda[0] >= miejsce)))
								{
									Winda.push_back(Poczekalnia[i].prog2);
									Poczekalnia.erase(Poczekalnia.begin() + i);
								}
							}

						pasazerowie(hWnd);
						if (Winda.size() != 0)
							SetTimer(hWnd, TMR_2, 25, 0);
						else if (gdzie.size() != 0)
							SetTimer(hWnd, TMR_1, 25, 0);
						else if(Poczekalnia.size() != 0)
						{
							gdzie.push_front(Poczekalnia.front().prog1);
							SetTimer(hWnd, TMR_1, 25, 0);
						}
						
					}

					repaintWindow(hWnd, hdc, ps, &drawArea1);
				}
			}
			
			break;

		}
		
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
