#include "gui/main_window.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QDockWidget>

#include <opencv2/opencv.hpp>

#include "globals.h"
#include "system/screen.h"
#include "gui/image_widget.h"
#include "gui/utils.h"
#include "filters/grayscale.h"

namespace gui
{

main_window::main_window (QWidget *parent) : QMainWindow (parent), engine (std::make_unique<core::cv_engine>())
{
  build_ui ();
  build_dock ();
  show_test_image ();

  engine->add_filter (std::make_shared<filters::grayscale> ());
  timer.setInterval (33); // ~ 30 fps
  connect (&timer, &QTimer::timeout, this, &main_window::onTick);
  timer.start ();
}

void main_window::build_ui ()
{
  auto *central = new QWidget (this);
  auto *layout = new QVBoxLayout (central);
  layout->setContentsMargins (0, 0, 0, 0);
  layout->setSpacing (0);

  viewport = new image_widget (central);
  
  system_utils::screen screen;
  int width = screen.get_width () / 1.5;
  int height = screen.get_height () / 1.5;

  layout->addWidget (viewport, /*stretch*/ 1);
  central->setLayout (layout);
  setCentralWidget (central);

  resize (width, height);
  setWindowTitle (WINDOW_NAME);
}

void main_window::build_dock ()
{
  auto *dock = new QDockWidget (tr ("Settings"), this);
  dock->setAllowedAreas (Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

  auto *panel = new QWidget (dock);
  auto *v = new QVBoxLayout (panel);
  v->setContentsMargins(8, 8, 8, 8);

  cb_grayscale = new QCheckBox (tr ("Grayscale"), panel);
  v->addWidget (cb_grayscale);
  v->addStretch (1);

  panel->setLayout (v);
  dock->setWidget (panel);
  addDockWidget (Qt::RightDockWidgetArea, dock);

  connect (cb_grayscale, &QCheckBox::toggled, this, [this] (bool on) {
    if (auto f = engine->find_filter ("grayscale")) 
      f->set_enabled (on);
  });
}

void main_window::show_test_image ()
{
  cv::Mat mat (480, 640, CV_8UC3, cv::Scalar (0, 0, 0));
  QImage img = cvmat_to_qimage (mat);
  viewport->set_image (img);
}

void main_window::onTick () 
{
  const QImage img = engine->process();
  if (!img.isNull ()) 
    viewport->set_image (img);
}

}
