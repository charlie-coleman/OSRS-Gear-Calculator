#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"
#include <ostream>

class Player
{
  public:
    Player();
    Player(PLAYER_STATS_T i_stats);
    Player(PLAYER_STATS_T i_stats, POTIONS_T i_potions, PRAYER_T i_prayer);
    Player(int i_attack, int i_strength, int i_defence, int i_ranged, int i_magic, int i_prayer, int i_hitpoints);
    Player(int i_attack, int i_strength, int i_defence, int i_ranged, int i_magic, int i_prayer, int i_hitpoints,
           POTIONS_E::Type i_attackPotion, POTIONS_E::Type i_strengthPotion, POTIONS_E::Type i_defencePotion, POTIONS_E::Type i_rangedPotion, MAGIC_POTIONS_E::Type i_magicPotion,
           ATTACK_PRAYER_E::Type i_attackPrayer, STRENGTH_PRAYER_E::Type i_strengthPrayer, DEFENCE_PRAYER_E::Type i_defencePrayer, RANGED_PRAYER_E::Type i_rangedPrayer, MAGIC_PRAYER_E::Type i_magicPrayer);

    ~Player();

    void SetStats(PLAYER_STATS_T i_stats);
    void SetStats(int i_attack, int i_strength, int i_defence, int i_ranged, int i_magic, int i_prayer, int i_hitpoints);

    void SetPotions(POTIONS_T i_potions);
    void SetPotions(POTIONS_E::Type i_attackPotion, POTIONS_E::Type i_strengthPotion, POTIONS_E::Type i_defencePotion, POTIONS_E::Type i_rangedPotion, MAGIC_POTIONS_E::Type i_magicPotion);

    void SetPrayer(PRAYER_T i_prayer);
    void SetPrayer(ATTACK_PRAYER_E::Type i_attackPrayer, STRENGTH_PRAYER_E::Type i_strengthPrayer, DEFENCE_PRAYER_E::Type i_defencePrayer, RANGED_PRAYER_E::Type i_rangedPrayer, MAGIC_PRAYER_E::Type i_magicPrayer);

    const PLAYER_STATS_T& Stats() const;
    const POTIONS_T& Potions() const;
    const PRAYER_T& Prayer() const;


    friend std::ostream &operator<<(std::ostream &os, const Player& obj)
    {
      os << "Stats: " << obj.Stats().Attack << "/" << obj.Stats().Strength << "/" << obj.Stats().Defence << "/" << obj.Stats().Ranged << "/" << obj.Stats().Magic << "/" << obj.Stats().Prayer << "/" << obj.Stats().Hitpoints;

      return os;
    }

  private:
    PLAYER_STATS_T m_stats;
    POTIONS_T m_potions;
    PRAYER_T m_prayer;
};

#endif