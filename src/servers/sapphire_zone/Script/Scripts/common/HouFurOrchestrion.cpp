#include "../ScriptObject.h"

class HouFurOrchestrion : public EventScript
{
public:
   HouFurOrchestrion() : EventScript( 721226 )
   {}

   void Scene00000( Entity::Player& player )
   {
      player.eventPlay( getId(), 0, 0x2000, 0, 1 );
   }

   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      Scene00000( player );
   }
};