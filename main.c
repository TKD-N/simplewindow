#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "SimpleWindowColorLib.h"

int main()
{
    Display     *display;
    Window      window;
    GC          gc;
    XEvent      event;
    Atom        a1, a2;
    long int    event_mask;
    int         quit_flag;
    int         current_color;
    
    char        *s = "Hello,Xlib!";
    
    /* ディスプレイ・サーバに接続 */
    display = XOpenDisplay(NULL);
    if(display == NULL) {
        fprintf(stderr, "Cannot open display.\n");
        exit(1);
    }
    
    /* ウィンドウを生成 */
    window = XCreateSimpleWindow(display, DefaultRootWindow(display),
                                 /* x, y */          50, 50,
                                 /* width, height */ 800, 480,
                                 /* border_width */  1,
                                 /* border */        RGB888(0, 0, 0),
                                 /* background */    RGB888(0, 255, 255));
    
    /* GCの生成 */
    gc = XCreateGC(display, window, 0, 0);
    
    /* ウィンドウを表示 */
    XMapWindow(display, window);

    /* クローズボタン関係の設定 */
    a1 = XInternAtom(display, "WM_PROTOCOLS", False);
    a2 = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, window, &a2, 1);
    
    /* イベントマスクの設定 */
    event_mask = ExposureMask | ButtonPressMask;
    XSelectInput(display, window, event_mask);
    
    /* リクエストを強制的に送信 */
    XFlush(display);
    
    quit_flag = 0;
    current_color = 0;
    
    /* イベントループ */
    while(quit_flag == 0) {
        /* イベントが来るまで待つ */
        XNextEvent(display, &event);
        
        /* イベント処理 */
        switch(event.type) {
            case ButtonPress:
                printf("(%d, %d)\n", event.xbutton.x, event.xbutton.y);
                if(current_color == 0) {
                    XSetForeground(display, gc, RGB888(255, 0, 0));
                    current_color = 1;
                } else if(current_color == 1) {
                    XSetForeground(display, gc, RGB888(0, 255, 0));
                    current_color = 2;
                } else {
                    XSetForeground(display, gc, RGB888(0, 0, 255));
                    current_color = 0;
                }
                XFillRectangle(display, window, gc, 50, 50, 200, 200);
                XSetForeground(display, gc, RGB888(0, 0, 255));
                XDrawLine(display, window, gc, 0, 0, 300, 300);
                break;
            case ClientMessage:
                if(event.xclient.message_type == a1 &&
                   event.xclient.data.l[0] == a2){
                    printf("End.\n");
                    quit_flag = 1;
                }
                break;            
            case Expose:
                XSetForeground(display, gc, RGB888(255, 255, 0));
                XFillRectangle(display, window, gc, 50, 50, 200, 200);
                
                XSetForeground(display, gc, RGB888(0, 0, 255));
                XDrawLine(display, window, gc, 0, 0, 300, 300);
                
                XSetForeground(display, gc, RGB888(0, 0, 0));
                XDrawString(display, window, gc, 25, 25, s, strlen(s));
                break;
            default:
                break;
        }
    }
    
    /* GCを破棄 */
    XFreeGC(display, gc);
    
    /* ディスプレイ・サーバとの接続を解除する */
    XCloseDisplay(display);
    
    return 0;
}
