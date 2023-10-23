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


// Chapter: Graphics / Output
// Short Description: Display an interactive button. 
void dev_disp_button (HTuple hv_String, HTuple hv_Row, HTuple hv_Column, HTuple hv_Width, 
    HTuple hv_Height, HTuple hv_ColorString, HTuple hv_ColorBackground, HTuple hv_ColorBackgroundActive, 
    HTuple hv_WindowHandle, HTuple *hv_SelectedButton)
{

  // Local iconic variables
  HObject  ho_ButtonRect, ho_ObjectSelected;

  // Local control variables
  HTuple  hv_ClipRegion, hv_Flush, hv__, hv_WindowWidth;
  HTuple  hv_WindowHeight, hv_PartHeight, hv_PartWidth, hv_WindowImageWidthRatio;
  HTuple  hv_WindowImageHeightRatio, hv_ButtonRowScaled, hv_ButtonColumnScaled;
  HTuple  hv_ButtonHeightScaled, hv_ButtonWidthScaled, hv_HighlightColors;
  HTuple  hv_Ascents, hv_Descents, hv_TextWidths, hv_Index;
  HTuple  hv_Ascent, hv_Descent, hv_TextWidth, hv_TextHeight;
  HTuple  hv_TextRow, hv_TextColumn, hv_Button, hv_ButtonIndex;
  HTuple  hv_IsInside, hv_Exception;

  //
  //This procedure displays one or more interactive buttons.
  //It is possible to customize the size, position, and color of the buttons.
  //The index of the clicked button is returned.
  //
  GetSystem("clip_region", &hv_ClipRegion);
  SetSystem("clip_region", "false");
  // dev_get_preferences(...); only in hdevelop
  // dev_set_preferences(...); only in hdevelop
  GetWindowParam(hv_WindowHandle, "flush", &hv_Flush);
  SetWindowParam(hv_WindowHandle, "flush", "false");
  //
  //Get the scaling factor for window/image coordinate conversion.
  GetWindowExtents(hv_WindowHandle, &hv__, &hv__, &hv_WindowWidth, &hv_WindowHeight);
  GetPart(hv_WindowHandle, &hv__, &hv__, &hv_PartHeight, &hv_PartWidth);
  hv_WindowImageWidthRatio = hv_WindowWidth/(1.0*hv_PartWidth);
  hv_WindowImageHeightRatio = hv_WindowHeight/(1.0*hv_PartHeight);
  //
  //Scale the button coordinates.
  hv_ButtonRowScaled = hv_Row/hv_WindowImageHeightRatio;
  hv_ButtonColumnScaled = hv_Column/hv_WindowImageWidthRatio;
  hv_ButtonHeightScaled = hv_Height/hv_WindowImageHeightRatio;
  hv_ButtonWidthScaled = hv_Width/hv_WindowImageWidthRatio;
  //
  GenRectangle1(&ho_ButtonRect, hv_ButtonRowScaled, hv_ButtonColumnScaled, hv_ButtonRowScaled+hv_ButtonHeightScaled, 
      hv_ButtonColumnScaled+hv_ButtonWidthScaled);
  if (0 != (int((hv_ColorBackground.TupleLength())==1)))
  {
    hv_ColorBackground = HTuple(hv_String.TupleLength(),hv_ColorBackground);
  }
  hv_HighlightColors = hv_ColorBackground;
  //
  //We want to place the text centered in the button.
  hv_Ascents = HTuple();
  hv_Descents = HTuple();
  hv_TextWidths = HTuple();
  {
  HTuple end_val34 = (hv_String.TupleLength())-1;
  HTuple step_val34 = 1;
  for (hv_Index=0; hv_Index.Continue(end_val34, step_val34); hv_Index += step_val34)
  {
    GetStringExtents(hv_WindowHandle, HTuple(hv_String[hv_Index]), &hv_Ascent, &hv_Descent, 
        &hv_TextWidth, &hv_TextHeight);
    hv_Ascents = hv_Ascents.TupleConcat(hv_Ascent);
    hv_Descents = hv_Descents.TupleConcat(hv_Descent);
    hv_TextWidths = hv_TextWidths.TupleConcat(hv_TextWidth);
  }
  }
  //
  hv_TextRow = (hv_Row+((hv_Height-hv_TextHeight)/2))-hv_Descent;
  hv_TextColumn = hv_Column+((hv_Width-hv_TextWidths)/2);
  (*hv_SelectedButton) = 0;
  hv_Button = 0;
  //
  while (0 != (HTuple(int((*hv_SelectedButton)==0)).TupleOr(int(hv_Button!=1))))
  {
    if (HDevWindowStack::IsOpen())
      SetColor(HDevWindowStack::GetActive(),hv_HighlightColors);
    if (HDevWindowStack::IsOpen())
      DispObj(ho_ButtonRect, HDevWindowStack::GetActive());
    if (HDevWindowStack::IsOpen())
      DispText(HDevWindowStack::GetActive(),hv_String, "window", hv_TextRow, hv_TextColumn, 
          hv_ColorString, "box", "false");
    //Actual display.
    FlushBuffer(hv_WindowHandle);
    try
    {
      GetMposition(hv_WindowHandle, &hv_Row, &hv_Column, &hv_Button);
      (*hv_SelectedButton) = 0;
      {
      HTuple end_val55 = hv_ButtonRowScaled.TupleLength();
      HTuple step_val55 = 1;
      for (hv_ButtonIndex=1; hv_ButtonIndex.Continue(end_val55, step_val55); hv_ButtonIndex += step_val55)
      {
        SelectObj(ho_ButtonRect, &ho_ObjectSelected, hv_ButtonIndex);
        TestRegionPoint(ho_ObjectSelected, hv_Row, hv_Column, &hv_IsInside);
        if (0 != hv_IsInside)
        {
          (*hv_SelectedButton) = hv_ButtonIndex;
          break;
        }
      }
      }
    }
    // catch (Exception) 
    catch (HException &HDevExpDefaultException)
    {
      HDevExpDefaultException.ToHTuple(&hv_Exception);
    }
    if (0 != (int((*hv_SelectedButton)>0)))
    {
      TupleReplace(hv_ColorBackground, (*hv_SelectedButton)-1, hv_ColorBackgroundActive, 
          &hv_HighlightColors);
    }
    else
    {
      hv_HighlightColors = hv_ColorBackground;
    }
  }
  //Wait for button to be released. Also return if mouse left window.
  while (0 != (int(hv_Button!=0)))
  {
    try
    {
      GetMposition(hv_WindowHandle, &hv_Row, &hv_Column, &hv_Button);
    }
    // catch (Exception) 
    catch (HException &HDevExpDefaultException)
    {
      HDevExpDefaultException.ToHTuple(&hv_Exception);
      hv_Button = 0;
    }
  }
  //Return index.
  (*hv_SelectedButton) = (*hv_SelectedButton)-1;
  //
  SetSystem("clip_region", hv_ClipRegion);
  // dev_set_preferences(...); only in hdevelop
  SetWindowParam(hv_WindowHandle, "flush", hv_Flush);
  //
  return;
}
