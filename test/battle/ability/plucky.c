#include "global.h"
#include "test/battle.h"

DOUBLE_BATTLE_TEST("Plucky sharply raises player's Speed after Intimidate")
{
    enum Ability abilityLeft, abilityRight;

    PARAMETRIZE { abilityLeft = ABILITY_STRIKER; abilityRight = ABILITY_STRIKER; }
    PARAMETRIZE { abilityLeft = ABILITY_STRIKER; abilityRight = ABILITY_PLUCKY; }
    PARAMETRIZE { abilityLeft = ABILITY_PLUCKY; abilityRight = ABILITY_STRIKER; }
    PARAMETRIZE { abilityLeft = ABILITY_PLUCKY; abilityRight = ABILITY_PLUCKY; }

    GIVEN {
        PLAYER(SPECIES_COMBUSKEN) { Ability(abilityLeft); }
        PLAYER(SPECIES_BLAZIKEN) { Ability(abilityRight); }
        OPPONENT(SPECIES_GYARADOS) { Ability(ABILITY_INTIMIDATE); }
        OPPONENT(SPECIES_ARBOK) { Ability(ABILITY_INTIMIDATE); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_SCRATCH, target:opponentLeft); MOVE(playerRight, MOVE_SCRATCH, target:opponentRight); }
    } SCENE {
        //1st mon Intimidate
        ABILITY_POPUP(opponentLeft, ABILITY_INTIMIDATE);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, playerLeft);
        MESSAGE("The opposing Gyarados's Intimidate cuts Combusken's Attack!");
        if (abilityLeft == ABILITY_PLUCKY) {
            ABILITY_POPUP(playerLeft, ABILITY_PLUCKY);
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, playerLeft);
            MESSAGE("Combusken's Speed sharply rose!");
        }
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, playerRight);
        MESSAGE("The opposing Gyarados's Intimidate cuts Blaziken's Attack!");
        if (abilityRight == ABILITY_PLUCKY) {
            ABILITY_POPUP(playerRight, ABILITY_PLUCKY);
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, playerRight);
            MESSAGE("Blaziken's Speed sharply rose!");
        }

        //2nd mon Intimidate
        ABILITY_POPUP(opponentRight, ABILITY_INTIMIDATE);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, playerLeft);
        MESSAGE("The opposing Arbok's Intimidate cuts Combusken's Attack!");
        if (abilityLeft == ABILITY_PLUCKY) {
            ABILITY_POPUP(playerLeft, ABILITY_PLUCKY);
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, playerLeft);
            MESSAGE("Combusken's Speed sharply rose!");
        }
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, playerRight);
        MESSAGE("The opposing Arbok's Intimidate cuts Blaziken's Attack!");
        if (abilityRight == ABILITY_PLUCKY) {
            ABILITY_POPUP(playerRight, ABILITY_PLUCKY);
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, playerRight);
            MESSAGE("Blaziken's Speed sharply rose!");
        }
    } THEN {
        // -2 from Intimidates and +4 from Plucky gets +2 total
        EXPECT_EQ(playerLeft->statStages[STAT_ATK], (abilityLeft == ABILITY_PLUCKY) ? DEFAULT_STAT_STAGE + 2 : DEFAULT_STAT_STAGE - 2);
        EXPECT_EQ(playerRight->statStages[STAT_ATK], (abilityRight == ABILITY_PLUCKY) ? DEFAULT_STAT_STAGE + 2 : DEFAULT_STAT_STAGE - 2);
    }
}

// Same as above, but for opponent.
DOUBLE_BATTLE_TEST("Plucky sharply raises opponent's Speed after Intimidate")
{
    enum Ability abilityLeft, abilityRight;

    PARAMETRIZE { abilityLeft = ABILITY_STRIKER; abilityRight = ABILITY_STRIKER; }
    PARAMETRIZE { abilityLeft = ABILITY_STRIKER; abilityRight = ABILITY_PLUCKY; }
    PARAMETRIZE { abilityLeft = ABILITY_PLUCKY; abilityRight = ABILITY_STRIKER; }
    PARAMETRIZE { abilityLeft = ABILITY_PLUCKY; abilityRight = ABILITY_PLUCKY; }

    GIVEN {
        OPPONENT(SPECIES_COMBUSKEN) { Ability(abilityLeft); }
        OPPONENT(SPECIES_BLAZIKEN) { Ability(abilityRight); }
        PLAYER(SPECIES_GYARADOS) { Ability(ABILITY_INTIMIDATE); }
        PLAYER(SPECIES_ARBOK) { Ability(ABILITY_INTIMIDATE); }
    } WHEN {
        TURN { MOVE(opponentLeft, MOVE_SCRATCH, target:playerLeft); MOVE(opponentRight, MOVE_SCRATCH, target:playerRight); }
    } SCENE {
        //1st mon Intimidate
        ABILITY_POPUP(playerLeft, ABILITY_INTIMIDATE);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponentLeft);
        MESSAGE("Gyarados's Intimidate cuts the opposing Combusken's Attack!");
        if (abilityLeft == ABILITY_PLUCKY) {
            ABILITY_POPUP(opponentLeft, ABILITY_PLUCKY);
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponentLeft);
            MESSAGE("The opposing Combusken's Speed sharply rose!");
        }
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponentRight);
        MESSAGE("Gyarados's Intimidate cuts the opposing Blaziken's Attack!");
        if (abilityRight == ABILITY_PLUCKY) {
            ABILITY_POPUP(opponentRight, ABILITY_PLUCKY);
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponentRight);
            MESSAGE("The opposing Blaziken's Speed sharply rose!");
        }

        //2nd mon Intimidate
        ABILITY_POPUP(playerRight, ABILITY_INTIMIDATE);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponentLeft);
        MESSAGE("Arbok's Intimidate cuts the opposing Combusken's Attack!");
        if (abilityLeft == ABILITY_PLUCKY) {
            ABILITY_POPUP(opponentLeft, ABILITY_PLUCKY);
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponentLeft);
            MESSAGE("The opposing Combusken's Speed sharply rose!");
        }
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponentRight);
        MESSAGE("Arbok's Intimidate cuts the opposing Blaziken's Attack!");
        if (abilityRight == ABILITY_PLUCKY) {
            ABILITY_POPUP(opponentRight, ABILITY_PLUCKY);
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponentRight);
            MESSAGE("The opposing Blaziken's Speed sharply rose!");
        }
    } THEN {
        // -2 from Intimidates and +4 from Plucky gets +2 total
        EXPECT_EQ(opponentLeft->statStages[STAT_ATK], (abilityLeft == ABILITY_PLUCKY) ? DEFAULT_STAT_STAGE + 2 : DEFAULT_STAT_STAGE - 2);
        EXPECT_EQ(opponentRight->statStages[STAT_ATK], (abilityRight == ABILITY_PLUCKY) ? DEFAULT_STAT_STAGE + 2 : DEFAULT_STAT_STAGE - 2);
    }
}

SINGLE_BATTLE_TEST("Plucky activates after Sticky Web lowers Speed")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_COMBUSKEN) { Ability(ABILITY_PLUCKY); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_STICKY_WEB); }
        TURN { SWITCH(player, 1); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_STICKY_WEB, opponent);
        // Switch-in - Sticky Web activates
        SEND_IN_MESSAGE("Combusken");
        MESSAGE("Combusken was caught in a sticky web!");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        MESSAGE("Combusken's Speed fell!");
        // Defiant activates
        ABILITY_POPUP(player, ABILITY_PLUCKY);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        MESSAGE("Combusken's Speed sharply rose!");
    }
}

SINGLE_BATTLE_TEST("Plucky doesn't activate after Sticky Web lowers Speed if Court Changed (Gen8)")
{
    GIVEN {
        WITH_CONFIG(B_DEFIANT_STICKY_WEB, GEN_8);
        ASSUME(GetMoveEffect(MOVE_GROWL) == EFFECT_ATTACK_DOWN);
        ASSUME(GetMoveEffect(MOVE_STICKY_WEB) == EFFECT_STICKY_WEB);
        ASSUME(GetMoveEffect(MOVE_COURT_CHANGE) == EFFECT_COURT_CHANGE);
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_COMBUSKEN) { Ability(ABILITY_PLUCKY); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_STICKY_WEB); MOVE(opponent, MOVE_COURT_CHANGE); }
        TURN { SWITCH(player, 1); MOVE(opponent, MOVE_GROWL); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_STICKY_WEB, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_COURT_CHANGE, opponent);
        // Switch-in - Sticky Web activates
        SEND_IN_MESSAGE("Combusken");
        MESSAGE("Combusken was caught in a sticky web!");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        MESSAGE("Combusken's Speed fell!");
        // Defiant doesn't activate
        NONE_OF {
            ABILITY_POPUP(player, ABILITY_PLUCKY);
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
            MESSAGE("Combusken's Speed sharply rose!");
        }
        // Defiant triggers correctly after Sticky Web
        ANIMATION(ANIM_TYPE_MOVE, MOVE_GROWL, opponent);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        MESSAGE("Combusken's Attack fell!");
        ABILITY_POPUP(player, ABILITY_PLUCKY);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        MESSAGE("Combusken's Speed sharply rose!");
    }
}

SINGLE_BATTLE_TEST("Plucky activates after Sticky Web lowers Speed if Court Changed (Gen9)")
{
    GIVEN {
        WITH_CONFIG(B_DEFIANT_STICKY_WEB, GEN_9);
        ASSUME(GetMoveEffect(MOVE_GROWL) == EFFECT_ATTACK_DOWN);
        ASSUME(GetMoveEffect(MOVE_STICKY_WEB) == EFFECT_STICKY_WEB);
        ASSUME(GetMoveEffect(MOVE_COURT_CHANGE) == EFFECT_COURT_CHANGE);
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_COMBUSKEN) { Ability(ABILITY_PLUCKY); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_STICKY_WEB); MOVE(opponent, MOVE_COURT_CHANGE); }
        TURN { SWITCH(player, 1); MOVE(opponent, MOVE_GROWL); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_STICKY_WEB, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_COURT_CHANGE, opponent);
        // Switch-in - Sticky Web activates
        SEND_IN_MESSAGE("Combusken");
        MESSAGE("Combusken was caught in a sticky web!");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        MESSAGE("Combusken's Speed fell!");
        ABILITY_POPUP(player, ABILITY_PLUCKY);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        MESSAGE("Combusken's Speed sharply rose!");
        // Defiant triggers correctly after Sticky Web
        ANIMATION(ANIM_TYPE_MOVE, MOVE_GROWL, opponent);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        MESSAGE("Combusken's Attack fell!");
        ABILITY_POPUP(player, ABILITY_PLUCKY);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        MESSAGE("Combusken's Speed sharply rose!");
    }
}

DOUBLE_BATTLE_TEST("Plucky is activated by Cotton Down for non-ally Pokémon")
{
    GIVEN {
        PLAYER(SPECIES_COMBUSKEN) { Ability(ABILITY_PLUCKY); }
        PLAYER(SPECIES_COMBUSKEN) { Ability(ABILITY_PLUCKY); }
        OPPONENT(SPECIES_ELDEGOSS) { Ability(ABILITY_COTTON_DOWN); }
        OPPONENT(SPECIES_COMBUSKEN) { Ability(ABILITY_PLUCKY); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_SCRATCH, target: opponentLeft); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, playerLeft);
        ABILITY_POPUP(opponentLeft, ABILITY_COTTON_DOWN);

        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, playerLeft);
        MESSAGE("Combusken's Speed fell!");
        ABILITY_POPUP(playerLeft, ABILITY_PLUCKY);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, playerLeft);
        MESSAGE("Combusken's Speed sharply rose!");

        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, playerRight);
        MESSAGE("Combusken's Speed fell!");
        ABILITY_POPUP(playerRight, ABILITY_PLUCKY);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, playerRight);
        MESSAGE("Combusken's Speed sharply rose!");

        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponentRight);
        MESSAGE("The opposing Combusken's Speed fell!");
    } THEN {
        EXPECT_EQ(playerLeft->statStages[STAT_SPEED], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(playerRight->statStages[STAT_SPEED], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(opponentRight->statStages[STAT_SPEED], DEFAULT_STAT_STAGE + 1);
    }
}x

SINGLE_BATTLE_TEST("Plucky activates before White Herb")
{
    enum Move move;

    PARAMETRIZE { move = MOVE_LEER; }
    PARAMETRIZE { move = MOVE_GROWL; }

    GIVEN {
        PLAYER(SPECIES_COMBUSKEN) { Ability(ABILITY_PLUCKY); Item(ITEM_WHITE_HERB); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, move); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, move, opponent);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);

        ABILITY_POPUP(player, ABILITY_PLUCKY);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        MESSAGE("Combusken's Speed sharply rose!");

        if (move == MOVE_LEER) {
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, player);
            MESSAGE("Combusken returned its stats to normal using its White Herb!");
        } else {
            NONE_OF {
                ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, player);
                MESSAGE("Combusken returned its stats to normal using its White Herb!");
            }
        }
    } THEN {
        if (move == MOVE_LEER) {
            EXPECT_EQ(player->statStages[STAT_DEF], DEFAULT_STAT_STAGE);
            EXPECT_EQ(player->statStages[STAT_SPEED], DEFAULT_STAT_STAGE + 2);
        } else {
            EXPECT_EQ(player->statStages[STAT_SPEED], DEFAULT_STAT_STAGE + 1);
        }
    }
}

SINGLE_BATTLE_TEST("Plucky activates for each stat that is lowered")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_TICKLE) == EFFECT_TICKLE);
        PLAYER(SPECIES_COMBUSKEN) { Ability(ABILITY_PLUCKY); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_TICKLE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TICKLE, opponent);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        MESSAGE("Combusken's Attack fell!");
        ABILITY_POPUP(player, ABILITY_PLUCKY);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        MESSAGE("Combusken's Speed sharply rose!");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        MESSAGE("Combusken's Defense fell!");
        ABILITY_POPUP(player, ABILITY_PLUCKY);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        MESSAGE("Combusken's Speed sharply rose!");

    } THEN {
        EXPECT_EQ(player->statStages[STAT_SPEED], DEFAULT_STAT_STAGE + 4);
    }
}

TO_DO_BATTLE_TEST("Plucky doesn't activate if the Pokémon lowers it's own stats & Plucky doesn't display ability popup when already at Maximum Speed test")

TO_DO_BATTLE_TEST ("Plucky doesn't display ability popup when already at Maximum Speed test")