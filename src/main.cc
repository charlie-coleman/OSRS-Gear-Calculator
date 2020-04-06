#include "Equipment.h"
#include "Player.h"
#include "DataFetcher.h"

#include <iostream>
#include <curl/curl.h>

int main(int argc, char** argv)
{
  Player p(99, 99, 99, 99, 99, 99, 99,
           POTIONS_E::SUPER_POTION, POTIONS_E::SUPER_POTION, POTIONS_E::SUPER_POTION, POTIONS_E::REGULAR_POTION, MAGIC_POTIONS_E::NONE,
           ATTACK_PRAYER_E::PIETY, STRENGTH_PRAYER_E::PIETY, DEFENSE_PRAYER_E::PIETY, RANGED_PRAYER_E::RIGOUR, MAGIC_PRAYER_E::AUGURY);

  std::cout << p.Stats().Attack << "\t=>\t" << p.EffectiveStats().Attack << std::endl;
  std::cout << p.Stats().Strength << "\t=>\t" << p.EffectiveStats().Strength << std::endl;
  std::cout << p.Stats().Defense << "\t=>\t" << p.EffectiveStats().Defense << std::endl;
  std::cout << p.Stats().Ranged << "\t=>\t" << p.EffectiveStats().Ranged << std::endl;
  std::cout << p.Stats().RangedStrength << "\t=>\t" << p.EffectiveStats().RangedStrength << std::endl;
  std::cout << p.Stats().Magic << "\t=>\t" << p.EffectiveStats().Magic << std::endl;

  DataFetcher df;

  std::vector<Equipment> equip = df.FetchEquipment();

  for (auto it = equip.begin(); it != equip.end(); ++it)
  {
    std::cout << *it << std::endl;
  }
}