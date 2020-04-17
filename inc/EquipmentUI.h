#ifndef SETUPUI_H
#define SETUPUI_H

#include <gtkmm.h>
#include "SearchableComboBox.h"
#include "StanceCombBox.h"
#include "Database.h"
#include "Setup.h"
#include "enums.h"

class EquipmentUI : public Gtk::Box
{
public:
  EquipmentUI(std::string i_title, Database *i_db, Setup *i_setup);
  virtual ~EquipmentUI();

  sigc::signal<void> signal_setup_update();

  Equipment Ammunition() const;
  Equipment Body() const;
  Equipment Cape() const;
  Equipment Feet() const;
  Equipment Hand() const;
  Equipment Head() const;
  Equipment Legs() const;
  Equipment Neck() const;
  Equipment Ring() const;
  Equipment Shield() const;
  Weapon    GetWeapon() const;

protected:
  void InitializeComboBoxes();
  void PopulateSetup();

  Database *m_db;
  Setup *m_setup;

  Gtk::Label m_titleLabel;
  Gtk::Grid m_grid;

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

  StanceComboBox *m_stanceCombo;

  void on_equipment_change(DB_TYPE_E::Type i_type);
  void on_weapon_change();
  void on_stance_change(int i_stanceIndex);

  sigc::signal<void> m_signal_setup_update;
};

#endif