#include "constants/abilities.h"
#include "species_info/shared_dex_text.h"

// Macros for ease of use.

#define EVOLUTION(...) (const struct Evolution[]) { __VA_ARGS__, { EVOLUTIONS_END }, }

#if P_FOOTPRINTS
#define FOOTPRINT(sprite) .footprint = gMonFootprint_## sprite,
#else
#define FOOTPRINT(sprite)
#endif

// Maximum value for a female Pokémon is 254 (MON_FEMALE) which is 100% female.
// 255 (MON_GENDERLESS) is reserved for genderless Pokémon.
#define PERCENT_FEMALE(percent) min(254, ((percent * 255) / 100))

#define MON_TYPES(type1, ...) { type1, DEFAULT(type1, __VA_ARGS__) }
#define MON_EGG_GROUPS(group1, ...) { group1, DEFAULT(group1, __VA_ARGS__) }

#define FLIP    0
#define NO_FLIP 1

const struct SpeciesInfo gSpeciesInfo[] =
{
    [SPECIES_NONE] =
    {
        .speciesName = _("??????????"),
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_NONE,
        .categoryName = _("Unknown"),
        .height = 0,
        .weight = 0,
        .description = COMPOUND_STRING(
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_CircledQuestionMark,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 12,
        .frontAnimFrames = sAnims_None,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_CircledQuestionMark,
        .backPicSize = MON_COORDS_SIZE(40, 40),
        .backPicYOffset = 12,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_CircledQuestionMark,
        .shinyPalette = gMonShinyPalette_CircledQuestionMark,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        .levelUpLearnset = sNoneLevelUpLearnset,
        .teachableLearnset = sNoneTeachableLearnset,
    },

    #include "species_info/gen_1_families.h"
    #include "species_info/gen_2_families.h"
    #include "species_info/gen_3_families.h"
    #include "species_info/gen_4_families.h"
    #include "species_info/gen_5_families.h"
    #include "species_info/gen_6_families.h"
    #include "species_info/gen_7_families.h"
    #include "species_info/gen_8_families.h"
    #include "species_info/gen_9_families.h"

    [SPECIES_EGG] =
    {
        .frontPic = gMonFrontPic_Egg,
        .frontPicSize = MON_COORDS_SIZE(24, 24),
        .frontPicYOffset = 20,
        .backPic = gMonFrontPic_Egg,
        .backPicSize = MON_COORDS_SIZE(24, 24),
        .backPicYOffset = 20,
        .palette = gMonPalette_Egg,
        .shinyPalette = gMonPalette_Egg,
        .iconSprite = gMonIcon_Egg,
        .iconPalIndex = 1,
    },

    /* You may add any custom species below this point based on the following structure: */
#if P_FAMILY_SANDY_SHOCKS
    [SPECIES_SANDY_SHOCKS_PRE_EVO] =
    {
        .baseHP        = 50,
        .baseAttack    = 36,
        .baseDefense   = 72,
        .baseSpeed     = 71,
        .baseSpAttack  = 96,
        .baseSpDefense = 55,
        .types = { TYPE_GROUND, TYPE_ELECTRIC },
        .catchRate = 190,
        .expYield = 65,
        .evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = { EGG_GROUP_MINERAL, EGG_GROUP_MINERAL },
        .abilities = { ABILITY_STEELWORKER, ABILITY_NONE, ABILITY_MAGNET_PULL },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("Magnetin"),
        .cryId = CRY_MAGNEMITE,
        .natDexNum = NATIONAL_DEX_NONE,
        .categoryName = _("Magnet"),
        .height = 64,
        .weight = 66,
        .description = COMPOUND_STRING(
            "When startled this pokémon tries to run.\n"
            "and hide. It leaves small piles of iron\n"
            "sand as it goes\n"
            ),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        FRONT_PIC(SandyShocksPreEvo, 64, 64),
        .frontPicYOffset = 12,
        .frontAnimFrames = sAnims_SandyShocksPreEvo,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 0,
        BACK_PIC(SandyShocksPreEvo, 64, 64),
        .backPicYOffset = 15,
        .backAnimId = BACK_ANIM_TRIANGLE_DOWN,
        PALETTES(SandyShocks),
        ICON(SandyShocksPreEvo, 0),
        //.footprint = gMonFootprint_SandyShocksPreEvo,
        LEARNSETS(SandyShocks),
        .evolutions = EVOLUTION({EVO_LEVEL, 35, SPECIES_SANDY_SHOCKS}),
    },
#endif //P_FAMILY_SANDY_SHOCKS

#if P_FAMILY_MOLTRES
    [SPECIES_MOLTRES_REGIONAL] =
    {
        .baseHP        = 90,
        .baseAttack    = 100,
        .baseDefense   = 95,
        .baseSpeed     = 85,
        .baseSpAttack  = 85,
        .baseSpDefense = 125,
        .types = { TYPE_POISON, TYPE_FLYING },
        .catchRate = 3,
        .expYield = 290,
        .evYield_SpDefense = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 35,
        .growthRate = GROWTH_SLOW,
        .eggGroups = { EGG_GROUP_NO_EGGS_DISCOVERED, EGG_GROUP_NO_EGGS_DISCOVERED },
        .abilities = { ABILITY_MERCILESS, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_PURPLE,
        .speciesName = _("Moltres"),
        .cryId = CRY_MOLTRES,
        .natDexNum = NATIONAL_DEX_MOLTRES,
        .categoryName = _("Spiteful"),
        .height = 20,
        .weight = 560,
        .description = COMPOUND_STRING(
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 270,
        .pokemonOffset = 0,
        .trainerScale = 387,
        .trainerOffset = 8,
        FRONT_PIC(MoltresRegional, 64, 64),
        .frontPicYOffset = 1,
        .frontAnimFrames = sAnims_MoltresRegional,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE_SLOW,
        .enemyMonElevation = 0,
        BACK_PIC(MoltresRegional, 64, 64),
        .backPicYOffset = 5,
        .backAnimId = BACK_ANIM_NONE,
        PALETTES(MoltresRegional),
        ICON(MoltresRegional, 5),
        .footprint = gMonFootprint_MoltresRegional,
        LEARNSETS(MoltresRegional),
        .formSpeciesIdTable = sMoltresFormSpeciesIdTable,
    },
#endif //P_FAMILY_MOLTRES

#if P_FAMILY_SWABLU
    [SPECIES_AZUTRICE] =
    {
        .baseHP        = 80,
        .baseAttack    = 95,
        .baseDefense   = 95,
        .baseSpeed     = 70,
        .baseSpAttack  = 95,
        .baseSpDefense = 105,
        .types = { TYPE_DRAGON, TYPE_FAIRY },
        .catchRate = 45,
        .expYield = 243,
        .evYield_Defense = 1,
        .evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_ERRATIC,
        .eggGroups = { EGG_GROUP_FLYING, EGG_GROUP_DRAGON },
        .bodyColor = BODY_COLOR_BLUE,
        .abilities = { ABILITY_PIXILATE, ABILITY_NONE, ABILITY_BERSERK },
        .speciesName = _("Azutrice"),
        .cryId = CRY_ALTARIA_MEGA,
        .categoryName = _("Fluffy Bird"),
        .height = 15,
        .weight = 206,
        .description = COMPOUND_STRING(
            "It sings with a voice that is even more\n"
            "beautiful than before it Mega Evolved.\n"
            "Its feathers became larger for protection\n"
            "and glimmer with an iridescent sheen."),
        .pokemonScale = 327,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        FRONT_PIC(Azutrice, 64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_Azutrice,
        .frontAnimId = ANIM_GROW,
        .enemyMonElevation = 6,
        BACK_PIC(Azutrice, 64, 48),
        .backPicYOffset = 10,
        .backAnimId = BACK_ANIM_CONVEX_DOUBLE_ARC,
        PALETTES(Azutrice),
        ICON(Azutrice, 0),
        .footprint = gMonFootprint_Azutrice,
        LEARNSETS(Altaria),
    },
#endif //P_FAMILY_SWABLU

    /*
    [SPECIES_NONE] =
    {
        .baseHP        = 1,
        .baseAttack    = 1,
        .baseDefense   = 1,
        .baseSpeed     = 1,
        .baseSpAttack  = 1,
        .baseSpDefense = 1,
        .types = MON_TYPES(TYPE_MYSTERY),
        .catchRate = 255,
        .expYield = 67,
        .evYield_HP = 1,
        .evYield_Defense = 1,
        .evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_NONE, ABILITY_CURSED_BODY, ABILITY_DAMP },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("??????????"),
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_NONE,
        .categoryName = _("Unknown"),
        .height = 0,
        .weight = 0,
        .description = COMPOUND_STRING(
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_CircledQuestionMark,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        //.frontPicFemale = gMonFrontPic_CircledQuestionMark,
        //.frontPicSizeFemale = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_None,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_CircledQuestionMark,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        //.backPicFemale = gMonBackPic_CircledQuestionMarkF,
        //.backPicSizeFemale = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_CircledQuestionMark,
        .shinyPalette = gMonShinyPalette_CircledQuestionMark,
        //.paletteFemale = gMonPalette_CircledQuestionMarkF,
        .shinyPaletteFemale = gMonShinyPalette_CircledQuestionMarkF,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //.iconSpriteFemale = gMonIcon_QuestionMarkF,
        //.iconPalIndexFemale = 1,
        //FOOTPRINT(None)
        .levelUpLearnset = sNoneLevelUpLearnset,
        .teachableLearnset = sNoneTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE},
                                {EVO_ITEM, ITEM_MOOMOO_MILK, SPECIES_NONE}),
        //.formSpeciesIdTable = sNoneFormSpeciesIdTable,
        //.formChangeTable = sNoneFormChangeTable,
        .allPerfectIVs = TRUE,
    },
    */
};
