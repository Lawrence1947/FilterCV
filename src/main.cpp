#include <QApplication>

#include "globals.h"
#include "gui/main_window.h"

int main(int argc, char *argv[])
{
  QApplication app (argc, argv);
  QApplication::setApplicationName (WINDOW_NAME);

  gui::main_window window;
  window.show ();

  return app.exec ();
}
