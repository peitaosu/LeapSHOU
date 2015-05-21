#ifndef GETWMNAME
#define GETWMNAME

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xos.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <string.h>
Status FetchName(Display *dpy, Window w, char **winname)
{

    XTextProperty text_prop;
    char **list;
    int num;

    XGetWMName(dpy, w, &text_prop);
    Xutf8TextPropertyToTextList(dpy, &text_prop, &list, &num);

    XFree(text_prop.value);
    *winname = (char *)strdup(*list);
    XFreeStringList(list);
    return 1;
}

int GetWMName(){
    Display *thedisp=XOpenDisplay(NULL);
    Window win = 0 ;
    int ret , val;
    ret = XGetInputFocus(thedisp, &win, &val);
    printf("disp=%x win=%x ret=%d ", thedisp, win , ret);
    char *str;
    ret = FetchName(thedisp, win, &str);

    printf("str=%s ret=%d ", str, ret);
    int strl = strlen(str);
    //str = substr();
    /*switch (str) {
    case "PalmA":
        return 1;
        break;
    default:
        break;
    }*/

}
#endif // GETWMNAME

