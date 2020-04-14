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
    Player(int i_attack, int i_strength, int i_defence, int i_ranged, int i_magic, int i_prayer, int i_hitpoints, int i_currentHitpoints);
    Player(int i_attack, int i_strength, int i_defence, int i_ranged, int i_magic, int i_prayer, int i_hitpoints, int i_currentHitpoints,
           POTIONS_E::Type i_attackPotion, POTIONS_E::Type i_strengthPotion, POTIONS_E::Type i_defencePotion, POTIONS_E::Type i_rangedPotion, MAGIC_POTIONS_E::Type i_magicPotion,
           ATTACK_PRAYER_E::Type i_attackPrayer, STRENGTH_PRAYER_E::Type i_strengthPrayer, DEFENCE_PRAYER_E::Type i_defencePrayer, RANGED_PRAYER_E::Type i_rangedPrayer, MAGIC_PRAYER_E::Type i_magicPrayer);

    ~Player();

    Player& operator=(Player i_obj);

    void SetStats(PLAYER_STATS_T i_stats);
    void SetStats(int i_attack, int i_strength, int i_defence, int i_ranged, int i_magic, int i_prayer, int i_hitpoints);

    void SetPotions(POTIONS_T i_potions);
    void SetPotions(POTIONS_E::Type i_attackPotion, POTIONS_E::Type i_strengthPotion, POTIONS_E::Type i_defencePotion, POTIONS_E::Type i_rangedPotion, MAGIC_POTIONS_E::Type i_magicPotion);

    void SetPrayer(PRAYER_T i_prayer);
    void SetPrayer(ATTACK_PRAYER_E::Type i_attackPrayer, STRENGTH_PRAYER_E::Type i_strengthPrayer, DEFENCE_PRAYER_E::Type i_defencePrayer, RANGED_PRAYER_E::Type i_rangedPrayer, MAGIC_PRAYER_E::Type i_magicPrayer);

    void SetAttack(int i_attack);
    void SetStrength(int i_strength);
    void SetDefence(int i_defence);
    void SetRanged(int i_ranged);
    void SetMagic(int i_magic);
    void SetPrayer(int i_prayer);
    void SetHitpoints(int i_hitpoints);
    void SetCurrentHitpoints(int i_currentHitpoints);

    void SetAttackPotion(POTIONS_E::Type i_attackPotion);
    void SetStrengthPotion(POTIONS_E::Type i_strengthPotion);
    void SetDefencePotion(POTIONS_E::Type i_defencePotion);
    void SetRangedPotion(POTIONS_E::Type i_rangedPotion);
    void SetMagicPotion(MAGIC_POTIONS_E::Type i_magicPotion);

    void SetAttackPrayer(ATTACK_PRAYER_E::Type i_attackPrayer);
    void SetStrengthPrayer(STRENGTH_PRAYER_E::Type i_strengthPrayer);
    void SetDefencePrayer(DEFENCE_PRAYER_E::Type i_defencePrayer);
    void SetRangedPrayer(RANGED_PRAYER_E::Type i_rangedPrayer);
    void SetMagicPrayer(MAGIC_PRAYER_E::Type i_magicPrayer);
    
    PLAYER_STATS_T Stats() const;
    POTIONS_T Potions() const;
    PRAYER_T Prayer() const;


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