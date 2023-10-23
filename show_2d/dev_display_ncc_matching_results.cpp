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


// Chapter: Matching / Correlation-Based
// Short Description: Display the results of Correlation-Based Matching. 
void dev_display_ncc_matching_results (HTuple hv_ModelID, HTuple hv_Color, HTuple hv_Row, 
    HTuple hv_Column, HTuple hv_Angle, HTuple hv_Model)
{

  // Local iconic variables
  HObject  ho_ModelRegion, ho_ModelContours, ho_ContoursAffinTrans;
  HObject  ho_Cross;

  // Local control variables
  HTuple  hv_NumMatches, hv_Index, hv_Match, hv_HomMat2DIdentity;
  HTuple  hv_HomMat2DRotate, hv_HomMat2DTranslate, hv_RowTrans;
  HTuple  hv_ColTrans;

  //This procedure displays the results of Correlation-Based Matching.
  //
  hv_NumMatches = hv_Row.TupleLength();
  if (0 != (int(hv_NumMatches>0)))
  {
    if (0 != (int((hv_Model.TupleLength())==0)))
    {
      TupleGenConst(hv_NumMatches, 0, &hv_Model);
    }
    else if (0 != (int((hv_Model.TupleLength())==1)))
    {
      TupleGenConst(hv_NumMatches, hv_Model, &hv_Model);
    }
    {
    HTuple end_val9 = (hv_ModelID.TupleLength())-1;
    HTuple step_val9 = 1;
    for (hv_Index=0; hv_Index.Continue(end_val9, step_val9); hv_Index += step_val9)
    {
      GetNccModelRegion(&ho_ModelRegion, HTuple(hv_ModelID[hv_Index]));
      GenContourRegionXld(ho_ModelRegion, &ho_ModelContours, "border_holes");
      if (HDevWindowStack::IsOpen())
        SetColor(HDevWindowStack::GetActive(),HTuple(hv_Color[hv_Index%(hv_Color.TupleLength())]));
      {
      HTuple end_val13 = hv_NumMatches-1;
      HTuple step_val13 = 1;
      for (hv_Match=0; hv_Match.Continue(end_val13, step_val13); hv_Match += step_val13)
      {
        if (0 != (int(hv_Index==HTuple(hv_Model[hv_Match]))))
        {
          HomMat2dIdentity(&hv_HomMat2DIdentity);
          HomMat2dRotate(hv_HomMat2DIdentity, HTuple(hv_Angle[hv_Match]), 0, 0, &hv_HomMat2DRotate);
          HomMat2dTranslate(hv_HomMat2DRotate, HTuple(hv_Row[hv_Match]), HTuple(hv_Column[hv_Match]), 
              &hv_HomMat2DTranslate);
          AffineTransContourXld(ho_ModelContours, &ho_ContoursAffinTrans, hv_HomMat2DTranslate);
          if (HDevWindowStack::IsOpen())
            DispObj(ho_ContoursAffinTrans, HDevWindowStack::GetActive());
          AffineTransPixel(hv_HomMat2DTranslate, 0, 0, &hv_RowTrans, &hv_ColTrans);
          GenCrossContourXld(&ho_Cross, hv_RowTrans, hv_ColTrans, 6, HTuple(hv_Angle[hv_Match]));
          if (HDevWindowStack::IsOpen())
            DispObj(ho_Cross, HDevWindowStack::GetActive());
        }
      }
      }
    }
    }
  }
  return;
}