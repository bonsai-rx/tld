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
 * AssemblyInfo.cpp
 *
 *  Created on: Nov 12, 2015
 *      Author: Xavier Faure
 */

using namespace System;
using namespace System::Reflection;
using namespace System::Runtime::CompilerServices;
using namespace System::Runtime::InteropServices;
using namespace System::Security::Permissions;

//
// General Information about an assembly is controlled through the following
// set of attributes. Change these attribute values to modify the information
// associated with an assembly.
//
[assembly:AssemblyTitleAttribute("OpenTLD.NET")];
[assembly:AssemblyDescriptionAttribute("A managed wrapper to the OpenTLD open-source tracking library.")];
[assembly:AssemblyConfigurationAttribute("")];
[assembly:AssemblyCompanyAttribute("Xavier Faure")];
[assembly:AssemblyProductAttribute("OpenTld.Net")];
[assembly:AssemblyCopyrightAttribute("Copyright (c) Xavier Faure 2015")];
[assembly:AssemblyTrademarkAttribute("")];
[assembly:AssemblyCultureAttribute("")];

//
// Version information for an assembly consists of the following four values:
//
//      Major Version
//      Minor Version
//      Build Number
//      Revision
//
// You can specify all the value or you can default the Revision and Build Numbers
// by using the '*' as shown below:

[assembly:AssemblyVersionAttribute("0.1.0.0")];
[assembly:AssemblyInformationalVersionAttribute("0.1.0")];

[assembly:ComVisible(false)];

[assembly:CLSCompliantAttribute(true)];

[assembly:SecurityPermission(SecurityAction::RequestMinimum, UnmanagedCode = true)];
