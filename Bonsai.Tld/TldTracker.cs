/*  Copyright 2015 Gonçalo Lopes
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
 * TldTracker.cs
 *
 *  Created on: Nov 16, 2015
 *      Author: Gonçalo Lopes
 */

using Bonsai;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reactive.Linq;
using System.Text;
using OpenCV.Net;
using System.ComponentModel;
using System.Drawing.Design;
using OpenTld.Net;
using Bonsai.Vision;

namespace Bonsai.Tld
{
    [DefaultProperty("RegionOfInterest")]
    [Description("Tracks a specified object over time using the self-supervised TLD algorithm.")]
    public class TldTracker : Transform<IplImage, TrackedComponent>
    {
        public TldTracker()
        {
            Tracking = true;
            Detection = true;
            Learning = true;
            Alternating = false;
        }

        [Description("Indicates whether the tracker is enabled.")]
        public bool Tracking { get; set; }

        [Description("Indicates whether the detector is enabled.")]
        public bool Detection { get; set; }

        [Description("Indicates whether new object poses should be recorded.")]
        public bool Learning { get; set; }

        [Description("Indicates whether the detector is disabled when tracking is available.")]
        public bool Alternating { get; set; }

        [Description("The region of interest to track inside the input image.")]
        [Editor("Bonsai.Vision.Design.IplImageInputRectangleEditor, Bonsai.Vision.Design", typeof(UITypeEditor))]
        public Rect RegionOfInterest { get; set; }

        public override IObservable<TrackedComponent> Process(IObservable<IplImage> source)
        {
            return Observable.Defer(() =>
            {
                var tracker = new TrackerTld();
                var inputRoi = new Rect();
                var initialized = false;
                return source.Select(input =>
                {
                    var frame = input;
                    if (input.Channels == 3)
                    {
                        frame = new IplImage(input.Size, input.Depth, 1);
                        CV.CvtColor(input, frame, ColorConversion.Bgr2Gray);
                    }

                    tracker.TrackerEnabled = Tracking;
                    tracker.DetectorEnabled = Detection;
                    tracker.LearningEnabled = Learning;
                    tracker.Alternating = Alternating;
                    if (inputRoi != RegionOfInterest)
                    {
                        tracker.Init(frame);
                        inputRoi = RegionOfInterest;
                        tracker.SelectObject(frame, inputRoi);
                        initialized = true;
                    }

                    var component = new TrackedComponent();
                    if (initialized)
                    {
                        tracker.ProcessImage(frame);
                        if (tracker.CurrentBoundingBox.HasValue)
                        {
                            var boundingBox = tracker.CurrentBoundingBox.Value;
                            component.Area = boundingBox.Width * boundingBox.Height;
                            component.Centroid = new Point2f(
                                boundingBox.X + boundingBox.Width / 2f,
                                boundingBox.Y + boundingBox.Height / 2f);
                            component.Patch = input.GetSubRect(boundingBox);
                            component.Contour = new BoxContour(boundingBox);
                            component.MajorAxisLength = 0;
                            component.MinorAxisLength = 0;
                        }
                        else
                        {
                            component.Centroid = new Point2f(float.NaN, float.NaN);
                            component.Orientation = double.NaN;
                        }
                    }
                    component.Confidence = tracker.CurrentConfidence;
                    return component;
                });
            });
        }
    }
}
