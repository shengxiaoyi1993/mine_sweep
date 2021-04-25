#include <gtk/gtk.h>
#include <stdio.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>


using namespace std;

gint CloseAppWindow (GtkWidget *widget, gpointer data)
{
  gtk_main_quit ();

  return (FALSE);
}
int getScreenShotSave(const string &v_path,const string &v_suffix){
  gtk_init(0,NULL);
  GdkScreen *screen = gdk_screen_get_default();
  int width = gdk_screen_get_width(screen), height = gdk_screen_get_height(screen);

  GdkWindow *root;
  GdkPixbuf *new_pixbuf;

  root = gdk_get_default_root_window ();
  if (root == NULL) {
    return -1;
  }
  gint x_orig, y_orig;
//  gdk_drawable_get_size (root_window, &width, &height);
  gdk_window_get_origin (root, &x_orig, &y_orig);


 new_pixbuf= gdk_pixbuf_get_from_drawable (NULL, root, NULL,
                                            x_orig, y_orig, 0, 0, width, height);
  if (new_pixbuf == NULL) {
                                              return -1;
                                            }

  gdk_pixbuf_save(new_pixbuf, v_path.c_str(), v_suffix.c_str(), NULL, NULL);
  return 0;


}
