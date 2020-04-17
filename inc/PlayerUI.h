#ifndef PLAYERUI_H
#define PLAYERUI_H

#include <gtkmm.h>
#include "Player.h"
#include "Monster.h"
#include "Database.h"
#include "Setup.h"
#include "SearchableComboBox.h"
#include "LevelEntry.h"

class PlayerUI : public Gtk::Box
{
public:
  PlayerUI(std::string i_title, Database *i_db, Setup **i_setups, int i_setupCount);
  virtual ~PlayerUI();

  Player GetPlayer() const;
  Monster GetMonster() const;

  sigc::signal<void> signal_all_setups_changed();

protected:
  Database *m_db;
  Setup **m_setups;
  int m_setupCount;

  Player m_player;

  Gtk::Grid m_playerGrid, m_monsterGrid;

  Gtk::Label m_playerTitle, m_monsterTitle, m_levelHeader, m_potionHeader, m_prayerHeader;

  LevelEntry *m_attackEntry,
             *m_strengthEntry,
             *m_defenceEntry,
             *m_rangedEntry,
             *m_magicEntry,
             *m_prayerEntry,
             *m_hitpointsEntry,
             *m_currentHitpointsEntry;

  SearchableComboBox<Monster> *m_monsterCombo;

  void on_attack_changed(int i_level),
       on_strength_changed(int i_level),
       on_defence_changed(int i_level),
       on_ranged_changed(int i_level),
       on_magic_changed(int i_level),
       on_prayer_changed(int i_level),
       on_hitpoints_changed(int i_level),
       on_current_hp_changed(int i_level),
       attack_potion_changed(int i_potion),
       strength_potion_changed(int i_potion),
       defence_potion_changed(int i_potion),
       ranged_potion_changed(int i_potion),
       magic_potion_changed(int i_potion),
       attack_prayer_changed(int i_prayer),
       strength_prayer_changed(int i_prayer),
       defence_prayer_changed(int i_prayer),
       ranged_prayer_changed(int i_prayer),
       magic_prayer_changed(int i_prayer);

  void on_monster_changed();

  sigc::signal<void> m_signal_all_setups_changed;

  void UpdateSetupPlayer();
  void InitializeEntries();
  void InitializeExtras();
};

#endif