#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QImage>

#include <QWidget>

namespace gui
{

class main_window
{
public:
  main_window (const QString &title, int width, int height);

  void show ();

  ~main_window ();

private:
  QWidget widget;
};

}

#endif