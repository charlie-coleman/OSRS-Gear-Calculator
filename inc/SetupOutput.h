#ifndef SETUP_OUTPUT_H
#define SETUP_OUTPUT_H

#include <gtkmm.h>
#include "Setup.h"

class SetupOutput : public Gtk::Grid
{
public:
  SetupOutput(Setup* i_setup);
  virtual ~SetupOutput();

  void Update();

protected:
  Setup *m_setup;

  Gtk::Label m_maxHitLabel, m_accuracyLabel, m_dpsLabel;
  Gtk::Entry m_maxHitEntry, m_accuracyEntry, m_dpsEntry;
};

#endif