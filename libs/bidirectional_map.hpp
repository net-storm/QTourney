///
/// Copyright &copy; Sergey Stepanov 2010-2011. All rights reserved.
/// \file    bidirectional_map.hpp , v 1.0 2011/04/05 15:47:28 Garret
/// \brief   bidirectional map template
/// \author  Sergey Stepanov (net_storm@rambler.ru)
/// \date    Tue Apr 05 15:47:28 MSK 2011 -- Initial design
/// \par     Maintenance person:
///          Sergey Stepanov (net_storm@rambler.ru)
///

#ifndef _6BEFFC5E_4F22_420E_B654_2A50FF3A5173_
#define _6BEFFC5E_4F22_420E_B654_2A50FF3A5173_

#  include <boost/multi_index_container.hpp>
#  include <boost/multi_index/member.hpp>
#  include <boost/multi_index/ordered_index.hpp>

// tags for accessing both sides of a bidirectional map
struct left_index{};
struct right_index{};

namespace boost {

template<typename FromType,typename ToType>
struct bidirectional_map
{
#  if defined(_MSC_VER)
     typedef std::_Pair_base<FromType,ToType> value_type;
#  else
     typedef std::pair<FromType,ToType> value_type;
#  endif

  typedef boost::multi_index::multi_index_container
  <
        value_type
      , boost::multi_index::indexed_by
      <
            boost::multi_index::ordered_unique
          <
                boost::multi_index::tag<left_index>
              , boost::multi_index::member
              <
                    value_type
                  , FromType
                  , &value_type::first
              > 
          >
          , boost::multi_index::ordered_unique
          <
                boost::multi_index::tag<right_index>
              , boost::multi_index::member
              <
                    value_type
                  , ToType
                  , &value_type::second
              > 
          >
      >
  > type;
};

}

#endif // _6BEFFC5E_4F22_420E_B654_2A50FF3A5173_