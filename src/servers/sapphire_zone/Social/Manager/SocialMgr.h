#ifndef _SOCIALMGR_H
#define _SOCIALMGR_H

#include <Common.h>

#include <map>
#include <cstdint>

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <sapphire_zone/Forwards.h>
#include <Social/Group.h>

#include "Forwards.h"
#include <Social/FriendList.h>
#include <Database/DatabaseDef.h>

#include "Framework.h"

extern Core::Framework g_fw;

namespace Core {
namespace Social {

template< class T >
class SocialMgr
{
public:

   SocialMgr() : m_groupCount( 0 ),
      m_lastGroupId( 0 ),
      m_groups{}
   {

   }

   ~SocialMgr()
   {

   }

   bool init();
   //bool< FriendList > init();

   boost::shared_ptr< T > findGroupByInviteIdForPlayer( uint64_t playerId ) const
   {
      auto it = m_invites.find( playerId );
      if ( it != m_invites.end() )
      {
         return findGroupById( it->second );
      }
      return nullptr;
   }

   boost::shared_ptr< T > findGroupById( uint64_t groupId ) const
   {
      auto it = m_groups.find( groupId );
      if ( it != m_groups.end() )
      {
         return it->second;
      }
      return nullptr;
   }

   bool hasInvite( uint64_t playerId ) const
   {
      auto it = m_invites.find( playerId );
      if ( it != m_invites.end() )
      {
         return true;
      }
      return false;
   }

   uint64_t loadFriendsList( uint32_t characterId );

protected:
// those would be implemented in T, so you'd have T.m_type and T.m_maxEntries
//   GroupType m_type{ GroupType::None };
//   uint32_t m_maxEntries{ 0xFFFFFFFF };

   uint64_t generateGroupId()
   {
      m_lastGroupId++;
      return m_lastGroupId;
   }

   uint64_t m_groupCount;   
   std::map< uint64_t, uint64_t > m_invites;

   uint64_t m_lastGroupId;

   std::map< uint64_t, boost::shared_ptr< T > > m_groups;

private:
   

};

}
};

// Specialization

template< class T >
bool Core::Social::SocialMgr< T >::init()
{
   return true;
}

template<> inline
uint64_t Core::Social::SocialMgr< Core::Social::FriendList >::loadFriendsList( uint32_t characterId )
{

   auto pDb = g_fw.get< Db::DbWorkerPool< Db::CharaDbConnection > >();
   auto res = pDb->query( "SELECT CharacterId, CharacterIdList, InviteDataList "
      "FROM charainfofriendlist "
      "WHERE CharacterId = " + std::to_string( characterId ) );


   if ( !res->next() )
      return false;

   uint64_t ownerId = res->getUInt64( 1 );

   auto groupID = generateGroupId();
   auto friendsList = Core::Social::FriendList( groupID, ownerId );

   auto func = []( std::set< uint64_t >& outList, std::vector< char >& inData )
   {
      if ( inData.size() )
      {
         std::vector< uint64_t > list( inData.size() / 8 );
         // todo: fix this garbage. maybe get rid of lambda altogether
         if( list.at( 0 ) != 0 )
         {
            outList.insert( list.begin(), list.end() );
         }
      }
   };

   std::vector< char > friends;
   friends = res->getBlobVector( 2 );
   func( friendsList.getMembers(), friends );

   std::vector< char > friendInvites;
   friendInvites = res->getBlobVector( 3 );
   func( friendsList.getInvites(), friendInvites );

   auto friendListPtr = boost::make_shared< Core::Social::FriendList >( friendsList );
      
   m_groups[groupID] = friendListPtr;

   return groupID;
}


#endif /* ! _SOCIALMGR_H  */
