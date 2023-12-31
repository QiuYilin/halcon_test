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
// Chapter: XLD / Creation
// Short Description: Create an arrow shaped XLD contour. 
extern void gen_arrow_contour_xld (HObject *ho_Arrow, HTuple hv_Row1, HTuple hv_Column1, 
    HTuple hv_Row2, HTuple hv_Column2, HTuple hv_HeadLength, HTuple hv_HeadWidth);
// Chapter: OCR / Deep OCR
// Short Description: Visualize Deep OCR detection and recognition results. 
void dev_display_deep_ocr_results (HObject ho_Image, HTuple hv_WindowHandle, HTuple hv_DeepOcrResult, 
    HTuple hv_GenParamName, HTuple hv_GenParamValue);
// Chapter: OCR / Deep OCR
// Short Description: Visualize Deep OCR detection and recognition results. 
void dev_display_deep_ocr_results_preprocessed (HTuple hv_WindowHandle, HTuple hv_DeepOcrResult, 
    HTuple hv_GenParamName, HTuple hv_GenParamValue);
// Chapter: OCR / Deep OCR
// Short Description: Display Deep OCR score maps. 
void dev_display_deep_ocr_score_maps (HTuple hv_WindowHandle, HTuple hv_DeepOcrResult, 
    HTuple hv_GenParamName, HTuple hv_GenParamValue);
// Chapter: OCR / Deep OCR
// Short Description: Get the detection word boxes contained in the specified ResultKey. 
void get_deep_ocr_detection_word_boxes (HTuple hv_DeepOcrResult, HTuple hv_ResultKey, 
    HTuple *hv_WordBoxRow, HTuple *hv_WordBoxCol, HTuple *hv_WordBoxPhi, HTuple *hv_WordBoxLength1, 
    HTuple *hv_WordBoxLength2);
// Chapter: OCR / Deep OCR
// Short Description: Parse generic visualization parameters. 
void parse_generic_visualization_parameters (HTuple hv_GenParamName, HTuple hv_GenParamValue, 
    HTuple *hv_BoxColor, HTuple *hv_LineWidth, HTuple *hv_FontSize, HTuple *hv_ShowWords, 
    HTuple *hv_ShowOrientation);

// Procedures 
// Chapter: OCR / Deep OCR
// Short Description: Visualize Deep OCR detection and recognition results. 
void dev_display_deep_ocr_results (HObject ho_Image, HTuple hv_WindowHandle, HTuple hv_DeepOcrResult, 
    HTuple hv_GenParamName, HTuple hv_GenParamValue)
{

  // Local iconic variables
  HObject  ho_PreprocessedImage, ho_ScoreMapsImage;
  HObject  ho_WordRectangle, ho_Arrow;

  // Local control variables
  HTuple  hv_NumberIconicObjects, hv_BoxColor, hv_LineWidth;
  HTuple  hv_FontSize, hv_ShowWords, hv_ShowOrientation, hv_ActiveWindow;
  HTuple  hv_ActiveFont, hv_Font, hv_DetectionMode, hv_RecognitionMode;
  HTuple  hv_Words, hv_HasImageKey, hv_HasScoreMapsKey, hv_Width;
  HTuple  hv_Height, hv_WordBoxesKey, hv_PreprocessedImageWidth;
  HTuple  hv_PreprocessedImageHeight, hv_ScoreMapsImageWidth;
  HTuple  hv_ScoreMapsImageHeight, hv_Row, hv_Col, hv_Phi;
  HTuple  hv_Length1, hv_Length2, hv_ArrowSizeFactorLength;
  HTuple  hv_ArrowSizeFactorHead, hv_MaxLengthArrow, hv_HalfLengthArrow;
  HTuple  hv_ArrowBaseRow, hv_ArrowBaseCol, hv_ArrowHeadRow;
  HTuple  hv_ArrowHeadCol, hv_ArrowHeadSize, hv_HasRecognition;
  HTuple  hv_RecognizedWord, hv_D, hv_Alpha, hv_WordRow, hv_WordCol;
  HTuple  hv_Ascent, hv_Descent, hv__, hv_MarginBottom, hv_WindowWidth;
  HTuple  hv_WindowHeight, hv_ImageWidth, hv_ImageHeight;
  HTuple  hv_ZoomedImageHeight, hv_ZoomedImageWidth;

  //This procedure visualizes the results DeepOcrResult of a Deep OCR model.
  //
  //
  CountObj(ho_Image, &hv_NumberIconicObjects);
  if (0 != (int(hv_NumberIconicObjects>1)))
  {
    throw HException("Only single input image allowed.");
  }
  //
  if (0 != (int((hv_DeepOcrResult.TupleLength())>1)))
  {
    throw HException("Only single result dictionary allowed.");
  }
  //
  //Parse generic visualization parameters.
  parse_generic_visualization_parameters(hv_GenParamName, hv_GenParamValue, &hv_BoxColor, 
      &hv_LineWidth, &hv_FontSize, &hv_ShowWords, &hv_ShowOrientation);
  //
  //Prepare the window.
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
  if (HDevWindowStack::IsOpen())
    SetLut(HDevWindowStack::GetActive(),"default");
  //
  //Check whether detection and recognition results are available.
  GetDictParam(hv_DeepOcrResult, "key_exists", "words", &hv_DetectionMode);
  GetDictParam(hv_DeepOcrResult, "key_exists", "word", &hv_RecognitionMode);
  //
  if (0 != hv_DetectionMode)
  {
    //Visualize the oriented rectangles marking the detected words.
    //
    if (HDevWindowStack::IsOpen())
      DispObj(ho_Image, HDevWindowStack::GetActive());
    //
    //Determine the dictionary key with word boxes to use based on the size of Image.
    GetDictTuple(hv_DeepOcrResult, "words", &hv_Words);
    GetDictParam(hv_DeepOcrResult, "key_exists", "image", &hv_HasImageKey);
    GetDictParam(hv_DeepOcrResult, "key_exists", "score_maps", &hv_HasScoreMapsKey);
    GetImageSize(ho_Image, &hv_Width, &hv_Height);
    hv_WordBoxesKey = "words";
    if (0 != hv_HasImageKey)
    {
      GetDictObject(&ho_PreprocessedImage, hv_DeepOcrResult, "image");
      GetImageSize(ho_PreprocessedImage, &hv_PreprocessedImageWidth, &hv_PreprocessedImageHeight);
      if (0 != (HTuple(int(hv_Width==hv_PreprocessedImageWidth)).TupleAnd(int(hv_Height==hv_PreprocessedImageHeight))))
      {
        hv_WordBoxesKey = "word_boxes_on_image";
      }
    }
    else if (0 != hv_HasScoreMapsKey)
    {
      GetDictObject(&ho_ScoreMapsImage, hv_DeepOcrResult, "score_maps");
      GetImageSize(ho_ScoreMapsImage, &hv_ScoreMapsImageWidth, &hv_ScoreMapsImageHeight);
      if (0 != (HTuple(int(hv_Width==hv_ScoreMapsImageWidth)).TupleAnd(int(hv_Height==hv_ScoreMapsImageHeight))))
      {
        hv_WordBoxesKey = "word_boxes_on_score_maps";
      }
    }
    //
    //Get rectangle2 boxes of detected words.
    get_deep_ocr_detection_word_boxes(hv_DeepOcrResult, hv_WordBoxesKey, &hv_Row, 
        &hv_Col, &hv_Phi, &hv_Length1, &hv_Length2);
    //
    if (0 != (int((hv_Row.TupleLength())>0)))
    {
      //Generate XLD contours of the word rectangles.
      GenRectangle2ContourXld(&ho_WordRectangle, hv_Row, hv_Col, hv_Phi, hv_Length1, 
          hv_Length2);
      //
      if (0 != hv_ShowOrientation)
      {
        //Generate orientation arrows.
        hv_ArrowSizeFactorLength = 0.4;
        hv_ArrowSizeFactorHead = 0.2;
        hv_MaxLengthArrow = 20;
        hv_HalfLengthArrow = hv_MaxLengthArrow.TupleMin2(hv_Length1*hv_ArrowSizeFactorLength);
        hv_ArrowBaseRow = hv_Row-((hv_Length1-hv_HalfLengthArrow)*(hv_Phi.TupleSin()));
        hv_ArrowBaseCol = hv_Col+((hv_Length1-hv_HalfLengthArrow)*(hv_Phi.TupleCos()));
        hv_ArrowHeadRow = hv_Row-((hv_Length1+hv_HalfLengthArrow)*(hv_Phi.TupleSin()));
        hv_ArrowHeadCol = hv_Col+((hv_Length1+hv_HalfLengthArrow)*(hv_Phi.TupleCos()));
        hv_ArrowHeadSize = (hv_MaxLengthArrow.TupleMin2(hv_Length1.TupleMin2(hv_Length2)))*hv_ArrowSizeFactorHead;
        gen_arrow_contour_xld(&ho_Arrow, hv_ArrowBaseRow, hv_ArrowBaseCol, hv_ArrowHeadRow, 
            hv_ArrowHeadCol, hv_ArrowHeadSize, hv_ArrowHeadSize);
      }
      //
      //Display black boundaries around rectangles and arrows.
      if (HDevWindowStack::IsOpen())
        SetColor(HDevWindowStack::GetActive(),"black");
      if (HDevWindowStack::IsOpen())
        SetLineWidth(HDevWindowStack::GetActive(),hv_LineWidth+2);
      if (HDevWindowStack::IsOpen())
        DispObj(ho_WordRectangle, HDevWindowStack::GetActive());
      if (0 != hv_ShowOrientation)
      {
        if (HDevWindowStack::IsOpen())
          DispObj(ho_Arrow, HDevWindowStack::GetActive());
      }
      //
      //Display rectangles and arrows.
      if (HDevWindowStack::IsOpen())
        SetColor(HDevWindowStack::GetActive(),hv_BoxColor);
      if (HDevWindowStack::IsOpen())
        SetLineWidth(HDevWindowStack::GetActive(),hv_LineWidth);
      if (HDevWindowStack::IsOpen())
        DispObj(ho_WordRectangle, HDevWindowStack::GetActive());
      if (0 != hv_ShowOrientation)
      {
        if (HDevWindowStack::IsOpen())
          DispObj(ho_Arrow, HDevWindowStack::GetActive());
      }
      //
      //Display recognized words, if available.
      if (0 != hv_ShowWords)
      {
        //
        //Check whether the result contains recognized words.
        GetDictParam(hv_Words, "key_exists", "word", &hv_HasRecognition);
        if (0 != hv_HasRecognition)
        {
          GetDictTuple(hv_Words, "word", &hv_RecognizedWord);
          //
          //Display each recognized word at the bottom-left corner of the respective word box.
          if (0 != (int((hv_RecognizedWord.TupleLength())>0)))
          {
            hv_D = hv_Length1.TupleHypot(hv_Length2);
            hv_Alpha = hv_Length2.TupleAtan2(hv_Length1);
            hv_WordRow = hv_Row+(((hv_Alpha+hv_Phi).TupleSin())*hv_D);
            hv_WordCol = hv_Col-(((hv_Alpha+hv_Phi).TupleCos())*hv_D);
            if (HDevWindowStack::IsOpen())
              DispText(HDevWindowStack::GetActive(),hv_RecognizedWord, "image", hv_WordRow, 
                  hv_WordCol, "white", (HTuple("box_color").Append("shadow")), (HTuple("black").Append("false")));
          }
        }
      }
    }
  }
  else if (0 != hv_RecognitionMode)
  {
    //Recognition mode: Show the recognized word.
    //
    GetDictTuple(hv_DeepOcrResult, "word", &hv_RecognizedWord);
    if (0 != (int((hv_RecognizedWord.TupleLength())>1)))
    {
      throw HException("In recognition mode only a single word can be processed.");
    }
    //
    GetStringExtents(hv_WindowHandle, hv_RecognizedWord, &hv_Ascent, &hv_Descent, 
        &hv__, &hv__);
    hv_MarginBottom = (hv_Ascent+hv_Descent)+5;
    //
    //Zoom the image to fit into the window.
    GetWindowExtents(hv_WindowHandle, &hv__, &hv__, &hv_WindowWidth, &hv_WindowHeight);
    GetImageSize(ho_Image, &hv_ImageWidth, &hv_ImageHeight);
    hv_ZoomedImageHeight = (HTuple(0).TupleMax2(hv_WindowHeight-hv_MarginBottom)).TupleInt();
    if (0 != (int(hv_ZoomedImageHeight==0)))
    {
      throw HException("Font size too large for given window size.");
    }
    hv_ZoomedImageWidth = ((hv_ImageWidth/(hv_ImageHeight.TupleReal()))*hv_ZoomedImageHeight).TupleInt();
    if (0 != (int(hv_ZoomedImageWidth>hv_WindowWidth)))
    {
      hv_ZoomedImageWidth = hv_WindowWidth;
      hv_ZoomedImageHeight = ((hv_ImageHeight/(hv_ImageWidth.TupleReal()))*hv_ZoomedImageWidth).TupleInt();
    }
    ZoomImageSize(ho_Image, &ho_Image, hv_ZoomedImageWidth, hv_ZoomedImageHeight, 
        "constant");
    //
    //Display the image.
    if (HDevWindowStack::IsOpen())
      SetPart(HDevWindowStack::GetActive(),0, 0, hv_WindowHeight, hv_WindowWidth);
    if (HDevWindowStack::IsOpen())
      DispObj(ho_Image, HDevWindowStack::GetActive());
    //
    //Display the recognized word below the image.
    if (0 != hv_ShowWords)
    {
      if (HDevWindowStack::IsOpen())
        DispText(HDevWindowStack::GetActive(),hv_RecognizedWord, "image", hv_WindowHeight-hv_MarginBottom, 
            5, "white", "box", "false");
    }
  }
  else
  {
    //Only display the image.
    if (HDevWindowStack::IsOpen())
      DispObj(ho_Image, HDevWindowStack::GetActive());
  }
  //
  //Update window.
  SetWindowParam(hv_WindowHandle, "flush", "true");
  FlushBuffer(hv_WindowHandle);
  //
  //Restore the original values.
  if (0 != (int(hv_ActiveWindow!=hv_WindowHandle)))
  {
    HDevWindowStack::SetActive(hv_ActiveWindow);
  }
  if (0 != (int(hv_ActiveFont!=hv_Font)))
  {
    SetFont(hv_WindowHandle, hv_ActiveFont);
  }
  //
  return;
}

// Chapter: OCR / Deep OCR
// Short Description: Visualize Deep OCR detection and recognition results. 
void dev_display_deep_ocr_results_preprocessed (HTuple hv_WindowHandle, HTuple hv_DeepOcrResult, 
    HTuple hv_GenParamName, HTuple hv_GenParamValue)
{

  // Local iconic variables
  HObject  ho_PreprocessedImage;

  // Local control variables
  HTuple  hv_DetectionMode, hv_HasImageKey, hv_ActiveWindow;

  //This procedure visualizes the results DeepOcrResult of a Deep OCR model
  //on the preprocessed image contained in DeepOcrResult.
  //
  //
  if (0 != (int((hv_DeepOcrResult.TupleLength())>1)))
  {
    throw HException("Only single result dictionary allowed.");
  }
  //
  //Validate key for detection mode.
  GetDictParam(hv_DeepOcrResult, "key_exists", "words", &hv_DetectionMode);
  if (0 != (hv_DetectionMode.TupleNot()))
  {
    throw HException("Only results for detection or auto mode are allowed.");
  }
  //
  //Extract the preprocessed image stored in the key 'image'.
  GetDictParam(hv_DeepOcrResult, "key_exists", "image", &hv_HasImageKey);
  if (0 != (hv_HasImageKey.TupleNot()))
  {
    throw HException("Preprocessed image not available in dictionary.");
  }
  GetDictObject(&ho_PreprocessedImage, hv_DeepOcrResult, "image");
  //
  //Visualize the results on the preprocessed image.
  dev_display_deep_ocr_results(ho_PreprocessedImage, hv_WindowHandle, hv_DeepOcrResult, 
      hv_GenParamName, hv_GenParamValue);
  //
  //Display the window title.
  if (HDevWindowStack::IsOpen())
    hv_ActiveWindow = HDevWindowStack::GetActive();
  if (0 != (int(hv_ActiveWindow!=hv_WindowHandle)))
  {
    HDevWindowStack::SetActive(hv_WindowHandle);
  }
  if (HDevWindowStack::IsOpen())
    DispText(HDevWindowStack::GetActive(),"Preprocessed image", "image", 10, 10, 
        "black", HTuple(), HTuple());
  HDevWindowStack::SetActive(hv_ActiveWindow);
  //
  return;
}

// Chapter: OCR / Deep OCR
// Short Description: Display Deep OCR score maps. 
void dev_display_deep_ocr_score_maps (HTuple hv_WindowHandle, HTuple hv_DeepOcrResult, 
    HTuple hv_GenParamName, HTuple hv_GenParamValue)
{

  // Local iconic variables
  HObject  ho_ScoreMaps, ho_CharacterScore, ho_LinkScore;
  HObject  ho_ScoreMapsConcat, ho_ScoreMapsTiled, ho_Line;

  // Local control variables
  HTuple  hv_ActiveWindow, hv_Width, hv_Height;

  //This procedure visualizes the character and link scores
  //returned by the detection component of the Deep OCR model.
  //
  if (0 != (int((hv_DeepOcrResult.TupleLength())>1)))
  {
    throw HException("Only single result dictionary allowed.");
  }
  //
  if (HDevWindowStack::IsOpen())
    hv_ActiveWindow = HDevWindowStack::GetActive();
  if (0 != (int(hv_ActiveWindow!=hv_WindowHandle)))
  {
    HDevWindowStack::SetActive(hv_WindowHandle);
  }
  if (HDevWindowStack::IsOpen())
    ClearWindow(HDevWindowStack::GetActive());
  SetWindowParam(hv_WindowHandle, "flush", "false");
  //
  //Extract score maps from the result dictionary.
  GetDictObject(&ho_ScoreMaps, hv_DeepOcrResult, "score_maps");
  AccessChannel(ho_ScoreMaps, &ho_CharacterScore, 1);
  AccessChannel(ho_ScoreMaps, &ho_LinkScore, 2);
  ConcatObj(ho_CharacterScore, ho_LinkScore, &ho_ScoreMapsConcat);
  TileImages(ho_ScoreMapsConcat, &ho_ScoreMapsTiled, 2, "horizontal");
  GetImageSize(ho_ScoreMaps, &hv_Width, &hv_Height);
  //
  //Make sure the minimum and maximum gray values of the score map image
  //are 0 and 1, respectively. This is necessary to get the correct color
  //range from the 'jet' color map.
  SetGrayval(ho_ScoreMapsTiled, HTuple(0).TupleConcat(hv_Height-1), HTuple(0).TupleConcat(hv_Width-1), 
      (HTuple(0).Append(1)));
  //
  //Display the score maps using the 'jet' color map.
  if (HDevWindowStack::IsOpen())
    SetLut(HDevWindowStack::GetActive(),"jet");
  if (HDevWindowStack::IsOpen())
    DispObj(ho_ScoreMapsTiled, HDevWindowStack::GetActive());
  if (HDevWindowStack::IsOpen())
    DispText(HDevWindowStack::GetActive(),(HTuple("Character score").Append("Link score")), 
        "image", (HTuple(10).Append(10)), HTuple(10).TupleConcat(hv_Width+10), "black", 
        HTuple(), HTuple());
  //
  //Draw a separating line between score maps.
  GenContourPolygonXld(&ho_Line, HTuple(-0.5).TupleConcat(hv_Height-0.5), (hv_Width-0.5).TupleConcat(hv_Width-0.5));
  if (HDevWindowStack::IsOpen())
    SetColor(HDevWindowStack::GetActive(),"white");
  if (HDevWindowStack::IsOpen())
    SetLineWidth(HDevWindowStack::GetActive(),2);
  if (HDevWindowStack::IsOpen())
    DispObj(ho_Line, HDevWindowStack::GetActive());
  //
  SetWindowParam(hv_WindowHandle, "flush", "true");
  FlushBuffer(hv_WindowHandle);
  //
  if (0 != (int(hv_ActiveWindow!=hv_WindowHandle)))
  {
    HDevWindowStack::SetActive(hv_ActiveWindow);
  }
  //
  return;
}

// Chapter: OCR / Deep OCR
// Short Description: Get the detection word boxes contained in the specified ResultKey. 
void get_deep_ocr_detection_word_boxes (HTuple hv_DeepOcrResult, HTuple hv_ResultKey, 
    HTuple *hv_WordBoxRow, HTuple *hv_WordBoxCol, HTuple *hv_WordBoxPhi, HTuple *hv_WordBoxLength1, 
    HTuple *hv_WordBoxLength2)
{

  // Local iconic variables

  // Local control variables
  HTuple  hv_SupportedKey, hv_WordBoxDict, hv_SameSize;

  //This procedure retrieves the rectangle2 parameters of the detection word boxes
  //contained in the specified result dictionary key.
  //
  hv_SupportedKey = HTuple(HTuple(int(hv_ResultKey==HTuple("words"))).TupleOr(int(hv_ResultKey==HTuple("word_boxes_on_image")))).TupleOr(int(hv_ResultKey==HTuple("word_boxes_on_score_maps")));
  if (0 != (hv_SupportedKey.TupleNot()))
  {
    throw HException("Unsupported dictionary key.");
  }
  //
  //Get detection rectangle2 parameters.
  GetDictTuple(hv_DeepOcrResult, hv_ResultKey, &hv_WordBoxDict);
  GetDictTuple(hv_WordBoxDict, "row", &(*hv_WordBoxRow));
  GetDictTuple(hv_WordBoxDict, "col", &(*hv_WordBoxCol));
  GetDictTuple(hv_WordBoxDict, "phi", &(*hv_WordBoxPhi));
  GetDictTuple(hv_WordBoxDict, "length1", &(*hv_WordBoxLength1));
  GetDictTuple(hv_WordBoxDict, "length2", &(*hv_WordBoxLength2));
  hv_SameSize = HTuple(HTuple(HTuple(int(((*hv_WordBoxRow).TupleLength())==((*hv_WordBoxCol).TupleLength()))).TupleAnd(int(((*hv_WordBoxRow).TupleLength())==((*hv_WordBoxPhi).TupleLength())))).TupleAnd(int(((*hv_WordBoxRow).TupleLength())==((*hv_WordBoxLength1).TupleLength())))).TupleAnd(int(((*hv_WordBoxRow).TupleLength())==((*hv_WordBoxLength2).TupleLength())));
  if (0 != (hv_SameSize.TupleNot()))
  {
    throw HException("Rectangle2 parameters do not have the same size.");
  }
  //
  return;
}

// Chapter: OCR / Deep OCR
// Short Description: Parse generic visualization parameters. 
void parse_generic_visualization_parameters (HTuple hv_GenParamName, HTuple hv_GenParamValue, 
    HTuple *hv_BoxColor, HTuple *hv_LineWidth, HTuple *hv_FontSize, HTuple *hv_ShowWords, 
    HTuple *hv_ShowOrientation)
{

  // Local iconic variables

  // Local control variables
  HTuple  hv_ShowScoreMaps, hv_ParamIdx, hv_AllowedGenParams;
  HTuple  hv_CaseIdx, hv_BoolShowWords, hv_BoolShowArrow;

  //Set default values.
  (*hv_BoxColor) = "green";
  (*hv_LineWidth) = 3;
  (*hv_FontSize) = 12;
  hv_ShowScoreMaps = 1;
  (*hv_ShowWords) = 1;
  (*hv_ShowOrientation) = 1;

  //Parse the generic parameters.
  {
  HTuple end_val9 = (hv_GenParamName.TupleLength())-1;
  HTuple step_val9 = 1;
  for (hv_ParamIdx=0; hv_ParamIdx.Continue(end_val9, step_val9); hv_ParamIdx += step_val9)
  {
    hv_AllowedGenParams.Clear();
    hv_AllowedGenParams[0] = "box_color";
    hv_AllowedGenParams[1] = "line_width";
    hv_AllowedGenParams[2] = "font_size";
    hv_AllowedGenParams[3] = "show_words";
    hv_AllowedGenParams[4] = "show_orientation";
    TupleFind(hv_AllowedGenParams, HTuple(hv_GenParamName[hv_ParamIdx]), &hv_CaseIdx);
    switch (hv_CaseIdx.I())
    {
    case 0:
      //Get color.
      (*hv_BoxColor) = HTuple(hv_GenParamValue[hv_ParamIdx]);
      break;
    case 1:
      //Get line width.
      (*hv_LineWidth) = HTuple(hv_GenParamValue[hv_ParamIdx]);
      break;
    case 2:
      //Get font size.
      (*hv_FontSize) = HTuple(hv_GenParamValue[hv_ParamIdx]);
      break;
    case 3:
      //Check whether words shall be displayed.
      hv_BoolShowWords = HTuple(hv_GenParamValue[hv_ParamIdx]);
      if (0 != (int(hv_BoolShowWords==HTuple("true"))))
      {
        (*hv_ShowWords) = 1;
      }
      else
      {
        (*hv_ShowWords) = 0;
      }
      break;
    case 4:
      //Check whether arrow of the word box should be displayed.
      hv_BoolShowArrow = HTuple(hv_GenParamValue[hv_ParamIdx]);
      if (0 != (int(hv_BoolShowArrow==HTuple("true"))))
      {
        (*hv_ShowOrientation) = 1;
      }
      else
      {
        (*hv_ShowOrientation) = 0;
      }
      break;
    case -1:
      //General parameter not valid.
      throw HException(("The general parameter \""+HTuple(hv_GenParamName[hv_ParamIdx]))+"\" is not valid.");
    }
  }
  }
  return;
}


