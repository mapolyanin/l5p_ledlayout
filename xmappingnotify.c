#include <stdio.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#include <system.h>
int main(int argc, char **argv)
{
        XEvent e;
        Display *d;

        if (!(d = XOpenDisplay(NULL))) {
                fprintf(stderr, "cannot open display\n");
                return 1;
        }

        XKeysymToKeycode(d, XK_F1);

    int xkbEventType;
    XkbQueryExtension(d, 0, &xkbEventType, 0, 0, 0);
    XkbSelectEvents(d, XkbUseCoreKbd, XkbAllEventsMask, XkbAllEventsMask);

    XSync(d, False);

    while (1) {
        XNextEvent(d, &e);
        if (e.type == xkbEventType) {
            XkbEvent* xkbEvent = (XkbEvent*) &e;
            if (xkbEvent->any.xkb_type == XkbStateNotify) {
                int lang = xkbEvent->state.group;
                if (lang == 1) {
                     system("~/scripts/l5p_ledlayout/venv/bin/bin/python3 ~/scripts/l5p_ledlayout/l5p_kbl.py static ff0000");

                } else {

		     system("~/scripts/l5p_ledlayout/venv/bin/bin/python3 ~/scripts/l5p_ledlayout/l5p_kbl.py static ffffff");

                }
            }
        }
    }

    return(0);
}
