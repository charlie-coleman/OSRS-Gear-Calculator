#ifndef ENUMS_H
#define ENUMS_H

#include <vector>
#include <string>

struct POTIONS_E
{
  enum Type
  {
    NONE = 0,
    REGULAR_POTION = 1,
    SUPER_POTION = 2,
    OVERLOAD_MINUS = 3,
    OVERLOAD = 4,
    OVERLOAD_PLUS = 5,
    SIZE_OF_POTIONS_E = 6
  };

  static std::vector<std::string> Names;
};

struct MAGIC_POTIONS_E
{
  enum Type
  {
    NONE = 0,
    REGULAR_POTION = 1,
    SUPER_POTION = 2,
    IMBUED_HEART = 3,
    OVERLOAD_MINUS = 4,
    OVERLOAD = 5,
    OVERLOAD_PLUS = 6,
    SIZE_OF_MAGIC_POTIONS_E = 7
  };

  static std::vector<std::string> Names;
};

struct ATTACK_PRAYER_E
{
  enum Type
  {
    NONE = 0,
    CLARITY_OF_THOUGHT = 1,
    IMPROVED_REFLEXES = 2,
    INCREDIBLE_REFLEXES = 3,
    CHIVALRY = 4,
    PIETY = 5,
    SIZE_OF_ATTACK_PRAYER_E = 6
  };

  static std::vector<std::string> Names;
};

struct STRENGTH_PRAYER_E
{
  enum Type
  {
    NONE = 0,
    BURST_OF_STRENGTH = 1,
    SUPERHUMAN_STRENGTH = 2,
    ULTIMATE_STRENGTH = 3,
    CHIVALRY = 4,
    PIETY = 5,
    SIZE_OF_STRENGTH_PRAYER_E = 6
  };

  static std::vector<std::string> Names;
};

struct DEFENCE_PRAYER_E
{
  enum Type
  {
    NONE = 0,
    THICK_SKIN = 1,
    ROCK_SKIN = 2,
    STEEL_SKIN = 3,
    CHIVALRY = 4,
    PIETY = 5,
    SIZE_OF_DEFENCE_PRAYER_E = 6
  };

  static std::vector<std::string> Names;
};

struct RANGED_PRAYER_E
{
  enum Type
  {
    NONE = 0,
    SHARP_EYE = 1,
    HAWK_EYE = 2,
    EAGLE_EYE = 3,
    RIGOUR = 4,
    SIZE_OF_RANGED_PRAYER_E = 5
  };

  static std::vector<std::string> Names;
};

struct MAGIC_PRAYER_E
{
  enum Type
  {
    NONE = 0,
    MYSTIC_WILL = 1,
    MYSTIC_LORE = 2,
    MYSTIC_MIGHT = 3,
    AUGURY = 4,
    SIZE_OF_MAGIC_PRAYER_E = 5
  };

  static std::vector<std::string> Names;
};

struct COMBAT_STYLE_E
{
  enum Type
  {
    MELEE = 0,
    RANGED = 1,
    MAGIC = 2,
    SIZE_OF_COMBAT_STYLE = 3
  };
};

struct MELEE_DAMAGE_TYPE_E
{
  enum Type
  {
    SLASH = 0,
    STAB = 1,
    CRUSH = 2,
    SIZE_OF_MELEE_DAMAGE_TYPE = 3
  };
};

struct DB_TYPE_E
{
  enum Type
  {
    AMMO = 0,
    BODY = 1,
    CAPE = 2,
    FEET = 3,
    HAND = 4,
    HEAD = 5,
    LEGS = 6,
    NECK = 7,
    RING = 8,
    SHIELD = 9,
    WEAPON = 10,
    MONSTER = 11,
    SIZE_OF_DB_TYPE_E = 12
  };
};

#endif