#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Striker increases the power of slicing moves by 30%", s16 damage)
{
    u32 move;
    enum Ability ability;
    PARAMETRIZE { move = MOVE_BLAZE_KICK; ability = ABILITY_STRIKER; }
    PARAMETRIZE { move = MOVE_BLAZE_KICK; ability = ABILITY_SPEED_BOOST; }
    PARAMETRIZE { move = MOVE_PECK; ability = ABILITY_STRIKER; }
    PARAMETRIZE { move = MOVE_PECK; ability = ABILITY_SPEED_BOOST; }

    GIVEN {
        ASSUME(IsKickingMove(MOVE_BLAZE_KICK));
        ASSUME(!IsKickingMove(MOVE_SCRATCH));
        PLAYER(SPECIES_BLAZIKEN) { Ability(ability); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[1].damage, Q_4_12(1.3), results[0].damage); // Striker affects slicing moves
        EXPECT_EQ(results[2].damage, results[3].damage); // Striker does not affect non-slicing moves
    }
}
