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


// Chapter: Matching / Shape-Based
// Short Description: Calculate the transformation matrix for results of Shape-Based Matching. 
void get_hom_mat2d_from_matching_result (HTuple hv_Row, HTuple hv_Column, HTuple hv_Angle, 
    HTuple hv_ScaleR, HTuple hv_ScaleC, HTuple *hv_HomMat2D)
{

  // Local control variables
  HTuple  hv_HomMat2DIdentity, hv_HomMat2DScale;
  HTuple  hv_HomMat2DRotate;

  //This procedure calculates the transformation matrix for the model contours
  //from the results of Shape-Based Matching.
  //
  HomMat2dIdentity(&hv_HomMat2DIdentity);
  HomMat2dScale(hv_HomMat2DIdentity, hv_ScaleR, hv_ScaleC, 0, 0, &hv_HomMat2DScale);
  HomMat2dRotate(hv_HomMat2DScale, hv_Angle, 0, 0, &hv_HomMat2DRotate);
  HomMat2dTranslate(hv_HomMat2DRotate, hv_Row, hv_Column, &(*hv_HomMat2D));
  return;


}
