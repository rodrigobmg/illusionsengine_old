/*************** <auto-copyright.pl BEGIN do not edit this line> **************
 *
 * PyJuggler is (C) Copyright 2002, 2003 by Patrick Hartling
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * -----------------------------------------------------------------
 * File:          _Point_int_2.cpp,v
 * Date modified: 2005/06/06 03:57:41
 * Version:       1.5
 * -----------------------------------------------------------------
 *
 *************** <auto-copyright.pl END do not edit this line> ***************/


// Includes ====================================================================
#include <boost/python.hpp>
#include <gmtl/Point.h>
#include <gmtl-pickle.h>

// Using =======================================================================
using namespace boost::python;

// Module ======================================================================
void _Export_Point_int_2()
{
    scope* gmtl_Point_int_2_scope = new scope(
    class_< gmtl::Point<int,2>, bases< gmtl::VecBase<int,2> > >("Point2i", init<  >())
        .def(init< const gmtl::Point<int,2> & >())
        .def(init< const gmtl::VecBase<int,2> & >())
        .def(init< const int &, const int & >())
        .def_pickle(gmtlPickle::Point2_pickle<int>())
    );

    enum_< gmtl::Point<int,2>::Params >("Params")
        .value("Size", gmtl::Point<int,2>::Size)
    ;

    delete gmtl_Point_int_2_scope;

}
