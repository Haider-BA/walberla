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
//! \file Sphere.cpp
//! \ingroup geometry
//! \author Martin Bauer <martin.bauer@fau.de>
//
//======================================================================================================================

#include "Sphere.h"
#include "core/logging/Logging.h"


namespace walberla {
namespace geometry {

   Sphere::Sphere( const Vector3<real_t> & midp, real_t rad )
      : midpoint_( midp ), radius_ (rad )
   {
      updateBoxes();
   }

   Sphere::Sphere( const Sphere & o )
      : midpoint_( o.midpoint_ ),
        radius_( o.radius_ ),
        boundingBox_ ( o.boundingBox_ ),
        innerBox_ ( o.innerBox_ )
   {}

   void Sphere::updateBoxes()
   {
      static const real_t oneOverSqrt3 = real_t(1) / std::sqrt( real_t(3) );

      boundingBox_ = AABB::createFromMinMaxCorner( midpoint_[0] - radius_, midpoint_[1] - radius_, midpoint_[2] - radius_,
                                                   midpoint_[0] + radius_, midpoint_[1] + radius_, midpoint_[2] + radius_ );

      real_t halfBoxEdge = radius_ * oneOverSqrt3;
      innerBox_ = AABB::createFromMinMaxCorner( midpoint_[0] - halfBoxEdge, midpoint_[1] - halfBoxEdge, midpoint_[2] - halfBoxEdge,
                                                midpoint_[0] + halfBoxEdge, midpoint_[1] + halfBoxEdge, midpoint_[2] + halfBoxEdge );
   }




   //===================================================================================================================
   //
   //  Body concept implementation
   //
   //===================================================================================================================


   template<>
   FastOverlapResult fastOverlapCheck ( const Sphere & sphere, const AABB & box )
   {
           if ( ! sphere.boundingBox().intersects( box ) ) return COMPLETELY_OUTSIDE;
      else if (   sphere.innerBox()   .contains( box ) )   return CONTAINED_INSIDE_BODY;
      else                                                 return DONT_KNOW;
   }

   template<>
   FastOverlapResult fastOverlapCheck ( const Sphere & sphere, const Vector3<real_t> & cellMidpoint, real_t dx )
   {
      static const real_t sqrt3half = std::sqrt( real_t(3) ) / real_t(2);

      const real_t midPointDistSq = (sphere.midpoint() - cellMidpoint).sqrLength();

      // Check against outer circle of box
      const real_t dist1 = sphere.radius() + sqrt3half * dx;
      if ( midPointDistSq > dist1 * dist1 )
         return COMPLETELY_OUTSIDE;

      // Check against inner circle of box
      const real_t dist2 = sphere.radius() - sqrt3half * dx;
      if ( midPointDistSq < dist2 * dist2 )
         return CONTAINED_INSIDE_BODY;

      return DONT_KNOW;
   }

   template<>
   bool contains ( const Sphere & sphere, const Vector3<real_t> & point )
   {
      return (sphere.midpoint() - point).sqrLength() <=  sphere.radius() * sphere.radius() ;
   }




} // namespace geometry
} // namespace walberla


