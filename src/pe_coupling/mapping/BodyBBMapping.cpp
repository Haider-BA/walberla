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
//! \file BodyBBMapping.cpp
//! \ingroup pe_coupling
//! \author Florian Schornbaum <florian.schornbaum@fau.de>
//! \author Christoph Rettinger <christoph.rettinger@fau.de>
//! \author Sebastian Eibl <sebastian.eibl@fau.de>
//
//======================================================================================================================

#include "BodyBBMapping.h"

#include "pe/rigidbody/RigidBody.h"

namespace walberla {
namespace pe_coupling {

CellInterval getCellBB( const pe::ConstBodyID body, const IBlock & block, const shared_ptr<StructuredBlockStorage> & blockStorage,
                        const uint_t numberOfGhostLayersToInclude )
{
   CellInterval cellBB;

   const auto & aabb = body->getAABB();
   blockStorage->getCellBBFromAABB( cellBB, aabb, blockStorage->getLevel(block) );

   cellBB.xMin() -= cell_idx_c(1); cellBB.yMin() -= cell_idx_c(1); cellBB.zMin() -= cell_idx_c(1);
   cellBB.xMax() += cell_idx_c(1); cellBB.yMax() += cell_idx_c(1); cellBB.zMax() += cell_idx_c(1);

   CellInterval blockBB = blockStorage->getBlockCellBB( block );

   cell_idx_t layers = cell_idx_c( numberOfGhostLayersToInclude );

   blockBB.xMin() -= layers; blockBB.yMin() -= layers; blockBB.zMin() -= layers;
   blockBB.xMax() += layers; blockBB.yMax() += layers; blockBB.zMax() += layers;

   cellBB.intersect( blockBB );

   blockStorage->transformGlobalToBlockLocalCellInterval( cellBB, block );

   return cellBB;
}



} // namespace pe_coupling
} // namespace walberla
