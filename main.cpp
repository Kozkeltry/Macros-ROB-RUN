#include <windows.h>

bool isRun = false;
bool isE = false;

void SendHardwareKey(WORD vKey, DWORD flags) {
    INPUT input = { 0 };
    input.type = INPUT_KEYBOARD;
    
    input.ki.wScan = MapVirtualKey(vKey, MAPVK_VK_TO_VSC); 
    input.ki.dwFlags = KEYEVENTF_SCANCODE | flags;
    
    SendInput(1, &input, sizeof(INPUT));
}

void func_e() {
    if ((GetAsyncKeyState(VK_XBUTTON2) & 0x8000) && !isE) {
        SendHardwareKey('E', 0);
        isE = true;
    }

    if (!(GetAsyncKeyState(VK_XBUTTON2) & 0x8000) && isE) {
        Sleep(30);
        SendHardwareKey('E', KEYEVENTF_KEYUP);
        isE = false;
    }
}

void func_run() {
    if ((GetAsyncKeyState('W') & 0x8000) && !isRun) {
        SendHardwareKey(VK_SHIFT, 0);
        isRun = true;
    }

    if (!(GetAsyncKeyState('W') & 0x8000) && isRun) {
        Sleep(30);
        SendHardwareKey(VK_SHIFT, KEYEVENTF_KEYUP);
        isRun = false;
    }
}

int main() {
    while (true)
    {
        func_e();
        func_run();
        Sleep(15);
    }

    return 0;
}