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
// Chapter: Tuple / Element Order
// Short Description: Sort the elements of a tuple randomly. 
extern void tuple_shuffle (HTuple hv_Tuple, HTuple *hv_Shuffled);
// Chapter: Image / Manipulation
void apply_brightness_variation_spot (HObject ho_Image, HObject *ho_ImageSpot, HTuple hv_SpotSize, 
    HTuple hv_SpotRow, HTuple hv_SpotColumn, HTuple hv_BrightnessVariation);
// Chapter: Image / Manipulation
// Short Description: Augment/distort the given images. 
void augment_images (HObject ho_Images, HObject *ho_ImagesAugmented, HTuple hv_GenParamName, 
    HTuple hv_GenParamValue);

// Procedures 
// Chapter: Image / Manipulation
void apply_brightness_variation_spot (HObject ho_Image, HObject *ho_ImageSpot, HTuple hv_SpotSize, 
    HTuple hv_SpotRow, HTuple hv_SpotColumn, HTuple hv_BrightnessVariation)
{

  // Local iconic variables
  HObject  ho_Filter, ho_GaussImage, ho_GaussFilter;
  HObject  ho_Gauss, ho_GaussTargetType, ho_AddImage;

  // Local control variables
  HTuple  hv_Direction, hv_Width, hv_Height, hv_ShiftRow;
  HTuple  hv_ShiftCol, hv_Type, hv_NChannels, hv_Index1;

  //This procedure applies a brightness spot
  //of a given intensity and size at a given location
  //to the input image.
  //The modified image is returned in ImageSpot.
  //
  if (0 != (int(hv_BrightnessVariation<0)))
  {
    hv_Direction = 0;
    hv_BrightnessVariation = -hv_BrightnessVariation;
  }
  else
  {
    hv_Direction = 1;
  }
  GetImageSize(ho_Image, &hv_Width, &hv_Height);
  //Generate Gauss filter that simulates an illumination spot of size 'SpotSize'.
  GenGaussFilter(&ho_Filter, 1, 1, 0, "none", "dc_center", hv_SpotSize, hv_SpotSize);
  //Shift the filter image to the given position.
  hv_ShiftRow = -((hv_SpotSize/2)-hv_SpotRow);
  hv_ShiftCol = -((hv_SpotSize/2)-hv_SpotColumn);
  TileImagesOffset(ho_Filter, &ho_GaussImage, hv_ShiftRow, hv_ShiftCol, -1, -1, -1, 
      -1, hv_Width, hv_Height);
  FullDomain(ho_GaussImage, &ho_GaussFilter);
  //Convert Gauss filter to target image type and apply brightness variation.
  GetImageType(ho_Image, &hv_Type);
  ScaleImage(ho_GaussFilter, &ho_Gauss, hv_BrightnessVariation, 0);
  ConvertImageType(ho_Gauss, &ho_GaussTargetType, hv_Type);
  //Add channels to fit input image.
  CountChannels(ho_Image, &hv_NChannels);
  CopyObj(ho_GaussTargetType, &ho_AddImage, 1, 1);
  {
  HTuple end_val26 = hv_NChannels-1;
  HTuple step_val26 = 1;
  for (hv_Index1=1; hv_Index1.Continue(end_val26, step_val26); hv_Index1 += step_val26)
  {
    AppendChannel(ho_AddImage, ho_GaussTargetType, &ho_AddImage);
  }
  }
  //Apply on image.
  if (0 != hv_Direction)
  {
    AddImage(ho_Image, ho_AddImage, &(*ho_ImageSpot), 1, 0);
  }
  else
  {
    SubImage(ho_Image, ho_AddImage, &(*ho_ImageSpot), 1, 0);
  }
  return;
}

// Chapter: Image / Manipulation
// Short Description: Augment/distort the given images. 
void augment_images (HObject ho_Images, HObject *ho_ImagesAugmented, HTuple hv_GenParamName, 
    HTuple hv_GenParamValue)
{

  // Local iconic variables
  HObject  ho_ImageSelected, ho_ImagePart, ho_ImageRotated;
  HObject  ho_DomainRotated, ho_ImageScaled, ho_ImageSpot;

  // Local control variables
  HTuple  hv_AugmentationPercentage, hv_CropPercentage;
  HTuple  hv_CropPixel, hv_Rotation, hv_RotationRange, hv_Mirror;
  HTuple  hv_BrightnessVariation, hv_BrightnessVariationSpot;
  HTuple  hv_GenParamIndex, hv_CurrentParamName, hv_CurrentParamValue;
  HTuple  hv_NumAvailableDistortions, hv_NumImages, hv_AugmentationRate;
  HTuple  hv_NumAugmentations, hv_ImageIndices, hv_SelectedImages;
  HTuple  hv_SelectedDistortions, hv_IndexDistortion, hv_Index;
  HTuple  hv_ImageIndex, hv_CurrentDistortion, hv_Width, hv_Height;
  HTuple  hv_CropRate, hv_Row1, hv_Row2, hv_Column1, hv_Column2;
  HTuple  hv_Length, hv_RotationStep, hv_NumPossibleRotations;
  HTuple  hv_CurrentRotation, hv_HomMat2DIdentity, hv_HomMat2DRotate;
  HTuple  hv_NumMirrorMethods, hv_PropabilityMethods, hv_StrMirror;
  HTuple  hv_StrIdx, hv_SelectedChar, hv_BrightnessVariationValue;
  HTuple  hv_SpotSize, hv_SpotRow, hv_SpotColumn;
  HTupleVector  hvec_AvailableDistortions(1), hvec_Distortions(1);

  //This procedure can be used to augment given input Images
  //using different methods, which can be specified using
  //GenParamName and GenParamValue. The augmented images are returned
  //in ImagesAugmented.
  //
  //Set default parameters.
  //
  //The percentages of the images that are to be augmented.
  hv_AugmentationPercentage.Clear();
  hv_AugmentationPercentage[0] = "augmentation_percentage";
  hv_AugmentationPercentage[1] = 50;
  //Fraction of image length and width that remains after cropping (in %).
  hv_CropPercentage.Clear();
  hv_CropPercentage[0] = "crop_percentage";
  hv_CropPercentage[1] = "off";
  //Image length and width that remains after cropping (in pixel).
  hv_CropPixel.Clear();
  hv_CropPixel[0] = "crop_pixel";
  hv_CropPixel[1] = "off";
  //Step size for possible rotations.
  hv_Rotation.Clear();
  hv_Rotation[0] = "rotate";
  hv_Rotation[1] = 0;
  //Step range for rotations with step size 1.
  hv_RotationRange.Clear();
  hv_RotationRange[0] = "rotate_range";
  hv_RotationRange[1] = 0;
  //Allowed mirroring methods coded by 'r' (row), 'c' (column).
  hv_Mirror.Clear();
  hv_Mirror[0] = "mirror";
  hv_Mirror[1] = "off";
  //The absolute brightness change can vary in the range[-value, +value].
  hv_BrightnessVariation.Clear();
  hv_BrightnessVariation[0] = "brightness_variation";
  hv_BrightnessVariation[1] = 0;
  //The absolute brightness peak of a randomly positioned spot can vary in the range[-value, +value].
  hv_BrightnessVariationSpot.Clear();
  hv_BrightnessVariationSpot[0] = "brightness_variation_spot";
  hv_BrightnessVariationSpot[1] = 0;
  //
  //Parse the generic parameters.
  //
  //Check if GenParamName matches GenParamValue.
  if (0 != (int((hv_GenParamName.TupleLength())!=(hv_GenParamValue.TupleLength()))))
  {
    throw HException("Number of generic parameters does not match number of generic parameter values");
  }
  //Check for generic parameter names and overwrite defaults.
  {
  HTuple end_val31 = (hv_GenParamName.TupleLength())-1;
  HTuple step_val31 = 1;
  for (hv_GenParamIndex=0; hv_GenParamIndex.Continue(end_val31, step_val31); hv_GenParamIndex += step_val31)
  {
    hv_CurrentParamName = HTuple(hv_GenParamName[hv_GenParamIndex]);
    hv_CurrentParamValue = HTuple(hv_GenParamValue[hv_GenParamIndex]);
    //
    if (0 != (int(hv_CurrentParamName==HTuple(hv_AugmentationPercentage[0]))))
    {
      //Set augmentation percentage.
      hv_AugmentationPercentage[1] = hv_CurrentParamValue;
      //Check if input value is in range of 1-100 %.
      if (0 != (hv_CurrentParamValue.TupleIsNumber()))
      {
        if (0 != (HTuple(int(hv_CurrentParamValue<1)).TupleOr(int(hv_CurrentParamValue>100))))
        {
          throw HException("The given value for augmentation_percentage has to be in the range 1-100.");
        }
      }
      else
      {
        throw HException("The given value for augmentation_percentage has to be in the range 1-100.");
      }
    }
    else if (0 != (int(hv_CurrentParamName==HTuple(hv_Rotation[0]))))
    {
      //Set rotation.
      hv_Rotation[1] = hv_CurrentParamValue;
      //Check if input value is in range of 0-180 deg.
      if (0 != (hv_CurrentParamValue.TupleIsNumber()))
      {
        if (0 != (HTuple(int(hv_CurrentParamValue<0)).TupleOr(int(hv_CurrentParamValue>180))))
        {
          throw HException("The given value for rotate has to be in the range 0-180.");
        }
      }
      else
      {
        throw HException("The given value for rotate has to be in the range 0-180.");
      }
    }
    else if (0 != (int(hv_CurrentParamName==HTuple(hv_RotationRange[0]))))
    {
      //Set rotation.
      hv_RotationRange[1] = hv_CurrentParamValue;
      //Check if input value is in range of 0-180 deg.
      if (0 != (hv_CurrentParamValue.TupleIsNumber()))
      {
        if (0 != (HTuple(int(hv_CurrentParamValue<0)).TupleOr(int(hv_CurrentParamValue>180))))
        {
          throw HException("The given value for rotate_range has to be in the range 0-180.\"");
        }
      }
      else
      {
        throw HException("The given value for rotate_range has to be in the range 0-180.");
      }
    }
    else if (0 != (int(hv_CurrentParamName==HTuple(hv_Mirror[0]))))
    {
      //Set mirroring.
      hv_Mirror[1] = hv_CurrentParamValue;
      //Check if input is string and is 'off' or contains the wanted strings.
      if (0 != ((hv_CurrentParamValue.TupleIsNumber()).TupleOr(HTuple(HTuple(HTuple(HTuple(HTuple(int(hv_CurrentParamValue==HTuple("off"))).TupleOr(int(hv_CurrentParamValue==HTuple("c")))).TupleOr(int(hv_CurrentParamValue==HTuple("r")))).TupleOr(int(hv_CurrentParamValue==HTuple("cr")))).TupleOr(int(hv_CurrentParamValue==HTuple("rc")))).TupleNot())))
      {
        throw HException("Unknown mirror method.");
      }
    }
    else if (0 != (int(hv_CurrentParamName==HTuple(hv_CropPercentage[0]))))
    {
      //Set cropping with percentage.
      hv_CropPercentage[1] = hv_CurrentParamValue;
      //Check if input value is in range of 1-100 %.
      if (0 != (hv_CurrentParamValue.TupleIsNumber()))
      {
        if (0 != (HTuple(int(hv_CurrentParamValue<1)).TupleOr(int(hv_CurrentParamValue>100))))
        {
          throw HException("The given value for crop_percentage has to be in the range 1-100.");
        }
      }
      else
      {
        throw HException("The given value for crop_percentage has to be in the range 1-100.");
      }
    }
    else if (0 != (int(hv_CurrentParamName==HTuple(hv_CropPixel[0]))))
    {
      //Set cropping with pixels.
      hv_CropPixel[1] = hv_CurrentParamValue;
      //Check if input value is greater 0.
      if (0 != (hv_CurrentParamValue.TupleIsNumber()))
      {
        if (0 != (int(hv_CurrentParamValue<1)))
        {
          throw HException("The given value for crop_pixel has to be greater then or equal to 1.");
        }
      }
      else
      {
        throw HException("The given value for crop_pixel has to be a string.");
      }
    }
    else if (0 != (int(hv_CurrentParamName==HTuple(hv_BrightnessVariation[0]))))
    {
      //Set brightness variation.
      hv_BrightnessVariation[1] = hv_CurrentParamValue;
      //Check if input value is in range of 0-255.
      if (0 != (hv_CurrentParamValue.TupleIsNumber()))
      {
        if (0 != (HTuple(int(hv_CurrentParamValue<0)).TupleOr(int(hv_CurrentParamValue>255))))
        {
          throw HException("The given value for brightness_variation has to be in the range 0-255.");
        }
      }
      else
      {
        throw HException("The given value for brightness_variation has to be in the range 0-255.");
      }
    }
    else if (0 != (int(hv_CurrentParamName==HTuple(hv_BrightnessVariationSpot[0]))))
    {
      //Set brightness variation of spot.
      hv_BrightnessVariationSpot[1] = hv_CurrentParamValue;
      //Check if input value is in range of 0-255.
      if (0 != (hv_CurrentParamValue.TupleIsNumber()))
      {
        if (0 != (HTuple(int(hv_CurrentParamValue<0)).TupleOr(int(hv_CurrentParamValue>255))))
        {
          throw HException("The given value for brightness_variation_spot has to be in the range 0-255.");
        }
      }
      else
      {
        throw HException("The given value for brightness_variation_spot has to be in the range 0-255.");
      }
    }
    else
    {
      throw HException(("Unknown generic parameter: '"+HTuple(hv_GenParamName[hv_GenParamIndex]))+"'");
    }
  }
  }
  //
  //Aggregate all possible distortions and parameter values into a vector.
  //
  hvec_AvailableDistortions = HTupleVector(1);
  //Cropping percentage.
  if (0 != (HTuple(hv_CropPercentage[1]).TupleIsNumber()))
  {
    hvec_AvailableDistortions[HTuple(hvec_AvailableDistortions.Length())] = HTupleVector(hv_CropPercentage);
  }
  //Cropping pixel.
  if (0 != (HTuple(hv_CropPixel[1]).TupleIsNumber()))
  {
    hvec_AvailableDistortions[HTuple(hvec_AvailableDistortions.Length())] = HTupleVector(hv_CropPixel);
  }
  //Rotation with a given angular step size.
  if (0 != (int(HTuple(hv_Rotation[1])>0)))
  {
    hvec_AvailableDistortions[HTuple(hvec_AvailableDistortions.Length())] = HTupleVector(hv_Rotation);
  }
  //Rotation within a given range (step size 1).
  if (0 != (int(HTuple(hv_RotationRange[1])>0)))
  {
    hvec_AvailableDistortions[HTuple(hvec_AvailableDistortions.Length())] = HTupleVector(hv_RotationRange);
  }
  //Mirroring: in row and column direction are allowed.
  if (0 != (HTuple(HTuple(hv_Mirror[1]).TupleRegexpTest("r")).TupleOr(HTuple(hv_Mirror[1]).TupleRegexpTest("c"))))
  {
    hvec_AvailableDistortions[HTuple(hvec_AvailableDistortions.Length())] = HTupleVector(hv_Mirror);
  }
  //Brightness variation.
  if (0 != (int(HTuple(hv_BrightnessVariation[1])>0)))
  {
    hvec_AvailableDistortions[HTuple(hvec_AvailableDistortions.Length())] = HTupleVector(hv_BrightnessVariation);
  }
  //Brightness variation spot.
  if (0 != (int(HTuple(hv_BrightnessVariationSpot[1])>0)))
  {
    hvec_AvailableDistortions[HTuple(hvec_AvailableDistortions.Length())] = HTupleVector(hv_BrightnessVariationSpot);
  }
  //Check number of available distortions
  hv_NumAvailableDistortions = HTuple(hvec_AvailableDistortions.Length());
  if (0 != (int(hv_NumAvailableDistortions==0)))
  {
    (*ho_ImagesAugmented) = ho_Images;
    return;
  }
  //
  //Randomly choose images and augmentation methods.
  //
  //Number of images to be augmented.
  CountObj(ho_Images, &hv_NumImages);
  if (0 != (int(hv_NumImages==0)))
  {
    throw HException("There are no images to be processed.");
  }
  //Calculate how many images are to be augmented.
  hv_AugmentationRate = HTuple(hv_AugmentationPercentage[1])*0.01;
  hv_NumAugmentations = ((hv_AugmentationRate*hv_NumImages).TupleCeil()).TupleInt();
  //Select a random subset of images
  //that are to be augmented.
  tuple_shuffle(HTuple::TupleGenSequence(0,hv_NumImages-1,1), &hv_ImageIndices);
  hv_SelectedImages = hv_ImageIndices.TupleSelectRange(0,hv_NumAugmentations-1);
  //Select a random distortion method for each image.
  hv_SelectedDistortions = ((HTuple::TupleRand(hv_NumAugmentations)*hv_NumAvailableDistortions).TupleFloor()).TupleInt();
  //Fill up vector of distortions for all input images.
  hvec_Distortions = HTupleVector(1);
  hv_IndexDistortion = 0;
  {
  HTuple end_val181 = hv_NumImages-1;
  HTuple step_val181 = 1;
  for (hv_Index=0; hv_Index.Continue(end_val181, step_val181); hv_Index += step_val181)
  {
    //Check if Index corresponds to a selected image.
    if (0 != (int(((hv_SelectedImages.TupleEqualElem(hv_Index)).TupleSum())>0)))
    {
      //Add a distortion method.
      hvec_Distortions[hv_Index] = hvec_AvailableDistortions[HTuple(hv_SelectedDistortions[hv_IndexDistortion])];
      hv_IndexDistortion += 1;
    }
    else
    {
      //Image will not be distorted.
      hvec_Distortions[hv_Index] = HTupleVector((HTuple("none").Append(0)));
    }
  }
  }
  //
  //Augment (distort) the images.
  //
  //Generate output image array.
  GenEmptyObj(&(*ho_ImagesAugmented));
  //Loop over all images and apply distortions.
  {
  HTuple end_val198 = hv_NumImages-1;
  HTuple step_val198 = 1;
  for (hv_ImageIndex=0; hv_ImageIndex.Continue(end_val198, step_val198); hv_ImageIndex += step_val198)
  {
    //Get distortion method.
    hv_CurrentDistortion = hvec_Distortions[hv_ImageIndex].T();
    //Get image to be processed.
    SelectObj(ho_Images, &ho_ImageSelected, hv_ImageIndex+1);
    GetImageSize(ho_ImageSelected, &hv_Width, &hv_Height);
    if (0 != (int(HTuple(hv_CurrentDistortion[0])==HTuple(hv_CropPercentage[0]))))
    {
      //Cropping:
      //Define cropping rectangle.
      hv_CropRate = HTuple(hv_CurrentDistortion[1])*0.01;
      hv_Row1 = (((1-hv_CropRate)*hv_Height)*HTuple::TupleRand(1)).TupleFloor();
      hv_Row2 = hv_Row1+(hv_CropRate*hv_Height);
      hv_Column1 = (((1-hv_CropRate)*hv_Width)*HTuple::TupleRand(1)).TupleFloor();
      hv_Column2 = hv_Column1+(hv_CropRate*hv_Width);
      //Crop the image and add to output.
      CropRectangle1(ho_ImageSelected, &ho_ImagePart, hv_Row1, hv_Column1, hv_Row2, 
          hv_Column2);
      ConcatObj((*ho_ImagesAugmented), ho_ImagePart, &(*ho_ImagesAugmented));
    }
    else if (0 != (int(HTuple(hv_CurrentDistortion[0])==HTuple(hv_CropPixel[0]))))
    {
      //Cropping:
      //Define cropping rectangle.
      hv_Length = ((const HTuple&)hv_CurrentDistortion)[1];
      hv_Row1 = HTuple::TupleRand(1)*(hv_Height-hv_Length);
      hv_Row2 = (hv_Row1+hv_Length)-1;
      hv_Column1 = HTuple::TupleRand(1)*(hv_Width-hv_Length);
      hv_Column2 = (hv_Column1+hv_Length)-1;
      //Crop the image and add to output.
      CropRectangle1(ho_ImageSelected, &ho_ImagePart, hv_Row1, hv_Column1, hv_Row2, 
          hv_Column2);
      ConcatObj((*ho_ImagesAugmented), ho_ImagePart, &(*ho_ImagesAugmented));
    }
    else if (0 != (HTuple(int(HTuple(hv_CurrentDistortion[0])==HTuple(hv_Rotation[0]))).TupleOr(int(HTuple(hv_CurrentDistortion[0])==HTuple(hv_RotationRange[0])))))
    {
      //Rotation:
      if (0 != (int(HTuple(hv_CurrentDistortion[0])==HTuple(hv_Rotation[0]))))
      {
        //Determine rotation angle for method 'rotate' (angle in range [0:CurrentDistortion[1]:360)).
        hv_RotationStep = ((const HTuple&)hv_CurrentDistortion)[1];
        hv_NumPossibleRotations = 360.0/hv_RotationStep;
        hv_CurrentRotation = hv_RotationStep*(((hv_NumPossibleRotations*HTuple::TupleRand(1)).TupleInt())+1);
      }
      else
      {
        //Determine rotation angle for method 'rotate_range' (angle in range [0:1:CurrentDistortion[1])).
        hv_RotationStep = 1;
        hv_NumPossibleRotations = ((const HTuple&)hv_CurrentDistortion)[1];
        hv_CurrentRotation = hv_RotationStep*(((hv_NumPossibleRotations*HTuple::TupleRand(1)).TupleInt())+1);
        //Select direction of rotation randomly.
        if (0 != (int((HTuple::TupleRand(1).TupleRound())>0.5)))
        {
          hv_CurrentRotation = 360.0-hv_CurrentRotation;
        }
      }
      if (0 != (HTuple(int((hv_CurrentRotation.TupleInt())==hv_CurrentRotation)).TupleAnd(int(((hv_CurrentRotation.TupleInt())%90)==0))))
      {
        //Rotations around 90 degrees are faster with rotate_image
        RotateImage(ho_ImageSelected, &ho_ImagePart, hv_CurrentRotation.TupleInt(), 
            "constant");
      }
      else
      {
        //Create rotation matrix.
        HomMat2dIdentity(&hv_HomMat2DIdentity);
        HomMat2dRotate(hv_HomMat2DIdentity, hv_CurrentRotation.TupleRad(), hv_Height/2.0, 
            hv_Width/2.0, &hv_HomMat2DRotate);
        //Apply rotation.
        AffineTransImage(ho_ImageSelected, &ho_ImageRotated, hv_HomMat2DRotate, "constant", 
            "false");
        //Remove potential undefined domain.
        GetDomain(ho_ImageRotated, &ho_DomainRotated);
        InnerRectangle1(ho_DomainRotated, &hv_Row1, &hv_Column1, &hv_Row2, &hv_Column2);
        CropRectangle1(ho_ImageRotated, &ho_ImagePart, hv_Row1, hv_Column1, hv_Row2, 
            hv_Column2);
      }
      //Add the image to the output.
      ConcatObj((*ho_ImagesAugmented), ho_ImagePart, &(*ho_ImagesAugmented));
    }
    else if (0 != (int(HTuple(hv_CurrentDistortion[0])==HTuple(hv_Mirror[0]))))
    {
      //Mirroring:
      //If more than one method is allowed, chose mirroring method(s) to be applied.
      hv_NumMirrorMethods = HTuple(hv_CurrentDistortion[1]).TupleStrlen();
      hv_PropabilityMethods = 1.0/hv_NumMirrorMethods;
      hv_StrMirror = "";
      while (0 != (int(hv_StrMirror==HTuple(""))))
      {
        {
        HTuple end_val266 = hv_NumMirrorMethods-1;
        HTuple step_val266 = 1;
        for (hv_StrIdx=0; hv_StrIdx.Continue(end_val266, step_val266); hv_StrIdx += step_val266)
        {
          hv_SelectedChar = HTuple(hv_CurrentDistortion[1]).TupleStrBitSelect(hv_StrIdx);
          if (0 != (int(HTuple::TupleRand(1)<hv_PropabilityMethods)))
          {
            hv_StrMirror += hv_SelectedChar;
          }
        }
        }
      }
      //Apply the chosen mirroring method(s).
      if (0 != (hv_StrMirror.TupleRegexpTest("c")))
      {
        MirrorImage(ho_ImageSelected, &ho_ImageSelected, "column");
      }
      if (0 != (hv_StrMirror.TupleRegexpTest("r")))
      {
        MirrorImage(ho_ImageSelected, &ho_ImageSelected, "row");
      }
      //Add the image to the output.
      ConcatObj((*ho_ImagesAugmented), ho_ImageSelected, &(*ho_ImagesAugmented));
    }
    else if (0 != (int(HTuple(hv_CurrentDistortion[0])==HTuple(hv_BrightnessVariation[0]))))
    {
      //Brightness variation:
      //Add random brightness variation.
      hv_BrightnessVariationValue = ((HTuple::TupleRand(1)*2)-1)*HTuple(hv_CurrentDistortion[1]);
      ScaleImage(ho_ImageSelected, &ho_ImageScaled, 1.0, hv_BrightnessVariationValue);
      //Add the image to the output.
      ConcatObj((*ho_ImagesAugmented), ho_ImageScaled, &(*ho_ImagesAugmented));
    }
    else if (0 != (int(HTuple(hv_CurrentDistortion[0])==HTuple(hv_BrightnessVariationSpot[0]))))
    {
      //Determine random brightness variation.
      hv_BrightnessVariationValue = ((HTuple::TupleRand(1)*2)-1)*HTuple(hv_CurrentDistortion[1]);
      //Determine random spot size between [0.5*Width, Width].
      hv_SpotSize = hv_Width*((HTuple::TupleRand(1)/2)+.5);
      //Determine random spot position.
      hv_SpotRow = HTuple::TupleRand(1)*hv_Height;
      hv_SpotColumn = HTuple::TupleRand(1)*hv_Width;
      apply_brightness_variation_spot(ho_ImageSelected, &ho_ImageSpot, hv_SpotSize, 
          hv_SpotRow, hv_SpotColumn, hv_BrightnessVariationValue);
      //Add the image to the output.
      ConcatObj((*ho_ImagesAugmented), ho_ImageSpot, &(*ho_ImagesAugmented));
    }
    else
    {
      //Add unchanged image to the output.
      ConcatObj((*ho_ImagesAugmented), ho_ImageSelected, &(*ho_ImagesAugmented));
    }
  }
  }
  return;
}


