// This is the main DLL file.

#include "stdafx.h"

#include "OpenTld.Net.h"


OpenTld::Net::OpenTld::OpenTld()
{
	tldTracker = new tld::TLD();
}

OpenTld::Net::OpenTld::~OpenTld()
{
	this->!OpenTld();
}

OpenTld::Net::OpenTld::!OpenTld()
{
	if(tldTracker != nullptr)
	{
		delete tldTracker;
	}
	tldTracker = nullptr;
}

void OpenTld::Net::OpenTld::Init(OpenCV::Net::IplImage ^image)
{
	tldTracker->detectorCascade->imgWidth = image->Width;
	tldTracker->detectorCascade->imgHeight = image->Height;
	tldTracker->detectorCascade->imgWidthStep = image->WidthStep;
}

void OpenTld::Net::OpenTld::Release()
{
	tldTracker->release();	
}

void OpenTld::Net::OpenTld::SelectObject(OpenCV::Net::IplImage ^image, OpenCV::Net::Rect ^roi)
{
	IntPtr handle = image->DangerousGetHandle();
	cv::Mat cvimage = cv::cvarrToMat(handle.ToPointer());
	cv::Rect *cvRoi = new cv::Rect(roi->X, roi->Y, roi->Width, roi->Height);
	if (cvRoi->x < 0) cvRoi->x = 0;
	if (cvRoi->y < 0) cvRoi->y = 0;
	if (cvRoi->x > cvimage.cols) cvRoi->x = cvimage.cols;
	if (cvRoi->y > cvimage.rows) cvRoi->y = cvimage.rows;
	if (cvRoi->x + cvRoi->width > cvimage.cols) cvRoi->width -= (cvRoi->x + cvRoi->width) - cvimage.cols;
	if (cvRoi->y + cvRoi->height > cvimage.rows) cvRoi->height -= (cvRoi->y + cvRoi->height) - cvimage.rows;

	tldTracker->selectObject(cvimage,  cvRoi);	
}

void OpenTld::Net::OpenTld::ProcessImage(OpenCV::Net::IplImage ^image)
{
	IntPtr handle = image->DangerousGetHandle();
	cv::Mat cvimage = cv::cvarrToMat(handle.ToPointer());
	tldTracker->processImage(cvimage);
}