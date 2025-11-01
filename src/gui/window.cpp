#include "gui/window.h"

#include <QString>

#include <string>

namespace gui
{

window::window (const QString &title, int width, int height)
{
  widget.setWindowTitle (title);
  widget.resize (width, height);
}

void window::show ()
{
  widget.show ();
}

window::~window () {}

}
