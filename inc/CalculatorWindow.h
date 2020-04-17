#ifndef CALCULATOR_APP_WINDOW_H
#define CALCULATOR_APP_WINDOW_H

#include "Setup.h"
#include "Database.h"
#include "SearchableComboBox.h"
#include "PlayerUI.h"
#include "EquipmentUI.h"
#include "SetupOutput.h"

#include <gtkmm.h>

class CalculatorWindow : public Gtk::Window
{
public:
  CalculatorWindow();
  virtual ~CalculatorWindow();

protected:
  void InitializeSetup();

  void on_all_setups_changed();
  void on_setup_update(int i_setupIndex);

  static const int SETUP_COUNT = 2;

  Setup *m_setup[SETUP_COUNT];
  Database m_db;

  PlayerUI *m_playerUI;
  EquipmentUI *m_equipmentUI[SETUP_COUNT];
  SetupOutput *m_setupOutput[SETUP_COUNT];
             
  Gtk::Box m_container,
           m_setupContainer,
           m_playerContainer,
           m_outputContainer;
};

#endif