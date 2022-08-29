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
                     system("/home/mike_pol/PycharmProjects/l5p-kbl/venv/bin/bin/python3 ~/PycharmProjects/l5p-kbl/l5p_kbl.py static ffffff");
                    //fprintf(stdout, "1\n");
                    //fflush(stdout);
                } else {
                   // fprintf(stdout, "0\n");
                   // fflush(stdout);
		     system("/home/mike_pol/PycharmProjects/l5p-kbl/venv/bin/bin/python3 ~/PycharmProjects/l5p-kbl/l5p_kbl.py static ff0000");

                }
            }
        }
    }

    return(0);
}
