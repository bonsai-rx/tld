// This is the main DLL file.

#include "stdafx.h"

#include "OpenTld.Net.h"


OpenTldNet::OpenTld::OpenTld()
{
	tldTracker = new tld::TLD();
}

OpenTldNet::OpenTld::~OpenTld()
{
	this->!OpenTld();
}

OpenTldNet::OpenTld::!OpenTld()
{
	if(tldTracker != nullptr)
	{
		delete tldTracker;
	}
	tldTracker = nullptr;
}

void OpenTldNet::OpenTld::Init(OpenCV::Net::IplImage ^image)
{
	tldTracker->detectorCascade->imgWidth = image->Width;
	tldTracker->detectorCascade->imgHeight = image->Height;
	tldTracker->detectorCascade->imgWidthStep = image->WidthStep;
}

void OpenTldNet::OpenTld::Release()
{
	tldTracker->release();	
}

void OpenTldNet::OpenTld::SelectObject(OpenCV::Net::IplImage ^image, OpenCV::Net::Rect ^roi)
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

void OpenTldNet::OpenTld::ProcessImage(OpenCV::Net::IplImage ^image)
{
	IntPtr handle = image->DangerousGetHandle();
	cv::Mat cvimage = cv::cvarrToMat(handle.ToPointer());
	tldTracker->processImage(cvimage);
}