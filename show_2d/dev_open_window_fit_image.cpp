///////////////////////////////////////////////////////////////////////////////
// File generated by HDevelop for HALCON/C++ Version 23.05.0.0
// Non-ASCII strings in this file are encoded in local-8-bit encoding (cp936).
// Ensure that the interface encoding is set to locale encoding by calling
// SetHcppInterfaceStringEncodingIsUtf8(false) at the beginning of the program.
// 
// Please note that non-ASCII characters in string constants are exported
// as octal codes in order to guarantee that the strings are correctly
// created on all systems, independent on any compiler settings.
// 
// Source files with different encoding should not be mixed in one project.
///////////////////////////////////////////////////////////////////////////////

#include "HalconCpp.h"
#include "HDevThread.h"



using namespace HalconCpp;


// Chapter: Develop
// Short Description: Open a new graphics window that preserves the aspect ratio of the given image. 
void dev_open_window_fit_image (HObject ho_Image, HTuple hv_Row, HTuple hv_Column, 
    HTuple hv_WidthLimit, HTuple hv_HeightLimit, HTuple *hv_WindowHandle)
{

  // Local iconic variables

  // Local control variables
  HTuple  hv_MinWidth, hv_MaxWidth, hv_MinHeight;
  HTuple  hv_MaxHeight, hv_ResizeFactor, hv_ImageWidth, hv_ImageHeight;
  HTuple  hv_TempWidth, hv_TempHeight, hv_WindowWidth, hv_WindowHeight;

  //This procedure opens a new graphics window and adjusts the size
  //such that it fits into the limits specified by WidthLimit
  //and HeightLimit, but also maintains the correct image aspect ratio.
  //
  //If it is impossible to match the minimum and maximum extent requirements
  //at the same time (f.e. if the image is very long but narrow),
  //the maximum value gets a higher priority,
  //
  //Parse input tuple WidthLimit
  if (0 != (HTuple(int((hv_WidthLimit.TupleLength())==0)).TupleOr(int(hv_WidthLimit<0))))
  {
    hv_MinWidth = 500;
    hv_MaxWidth = 800;
  }
  else if (0 != (int((hv_WidthLimit.TupleLength())==1)))
  {
    hv_MinWidth = 0;
    hv_MaxWidth = hv_WidthLimit;
  }
  else
  {
    hv_MinWidth = ((const HTuple&)hv_WidthLimit)[0];
    hv_MaxWidth = ((const HTuple&)hv_WidthLimit)[1];
  }
  //Parse input tuple HeightLimit
  if (0 != (HTuple(int((hv_HeightLimit.TupleLength())==0)).TupleOr(int(hv_HeightLimit<0))))
  {
    hv_MinHeight = 400;
    hv_MaxHeight = 600;
  }
  else if (0 != (int((hv_HeightLimit.TupleLength())==1)))
  {
    hv_MinHeight = 0;
    hv_MaxHeight = hv_HeightLimit;
  }
  else
  {
    hv_MinHeight = ((const HTuple&)hv_HeightLimit)[0];
    hv_MaxHeight = ((const HTuple&)hv_HeightLimit)[1];
  }
  //
  //Test, if window size has to be changed.
  hv_ResizeFactor = 1;
  GetImageSize(ho_Image, &hv_ImageWidth, &hv_ImageHeight);
  //First, expand window to the minimum extents (if necessary).
  if (0 != (HTuple(int(hv_MinWidth>hv_ImageWidth)).TupleOr(int(hv_MinHeight>hv_ImageHeight))))
  {
    hv_ResizeFactor = (((hv_MinWidth.TupleReal())/hv_ImageWidth).TupleConcat((hv_MinHeight.TupleReal())/hv_ImageHeight)).TupleMax();
  }
  hv_TempWidth = hv_ImageWidth*hv_ResizeFactor;
  hv_TempHeight = hv_ImageHeight*hv_ResizeFactor;
  //Then, shrink window to maximum extents (if necessary).
  if (0 != (HTuple(int(hv_MaxWidth<hv_TempWidth)).TupleOr(int(hv_MaxHeight<hv_TempHeight))))
  {
    hv_ResizeFactor = hv_ResizeFactor*((((hv_MaxWidth.TupleReal())/hv_TempWidth).TupleConcat((hv_MaxHeight.TupleReal())/hv_TempHeight)).TupleMin());
  }
  hv_WindowWidth = hv_ImageWidth*hv_ResizeFactor;
  hv_WindowHeight = hv_ImageHeight*hv_ResizeFactor;
  //Resize window
  SetWindowAttr("background_color","black");
  OpenWindow(hv_Row,hv_Column,hv_WindowWidth,hv_WindowHeight,0,"visible","",&(*hv_WindowHandle));
  HDevWindowStack::Push((*hv_WindowHandle));
  if (HDevWindowStack::IsOpen())
    SetPart(HDevWindowStack::GetActive(),0, 0, hv_ImageHeight-1, hv_ImageWidth-1);
  return;
}
