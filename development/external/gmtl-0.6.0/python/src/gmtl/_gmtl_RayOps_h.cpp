/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          _gmtl_RayOps_h.cpp,v
 * Date modified: 2005/06/02 22:07:58
 * Version:       1.1
 * -----------------------------------------------------------------
 *
 *********************************************************** ggt-head end */
/*************************************************************** ggt-cpr beg
*
* GGT: The Generic Graphics Toolkit
* Copyright (C) 2001,2002 Allen Bierbaum
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*
 ************************************************************ ggt-cpr end */

// Includes ====================================================================
#include <boost/python.hpp>
#include <gmtl-RayOps.h>

// Using =======================================================================
using namespace boost::python;

// Module ======================================================================
void _Export_gmtl_RayOps_h()
{
    def("isEqual", (bool (*)(const gmtl::Ray<double> &, const gmtl::Ray<double> &, const double &))&gmtl::isEqual);
    def("isEqual", (bool (*)(const gmtl::Ray<float> &, const gmtl::Ray<float> &, const float &))&gmtl::isEqual);
}
