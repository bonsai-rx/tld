// OpenTld.Net.h
#include "opentld/tld/TLD.h"
#include "opencv2/core/core.hpp"

#pragma once

using namespace System;

namespace OpenTld
{
	namespace Net
	{
		public ref class OpenTld
		{
		public:
			/// <summary>
			/// Initializes a new instance of the <see cref="OpenTld"/> class.
			/// </summary>
			OpenTld();

			/// <summary>
			/// Destructs an instance of the <see cref="OpenTld"/> class.
			/// </summary>
			~OpenTld();

			/// <summary>
			/// Finalizes an instance of the <see cref="OpenTld"/> class.
			/// </summary>
			!OpenTld();

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
		};
	}
}
