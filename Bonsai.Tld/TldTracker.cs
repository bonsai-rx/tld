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

namespace Bonsai.Tld
{
    public class TldTracker : Transform<IplImage, IplImage>
    {
        public TldTracker()
        {
            Tracking = true;
            Detection = true;
            Learning = true;
            Alternating = false;
        }

        public bool Tracking { get; set; }

        public bool Detection { get; set; }

        public bool Learning { get; set; }

        public bool Alternating { get; set; }

        [Description("The region of interest inside the input image.")]
        [Editor("Bonsai.Vision.Design.IplImageInputRectangleEditor, Bonsai.Vision.Design", typeof(UITypeEditor))]
        public Rect RegionOfInterest { get; set; }

        public override IObservable<IplImage> Process(IObservable<IplImage> source)
        {
            return Observable.Defer(() =>
            {
                var tracker = new TrackerTld();
                var inputRoi = new Rect();
                var initialized = false;
                return source.Select(input =>
                {
                    tracker.TrackerEnabled = Tracking;
                    tracker.DetectorEnabled = Detection;
                    tracker.LearningEnabled = Learning;
                    tracker.Alternating = Alternating;
                    var output = input.Clone();
                    //Initialize
                    if (inputRoi != RegionOfInterest)
                    {
                        tracker.Init(output);
                        inputRoi = RegionOfInterest;
                        tracker.SelectObject(output, inputRoi);
                        initialized = true;
                    }

                    if (initialized)
                    {
                        tracker.ProcessImage(output);
                        if (tracker.CurrentBoundingBox.HasValue) //When target is lost, bounding box is null
                        {
                            var currentRect = tracker.CurrentBoundingBox.Value;
                            CV.Rectangle(output, currentRect, Scalar.Rgb(0, 255, 0));
                        }
                    }
                    return output;
                });
            });
        }
    }
}
