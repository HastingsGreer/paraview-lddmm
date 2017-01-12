/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkImageGaussianSmooth2.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkImageGaussianSmooth2 - Performs a gaussian convolution.
// .SECTION Description
// vtkImageGaussianSmooth2 implements a convolution of the input image
// with a gaussian. Supports from one to three dimensional convolutions.

#ifndef vtkImageGaussianSmooth2_h
#define vtkImageGaussianSmooth2_h


#include "vtkImagingGeneralModule.h" // For export macro
#include "vtkThreadedImageAlgorithm.h"
#include "vtkSetGet.h"

class VTKIMAGINGGENERAL_EXPORT vtkImageGaussianSmooth2 : public vtkThreadedImageAlgorithm
{
public:
  vtkTypeMacro(vtkImageGaussianSmooth2,vtkThreadedImageAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Creates an instance of vtkImageGaussianSmooth2 with the following
  // defaults: Dimensionality 3, StandardDeviations( 2, 2, 2),
  // Radius Factors ( 1.5, 1.5, 1.5)
  static vtkImageGaussianSmooth2 *New();


  // Description:
  // Sets/Gets the Standard deviation of the gaussian in pixel units.
  vtkSetVector3Macro(StandardDeviations, double);
  void SetStandardDeviation(double std)
        {this->SetStandardDeviations(std,std,std);}
  void SetStandardDeviations(double a,double b)
        {this->SetStandardDeviations(a,b,0.0);}
  vtkGetVector3Macro(StandardDeviations, double);

  // Description:
  // Sets/Gets the Standard deviation of the gaussian in pixel units.
  // These methods are provided for compatibility with old scripts
  void SetStandardDeviation(double a,double b)
        {this->SetStandardDeviations(a,b,0.0);}
  void SetStandardDeviation(double a,double b,double c)
        {this->SetStandardDeviations(a,b,c);}

  // Description:
  // Sets/Gets the Radius Factors of the gaussian (no unit).
  // The radius factors determine how far out the gaussian kernel will
  // go before being clamped to zero.
  vtkSetVector3Macro(RadiusFactors, double);
  void SetRadiusFactors(double f, double f2) {
    this->SetRadiusFactors(f,f2,1.5);}
  void SetRadiusFactor(double f) {this->SetRadiusFactors(f, f, f);}
  vtkGetVector3Macro(RadiusFactors, double);

  // Description:
  // Set/Get the dimensionality of this filter. This determines whether
  // a one, two, or three dimensional gaussian is performed.
  vtkSetMacro(Dimensionality, int);
  vtkGetMacro(Dimensionality, int);

protected:
  vtkImageGaussianSmooth2();
  ~vtkImageGaussianSmooth2();

  int Dimensionality;
  double StandardDeviations[3];
  double RadiusFactors[3];

  void ComputeKernel(double *kernel, int min, int max, double std);
  virtual int RequestUpdateExtent (vtkInformation *, vtkInformationVector **, vtkInformationVector *);
  void InternalRequestUpdateExtent(int *, int*);
  void ExecuteAxis(int axis, vtkImageData *inData, int inExt[6],
                   vtkImageData *outData, int outExt[6],
                   int *pcycle, int target, int *pcount, int total,
                   vtkInformation *inInfo);
  void ThreadedRequestData(vtkInformation *request,
                           vtkInformationVector **inputVector,
                           vtkInformationVector *outputVector,
                           vtkImageData ***inData, vtkImageData **outData,
                           int outExt[6], int id);

};

#endif










