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
    public class TldTracker : Transform<IplImage, ConnectedComponent>
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

        public override IObservable<ConnectedComponent> Process(IObservable<IplImage> source)
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
                    if (inputRoi != RegionOfInterest)
                    {
                        tracker.Init(input);
                        inputRoi = RegionOfInterest;
                        tracker.SelectObject(input, inputRoi);
                        initialized = true;
                    }

                    var component = new ConnectedComponent();
                    if (initialized)
                    {
                        tracker.ProcessImage(input);
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
                    return component;
                });
            });
        }
    }
}
