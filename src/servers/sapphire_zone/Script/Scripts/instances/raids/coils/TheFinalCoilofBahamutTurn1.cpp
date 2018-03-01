#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheFinalCoilofBahamutTurn1 : public InstanceContentScript
{
public:
   TheFinalCoilofBahamutTurn1() : InstanceContentScript( 30016 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2004612, 0, 4, { -0.116493f, -0.000001f, -293.875214f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2004613, 0, 4, { -5.014206f, -0.000001f, -285.730896f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 4894214, 5, { 0.172209f, 1.707170f, 221.425903f }, 1.000000f );
      instance->registerEObj( "Shortcut", 2000700, 0, 4, { -6.029538f, -0.000005f, 188.016205f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2003679, 4868598, 4, { -0.125790f, 0.523954f, 167.023605f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2004605, 4852714, 4, { -0.194780f, -0.000003f, 177.104095f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2003849, 4881763, 4, { 0.031929f, -19.494820f, 141.135101f }, 0.991760f );
      instance->registerEObj( "Unknown6", 2003905, 4868599, 4, { -0.095059f, -7.275987f, 79.729607f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2004605, 4879813, 4, { -10.904620f, -18.183340f, 116.685303f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2004605, 4879797, 4, { 11.416480f, -18.931650f, 116.685303f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2004605, 4879805, 4, { 11.416480f, -19.000000f, 103.064003f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2004605, 4879822, 4, { -11.312880f, -19.000000f, 103.064003f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2004116, 4881762, 4, { 0.171127f, -19.487169f, 30.039690f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2004117, 4868600, 4, { 0.009460f, -29.465590f, 10.045650f }, 1.000000f );
      instance->registerEObj( "Unknown13", 2004605, 4879838, 4, { 0.047739f, -29.000000f, 19.918270f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2004605, 4879850, 4, { 0.018590f, -29.000000f, 19.923750f }, 1.000000f );
      instance->registerEObj( "Unknown15", 2004118, 4881761, 4, { 0.003261f, -4.463747f, -152.984604f }, 1.000000f );
      instance->registerEObj( "Unknown16", 2004119, 4868601, 4, { 0.003693f, -4.463205f, -166.994400f }, 0.991760f );
      instance->registerEObj( "Unknown17", 2002735, 0, 4, { 0.007116f, -5.000001f, -171.749207f }, 1.000000f );
      instance->registerEObj( "Unknown18", 2002872, 4895024, 4, { -0.005186f, -4.890112f, -171.362305f }, 1.000000f );
      instance->registerEObj( "Unknown19", 2004305, 4841650, 4, { 0.086417f, 0.090680f, -300.234711f }, 1.000000f );
      instance->registerEObj( "Allaganterminal", 2004141, 4841682, 4, { 0.003672f, 1.083544f, -337.998596f }, 0.991760f );
      instance->registerEObj( "Unknown20", 2004137, 4895069, 4, { 3.638081f, 0.152056f, -331.675415f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};