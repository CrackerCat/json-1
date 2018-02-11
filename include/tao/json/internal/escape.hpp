// Copyright (c) 2016-2018 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#ifndef TAOCPP_INCLUDE_JSON_INTERNAL_ESCAPE_HPP
#define TAOCPP_INCLUDE_JSON_INTERNAL_ESCAPE_HPP

#include <ostream>

#include "../external/string_view.hpp"

namespace tao
{
   namespace json
   {
      namespace internal
      {
         inline void escape( std::ostream& os, const tao::string_view s )
         {
            static const char* h = "0123456789abcdef";

            const char* p = s.data();
            const char* l = p;
            const char* const e = s.data() + s.size();
            while( p != e ) {
               const unsigned char c = *p;
               if( c == '\\' ) {
                  os.write( l, p - l );
                  l = ++p;
                  os << "\\\\";
               }
               else if( c == '"' ) {
                  os.write( l, p - l );
                  l = ++p;
                  os << "\\\"";
               }
               else if( c < 32 ) {
                  os.write( l, p - l );
                  l = ++p;
                  switch( c ) {
                     case '\b':
                        os << "\\b";
                        break;
                     case '\f':
                        os << "\\f";
                        break;
                     case '\n':
                        os << "\\n";
                        break;
                     case '\r':
                        os << "\\r";
                        break;
                     case '\t':
                        os << "\\t";
                        break;
                     default:
                        os << "\\u00" << h[ ( c & 0xf0 ) >> 4 ] << h[ c & 0x0f ];
                  }
               }
               else if( c == 127 ) {
                  os.write( l, p - l );
                  l = ++p;
                  os << "\\u007f";
               }
               else {
                  ++p;
               }
            }
            os.write( l, p - l );
         }

      }  // namespace internal

   }  // namespace json

}  // namespace tao

#endif
