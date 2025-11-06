#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QCheckBox>
#include <QRadioButton>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QSlider>
#include <QLabel>

#include "core/cv_engine.h"

namespace gui
{

class image_widget;

class main_window : public QMainWindow
{
  Q_OBJECT
public:
  explicit main_window (QWidget *parent = nullptr);
  ~main_window () {};

private:
  image_widget *viewport = nullptr;
  std::unique_ptr<core::cv_engine> engine;
  QTimer timer;

  void build_ui ();
  void show_test_image ();

  QRadioButton *rb_image  = nullptr;
  QRadioButton *rb_video  = nullptr;
  QRadioButton *rb_camera = nullptr;
  QSpinBox     *sb_camera_index = nullptr;

  void build_dock ();
  void build_source_dock ();

  QCheckBox *cb_grayscale = nullptr;
  QSlider *sl_blur_ksize = nullptr;
  QLabel *lb_blur_value = nullptr;

  void add_grayscale_filter (QVBoxLayout *v, QWidget *panel);
  void add_blur_filter (QVBoxLayout *v, QWidget *panel);

private slots:
  void onTick ();
};

}

#endif