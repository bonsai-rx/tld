﻿using Bonsai.Vision;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bonsai.Tld
{
    public class TrackedComponent : ConnectedComponent
    {
        public double Confidence { get; set; }
    }
}
