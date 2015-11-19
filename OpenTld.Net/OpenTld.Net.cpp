/*  Copyright 2015 Xavier Faure
*
*   This file is part of OpenTLD.NET.
*
*   OpenTLD.NET is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   OpenTLD.NET is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with OpenTLD.NET.  If not, see <http://www.gnu.org/licenses/>.
*
*/
/*
 * OpenTld.Net.cpp
 *
 *  Created on: Nov 12, 2015
 *      Author: Xavier Faure
 */

#include "OpenTld.Net.h"

using namespace System::Runtime::InteropServices;

OpenTld::Net::TrackerTld::TrackerTld()
{
	tldTracker = new tld::TLD();
}

OpenTld::Net::TrackerTld::~TrackerTld()
{
	this->!TrackerTld();
}

OpenTld::Net::TrackerTld::!TrackerTld()
{
	delete tldTracker;
	previous = nullptr;
}

void OpenTld::Net::TrackerTld::Init(OpenCV::Net::IplImage ^image)
{
	tldTracker->detectorCascade->imgWidth = image->Width;
	tldTracker->detectorCascade->imgHeight = image->Height;
	tldTracker->detectorCascade->imgWidthStep = image->WidthStep;
}

void OpenTld::Net::TrackerTld::Release()
{
	tldTracker->release();	
}

void OpenTld::Net::TrackerTld::SelectObject(OpenCV::Net::IplImage ^image, OpenCV::Net::Rect ^roi)
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
	previous = image;
}

void OpenTld::Net::TrackerTld::ProcessImage(OpenCV::Net::IplImage ^image)
{
	IntPtr handle = image->DangerousGetHandle();
	cv::Mat cvimage = cv::cvarrToMat(handle.ToPointer());
	tldTracker->processImage(cvimage);
	previous = image;
}

void OpenTld::Net::TrackerTld::ReadFromFile(String ^fileName)
{
	IntPtr hFileName = Marshal::StringToHGlobalAnsi(fileName);
	tldTracker->readFromFile((char *)hFileName.ToPointer());
	Marshal::FreeHGlobal(hFileName);
}

void OpenTld::Net::TrackerTld::WriteToFile(String ^fileName)
{
	IntPtr hFileName = Marshal::StringToHGlobalAnsi(fileName);
	tldTracker->writeToFile((char *)hFileName.ToPointer());
	Marshal::FreeHGlobal(hFileName);
}
