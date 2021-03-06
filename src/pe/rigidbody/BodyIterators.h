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
//! \file BodyIterators.h
//! \ingroup pe
//! \author Florian Schornbaum <florian.schornbaum@fau.de>
//! \author Christoph Rettinger <christoph.rettinger@fau.de>
//! \author Sebastian Eibl <sebastian.eibl@fau.de>
//======================================================================================================================

#pragma once

#include <iterator>

#include "domain_decomposition/IBlock.h"
#include "pe/rigidbody/BodyStorage.h"

namespace walberla {
namespace pe {

class BodyIterator
{
public:

    template< typename T >
    class iterator : public std::iterator< std::input_iterator_tag, typename T::value_type, typename T::difference_type, typename T::pointer, typename T::reference >
    {
        friend class BodyIterator;
    public:
        iterator & operator++()    { ++it_; checkStateAndAdapt(); return *this; }      // prefix ++X
        iterator   operator++(int) { iterator it( *this ); operator++(); return it; }; // postfix X++

        bool operator==( const iterator & rhs ) const
        {
            if (ended_ || rhs.ended_)
            {
               if (ended_ == rhs.ended_)
               {
                  return true;
               }
               else
               {
                  return false;
               }
            }

            return it_ == rhs.it_;
        }
        bool operator!=( const iterator & rhs ) const { return !(*this == rhs); }

        typename T::value_type operator*()  { return *it_; }
        typename T::pointer    operator->() { return *it_; }

    private:

        iterator( const T& begin,
                  const T& localEnd,
                  const T& shadowBegin,
                  const T& shadowEnd )
            : it_(begin)
            , itLocalEnd_(localEnd)
            , itShadowBegin_(shadowBegin)
            , itShadowEnd_(shadowEnd)
            , local_(true)
            , ended_(false)
        {
            checkStateAndAdapt();
        }

        iterator( )
            : ended_( true )
        {}

        void checkStateAndAdapt()
        {
            if( local_ && it_ == itLocalEnd_ )
            {
               it_ = itShadowBegin_;
               local_ = false;
            }

            if( it_ == itShadowEnd_ )
            {
                ended_ = true;
            }
        }

        T it_;
        T itLocalEnd_;
        T itShadowBegin_;
        T itShadowEnd_;

        bool local_;

        bool ended_;
    };

    static inline iterator<pe::BodyStorage::Bodies::Iterator>         begin(      IBlock & block,
                                                                            const BlockDataID & bodyStorageId)
    {
        pe::Storage * storage = block.getData< pe::Storage >( bodyStorageId );
        return iterator<pe::BodyStorage::Bodies::Iterator> ( (*storage)[0].begin(), (*storage)[0].end(), (*storage)[1].begin(), (*storage)[1].end() );
    }

    template< typename C >
    static inline iterator<pe::BodyStorage::Bodies::CastIterator<C> > begin(      IBlock & block,
                                                                            const BlockDataID & bodyStorageId)
    {
        pe::Storage * storage = block.getData< pe::Storage >( bodyStorageId );
        return iterator<pe::BodyStorage::Bodies::CastIterator<C> > ( (*storage)[0].begin<C>(), (*storage)[0].end<C>(), (*storage)[1].begin<C>(), (*storage)[1].end<C>() );
    }


    static inline iterator<pe::BodyStorage::Bodies::Iterator>             end()
    {
        return iterator<pe::BodyStorage::Bodies::Iterator> ( );
    }
    template< typename C >
    static inline iterator<pe::BodyStorage::Bodies::CastIterator<C> >     end()
    {
        return iterator<pe::BodyStorage::Bodies::CastIterator<C> > ( );
    }

}; // class BodyIterator



class LocalBodyIterator
{
public:

    template< typename T >
    class iterator : public std::iterator< std::input_iterator_tag, typename T::value_type, typename T::difference_type, typename T::pointer, typename T::reference >
    {
        friend class LocalBodyIterator;
    public:
        iterator & operator++()    { ++it_; checkStateAndAdapt(); return *this; }      // prefix ++X
        iterator   operator++(int) { iterator it( *this ); operator++(); return it; }; // postfix X++

        bool operator==( const iterator & rhs ) const
        {
            if (ended_ || rhs.ended_)
            {
               if (ended_ == rhs.ended_)
               {
                  return true;
               }
               else
               {
                  return false;
               }
            }

            return it_ == rhs.it_;
        }
        bool operator!=( const iterator & rhs ) const { return !(*this == rhs); }

        typename T::value_type operator*()  { return *it_; }
        typename T::pointer    operator->() { return *it_; }

    private:

        iterator( const T& begin,
                  const T& end )
            : it_(begin), itEnd_(end), ended_( false )
        {
            checkStateAndAdapt();
        }

        iterator( )
            : ended_( true )
        {}

        void checkStateAndAdapt()
        {
            if( it_ == itEnd_ )
            {
                ended_ = true;
            }
        }

        T it_;
        T itEnd_;

        bool ended_;
    };

    static inline iterator<pe::BodyStorage::Bodies::Iterator>         begin(      IBlock & block,
                                                                            const BlockDataID & bodyStorageId)
    {
        pe::Storage * storage = block.getData< pe::Storage >( bodyStorageId );
        return iterator<pe::BodyStorage::Bodies::Iterator> ( (*storage)[0].begin(), (*storage)[0].end() );
    }

    template< typename C >
    static inline iterator<pe::BodyStorage::Bodies::CastIterator<C> > begin(      IBlock & block,
                                                                            const BlockDataID & bodyStorageId)
    {
        pe::Storage * storage = block.getData< pe::Storage >( bodyStorageId );
        return iterator<pe::BodyStorage::Bodies::CastIterator<C> > ( (*storage)[0].begin<C>(), (*storage)[0].end<C>() );
    }


    static inline iterator<pe::BodyStorage::Bodies::Iterator>             end()
    {
        return iterator<pe::BodyStorage::Bodies::Iterator> ( );
    }
    template< typename C >
    static inline iterator<pe::BodyStorage::Bodies::CastIterator<C> >     end()
    {
        return iterator<pe::BodyStorage::Bodies::CastIterator<C> > ( );
    }

}; // class LocalBodyIterator


class ShadowBodyIterator
{
public:

    template< typename T >
    class iterator : public std::iterator< std::input_iterator_tag, typename T::value_type, typename T::difference_type, typename T::pointer, typename T::reference >
    {
        friend class ShadowBodyIterator;
    public:
        iterator & operator++()    { ++it_; checkStateAndAdapt(); return *this; }      // prefix ++X
        iterator   operator++(int) { iterator it( *this ); operator++(); return it; }; // postfix X++

        bool operator==( const iterator & rhs ) const
        {
            if (ended_ || rhs.ended_)
            {
               if (ended_ == rhs.ended_)
               {
                  return true;
               }
               else
               {
                  return false;
               }
            }

            return it_ == rhs.it_;
        }
        bool operator!=( const iterator & rhs ) const { return !(*this == rhs); }

        typename T::value_type operator*()  { return *it_; }
        typename T::pointer    operator->() { return *it_; }

    private:

        iterator( const T& begin,
                  const T& end )
            : it_(begin), itEnd_(end), ended_( false )
        {
            checkStateAndAdapt();
        }

        iterator( )
            : ended_( true )
        {}

        void checkStateAndAdapt()
        {
            if( it_ == itEnd_ )
            {
                ended_ = true;
            }
        }

        T it_;
        T itEnd_;

        bool ended_;
    };

    static inline iterator<pe::BodyStorage::Bodies::Iterator>         begin(      IBlock & block,
                                                                            const BlockDataID & bodyStorageId)
    {
        pe::Storage * storage = block.getData< pe::Storage >( bodyStorageId );
        return iterator<pe::BodyStorage::Bodies::Iterator> ( (*storage)[1].begin(), (*storage)[1].end() );
    }

    template< typename C >
    static inline iterator<pe::BodyStorage::Bodies::CastIterator<C> > begin(      IBlock & block,
                                                                            const BlockDataID & bodyStorageId)
    {
        pe::Storage * storage = block.getData< pe::Storage >( bodyStorageId );
        return iterator<pe::BodyStorage::Bodies::CastIterator<C> > ( (*storage)[1].begin<C>(), (*storage)[1].end<C>() );
    }


    static inline iterator<pe::BodyStorage::Bodies::Iterator>             end()
    {
        return iterator<pe::BodyStorage::Bodies::Iterator> ( );
    }
    template< typename C >
    static inline iterator<pe::BodyStorage::Bodies::CastIterator<C> >     end()
    {
        return iterator<pe::BodyStorage::Bodies::CastIterator<C> > ( );
    }

}; // class ShadowBodyIterator


} // namespace pe
} // namespace walberla
