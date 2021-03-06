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
//! \file SimpleCCDDataHandling.h
//! \ingroup FineCollisionDetection
//! \author Sebastian Eibl <sebastian.eibl@fau.de>
//
//======================================================================================================================

#pragma once

#include "pe/rigidbody/BodyStorage.h"

#include "blockforest/BlockDataHandling.h"

namespace walberla{
namespace pe{
namespace ccd {

template <typename CCD>
class CCDDataHandling : public blockforest::AlwaysInitializeBlockDataHandling<CCD>{
public:
   CCDDataHandling(const BlockDataID& storageID) : storageID_(storageID) {}
private:
   BlockDataID storageID_;
};

template <typename CCD>
shared_ptr<CCD> createCCDDataHandling( const BlockDataID& storageID)
{
   return make_shared< CCDDataHandling<CCD> >( storageID );
}

}
}
}
