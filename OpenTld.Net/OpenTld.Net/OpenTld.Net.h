// OpenTld.Net.h
#include "opentld/tld/TLD.h"
#include "opencv2/core/core.hpp"

#pragma once

using namespace System;

namespace OpenTldNet {

	public ref class OpenTLD
	{
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="OpenTLD"/> class.
		/// </summary>
		OpenTLD();

		/// <summary>
		/// Destructs an instance of the <see cref="OpenTLD"/> class.
		/// </summary>
		~OpenTLD();

		/// <summary>
		/// Finalizes an instance of the <see cref="OpenTLD"/> class.
		/// </summary>
		!OpenTLD();

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

		property OpenCV::Net::Rect^ CurrentBoundingBox
		{
			OpenCV::Net::Rect ^get()
			{
				if(tldTracker->currBB != NULL)
				{
					return gcnew OpenCV::Net::Rect( tldTracker->currBB->x, tldTracker->currBB->y, tldTracker->currBB->width, tldTracker->currBB->height);
				}
				else 
					return nullptr;			
			}
		}

		property bool LearningEnabled
		{
			bool get()
			{
				return tldTracker->learningEnabled;
			}
			void set(bool value)
			{
				tldTracker->learningEnabled = value;	
			}
		}

		property bool Alternating
		{
			bool get()
			{
				return tldTracker->alternating;
			}
			void set(bool value)
			{
				tldTracker->alternating = value;	
			}
		}

	private:
		tld::TLD *tldTracker;
	};
}
