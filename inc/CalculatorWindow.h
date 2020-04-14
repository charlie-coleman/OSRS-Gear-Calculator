#ifndef CALCULATOR_APP_WINDOW_H
#define CALCULATOR_APP_WINDOW_H

#include "Setup.h"
#include "Database.h"
#include "SearchableComboBox.h"
#include "PlayerUI.h"
#include "EquipmentUI.h"

#include <gtkmm.h>

class CalculatorWindow : public Gtk::Window
{
public:
  CalculatorWindow();
  virtual ~CalculatorWindow();

protected:
  void InitializeSetup();

  void on_player_changed();
  void on_equipment_changed(DB_TYPE_E::Type i_type);

  Setup *m_setup;
  Database m_db;

  PlayerUI *m_playerUI;
  EquipmentUI *m_equipmentUI;
             
  Gtk::Box m_container,
           m_setupContainer,
           m_playerContainer;
};

#endif