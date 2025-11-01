#include <QApplication>

#include "globals.h"
#include "gui/window.h"
#include "system/screen.h"

int main(int argc, char *argv[])
{
  QApplication app (argc, argv);

  system_utils::screen screen;

  gui::window main_window (WINDOW_NAME, screen.get_width (), screen.get_height ());
  main_window.show ();

  return app.exec ();
}
