#pragma once

//
// Boost includes and definitions.
//

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/gregorian/greg_serialize.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <boost/range/algorithm/remove_if.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/throw_exception.hpp>

namespace bfs = boost::filesystem;
namespace bsrlz = boost::serialization;
