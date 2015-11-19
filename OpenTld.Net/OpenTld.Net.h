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
 * OpenTld.Net.h
 *
 *  Created on: Nov 12, 2015
 *      Author: Xavier Faure
 */

#include "tld/TLD.h"
#include "opencv2/core/core.hpp"

#pragma once

using namespace System;

namespace OpenTld
{
	namespace Net
	{
		public ref class TrackerTld
		{
		public:
			/// <summary>
			/// Initializes a new instance of the <see cref="TrackerTld"/> class.
			/// </summary>
			TrackerTld();

			/// <summary>
			/// Destructs an instance of the <see cref="TrackerTld"/> class.
			/// </summary>
			~TrackerTld();

			/// <summary>
			/// Finalizes an instance of the <see cref="TrackerTld"/> class.
			/// </summary>
			!TrackerTld();

			/// <summary>
			/// Initializes this instance.
			/// </summary>
			/// <param name="image">input image</param>
			void Init(OpenCV::Net::IplImage ^image);

			/// <summary>
			/// Clears this instance.
			/// </summary>
			void Release();

			/// <summary>
			/// Selects a region of interest to track.
			/// </summary>
			/// <param name="image">input image</param>
			/// <param name="roi">input region of interest</param>
			void SelectObject(OpenCV::Net::IplImage ^image, OpenCV::Net::Rect ^roi);

			/// <summary>
			/// Processes an image and update tracking.
			/// </summary>
			/// <param name="image">input image</param>
			void ProcessImage(OpenCV::Net::IplImage ^image);

			/// <summary>
			/// Load a previously saved tracking model.
			/// </summary>
			/// <param name="fileName">The path to the file containing the stored model.</param>
			void ReadFromFile(String ^fileName);

			/// <summary>
			/// Save the currently active tracking model to file.
			/// </summary>
			/// <param name="fileName">The path to the file that will store the tracking model.</param>
			void WriteToFile(String ^fileName);

			/// <summary>
			/// Gets or sets a value indicating whether the tracker is enabled.
			/// </summary>
			property bool TrackerEnabled
			{
				bool get() { return tldTracker->trackerEnabled; }
				void set(bool value) { tldTracker->trackerEnabled = value; }
			}

			/// <summary>
			/// Gets or sets a value indicating whether the detector is enabled.
			/// </summary>
			property bool DetectorEnabled
			{
				bool get() { return tldTracker->detectorEnabled; }
				void set(bool value) { tldTracker->detectorEnabled = value; }
			}

			/// <summary>
			/// Gets or sets a value indicating whether new object poses should be recorded.
			/// </summary>
			property bool LearningEnabled
			{
				bool get() { return tldTracker->learningEnabled; }
				void set(bool value) { tldTracker->learningEnabled = value; }
			}

			/// <summary>
			/// Gets or sets a value indicating whether the detector is switched off when
			/// tracker is available.
			/// </summary>
			property bool Alternating
			{
				bool get() { return tldTracker->alternating; }
				void set(bool value) { tldTracker->alternating = value; }
			}

			/// <summary>
			/// Gets the currently tracked bounding box.
			/// </summary>
			property Nullable<OpenCV::Net::Rect> CurrentBoundingBox
			{
				Nullable<OpenCV::Net::Rect> get()
				{
					if(tldTracker->currBB != NULL)
					{
						return Nullable<OpenCV::Net::Rect>(OpenCV::Net::Rect(
							tldTracker->currBB->x,
							tldTracker->currBB->y,
							tldTracker->currBB->width,
							tldTracker->currBB->height));
					}
					else return Nullable<OpenCV::Net::Rect>();	
				}
			}

			/// <summary>
			/// Gets the confidence level for the currently tracked bounding box.
			/// </summary>
			property float CurrentConfidence
			{
				float get() { return tldTracker->currConf; }
			}
		private:
			tld::TLD *tldTracker;
			OpenCV::Net::IplImage ^previous;
		};
	}
}
