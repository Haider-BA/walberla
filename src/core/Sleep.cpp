//======================================================================================================================
//
//  This file is part of waLBerla. waLBerla is free software: you can 
//  redistribute it and/or modify it under the terms of the GNU General Public
//  License as published by the Free Software Foundation, either version 3 of 
//  the License, or (at your option) any later version.
//  
//  waLBerla is distributed in the hope that it will be useful, but WITHOUT 
//  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
//  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License 
//  for more details.
//  
//  You should have received a copy of the GNU General Public License along
//  with waLBerla (see COPYING.txt). If not, see <http://www.gnu.org/licenses/>.
//
//! \file Sleep.cpp
//! \ingroup core
//! \author Matthias Markl <matthias.markl@fau.de>
//
//======================================================================================================================

#include "Sleep.h"
#include "waLBerlaDefinitions.h"

#ifdef WALBERLA_CXX_COMPILER_IS_MSVC

#include <windows.h>

namespace walberla {

   void sleep( uint_t seconds )
   {
      ::Sleep( static_cast<DWORD>( uint_t(1000) * seconds ) );
   }

}

#else

#ifdef WALBERLA_CXX_COMPILER_IS_IBM
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE
#endif
#endif

#include <unistd.h>

namespace walberla {

   void sleep( uint_t seconds )
   {
      ::sleep( static_cast<unsigned int>(seconds) );
   }

}

#endif