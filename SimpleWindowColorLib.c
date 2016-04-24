#include "SimpleWindowColorLib.h"

unsigned long RGB(Display *display,
                  unsigned char r,
                  unsigned char g,
                  unsigned char b)
{
    Colormap    cm;
    XColor      xc;
    
    cm = DefaultColormap(display, DefaultScreen(display));
    
    xc.red      = 257 * r;
    xc.green    = 257 * g;
    xc.blue     = 257 * b;
    XAllocColor(display, cm, &xc);
    
    return xc.pixel;
}

unsigned long RGB888(unsigned char r,
                     unsigned char g,
                     unsigned char b)
{
    unsigned long pixel;
    
    pixel = r;
    pixel = pixel << 8;
    pixel += g;
    pixel = pixel << 8;
    pixel += b;
    
    return pixel;
}

unsigned char GetRValue(Display *display, unsigned long pixel)
{
    Colormap    cm;
    XColor      xc;
    
    cm = DefaultColormap(display, DefaultScreen(display));
    
    XQueryColor(display, cm, &xc);
    
    return xc.red / 256;
}

unsigned char GetGValue(Display *display, unsigned long pixel)
{
    Colormap cm;
    XColor xc;
    
    cm = DefaultColormap(display, DefaultScreen(display));
    
    XQueryColor(display, cm, &xc);
    
    return xc.green / 256;
}

unsigned char GetBValue(Display *display, unsigned long pixel)
{
    Colormap cm;
    XColor xc;
    
    cm = DefaultColormap(display, DefaultScreen(display));
    
    XQueryColor(display, cm, &xc);
    
    return xc.blue / 256;
}

unsigned char GetRValue888(unsigned long pixel)
{
    return pixel >> 16;
}

unsigned char GetGValue888(unsigned long pixel)
{
    return pixel >> 8;
}

unsigned char GetBValue888(unsigned long pixel)
{
    return pixel;
}
