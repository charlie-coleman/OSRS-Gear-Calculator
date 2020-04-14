#ifndef SETUPUI_H
#define SETUPUI_H

#include <gtkmm.h>
#include "SearchableComboBox.h"
#include "Database.h"
#include "Equipment.h"
#include "Weapon.h"
#include "Monster.h"

class EquipmentUI : public Gtk::Grid
{
public:
  EquipmentUI(Database *i_db);
  virtual ~EquipmentUI();

  sigc::signal<void, DB_TYPE_E::Type> signal_equipment_change();

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
  Monster   GetMonster() const;

protected:
  void InitializeComboBoxes();

  Database *m_db;

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

  sigc::signal<void, DB_TYPE_E::Type> m_equipment_changed;
  void on_equipment_change(DB_TYPE_E::Type i_type);
};

#endif