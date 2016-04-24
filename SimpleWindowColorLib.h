/* inclusion guard */
#ifndef __SIMPLEWINDOWCOLORLIB_H__
#define __SIMPLEWINDOWCOLORLIB_H__

#include <X11/Xlib.h>
#include <X11/Xutil.h>

unsigned long RGB(Display *display,
                  unsigned char r,
                  unsigned char g,
                  unsigned char b);
unsigned long RGB888(unsigned char r,
                     unsigned char g,
                     unsigned char b);

unsigned char GetRValue(Display *display, unsigned long pixel);
unsigned char GetGValue(Display *display, unsigned long pixel);
unsigned char GetBValue(Display *display, unsigned long pixel);

unsigned char GetRValue888(unsigned long pixel);
unsigned char GetGValue888(unsigned long pixel);
unsigned char GetBValue888(unsigned long pixel);

#endif /* __SIMPLEWINDOWCOLORLIB_H__ */
