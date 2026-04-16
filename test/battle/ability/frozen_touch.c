#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Frozen Touch has a 30% chance to inflict frostbite when attacking with contact moves")
{
    PASSES_RANDOMLY(3, 10, RNG_FROZEN_TOUCH);
    GIVEN {
        ASSUME(GetMovePower(MOVE_SCRATCH) > 0);
        ASSUME(MoveMakesContact(MOVE_SCRATCH));
        PLAYER(SPECIES_BERGMITE) { Ability(ABILITY_FROZEN_TOUCH); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        ABILITY_POPUP(player, ABILITY_FROZEN_TOUCH);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_FRB, opponent);
        MESSAGE("The opposing Wobbuffet got frostbite from Bergmite's Frozen Touch!");
        STATUS_ICON(opponent, frostbite: TRUE);
    }
}

SINGLE_BATTLE_TEST("Frozen Touch only applies when using contact moves")
{
    enum Move move;

    PARAMETRIZE { move = MOVE_SCRATCH; }
    PARAMETRIZE { move = MOVE_SWIFT; }
    GIVEN {
        ASSUME(MoveMakesContact(MOVE_SCRATCH));
        ASSUME(!MoveMakesContact(MOVE_SWIFT));
        PLAYER(SPECIES_BERGMITE) { Ability(ABILITY_FROZEN_TOUCH); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, move, player);
        if (MoveMakesContact(move)) {
            ABILITY_POPUP(player, ABILITY_FROZEN_TOUCH);
            ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_FRB, opponent);
            MESSAGE("The opposing Wobbuffet was poisoned by Grimer's Poison Touch!");
            STATUS_ICON(opponent, frostbite: TRUE);
        } else {
            NONE_OF {
                ABILITY_POPUP(player, ABILITY_FROZEN_TOUCH);
                ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_FRB, opponent);
                MESSAGE("The opposing Wobbuffet got frostbite from Bergmite's Frozen Touch!");
                STATUS_ICON(opponent, frostbite: TRUE);
            }
        }
    }
}

SINGLE_BATTLE_TEST("Frozen Touch applies between multi-hit move hits")
{
    GIVEN {
        ASSUME(IsMultiHitMove(MOVE_ARM_THRUST));
        ASSUME(MoveMakesContact(MOVE_ARM_THRUST));
        ASSUME(gItemsInfo[ITEM_ASPEAR_BERRY].holdEffect == HOLD_EFFECT_CURE_FRZ);
        PLAYER(SPECIES_BERGMITE) { Ability(ABILITY_FROZEN_TOUCH); }
        OPPONENT(SPECIES_WOBBUFFET) { Item(ITEM_ASPEAR_BERRY); }
    } WHEN {
        TURN { MOVE(player, MOVE_ARM_THRUST); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ARM_THRUST, player);
        ABILITY_POPUP(player, ABILITY_FROZEN_TOUCH);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_FRB, opponent);
        MESSAGE("The opposing Wobbuffet got frostbite from Bergmite's Frozen Touch!");
        STATUS_ICON(opponent, frostbite: TRUE);
        MESSAGE("The opposing Wobbuffet's Aspear Berry cured its frostbite!");
        STATUS_ICON(opponent, frostbite: FALSE);
        ABILITY_POPUP(player, ABILITY_FROZEN_TOUCH);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_FRB, opponent);
        MESSAGE("The opposing Wobbuffet got frostbite from Bergmite's Frozen Touch!");
        STATUS_ICON(opponent, frostbite: TRUE);
    }
}

SINGLE_BATTLE_TEST("Frozen Touch activates when user has Protective Pads, but not with Punching Glove")
{
    u32 item;

    PARAMETRIZE { item = ITEM_PROTECTIVE_PADS; }
    PARAMETRIZE { item = ITEM_PUNCHING_GLOVE; }

    GIVEN {
        ASSUME(MoveMakesContact(MOVE_MACH_PUNCH));
        ASSUME(IsPunchingMove(MOVE_MACH_PUNCH));
        ASSUME(GetItemHoldEffect(ITEM_PROTECTIVE_PADS) == HOLD_EFFECT_PROTECTIVE_PADS);
        ASSUME(GetItemHoldEffect(ITEM_PUNCHING_GLOVE) == HOLD_EFFECT_PUNCHING_GLOVE);
        PLAYER(SPECIES_BERGMITE) { Ability(ABILITY_FROZEN_TOUCH); Item(item); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_MACH_PUNCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MACH_PUNCH, player);

        if (item != ITEM_PUNCHING_GLOVE) {
            ABILITY_POPUP(player, ABILITY_FROZEN_TOUCH);
            ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_FRB, opponent);
            MESSAGE("The opposing Wobbuffet got frostbite from Bergmite's Frozen Touch!");
            STATUS_ICON(opponent, frostbite: TRUE);
        } else {
            NONE_OF {
                ABILITY_POPUP(player, ABILITY_FROZEN_TOUCH);
                ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_FRB, opponent);
                MESSAGE("The opposing Wobbuffet got frostbite from Bergmite's Frozen Touch!");
                STATUS_ICON(opponent, frostbite: TRUE);
            }
        }
    }
}
