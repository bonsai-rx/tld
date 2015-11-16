// OpenTld.Net.h
#include "opentld/tld/TLD.h"
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
		};
	}
}
