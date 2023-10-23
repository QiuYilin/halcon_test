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

// Procedure declarations 
// Chapter: Graphics / Output
// Short Description: Display an interactive button. 
extern void dev_disp_button (HTuple hv_String, HTuple hv_Row, HTuple hv_Column, HTuple hv_Width, 
    HTuple hv_Height, HTuple hv_ColorString, HTuple hv_ColorBackground, HTuple hv_ColorBackgroundActive, 
    HTuple hv_WindowHandle, HTuple *hv_SelectedButton);
// Chapter: Develop
// Short Description: Open a new graphics window that preserves the aspect ratio of the given image size. 
extern void dev_open_window_fit_size (HTuple hv_Row, HTuple hv_Column, HTuple hv_Width, 
    HTuple hv_Height, HTuple hv_WidthLimit, HTuple hv_HeightLimit, HTuple *hv_WindowHandle);
// Chapter: Develop
// Short Description: Open a new graphics window that preserves the aspect ratio of the given image size. 
extern void dev_open_window_fit_size (HTuple hv_Row, HTuple hv_Column, HTuple hv_Width, 
    HTuple hv_Height, HTuple hv_WidthLimit, HTuple hv_HeightLimit, HTuple *hv_WindowHandle);
// Chapter: Develop
// Short Description: Open a new graphics window that preserves the aspect ratio of the given image size. 
extern void dev_open_window_fit_size (HTuple hv_Row, HTuple hv_Column, HTuple hv_Width, 
    HTuple hv_Height, HTuple hv_WidthLimit, HTuple hv_HeightLimit, HTuple *hv_WindowHandle);
// Chapter: Graphics / Text
// Short Description: Set font independent of OS 
extern void set_display_font (HTuple hv_WindowHandle, HTuple hv_Size, HTuple hv_Font, 
    HTuple hv_Bold, HTuple hv_Slant);
// Chapter: Matching / Deep Counting
// Short Description: Visualize Deep Counting results with an image. 
void dev_display_deep_counting_results (HObject ho_Image, HTuple hv_WindowHandle, 
    HTuple hv_DeepCountingResult, HTuple hv_GenParamName, HTuple hv_GenParamValue);
// Chapter: Matching / Deep Counting
// Short Description: Display a slider. 
void disp_slider_deep_counting (HTuple hv_WindowHandle, HTuple hv_Row, HTuple hv_TotalHeight, 
    HTuple hv_ColLabel, HTuple hv_ColValue, HTuple hv_ColSliderStart, HTuple hv_ColSliderEnd, 
    HTuple hv_Label, HTuple hv_ValueStart, HTuple hv_ValueEnd, HTuple hv_ValueCurr, 
    HTuple hv_FormatString);
// Chapter: Matching / Deep Counting
// Short Description: Draw templates for Deep Counting models. 
void draw_deep_counting_templates (HObject ho_Image, HObject *ho_TemplateRegion, 
    HObject *ho_Template);
// Chapter: Matching / Deep Counting
// Short Description: Parse generic Deep Counting visualization parameters. 
void parse_generic_deep_counting_visualization_parameters (HTuple hv_GenParamName, 
    HTuple hv_GenParamValue, HTuple *hv_LineWidth, HTuple *hv_CrossColor, HTuple *hv_CrossScale, 
    HTuple *hv_FontSize, HTuple *hv_ScaleMode, HTuple *hv_InteractiveMinScore);

// Procedures 
// Chapter: Matching / Deep Counting
// Short Description: Visualize Deep Counting results with an image. 
void dev_display_deep_counting_results (HObject ho_Image, HTuple hv_WindowHandle, 
    HTuple hv_DeepCountingResult, HTuple hv_GenParamName, HTuple hv_GenParamValue)
{

  // Local iconic variables
  HObject  ho_ImageTmp, ho_Cross, ho_ButtonRect;

  // Local control variables
  HTuple  hv_Width, hv_Height, hv_LineWidth, hv_CrossColor;
  HTuple  hv_CrossScale, hv_FontSize, hv_ScaleMode, hv_InteractiveMinScore;
  HTuple  hv_FlushOrigin, hv_ActiveWindow, hv_ActiveFont;
  HTuple  hv_Font, hv__, hv_WindowWidth, hv_WindowHeight;
  HTuple  hv_AdditionalVSpace, hv_AreaWindow, hv_WindowImageRatioWidth;
  HTuple  hv_WindowImageRatioHeight, hv_CurrMinScore, hv_ExitButtonPressed;
  HTuple  hv_WindowClosed, hv_OldMButton, hv_Dragging, hv_OverButton;
  HTuple  hv_CurrResult, hv_AboveMinScore, hv_Count, hv_Rows;
  HTuple  hv_Cols, hv_Scores, hv_Areas, hv_AreaRatios, hv_CrossSize;
  HTuple  hv_Index, hv_AreaMean, hv_SliderLabel, hv_ExitTextDescent;
  HTuple  hv_ExitTextWidth, hv_ExitTextHeight, hv_SliderValWidth;
  HTuple  hv_SliderLabelWidth, hv_ExitButtonWidth, hv_ExitButtonHeight;
  HTuple  hv_ExitButtonRow, hv_ExitButtonCol, hv_ExitButtonRowText;
  HTuple  hv_ExitButtonColText, hv_SliderHeight, hv_SliderRow;
  HTuple  hv_ColSliderLabel, hv_ColSliderStart, hv_ColSliderValue;
  HTuple  hv_ColSliderEnd, hv_OldMinScore, hv_OldOverButton;
  HTuple  hv_MouseRow, hv_MouseColumn, hv_Button, hv_Exception;
  HTuple  hv_IsInSlider, hv_ValueSliderRel, hv_SemType;

  //
  //Get window, use active window if none given
  GetImageSize(ho_Image, &hv_Width, &hv_Height);
  if (0 != (int(hv_WindowHandle==HTuple())))
  {
    //Open new window for drawing the regions.
    dev_open_window_fit_size(0, 0, hv_Width, hv_Height, (HTuple(700).Append(1000)), 
        (HTuple(600).Append(800)), &hv_WindowHandle);
  }
  else
  {
    if (HDevWindowStack::IsOpen())
      hv_WindowHandle = HDevWindowStack::GetActive();
  }
  //
  parse_generic_deep_counting_visualization_parameters(hv_GenParamName, hv_GenParamValue, 
      &hv_LineWidth, &hv_CrossColor, &hv_CrossScale, &hv_FontSize, &hv_ScaleMode, 
      &hv_InteractiveMinScore);
  //
  //Prepare the window.
  GetWindowParam(hv_WindowHandle, "flush", &hv_FlushOrigin);
  SetWindowParam(hv_WindowHandle, "flush", "false");
  if (HDevWindowStack::IsOpen())
    hv_ActiveWindow = HDevWindowStack::GetActive();
  if (0 != (int(hv_ActiveWindow!=hv_WindowHandle)))
  {
    HDevWindowStack::SetActive(hv_WindowHandle);
  }
  GetFont(hv_WindowHandle, &hv_ActiveFont);
  hv_Font = "default-Normal-"+hv_FontSize;
  if (0 != (int(hv_ActiveFont!=hv_Font)))
  {
    SetFont(hv_WindowHandle, hv_Font);
  }
  if (HDevWindowStack::IsOpen())
    ClearWindow(HDevWindowStack::GetActive());
  //
  GetWindowExtents(hv_WindowHandle, &hv__, &hv__, &hv_WindowWidth, &hv_WindowHeight);
  hv_AdditionalVSpace = 0;
  if (0 != hv_InteractiveMinScore)
  {
    //Reserve additional space at the bottom for the min_score slider.
    hv_AdditionalVSpace = 50;
  }
  GenImageConst(&ho_ImageTmp, "byte", hv_WindowWidth, hv_WindowHeight+hv_AdditionalVSpace);
  if (HDevWindowStack::IsOpen())
    SetWindowExtents(HDevWindowStack::GetActive(),0, 0, hv_WindowWidth, hv_WindowHeight+hv_AdditionalVSpace);
  if (HDevWindowStack::IsOpen())
    SetPart(HDevWindowStack::GetActive(),0, 0, hv_Height+hv_AdditionalVSpace, hv_Width);
  hv_AreaWindow = hv_WindowWidth*hv_WindowHeight;
  //
  hv_WindowImageRatioWidth = hv_WindowWidth/(hv_Width*1.0);
  hv_WindowImageRatioHeight = (hv_WindowHeight+hv_AdditionalVSpace)/(hv_Height*1.0);
  //
  //Variables for the min_score slider
  hv_CurrMinScore = 0.2;
  hv_ExitButtonPressed = 0;
  hv_WindowClosed = 0;
  hv_OldMButton = 0;
  hv_Dragging = 0;
  hv_OverButton = 0;
  //
  while (true)
  {
    //Display the image, scores, and crosses.
    if (HDevWindowStack::IsOpen())
      ClearWindow(HDevWindowStack::GetActive());
    HDevWindowStack::SetActive(hv_WindowHandle);
    if (HDevWindowStack::IsOpen())
      DispObj(ho_Image, HDevWindowStack::GetActive());
    if (HDevWindowStack::IsOpen())
      SetLineWidth(HDevWindowStack::GetActive(),hv_LineWidth);
    if (HDevWindowStack::IsOpen())
      SetColor(HDevWindowStack::GetActive(),hv_CrossColor);
    //
    hv_CurrResult = ((const HTuple&)hv_DeepCountingResult)[0];
    hv_AboveMinScore = (hv_CurrResult.TupleGetDictTuple("score")).TupleGreaterEqualElem(hv_CurrMinScore);
    hv_Count = hv_AboveMinScore.TupleSum();
    hv_Rows = (hv_DeepCountingResult.TupleGetDictTuple("row")).TupleSelectMask(hv_AboveMinScore);
    hv_Cols = (hv_DeepCountingResult.TupleGetDictTuple("column")).TupleSelectMask(hv_AboveMinScore);
    hv_Scores = (hv_DeepCountingResult.TupleGetDictTuple("score")).TupleSelectMask(hv_AboveMinScore);
    //
    //Calculate suitable sizes for the crosses.
    hv_Areas = (hv_DeepCountingResult.TupleGetDictTuple("area")).TupleSelectMask(hv_AboveMinScore);
    //
    if (0 != (int(hv_ScaleMode==HTuple("equal"))))
    {
      hv_AreaRatios = hv_Areas/(hv_AreaWindow.TupleReal());
      hv_CrossSize = ((hv_CrossScale*100)*hv_AreaRatios).TupleInt();
      //
      {
      HTuple end_val70 = (hv_Rows.TupleLength())-1;
      HTuple step_val70 = 1;
      for (hv_Index=0; hv_Index.Continue(end_val70, step_val70); hv_Index += step_val70)
      {
        GenCrossContourXld(&ho_Cross, HTuple(hv_Rows[hv_Index]), HTuple(hv_Cols[hv_Index]), 
            HTuple(hv_CrossSize[hv_Index]), 0.785398);
        if (HDevWindowStack::IsOpen())
          DispObj(ho_Cross, HDevWindowStack::GetActive());
      }
      }
    }
    else if (0 != (int(hv_ScaleMode==HTuple("mean"))))
    {
      hv_AreaMean = hv_Areas.TupleMean();
      hv_AreaRatios = hv_AreaMean/(hv_AreaWindow.TupleReal());
      hv_CrossSize = ((hv_CrossScale*100)*hv_AreaRatios).TupleInt();
      GenCrossContourXld(&ho_Cross, hv_Rows, hv_Cols, hv_CrossSize, 0.785398);
      if (HDevWindowStack::IsOpen())
        DispObj(ho_Cross, HDevWindowStack::GetActive());
    }
    else
    {
      SetWindowParam(hv_WindowHandle, "flush", hv_FlushOrigin);
      throw HException(("Unsupported value for GenParamName "+hv_GenParamName)+".");
    }
    //
    if (HDevWindowStack::IsOpen())
      DispText(HDevWindowStack::GetActive(),""+(hv_Scores.TupleString(".2")), "image", 
          hv_Rows+12, hv_Cols+12, "black", HTuple(), HTuple());
    if (HDevWindowStack::IsOpen())
      DispText(HDevWindowStack::GetActive(),"Count: "+hv_Count, "window", "top", 
          "right", "black", HTuple(), HTuple());
    //
    if (0 != (HTuple(hv_InteractiveMinScore.TupleNot()).TupleOr(hv_ExitButtonPressed)))
    {
      SetWindowParam(hv_WindowHandle, "flush", "true");
      FlushBuffer(hv_WindowHandle);
      break;
    }
    //
    //Draw a slider for the interactive min_score.
    hv_SliderLabel = "MinScore: ";
    GetStringExtents(hv_WindowHandle, "Exit", &hv__, &hv_ExitTextDescent, &hv_ExitTextWidth, 
        &hv_ExitTextHeight);
    GetStringExtents(hv_WindowHandle, "0.00", &hv__, &hv__, &hv_SliderValWidth, &hv__);
    GetStringExtents(hv_WindowHandle, hv_SliderLabel, &hv__, &hv__, &hv_SliderLabelWidth, 
        &hv__);
    hv_ExitButtonWidth = (hv_ExitTextWidth/hv_WindowImageRatioWidth)+20;
    hv_ExitButtonHeight = (hv_ExitTextHeight/hv_WindowImageRatioHeight)+10;
    hv_ExitButtonRow = hv_Height+10;
    hv_ExitButtonCol = (hv_Width-hv_ExitButtonWidth)-10;
    hv_ExitButtonRowText = hv_ExitButtonRow+(0.5*(hv_ExitButtonHeight-((hv_ExitTextDescent+hv_ExitTextHeight)/hv_WindowImageRatioHeight)));
    hv_ExitButtonColText = hv_ExitButtonCol+(0.5*(hv_ExitButtonWidth-(hv_ExitTextWidth/hv_WindowImageRatioWidth)));
    //
    //Set and compute slider position and size.
    hv_SliderHeight = 40;
    hv_SliderRow = hv_Height;
    hv_ColSliderLabel = 10;
    hv_ColSliderStart = (hv_ColSliderLabel+(hv_SliderLabelWidth/hv_WindowImageRatioWidth))+10;
    hv_ColSliderValue = ((hv_Width-hv_ExitButtonWidth)-(hv_SliderValWidth/hv_WindowImageRatioWidth))-30;
    hv_ColSliderEnd = hv_ColSliderValue-10;
    disp_slider_deep_counting(hv_WindowHandle, hv_SliderRow, hv_SliderHeight, hv_ColSliderLabel, 
        hv_ColSliderValue, hv_ColSliderStart, hv_ColSliderEnd, hv_SliderLabel, 0, 
        1, hv_CurrMinScore, "2.2f");
    //
    //Draw exit button.
    GenRectangle1(&ho_ButtonRect, hv_ExitButtonRow, hv_ExitButtonCol, hv_ExitButtonRow+hv_ExitButtonHeight, 
        (hv_ExitButtonCol+hv_ExitButtonWidth)-1);
    if (0 != hv_OverButton)
    {
      if (HDevWindowStack::IsOpen())
        SetColor(HDevWindowStack::GetActive(),"#fce9d4");
    }
    else
    {
      if (HDevWindowStack::IsOpen())
        SetColor(HDevWindowStack::GetActive(),"#f28d26");
    }
    if (HDevWindowStack::IsOpen())
      DispObj(ho_ButtonRect, HDevWindowStack::GetActive());
    if (HDevWindowStack::IsOpen())
      DispText(HDevWindowStack::GetActive(),"Exit", "image", hv_ExitButtonRowText, 
          hv_ExitButtonColText, "black", (HTuple("box").Append("box_padding")), (HTuple("false").Append(2)));
    //
    //Update window.
    FlushBuffer(hv_WindowHandle);
    //
    //Wait for user input (mouse moves the min_score bar).
    hv_OldMinScore = hv_CurrMinScore;
    hv_OldOverButton = hv_OverButton;
    while (0 != (HTuple(HTuple(HTuple(int(hv_OldMinScore==hv_CurrMinScore)).TupleAnd(int(hv_OldOverButton==hv_OverButton))).TupleAnd(hv_WindowClosed.TupleNot())).TupleAnd(hv_ExitButtonPressed.TupleNot())))
    {
      try
      {
        GetMposition(hv_WindowHandle, &hv_MouseRow, &hv_MouseColumn, &hv_Button);
        hv_OverButton = HTuple(HTuple(HTuple(int(hv_MouseRow>hv_ExitButtonRow)).TupleAnd(int(hv_MouseRow<(hv_ExitButtonRow+hv_ExitButtonHeight)))).TupleAnd(int(hv_MouseColumn>hv_ExitButtonCol))).TupleAnd(int(hv_MouseColumn<(hv_ExitButtonCol+hv_ExitButtonWidth)));
        if (0 != (int(hv_Button==0)))
        {
          hv_Dragging = 0;
          hv_OldMButton = hv_Button;
          if (0 != (int(hv_OldOverButton==hv_OverButton)))
          {
            WaitSeconds(0.02);
          }
          continue;
        }
      }
      // catch (Exception) 
      catch (HException &HDevExpDefaultException)
      {
        HDevExpDefaultException.ToHTuple(&hv_Exception);
        if (0 != (int(HTuple(hv_Exception[0])==2454)))
        {
          //Window was closed, exit the procedure.
          hv_WindowClosed = 1;
        }
        WaitSeconds(0.02);
        continue;
      }
      //
      //Exit button pressed?
      if (0 != (HTuple(hv_Dragging.TupleNot()).TupleAnd(hv_OverButton)))
      {
        hv_ExitButtonPressed = 1;
        break;
      }
      //
      //Check if mouse is inside slider, and at which position.
      hv_IsInSlider = HTuple(HTuple(HTuple(int(hv_MouseRow>hv_SliderRow)).TupleAnd(int(hv_MouseRow<(hv_SliderRow+hv_SliderHeight)))).TupleAnd(int(hv_MouseColumn>=hv_ColSliderStart))).TupleAnd(int(hv_MouseColumn<=hv_ColSliderEnd));
      hv_ValueSliderRel = (hv_MouseColumn-hv_ColSliderStart)/(hv_ColSliderEnd-hv_ColSliderStart);
      if (0 != (int(hv_ValueSliderRel<0)))
      {
        hv_ValueSliderRel = 0;
      }
      else if (0 != (int(hv_ValueSliderRel>1)))
      {
        hv_ValueSliderRel = 1;
      }
      //
      //Start dragging the slider?
      if (0 != (int(hv_OldMButton==0)))
      {
        //Slider button was just clicked.
        if (0 != hv_IsInSlider)
        {
          hv_Dragging = 1;
        }
      }
      //
      if (0 != hv_Dragging)
      {
        hv_CurrMinScore = hv_ValueSliderRel;
      }
      hv_OldMButton = hv_Button;
    }
    //
    if (0 != hv_WindowClosed)
    {
      //Window was closed, exit.
      break;
    }
  }
  //
  //Update window.
  TupleSemType(hv_WindowHandle, &hv_SemType);
  if (0 != (int(hv_SemType==HTuple("window"))))
  {
    //Window was not yet closed.
    SetWindowParam(hv_WindowHandle, "flush", "true");
    FlushBuffer(hv_WindowHandle);
    SetWindowParam(hv_WindowHandle, "flush", hv_FlushOrigin);
    //
    //Restore original window data.
    if (0 != (int(hv_ActiveWindow!=hv_WindowHandle)))
    {
      HDevWindowStack::SetActive(hv_ActiveWindow);
    }
    if (0 != (int(hv_ActiveFont!=hv_Font)))
    {
      SetFont(hv_WindowHandle, hv_ActiveFont);
    }
  }
  //
  return;
}

// Chapter: Matching / Deep Counting
// Short Description: Display a slider. 
void disp_slider_deep_counting (HTuple hv_WindowHandle, HTuple hv_Row, HTuple hv_TotalHeight, 
    HTuple hv_ColLabel, HTuple hv_ColValue, HTuple hv_ColSliderStart, HTuple hv_ColSliderEnd, 
    HTuple hv_Label, HTuple hv_ValueStart, HTuple hv_ValueEnd, HTuple hv_ValueCurr, 
    HTuple hv_FormatString)
{

  // Local iconic variables
  HObject  ho_ButtonRegion, ho_RegionBorder;

  // Local control variables
  HTuple  hv_BarHeight, hv_ButtonHeight, hv_ButtonWidth;
  HTuple  hv_RowMid, hv_LabelAscent, hv_LabelDescent, hv_LabelWidth;
  HTuple  hv_LabelHeight, hv__, hv_WindowWidth, hv_WindowHeight;
  HTuple  hv_Row1, hv_Column1, hv_Row2, hv_Column2, hv_WindowImageRatioHeight;
  HTuple  hv_WindowImageRatioWidth, hv_TextAlignVertical;
  HTuple  hv_SliderPosRel, hv_SliderColMid, hv_Rows, hv_Cols;

  //Compute coordinates for various items.
  hv_BarHeight = 2;
  hv_ButtonHeight = hv_TotalHeight*0.6;
  hv_ButtonWidth = HTuple(3).TupleMax2((hv_ColSliderEnd-hv_ColSliderStart)*0.01);
  hv_RowMid = hv_Row+(hv_TotalHeight/2);
  //
  //Use string extends to avoid overlapping slider and text.
  GetStringExtents(hv_WindowHandle, hv_Label, &hv_LabelAscent, &hv_LabelDescent, 
      &hv_LabelWidth, &hv_LabelHeight);
  GetWindowExtents(hv_WindowHandle, &hv__, &hv__, &hv_WindowWidth, &hv_WindowHeight);
  GetPart(hv_WindowHandle, &hv_Row1, &hv_Column1, &hv_Row2, &hv_Column2);
  hv_WindowImageRatioHeight = hv_WindowHeight/((hv_Row2-hv_Row1)*1.0);
  hv_WindowImageRatioWidth = hv_WindowWidth/((hv_Column2-hv_Column1)*1.0);
  hv_TextAlignVertical = (0.5*(((hv_TotalHeight-hv_LabelHeight)-hv_LabelDescent)+hv_LabelAscent))/hv_WindowImageRatioHeight;
  //
  //Paint the long bar of the slider.
  SetColor(hv_WindowHandle, "light gray");
  DispLine(hv_WindowHandle, hv_RowMid, hv_ColSliderStart, hv_RowMid, hv_ColSliderEnd);
  DispLine(hv_WindowHandle, hv_RowMid-(hv_ButtonHeight/2), hv_ColSliderStart, hv_RowMid+(hv_ButtonHeight/2), 
      hv_ColSliderStart);
  DispLine(hv_WindowHandle, hv_RowMid-(hv_ButtonHeight/2), hv_ColSliderEnd, hv_RowMid+(hv_ButtonHeight/2), 
      hv_ColSliderEnd);
  //
  //Paint the slider itself.
  hv_SliderPosRel = ((hv_ValueCurr-hv_ValueStart)*1.0)/(hv_ValueEnd-hv_ValueStart);
  if (0 != (int(hv_SliderPosRel<0)))
  {
    hv_SliderPosRel = 0;
  }
  else if (0 != (int(hv_SliderPosRel>1)))
  {
    hv_SliderPosRel = 1;
  }
  hv_SliderColMid = hv_ColSliderStart+(hv_SliderPosRel*(hv_ColSliderEnd-hv_ColSliderStart));
  GenRectangle1(&ho_ButtonRegion, hv_RowMid-(hv_ButtonHeight/2), hv_SliderColMid-(hv_ButtonWidth/2), 
      hv_RowMid+(hv_ButtonHeight/2), hv_SliderColMid+(hv_ButtonWidth/2));
  SetDraw(hv_WindowHandle, "fill");
  SetColor(hv_WindowHandle, "dark olive green");
  DispRegion(ho_ButtonRegion, hv_WindowHandle);
  GetRegionContour(ho_ButtonRegion, &hv_Rows, &hv_Cols);
  SetColor(hv_WindowHandle, "dim gray");
  GenRegionPoints(&ho_RegionBorder, hv_Rows, hv_Cols);
  DispRegion(ho_RegionBorder, hv_WindowHandle);
  //
  //Print label.
  DispText(hv_WindowHandle, hv_Label, "image", hv_Row+hv_TextAlignVertical, hv_ColLabel, 
      "white", "box", "false");
  //
  //Print value.
  DispText(hv_WindowHandle, hv_ValueCurr.TupleString(hv_FormatString), "image", hv_Row+hv_TextAlignVertical, 
      hv_ColValue, "white", "box", "false");
  //
  return;

}

// Chapter: Matching / Deep Counting
// Short Description: Draw templates for Deep Counting models. 
void draw_deep_counting_templates (HObject ho_Image, HObject *ho_TemplateRegion, 
    HObject *ho_Template)
{

  // Local iconic variables
  HObject  ho_Rectangle1, ho_ImageReduced, ho_Rectangle2;

  // Local control variables
  HTuple  hv_DrawText, hv_TextRow, hv_TextColumn;
  HTuple  hv_ButtonHeight, hv_ButtonWidth, hv_ValueColors;
  HTuple  hv_BoxColor, hv_HighlightColor, hv_TemplateRegionColor;
  HTuple  hv_Rectangles, hv_WindowRow, hv_WindowColumn, hv_Width;
  HTuple  hv_Height, hv_WindowHandle, hv__, hv_WindowWidth;
  HTuple  hv_WindowHeight, hv_WindowHeightExtension, hv_WindowImageRatioHeight;
  HTuple  hv_WindowImageRatioWidth, hv_WindowRow2, hv_WindowColumn2;
  HTuple  hv_WindowRatio, hv_ImageRow2, hv_ImageColumn2, hv_ImageRatio;
  HTuple  hv_SetPartColumn2, hv_ImageWindowRatioHeight, hv_ImageRow2InWindow;
  HTuple  hv_SetPartRow2, hv_ImageCol2InWindow, hv_ExplanationText;
  HTuple  hv_PrevWindowHeight, hv_TextWindowRow, hv_TextWindowColumn;
  HTuple  hv_WindowHandleText, hv_RectText, hv_Index, hv_RectTextWidth;
  HTuple  hv_RectTextHeight, hv_UndoTextWidth, hv_UndoTextHeight;
  HTuple  hv_ContinueTextWidth, hv_ContinueTextHeight, hv_SelectedButton;
  HTuple  hv_Row1, hv_Column1, hv_Row2, hv_Column2, hv_Phi1;
  HTuple  hv_Length1, hv_Length2, hv_Count;

  //This procedure is used to draw user-defined templates
  //for the Deep Counting workflow.
  //
  //Output parameters:
  //Template: The template which is later used for finding the objects.
  //TemplateRegion: The regions for later creating the matching template.
  //
  //Initialize parameters for draw procedure.
  hv_DrawText = HTuple();
  hv_TextRow = HTuple();
  hv_TextColumn = HTuple();
  hv_ButtonHeight = HTuple();
  hv_ButtonWidth = HTuple();
  hv_ValueColors = HTuple();
  hv_BoxColor = HTuple();
  hv_HighlightColor = "#fce9d4";
  hv_TemplateRegionColor = "#00f0f0c0";
  //
  hv_Rectangles = HTuple();
  GenEmptyObj(&(*ho_Template));
  GenEmptyObj(&(*ho_TemplateRegion));
  //
  //Open new window for drawing the regions.
  hv_WindowRow = 0;
  hv_WindowColumn = 0;
  GetImageSize(ho_Image, &hv_Width, &hv_Height);
  dev_open_window_fit_size(hv_WindowRow, hv_WindowColumn, hv_Width, hv_Height, (HTuple(500).Append(800)), 
      (HTuple(400).Append(600)), &hv_WindowHandle);
  GetWindowExtents(hv_WindowHandle, &hv__, &hv__, &hv_WindowWidth, &hv_WindowHeight);
  hv_WindowHeightExtension = 40;
  if (HDevWindowStack::IsOpen())
    SetWindowExtents(HDevWindowStack::GetActive(),hv_WindowRow, hv_WindowColumn, 
        hv_WindowWidth, hv_WindowHeight+hv_WindowHeightExtension);
  //
  // dev_set_preferences(...); only in hdevelop
  // dev_set_preferences(...); only in hdevelop
  //
  //Set part for the image to be displayed later and adapt window size (+ MarginBottom + MapColorBarWidth).
  GetWindowExtents(hv_WindowHandle, &hv__, &hv__, &hv_WindowWidth, &hv_WindowHeight);
  hv_WindowImageRatioHeight = hv_WindowHeight/(hv_Height*1.0);
  hv_WindowImageRatioWidth = hv_WindowWidth/(hv_Width*1.0);
  //
  //Set window part such that image is displayed undistorted.
  hv_WindowRow2 = hv_WindowHeight;
  hv_WindowColumn2 = hv_WindowWidth;
  hv_WindowRatio = hv_WindowColumn2/(hv_WindowRow2*1.0);
  //
  hv_ImageRow2 = hv_Height+(hv_WindowHeightExtension/hv_WindowImageRatioHeight);
  hv_ImageColumn2 = hv_Width+(0/hv_WindowImageRatioWidth);
  hv_ImageRatio = hv_ImageColumn2/(hv_ImageRow2*1.0);
  if (0 != (int(hv_ImageRatio>hv_WindowRatio)))
  {
    //
    //Extend image until right window border.
    hv_SetPartColumn2 = hv_ImageColumn2;
    hv_ImageWindowRatioHeight = hv_ImageColumn2/(hv_WindowColumn2*1.0);
    hv_ImageRow2InWindow = hv_ImageRow2/hv_ImageWindowRatioHeight;
    hv_SetPartRow2 = hv_ImageRow2+((hv_WindowRow2-hv_ImageRow2InWindow)/hv_WindowImageRatioWidth);
  }
  else
  {
    //
    //Extend image until bottom of window.
    hv_SetPartRow2 = hv_ImageRow2;
    hv_ImageWindowRatioHeight = hv_ImageRow2/(hv_WindowRow2*1.0);
    hv_ImageCol2InWindow = hv_ImageColumn2/hv_ImageWindowRatioHeight;
    hv_SetPartColumn2 = hv_ImageColumn2+((hv_WindowColumn2-hv_ImageCol2InWindow)/hv_WindowImageRatioHeight);
  }
  if (HDevWindowStack::IsOpen())
    SetPart(HDevWindowStack::GetActive(),0, 0, hv_SetPartRow2-1, hv_SetPartColumn2-1);
  if (HDevWindowStack::IsOpen())
    DispObj(ho_Image, HDevWindowStack::GetActive());
  //
  //
  //Calculate the window size.
  GetWindowExtents(hv_WindowHandle, &hv__, &hv__, &hv_WindowWidth, &hv_WindowHeight);
  //
  //Visualize explanation text and image.
  hv_ExplanationText = HTuple();
  hv_ExplanationText[hv_ExplanationText.TupleLength()] = " * Choose between 'Rectangle1' or 'Rectangle2' templates.";
  hv_ExplanationText[hv_ExplanationText.TupleLength()] = " ";
  hv_ExplanationText[hv_ExplanationText.TupleLength()] = " * Draw one or more templates.";
  hv_ExplanationText[hv_ExplanationText.TupleLength()] = "   (Right-click) to finish drawing the current template.";
  hv_ExplanationText[hv_ExplanationText.TupleLength()] = " ";
  hv_ExplanationText[hv_ExplanationText.TupleLength()] = " * Press the 'Undo' button to remove the last drawn object.";
  hv_ExplanationText[hv_ExplanationText.TupleLength()] = " ";
  hv_ExplanationText[hv_ExplanationText.TupleLength()] = " * Click 'Continue' to finish.";
  //
  //Get coordinates of previous window.
  hv_PrevWindowHeight = ((const HTuple&)hv_WindowHeight)[0];
  //
  //Open window in same row.
  hv_TextWindowRow = hv_WindowRow;
  hv_TextWindowColumn = hv_WindowColumn+hv_WindowWidth;
  if (0 != (int(hv_TextWindowColumn!=0)))
  {
    hv_TextWindowColumn += 5;
  }
  //
  dev_open_window_fit_size(hv_TextWindowRow, hv_TextWindowColumn, 560, hv_PrevWindowHeight, 
      560, hv_PrevWindowHeight, &hv_WindowHandleText);
  set_display_font(hv_WindowHandleText, 14, "mono", "true", "false");
  if (HDevWindowStack::IsOpen())
    DispText(HDevWindowStack::GetActive(),hv_ExplanationText, "window", "top", "left", 
        "black", HTuple(), HTuple());
  HDevWindowStack::SetActive(hv_WindowHandle);
  //
  //
  //Visualize the buttons for drawing the template regions.
  //
  //Add the 'Rectangle1' and 'Rectangle2' buttons.
  hv_RectText.Clear();
  hv_RectText[0] = "Rectangle1";
  hv_RectText[1] = "Rectangle2";
  hv_DrawText = hv_DrawText.TupleConcat(hv_RectText);
  {
  HTuple end_val101 = (hv_RectText.TupleLength())-1;
  HTuple step_val101 = 1;
  for (hv_Index=0; hv_Index.Continue(end_val101, step_val101); hv_Index += step_val101)
  {
    //Calculate the text size for 'Rectangle1' and 'Rectangle2' button.
    GetStringExtents(hv_WindowHandle, HTuple(hv_RectText[hv_Index]), &hv__, &hv__, 
        &hv_RectTextWidth, &hv_RectTextHeight);
    //
    hv_TextRow = hv_TextRow.TupleConcat((hv_WindowHeight-hv_RectTextHeight)-20);
    //
    if (0 != (int(HTuple(hv_RectText[hv_Index])==HTuple("Rectangle1"))))
    {
      hv_TextColumn = hv_TextColumn.TupleConcat(20);
    }
    else
    {
      hv_TextColumn = hv_TextColumn.TupleConcat(40+hv_RectTextWidth);
    }
    //Set the button size and color for 'Rectangle1' and 'Rectangle2'.
    hv_ButtonWidth = hv_ButtonWidth.TupleConcat(hv_RectTextWidth*1.2);
    hv_ButtonHeight = hv_ButtonHeight.TupleConcat(hv_RectTextHeight*1.5);
    hv_ValueColors = hv_ValueColors.TupleConcat("black");
    hv_BoxColor = hv_BoxColor.TupleConcat("#f28d26");
  }
  }
  //
  //Add the 'Undo' button.
  hv_DrawText = hv_DrawText.TupleConcat("Undo");
  //Calculate the text size for 'Undo' button.
  GetStringExtents(hv_WindowHandle, "Undo", &hv__, &hv__, &hv_UndoTextWidth, &hv_UndoTextHeight);
  //
  hv_TextRow = hv_TextRow.TupleConcat((hv_WindowHeight-hv_UndoTextHeight)-20);
  hv_TextColumn = hv_TextColumn.TupleConcat((40+(2*hv_RectTextWidth))+40);
  //Set the button size and color for 'Undo'.
  hv_ButtonWidth = hv_ButtonWidth.TupleConcat(hv_UndoTextWidth*1.2);
  hv_ButtonHeight = hv_ButtonHeight.TupleConcat(hv_UndoTextHeight*1.5);
  hv_ValueColors = hv_ValueColors.TupleConcat("black");
  hv_BoxColor = hv_BoxColor.TupleConcat("#f28d26");
  //
  //Add the 'Continue' button.
  hv_DrawText = hv_DrawText.TupleConcat("Continue");
  //Calculate the text size for 'Continue' button.
  GetStringExtents(hv_WindowHandle, "Continue", &hv__, &hv__, &hv_ContinueTextWidth, 
      &hv_ContinueTextHeight);
  //
  hv_TextRow = hv_TextRow.TupleConcat((hv_WindowHeight-hv_ContinueTextHeight)-20);
  hv_TextColumn = hv_TextColumn.TupleConcat((hv_WindowWidth-hv_ContinueTextWidth)-30);
  //Set the button size and color for 'Continue'.
  hv_ButtonWidth = hv_ButtonWidth.TupleConcat(hv_ContinueTextWidth*1.2);
  hv_ButtonHeight = hv_ButtonHeight.TupleConcat(hv_ContinueTextHeight*1.5);
  hv_ValueColors = hv_ValueColors.TupleConcat("black");
  hv_BoxColor = hv_BoxColor.TupleConcat("#f28d26");
  //
  while (true)
  {
    //Visualize image and templates.
    if (HDevWindowStack::IsOpen())
      DispObj(ho_Image, HDevWindowStack::GetActive());
    if (HDevWindowStack::IsOpen())
      SetColor(HDevWindowStack::GetActive(),hv_TemplateRegionColor);
    if (HDevWindowStack::IsOpen())
      DispObj((*ho_TemplateRegion), HDevWindowStack::GetActive());
    //
    dev_disp_button(hv_DrawText, hv_TextRow, hv_TextColumn, hv_ButtonWidth, hv_ButtonHeight, 
        hv_ValueColors, hv_BoxColor, hv_HighlightColor, hv_WindowHandle, &hv_SelectedButton);
    //
    //Re-draw image and templates.
    if (HDevWindowStack::IsOpen())
      DispObj(ho_Image, HDevWindowStack::GetActive());
    if (HDevWindowStack::IsOpen())
      SetColor(HDevWindowStack::GetActive(),hv_TemplateRegionColor);
    if (HDevWindowStack::IsOpen())
      DispObj((*ho_TemplateRegion), HDevWindowStack::GetActive());
    //
    if (0 != (int(hv_SelectedButton==0)))
    {
      //This is the 'Rectangle1' case.
      DrawRectangle1(hv_WindowHandle, &hv_Row1, &hv_Column1, &hv_Row2, &hv_Column2);
      if (0 != (int(hv_Column2==0)))
      {
        //Right-click --> abort drawing the rectangle
        continue;
      }
      GenRectangle1(&ho_Rectangle1, hv_Row1, hv_Column1, hv_Row2, hv_Column2);
      ConcatObj((*ho_TemplateRegion), ho_Rectangle1, &(*ho_TemplateRegion));
      ReduceDomain(ho_Image, ho_Rectangle1, &ho_ImageReduced);
      ConcatObj((*ho_Template), ho_ImageReduced, &(*ho_Template));
    }
    else if (0 != (int(hv_SelectedButton==1)))
    {
      //This is the 'Rectangle2' case.
      DrawRectangle2(hv_WindowHandle, &hv_Row1, &hv_Column1, &hv_Phi1, &hv_Length1, 
          &hv_Length2);
      if (0 != (int(hv_Length1==0)))
      {
        //Right-click --> abort drawing the rectangle
        continue;
      }
      GenRectangle2(&ho_Rectangle2, hv_Row1, hv_Column1, hv_Phi1, hv_Length1, hv_Length2);
      ConcatObj((*ho_TemplateRegion), ho_Rectangle2, &(*ho_TemplateRegion));
      ReduceDomain(ho_Image, ho_Rectangle2, &ho_ImageReduced);
      ConcatObj((*ho_Template), ho_ImageReduced, &(*ho_Template));
    }
    else if (0 != (int(hv_SelectedButton==2)))
    {
      //This is the 'Undo' button case.
      CountObj((*ho_TemplateRegion), &hv_Count);
      if (0 != (int(hv_Count==0)))
      {
        continue;
      }
      else
      {
        RemoveObj((*ho_TemplateRegion), &(*ho_TemplateRegion), hv_Count);
        RemoveObj((*ho_Template), &(*ho_Template), hv_Count);
      }
    }
    else if (0 != (int(hv_SelectedButton==3)))
    {
      //This is the 'Continue' button case.
      break;
    }
  }
  //
  // dev_set_preferences(...); only in hdevelop
  // dev_set_preferences(...); only in hdevelop
  //
  //Close the windows.
  if (HDevWindowStack::IsOpen())
    CloseWindow(HDevWindowStack::Pop());
  if (HDevWindowStack::IsOpen())
    CloseWindow(HDevWindowStack::Pop());
  return;
}

// Chapter: Matching / Deep Counting
// Short Description: Parse generic Deep Counting visualization parameters. 
void parse_generic_deep_counting_visualization_parameters (HTuple hv_GenParamName, 
    HTuple hv_GenParamValue, HTuple *hv_LineWidth, HTuple *hv_CrossColor, HTuple *hv_CrossScale, 
    HTuple *hv_FontSize, HTuple *hv_ScaleMode, HTuple *hv_InteractiveMinScore)
{

  // Local iconic variables

  // Local control variables
  HTuple  hv_ParamIdx, hv_AllowedGenParams, hv_CaseIdx;

  //Define default visualization parameters.
  (*hv_LineWidth) = 5;
  (*hv_CrossColor) = "green";
  (*hv_CrossScale) = 15;
  (*hv_FontSize) = 12;
  (*hv_ScaleMode) = "equal";
  (*hv_InteractiveMinScore) = 0;
  //
  //Parse the generic parameters.
  {
  HTuple end_val9 = (hv_GenParamName.TupleLength())-1;
  HTuple step_val9 = 1;
  for (hv_ParamIdx=0; hv_ParamIdx.Continue(end_val9, step_val9); hv_ParamIdx += step_val9)
  {
    hv_AllowedGenParams.Clear();
    hv_AllowedGenParams[0] = "cross_color";
    hv_AllowedGenParams[1] = "cross_scale";
    hv_AllowedGenParams[2] = "line_width";
    hv_AllowedGenParams[3] = "font_size";
    hv_AllowedGenParams[4] = "scale_mode";
    hv_AllowedGenParams[5] = "interactive_min_score";
    TupleFind(hv_AllowedGenParams, HTuple(hv_GenParamName[hv_ParamIdx]), &hv_CaseIdx);
    switch (hv_CaseIdx.I())
    {
    case 0:
      //Get cross color.
      (*hv_CrossColor) = HTuple(hv_GenParamValue[hv_ParamIdx]);
      break;
    case 1:
      //Get cross scale.
      (*hv_CrossScale) = HTuple(hv_GenParamValue[hv_ParamIdx]);
      break;
    case 2:
      //Get line width.
      (*hv_LineWidth) = HTuple(hv_GenParamValue[hv_ParamIdx]);
      break;
    case 3:
      //Get font size.
      (*hv_FontSize) = HTuple(hv_GenParamValue[hv_ParamIdx]);
      break;
    case 4:
      //Get scale mode.
      (*hv_ScaleMode) = HTuple(hv_GenParamValue[hv_ParamIdx]);
      break;
    case 5:
      //Enable or disable interactive min score.
      (*hv_InteractiveMinScore) = HTuple(hv_GenParamValue[hv_ParamIdx]);
      (*hv_InteractiveMinScore) = HTuple(int((*hv_InteractiveMinScore)==1)).TupleOr(int((*hv_InteractiveMinScore)==HTuple("true")));
      break;
    case -1:
      //General parameter not valid.
      throw HException(("The generic parameter \""+HTuple(hv_GenParamName[hv_ParamIdx]))+"\" is not valid.");
    }
  }
  }
  return;
}

