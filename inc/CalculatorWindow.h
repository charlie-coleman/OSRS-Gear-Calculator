#ifndef CALCULATOR_APP_WINDOW_H
#define CALCULATOR_APP_WINDOW_H

#include "Setup.h"
#include "Database.h"
#include "SearchableComboBox.h"

#include <gtkmm.h>

class CalculatorWindow : public Gtk::Window
{
public:
  CalculatorWindow();
  virtual ~CalculatorWindow();

protected:
  void InitializeLabels();
  void InitializeComboBoxes();
  void InitializeSetup();

  Setup m_setup;
  Database m_db;
  Player m_player;

  // Player stats entry;
  Gtk::Label m_attackLabel,
             m_strengthLabel,
             m_defenceLabel,
             m_rangedLabel,
             m_magicLabel,
             m_prayerLabel,
             m_hitpointsLabel;

  Gtk::Entry m_attackEntry,
             m_strengthEntry,
             m_defenceEntry,
             m_rangedEntry,
             m_magicEntry,
             m_prayerEntry,
             m_hitpointsEntry;
             
  Gtk::Box m_container,
           m_playerBox,
           m_gearBox;

  SearchableComboBox<Equipment> *m_ammoCombo,
                                *m_bodyCombo,
                                *m_capeCombo, 
                                *m_feetCombo, 
                                *m_handCombo, 
                                *m_headCombo,
                                *m_legsCombo,
                                *m_neckCombo,
                                *m_ringCombo,
                                *m_shieldCombo;

  SearchableComboBox<Weapon>    *m_weaponCombo;
  SearchableComboBox<Monster>   *m_monsterCombo;
};

#endif