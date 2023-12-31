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

extern void get_hom_mat2d_from_matching_result (HTuple hv_Row, HTuple hv_Column, 
    HTuple hv_Angle, HTuple hv_ScaleR, HTuple hv_ScaleC, HTuple *hv_HomMat2D);


// Chapter: Matching / Shape-Based
// Short Description: Display the results of Shape-Based Matching. 
void dev_display_shape_matching_results (HTuple hv_ModelID, HTuple hv_Color, HTuple hv_Row, 
    HTuple hv_Column, HTuple hv_Angle, HTuple hv_ScaleR, HTuple hv_ScaleC, HTuple hv_Model)
{

  // Local iconic variables
  HObject  ho_ClutterRegion, ho_ModelContours, ho_ContoursAffinTrans;
  HObject  ho_RegionAffineTrans;

  // Local control variables
  HTuple  hv_WindowHandle, hv_UseClutter, hv_UseClutter0;
  HTuple  hv_HomMat2D, hv_ClutterContrast, hv_Index, hv_Exception;
  HTuple  hv_NumMatches, hv_GenParamValue, hv_HomMat2DInvert;
  HTuple  hv_Match, hv_HomMat2DTranslate, hv_HomMat2DCompose;

  //This procedure displays the results of Shape-Based Matching.
  //
  //Ensure that the different models have the same use_clutter value.
  //
  //This procedure displays the results on the active graphics window.
  if (HDevWindowStack::IsOpen())
    hv_WindowHandle = HDevWindowStack::GetActive();
  //If no graphics window is currently open, nothing can be displayed.
  if (0 != (int(hv_WindowHandle==-1)))
  {
    return;
  }
  //
  hv_UseClutter = "false";
  try
  {
    GetShapeModelClutter(&ho_ClutterRegion, HTuple(hv_ModelID[0]), "use_clutter", 
        &hv_UseClutter0, &hv_HomMat2D, &hv_ClutterContrast);
    {
    HTuple end_val14 = (hv_ModelID.TupleLength())-1;
    HTuple step_val14 = 1;
    for (hv_Index=0; hv_Index.Continue(end_val14, step_val14); hv_Index += step_val14)
    {
      GetShapeModelClutter(&ho_ClutterRegion, HTuple(hv_ModelID[hv_Index]), "use_clutter", 
          &hv_UseClutter, &hv_HomMat2D, &hv_ClutterContrast);
      if (0 != (int(hv_UseClutter!=hv_UseClutter0)))
      {
        throw HException("Shape models are not of the same clutter type");
      }
    }
    }
  }
  // catch (Exception) 
  catch (HException &HDevExpDefaultException)
  {
    HDevExpDefaultException.ToHTuple(&hv_Exception);
  }
  if (0 != (int(hv_UseClutter==HTuple("true"))))
  {
    if (HDevWindowStack::IsOpen())
      SetDraw(HDevWindowStack::GetActive(),"margin");
    //For clutter-enabled models, the Color tuple should have either
    //exactly 2 entries, or 2* the number of models. The first color
    //is used for the match and the second for the clutter region,
    //respectively.
    if (0 != (HTuple(int((hv_Color.TupleLength())!=(2*(hv_ModelID.TupleLength())))).TupleAnd(int((hv_Color.TupleLength())!=2))))
    {
      throw HException("Length of Color does not correspond to models with enabled clutter parameters");
    }
  }

  hv_NumMatches = hv_Row.TupleLength();
  if (0 != (int(hv_NumMatches>0)))
  {
    if (0 != (int((hv_ScaleR.TupleLength())==1)))
    {
      TupleGenConst(hv_NumMatches, hv_ScaleR, &hv_ScaleR);
    }
    if (0 != (int((hv_ScaleC.TupleLength())==1)))
    {
      TupleGenConst(hv_NumMatches, hv_ScaleC, &hv_ScaleC);
    }
    if (0 != (int((hv_Model.TupleLength())==0)))
    {
      TupleGenConst(hv_NumMatches, 0, &hv_Model);
    }
    else if (0 != (int((hv_Model.TupleLength())==1)))
    {
      TupleGenConst(hv_NumMatches, hv_Model, &hv_Model);
    }
    //Redirect all display calls to a buffer window and update the
    //graphics window only at the end, to speed up the visualization.
    SetWindowParam(hv_WindowHandle, "flush", "false");
    {
    HTuple end_val49 = (hv_ModelID.TupleLength())-1;
    HTuple step_val49 = 1;
    for (hv_Index=0; hv_Index.Continue(end_val49, step_val49); hv_Index += step_val49)
    {
      GetShapeModelContours(&ho_ModelContours, HTuple(hv_ModelID[hv_Index]), 1);
      if (0 != (int(hv_UseClutter==HTuple("true"))))
      {
        GetShapeModelClutter(&ho_ClutterRegion, HTuple(hv_ModelID[hv_Index]), HTuple(), 
            &hv_GenParamValue, &hv_HomMat2D, &hv_ClutterContrast);
        HomMat2dInvert(hv_HomMat2D, &hv_HomMat2DInvert);
      }
      if (HDevWindowStack::IsOpen())
        SetColor(HDevWindowStack::GetActive(),HTuple(hv_Color[hv_Index%(hv_Color.TupleLength())]));
      {
      HTuple end_val56 = hv_NumMatches-1;
      HTuple step_val56 = 1;
      for (hv_Match=0; hv_Match.Continue(end_val56, step_val56); hv_Match += step_val56)
      {
        if (0 != (int(hv_Index==HTuple(hv_Model[hv_Match]))))
        {
          get_hom_mat2d_from_matching_result(HTuple(hv_Row[hv_Match]), HTuple(hv_Column[hv_Match]), 
              HTuple(hv_Angle[hv_Match]), HTuple(hv_ScaleR[hv_Match]), HTuple(hv_ScaleC[hv_Match]), 
              &hv_HomMat2DTranslate);
          AffineTransContourXld(ho_ModelContours, &ho_ContoursAffinTrans, hv_HomMat2DTranslate);
          if (0 != (int(hv_UseClutter==HTuple("true"))))
          {
            HomMat2dCompose(hv_HomMat2DTranslate, hv_HomMat2DInvert, &hv_HomMat2DCompose);
            AffineTransRegion(ho_ClutterRegion, &ho_RegionAffineTrans, hv_HomMat2DCompose, 
                "constant");
            if (0 != (int((hv_Color.TupleLength())==2)))
            {
              if (HDevWindowStack::IsOpen())
                SetColor(HDevWindowStack::GetActive(),HTuple(hv_Color[1]));
              if (HDevWindowStack::IsOpen())
                DispObj(ho_RegionAffineTrans, HDevWindowStack::GetActive());
              if (HDevWindowStack::IsOpen())
                SetColor(HDevWindowStack::GetActive(),HTuple(hv_Color[0]));
            }
            else
            {
              if (HDevWindowStack::IsOpen())
                SetColor(HDevWindowStack::GetActive(),HTuple(hv_Color[(hv_Index*2)+1]));
              if (HDevWindowStack::IsOpen())
                DispObj(ho_RegionAffineTrans, HDevWindowStack::GetActive());
              if (HDevWindowStack::IsOpen())
                SetColor(HDevWindowStack::GetActive(),HTuple(hv_Color[hv_Index*2]));
            }
          }
          if (HDevWindowStack::IsOpen())
            DispObj(ho_ContoursAffinTrans, HDevWindowStack::GetActive());
        }
      }
      }
    }
    }
    //Copy the content of the buffer window to the graphics window.
    SetWindowParam(hv_WindowHandle, "flush", "true");
    FlushBuffer(hv_WindowHandle);
  }
  return;
}
