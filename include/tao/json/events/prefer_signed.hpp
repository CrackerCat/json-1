// Copyright (c) 2017 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#ifndef TAOCPP_JSON_INCLUDE_EVENTS_PREFER_SIGNED_HPP
#define TAOCPP_JSON_INCLUDE_EVENTS_PREFER_SIGNED_HPP

namespace tao
{
   namespace json
   {
      namespace events
      {
         template< typename Consumer >
         struct prefer_signed
         {
            template< typename... Ts >
            prefer_signed( Ts&&... ts )
               : m_consumer( std::forward< Ts >( ts )... )
            {
            }

            void null()
            {
               m_consumer.null();
            }

            void boolean( const bool v )
            {
               m_consumer.boolean( v );
            }

            void number( const std::int64_t v )
            {
               m_consumer.number( v );
            }

            void number( const std::uint64_t v )
            {
               if( v <= 9223372036854775807ull ) {
                  m_consumer.number( std::int64_t( v ) );
               }
               else {
                  m_consumer.number( v );
               }
            }

            void number( const double v )
            {
               m_consumer.number( v );
            }

            void string( const std::string& v )
            {
               m_consumer.string( v );
            }

            void binary( const std::vector< byte >& v )
            {
               m_consumer.binary( v );
            }

            void begin_array()
            {
               m_consumer.begin_array();
            }

            void begin_array( const std::size_t v )
            {
               m_consumer.begin_array( v );
            }

            void element()
            {
               m_consumer.element();
            }

            void end_array()
            {
               m_consumer.end_array();
            }

            void end_array( const std::size_t v )
            {
               m_consumer.end_array( v );
            }

            void begin_object()
            {
               m_consumer.begin_object();
            }

            void begin_object( const std::size_t v )
            {
               m_consumer.begin_object( v );
            }

            void key( const std::string& v )
            {
               m_consumer.key( v );
            }

            void member()
            {
               m_consumer.member();
            }

            void end_object()
            {
               m_consumer.end_object();
            }

            void end_object( const std::size_t v )
            {
               m_consumer.end_object( v );
            }

         private:
            Consumer m_consumer;
         };

      } // events

   } // json

} // tao

#endif