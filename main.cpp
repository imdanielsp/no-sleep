#include <cstdlib>
#include <iostream>

#ifdef __APPLE__
#include <ApplicationServices/ApplicationServices.h>
#endif

#ifdef _WIN32
#include <Windows.h>
#endif

enum destination { kleft, kright };

#ifdef __APPLE__
void make_mouse_move_to(destination dest) {
  CGPoint pt;

  if (dest == kleft) {
    pt.x = 0;
    pt.y = 0;
  } else {
    pt.x = 50;
    pt.y = 50;
  }

  CGEventRef theEvent =
      CGEventCreateMouseEvent(NULL, kCGEventMouseMoved, pt, kCGMouseButtonLeft);
  CGEventSetType(theEvent, kCGEventMouseMoved);
  CGEventPost(kCGHIDEventTap, theEvent);
  CFRelease(theEvent);
}
#endif

#ifdef _WIN32
void make_mouse_move_to(destination dest) {
  INPUT inputs;
  ZeroMemory(inputs, sizeof(inputs));

  inputs.type = INPUT_MOUSE;

  MOUSEINPUT mouse_input;
  mouse_input.dwflags = MOUSEEVENTF_MOVE;

  if (dest == kleft) {
    mouse_input.dx = 0;
    mouse_input.dy = 0;
  } else {
    mouse_input.dx = 0;
    mouse_input.dy = 0;
  }

  inputs.mi = mouse_input;

  UINT status = SendInput(ARRAYSIZE(&inputs), &inputs, sizeof(INPUT));
  if (status != ARRAYSIZE(inputs)) {
    OutputString(L"SendInput failed: 0x%x\n",
                 HRESULT_FROM_WIN32(GetLastError()));
  }
}
#endif

int main(int argc, char const* argv[]) {
  destination dest = kleft;

  std::cout << "Ctrl +  C to stop" << std::endl;

  while (true) {
    if (dest == kleft) {
      make_mouse_move_to(dest);
      dest = kright;
    } else {
      make_mouse_move_to(dest);
      dest = kleft;
    }

    sleep(1);
  }

  return 0;
}
