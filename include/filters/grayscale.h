#ifndef GRAYSCALE_H
#define GRAYSCALE_H

#include "filters/filter.h"

namespace filters
{

class grayscale : public filter
{
public:
  const char *id () const override final { return "grayscale"; }
  bool is_enabled () const override final { return enabled; }
  void set_enabled (bool on) override final { enabled = on; }

  void apply (const cv::Mat &src_bgr, cv::Mat &dst_bgr) override final 
  {
    if (!enabled) 
      { 
        dst_bgr = src_bgr;
        return; 
      }

    cv::Mat gray; 
    cv::cvtColor (src_bgr, gray, cv::COLOR_BGR2GRAY);
    cv::cvtColor (gray, dst_bgr, cv::COLOR_GRAY2BGR);
  }

private:
  bool enabled = false;
};

}


#endif