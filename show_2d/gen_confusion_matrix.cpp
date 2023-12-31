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

extern void dev_resize_window_fit_size (HTuple hv_Row, HTuple hv_Column, HTuple hv_Width, 
    HTuple hv_Height, HTuple hv_WidthLimit, HTuple hv_HeightLimit);


// Chapter: Deep Learning / Classification
// Short Description: Compute a confusion matrix, which an be visualized and/or returned. 
void gen_confusion_matrix (HTuple hv_GroundTruthLabels, HTuple hv_PredictedClasses, 
    HTuple hv_GenParamName, HTuple hv_GenParamValue, HTuple hv_WindowHandle, HTuple *hv_ConfusionMatrix)
{

  // Local iconic variables

  // Local control variables
  HTuple  hv_DisplayMatrix, hv_ReturnMatrix, hv_DisplayColor;
  HTuple  hv_DisplayColumnWidth, hv_GenParamIndex, hv_CalculateRelativeMatrix;
  HTuple  hv_Classes, hv_NumClasses, hv_AbsoluteMatrixID;
  HTuple  hv_RelativeMatrixID, hv_ColumnMatrix, hv_Class;
  HTuple  hv_ThisLabel, hv_NumClassGroundTruth, hv_RowMatrix;
  HTuple  hv_PredictedClass, hv_ThisPredictedClass, hv_NumMatches;
  HTuple  hv_RelativeError, hv_StringWidths, hv_StringIndex;
  HTuple  hv_String, hv_Ascent, hv_Descent, hv_StringWidth;
  HTuple  hv_StringHeight, hv_MaxStringWidth, hv_RowStart;
  HTuple  hv_RowDistance, hv_RowEnd, hv_ColumnStart, hv_ColumnOffset;
  HTuple  hv_ColumnEnd, hv_Width, hv_Height, hv_WidthLimit;
  HTuple  hv_HeightLimit, hv_TextRow, hv_TextColumn, hv_Index;
  HTuple  hv_Text, hv_Row, hv_Column, hv_AbsoluteTransposedMatrixID;
  HTuple  hv_MatrixText, hv_MatrixMaxID, hv_MaxValue, hv_StringConversion;
  HTuple  hv_RelativeTransposedMatrixID, hv_TextColor, hv_RelativeValues;
  HTuple  hv_Thresholds, hv_Colors, hv_Greater, hv_Indices;
  HTuple  hv_DiagonalIndex, hv_Value;

  //This procedure computes a confusion matrix.
  //Therefore, it compares the classes
  //assigned in GroundTruthLabels and PredictedClasses.
  //The resulting confusion matrix can be
  //visualized, returned, or both.
  //In each case, the output can be changed
  //via generic parameters using GenParamName and GenParamValue.
  //For the visualization, the graphics window
  //must be specified with WindowHandle.
  //
  if (0 != (int((hv_GroundTruthLabels.TupleLength())!=(hv_PredictedClasses.TupleLength()))))
  {
    throw HException("Number of ground truth labels and predicted classes must be equal.");
  }
  //
  //Set generic parameter defaults.
  hv_DisplayMatrix = "absolute";
  hv_ReturnMatrix = "absolute";
  hv_DisplayColor = "true";
  hv_DisplayColumnWidth = "minimal";
  //
  //Parse generic parameters.
  {
  HTuple end_val21 = (hv_GenParamName.TupleLength())-1;
  HTuple step_val21 = 1;
  for (hv_GenParamIndex=0; hv_GenParamIndex.Continue(end_val21, step_val21); hv_GenParamIndex += step_val21)
  {
    if (0 != (int(HTuple(hv_GenParamName[hv_GenParamIndex])==HTuple("display_matrix"))))
    {
      //Set 'display_matrix'.
      hv_DisplayMatrix = HTuple(hv_GenParamValue[hv_GenParamIndex]);
    }
    else if (0 != (int(HTuple(hv_GenParamName[hv_GenParamIndex])==HTuple("return_matrix"))))
    {
      //Set 'return_matrix'.
      hv_ReturnMatrix = HTuple(hv_GenParamValue[hv_GenParamIndex]);
    }
    else if (0 != (int(HTuple(hv_GenParamName[hv_GenParamIndex])==HTuple("display_color"))))
    {
      //Set 'display_color'.
      hv_DisplayColor = HTuple(hv_GenParamValue[hv_GenParamIndex]);
    }
    else if (0 != (int(HTuple(hv_GenParamName[hv_GenParamIndex])==HTuple("display_column_width"))))
    {
      //Set 'display_column_width'.
      hv_DisplayColumnWidth = HTuple(hv_GenParamValue[hv_GenParamIndex]);
    }
    else
    {
      throw HException(("Unknown generic parameter: '"+HTuple(hv_GenParamName[hv_GenParamIndex]))+"'");
    }
  }
  }
  //
  if (0 != (HTuple(HTuple(int(hv_DisplayMatrix==HTuple("relative"))).TupleOr(int(hv_ReturnMatrix==HTuple("relative")))).TupleOr(int(hv_DisplayColor==HTuple("true")))))
  {
    hv_CalculateRelativeMatrix = 1;
  }
  else
  {
    hv_CalculateRelativeMatrix = 0;
  }
  //
  //Calculate the confusion matrix with absolute values
  //and the confusion matrix with relative errors.
  //We start with an empty matrix
  //and add the number of matching labels.
  hv_Classes = (hv_GroundTruthLabels.TupleSort()).TupleUniq();
  hv_NumClasses = hv_Classes.TupleLength();
  CreateMatrix(hv_NumClasses, hv_NumClasses, 0, &hv_AbsoluteMatrixID);
  if (0 != hv_CalculateRelativeMatrix)
  {
    CreateMatrix(hv_NumClasses, hv_NumClasses, 0, &hv_RelativeMatrixID);
  }
  {
  HTuple end_val55 = hv_NumClasses-1;
  HTuple step_val55 = 1;
  for (hv_ColumnMatrix=0; hv_ColumnMatrix.Continue(end_val55, step_val55); hv_ColumnMatrix += step_val55)
  {
    hv_Class = HTuple(hv_Classes[hv_ColumnMatrix]);
    hv_ThisLabel = hv_GroundTruthLabels.TupleEqualElem(hv_Class);
    if (0 != hv_CalculateRelativeMatrix)
    {
      //Obtain the number of ground truth labels per class.
      hv_NumClassGroundTruth = hv_ThisLabel.TupleSum();
    }
    {
    HTuple end_val62 = hv_NumClasses-1;
    HTuple step_val62 = 1;
    for (hv_RowMatrix=0; hv_RowMatrix.Continue(end_val62, step_val62); hv_RowMatrix += step_val62)
    {
      //Select classes for this row/column.
      hv_PredictedClass = HTuple(hv_Classes[hv_RowMatrix]);
      //Check whether the input data
      //corresponds to these classes.
      hv_ThisPredictedClass = hv_PredictedClasses.TupleEqualElem(hv_PredictedClass);
      //Count the number of elements where the predicted class
      //matches the ground truth label.
      hv_NumMatches = ((hv_ThisLabel+hv_ThisPredictedClass).TupleEqualElem(2)).TupleSum();
      //Set value in matrix.
      SetValueMatrix(hv_AbsoluteMatrixID, hv_RowMatrix, hv_ColumnMatrix, hv_NumMatches);
      if (0 != hv_CalculateRelativeMatrix)
      {
        if (0 != (int(hv_NumClassGroundTruth>0)))
        {
          hv_RelativeError = (hv_NumMatches.TupleReal())/hv_NumClassGroundTruth;
        }
        else
        {
          hv_RelativeError = 0;
        }
        SetValueMatrix(hv_RelativeMatrixID, hv_RowMatrix, hv_ColumnMatrix, hv_RelativeError);
      }
    }
    }
  }
  }
  //
  //Return the result.
  if (0 != (int(hv_ReturnMatrix==HTuple("absolute"))))
  {
    CopyMatrix(hv_AbsoluteMatrixID, &(*hv_ConfusionMatrix));
  }
  else if (0 != (int(hv_ReturnMatrix==HTuple("relative"))))
  {
    CopyMatrix(hv_RelativeMatrixID, &(*hv_ConfusionMatrix));
  }
  else if (0 != (int(hv_ReturnMatrix==HTuple("none"))))
  {
    //No matrix is returned.
  }
  else
  {
    throw HException("Unsupported mode for 'return_matrix'");
  }
  //
  //Display the matrix.
  if (0 != (int(hv_DisplayMatrix!=HTuple("none"))))
  {
    //
    //Find maximal string width and set display position parameters.
    hv_StringWidths = HTuple();
    //Get the string width of each class.
    {
    HTuple end_val101 = (hv_Classes.TupleLength())-1;
    HTuple step_val101 = 1;
    for (hv_StringIndex=0; hv_StringIndex.Continue(end_val101, step_val101); hv_StringIndex += step_val101)
    {
      hv_String = HTuple(hv_Classes[hv_StringIndex]);
      GetStringExtents(hv_WindowHandle, hv_String, &hv_Ascent, &hv_Descent, &hv_StringWidth, 
          &hv_StringHeight);
      hv_StringWidths = hv_StringWidths.TupleConcat(hv_StringWidth);
    }
    }
    //The columns should have a minimum width for 4 characters.
    GetStringExtents(hv_WindowHandle, "test", &hv_Ascent, &hv_Descent, &hv_StringWidth, 
        &hv_StringHeight);
    hv_MaxStringWidth = (hv_StringWidths.TupleMax()).TupleMax2(hv_StringWidth);
    //Get the maximum string width
    //and resize the window accordingly.
    hv_RowStart = 80;
    hv_RowDistance = hv_StringHeight+10;
    hv_RowEnd = hv_StringHeight*7;
    hv_ColumnStart = 50+hv_MaxStringWidth;
    hv_ColumnOffset = 20;
    hv_ColumnEnd = hv_ColumnOffset;
    //
    //Adapt the window size to fit the confusion matrix.
    if (0 != (int(hv_DisplayColumnWidth==HTuple("minimal"))))
    {
      //Every column of the confusion matrix is as narrow as possible
      //based to the respective string widths.
      hv_Width = (((hv_StringWidths.TupleSum())+(hv_ColumnOffset*hv_NumClasses))+hv_ColumnStart)+hv_ColumnEnd;
    }
    else if (0 != (int(hv_DisplayColumnWidth==HTuple("equal"))))
    {
      //Every column of the confusion matrix should have the same width.
      //based on the maximum string width.
      hv_Width = (((hv_MaxStringWidth+hv_ColumnOffset)*hv_NumClasses)+hv_ColumnStart)+hv_ColumnEnd;
    }
    else
    {
      throw HException("");
    }
    hv_Height = ((hv_RowDistance*hv_NumClasses)+hv_RowStart)+hv_RowEnd;
    HDevWindowStack::SetActive(hv_WindowHandle);
    if (HDevWindowStack::IsOpen())
      ClearWindow(HDevWindowStack::GetActive());
    //
    //Set reasonable limits for graphics window (adapt if necessary).
    hv_WidthLimit.Clear();
    hv_WidthLimit[0] = 450;
    hv_WidthLimit[1] = 1920;
    hv_HeightLimit.Clear();
    hv_HeightLimit[0] = 250;
    hv_HeightLimit[1] = 1080;
    if (0 != (HTuple(int(hv_Width>HTuple(hv_WidthLimit[1]))).TupleOr(int(hv_Height>HTuple(hv_HeightLimit[1])))))
    {
      throw HException("Confusion Matrix does not fit into graphics window. Please adapt font and/or size limits.");
    }
    dev_resize_window_fit_size(0, 0, hv_Width, hv_Height, hv_WidthLimit, hv_HeightLimit);
    //
    //Get display coordinates.
    //Get row coordinates for display.
    hv_TextRow = HTuple();
    {
    HTuple end_val145 = hv_NumClasses-1;
    HTuple step_val145 = 1;
    for (hv_ColumnMatrix=0; hv_ColumnMatrix.Continue(end_val145, step_val145); hv_ColumnMatrix += step_val145)
    {
      hv_TextRow = hv_TextRow.TupleConcat(HTuple::TupleGenSequence(0,(hv_NumClasses-1)*hv_RowDistance,hv_RowDistance));
    }
    }
    //Get column coordinates for display.
    hv_TextColumn = HTuple();
    {
    HTuple end_val150 = hv_NumClasses-1;
    HTuple step_val150 = 1;
    for (hv_Index=0; hv_Index.Continue(end_val150, step_val150); hv_Index += step_val150)
    {
      hv_TextColumn = hv_TextColumn.TupleConcat(HTuple(hv_NumClasses,hv_ColumnStart));
      if (0 != (int(hv_DisplayColumnWidth==HTuple("minimal"))))
      {
        hv_ColumnStart = (hv_ColumnStart+HTuple(hv_StringWidths[hv_Index]))+hv_ColumnOffset;
      }
      else if (0 != (int(hv_DisplayColumnWidth==HTuple("equal"))))
      {
        hv_ColumnStart = (hv_ColumnStart+hv_MaxStringWidth)+hv_ColumnOffset;
      }
    }
    }
    //Display the confusion matrix with a margin from the top.
    hv_TextRow += hv_RowStart;
    //Display axis titles.
    if (HDevWindowStack::IsOpen())
      DispText(HDevWindowStack::GetActive(),"Ground truth labels", "window", "top", 
          "right", "white", "box", "false");
    if (HDevWindowStack::IsOpen())
      DispText(HDevWindowStack::GetActive(),"Predicted classes", "window", "bottom", 
          "left", "white", "box", "false");
    {
    HTuple end_val163 = (hv_Classes.TupleLength())-1;
    HTuple step_val163 = 1;
    for (hv_Index=0; hv_Index.Continue(end_val163, step_val163); hv_Index += step_val163)
    {
      hv_Text = HTuple(hv_Classes[hv_Index]);
      //Display predicted class names.
      hv_Row = HTuple(hv_TextRow[hv_Index]);
      hv_Column = (HTuple(hv_TextColumn[0])-hv_MaxStringWidth)-hv_ColumnOffset;
      if (HDevWindowStack::IsOpen())
        DispText(HDevWindowStack::GetActive(),hv_Text, "window", hv_Row, hv_Column, 
            "light gray", "box", "false");
      //Display ground truth label names.
      hv_Row = HTuple(hv_TextRow[0])-hv_RowDistance;
      hv_Column = HTuple(hv_TextColumn[hv_Index*hv_NumClasses]);
      if (HDevWindowStack::IsOpen())
        DispText(HDevWindowStack::GetActive(),hv_Text, "window", hv_Row, hv_Column, 
            "light gray", "box", "false");
    }
    }
    //
    //Get the confusion matrix values for display.
    if (0 != (int(hv_DisplayMatrix==HTuple("absolute"))))
    {
      //Displayed matrix corresponds to the transposed returned matrix.
      TransposeMatrix(hv_AbsoluteMatrixID, &hv_AbsoluteTransposedMatrixID);
      GetFullMatrix(hv_AbsoluteTransposedMatrixID, &hv_MatrixText);
      ClearMatrix(hv_AbsoluteTransposedMatrixID);
      //Align the numbers right.
      MaxMatrix(hv_AbsoluteMatrixID, "full", &hv_MatrixMaxID);
      GetFullMatrix(hv_MatrixMaxID, &hv_MaxValue);
      ClearMatrix(hv_MatrixMaxID);
      hv_StringConversion = (((hv_MaxValue.TupleLog10()).TupleCeil()).TupleInt())+".0f";
      hv_MatrixText = hv_MatrixText.TupleString(hv_StringConversion);
    }
    else
    {
      //Displayed matrix corresponds to the transposed returned matrix.
      TransposeMatrix(hv_RelativeMatrixID, &hv_RelativeTransposedMatrixID);
      GetFullMatrix(hv_RelativeTransposedMatrixID, &hv_MatrixText);
      ClearMatrix(hv_RelativeTransposedMatrixID);
      hv_MatrixText = hv_MatrixText.TupleString(".2f");
    }
    //Set color for displayed confusion matrix.
    if (0 != (int(hv_DisplayColor==HTuple("true"))))
    {
      TupleGenConst(hv_MatrixText.TupleLength(), "#666666", &hv_TextColor);
      //Use the relative values to adapt the color of the text.
      TransposeMatrix(hv_RelativeMatrixID, &hv_RelativeTransposedMatrixID);
      GetFullMatrix(hv_RelativeTransposedMatrixID, &hv_RelativeValues);
      ClearMatrix(hv_RelativeTransposedMatrixID);
      //Set the colors and respective thresholds for the off-diagonal values.
      hv_Thresholds.Clear();
      hv_Thresholds[0] = 0.0;
      hv_Thresholds[1] = 0.05;
      hv_Thresholds[2] = 0.1;
      hv_Thresholds[3] = 0.2;
      hv_Colors.Clear();
      hv_Colors[0] = "#8C4D4D";
      hv_Colors[1] = "#B33333";
      hv_Colors[2] = "#D91A1A";
      hv_Colors[3] = "#FF0000";
      {
      HTuple end_val204 = (hv_Thresholds.TupleLength())-1;
      HTuple step_val204 = 1;
      for (hv_Index=0; hv_Index.Continue(end_val204, step_val204); hv_Index += step_val204)
      {
        TupleGreaterElem(hv_RelativeValues, HTuple(hv_Thresholds[hv_Index]), &hv_Greater);
        TupleFind(hv_Greater, 1, &hv_Indices);
        if (0 != (int(hv_Indices!=-1)))
        {
          TupleReplace(hv_TextColor, hv_Indices, HTuple(hv_Colors[hv_Index]), &hv_TextColor);
        }
        else
        {
          break;
        }
      }
      }
      //Set the colors and respective thresholds for the diagonal values.
      hv_Thresholds.Clear();
      hv_Thresholds[0] = -0.01;
      hv_Thresholds[1] = 0.60;
      hv_Thresholds[2] = 0.80;
      hv_Thresholds[3] = 0.90;
      hv_Thresholds[4] = 0.95;
      hv_Thresholds[5] = 0.98;
      hv_Colors.Clear();
      hv_Colors[0] = "#666666";
      hv_Colors[1] = "#508650";
      hv_Colors[2] = "#419C41";
      hv_Colors[3] = "#2BBD2B";
      hv_Colors[4] = "#15DE15";
      hv_Colors[5] = "#00FF00";
      {
      HTuple end_val216 = hv_NumClasses-1;
      HTuple step_val216 = 1;
      for (hv_DiagonalIndex=0; hv_DiagonalIndex.Continue(end_val216, step_val216); hv_DiagonalIndex += step_val216)
      {
        GetValueMatrix(hv_RelativeMatrixID, hv_DiagonalIndex, hv_DiagonalIndex, &hv_Value);
        {
        HTuple end_val218 = (hv_Thresholds.TupleLength())-1;
        HTuple step_val218 = 1;
        for (hv_Index=0; hv_Index.Continue(end_val218, step_val218); hv_Index += step_val218)
        {
          if (0 != (int(hv_Value>HTuple(hv_Thresholds[hv_Index]))))
          {
            hv_TextColor[hv_DiagonalIndex*(hv_NumClasses+1)] = HTuple(hv_Colors[hv_Index]);
          }
          else
          {
            break;
          }
        }
        }
      }
      }
    }
    else
    {
      //Default value for the text color.
      TupleGenConst(hv_MatrixText.TupleLength(), "white", &hv_TextColor);
    }
    //
    //Display confusion matrix.
    if (HDevWindowStack::IsOpen())
      DispText(HDevWindowStack::GetActive(),hv_MatrixText, "window", hv_TextRow, 
          hv_TextColumn, hv_TextColor, "box", "false");
    //
    //Clean up.
    if (0 != hv_CalculateRelativeMatrix)
    {
      ClearMatrix(hv_RelativeMatrixID);
    }
    ClearMatrix(hv_AbsoluteMatrixID);
  }
  return;
}
