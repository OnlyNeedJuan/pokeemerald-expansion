#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Cacophony increases the power of sound moves by 30%", s16 damage)
{
    u32 move;
    enum Ability ability;
    PARAMETRIZE { move = MOVE_HYPER_VOICE; ability = ABILITY_CACOPHONY; }
    PARAMETRIZE { move = MOVE_HYPER_VOICE; ability = ABILITY_SCRAPPY; }
    PARAMETRIZE { move = MOVE_STRENGTH; ability = ABILITY_CACOPHONY; }
    PARAMETRIZE { move = MOVE_STRENGTH; ability = ABILITY_SCRAPPY; }

    GIVEN {
        ASSUME(IsSoundMove(MOVE_HYPER_VOICE));
        ASSUME(!IsSoundMove(MOVE_STRENGTH));
        PLAYER(SPECIES_EXPLOUD) { Ability(ability); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[1].damage, Q_4_12(1.3), results[0].damage); // Cacophony affects sound moves
        EXPECT_EQ(results[2].damage, results[3].damage); // Cacophony does not affect non-sound moves
    }
}

SINGLE_BATTLE_TEST("Cacophony halves damage from sound moves", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_SCRAPPY; }
    PARAMETRIZE { ability = ABILITY_CACOPHONY; }
    GIVEN {
        ASSUME(IsSoundMove(MOVE_HYPER_VOICE));
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_EXPLOUD) { Ability(ability); }
    } WHEN {
        TURN { MOVE(player, MOVE_HYPER_VOICE); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(0.5), results[1].damage); // Cacophony reduces the damage of incoming sound moves by 50%
    }
}