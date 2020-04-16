#include "SetupOutput.h"

#include <string>

SetupOutput::SetupOutput(Setup* i_setup)
  : m_maxHitLabel("Max Hit: "),
    m_maxHitEntry(),
    m_accuracyLabel("Accuracy: "),
    m_accuracyEntry(),
    m_dpsLabel("DPS: "),
    m_dpsEntry(),
    m_setup(i_setup)
{
  m_maxHitEntry.set_editable(false);
  m_accuracyEntry.set_editable(false);
  m_dpsEntry.set_editable(false);

  m_maxHitEntry.set_text("0");
  m_accuracyEntry.set_text("0%");
  m_dpsEntry.set_text("0");

  m_maxHitLabel.set_alignment(Gtk::Align::ALIGN_START, Gtk::Align::ALIGN_CENTER);
  m_accuracyLabel.set_alignment(Gtk::Align::ALIGN_START, Gtk::Align::ALIGN_CENTER);
  m_dpsLabel.set_alignment(Gtk::Align::ALIGN_START, Gtk::Align::ALIGN_CENTER);

  attach(m_maxHitLabel, 0, 0);
  attach(m_maxHitEntry, 1, 0);
  attach(m_accuracyLabel, 0, 1);
  attach(m_accuracyEntry, 1, 1);
  attach(m_dpsLabel, 0, 2);
  attach(m_dpsEntry, 1, 2);
}

SetupOutput::~SetupOutput()
{
}

void SetupOutput::Update()
{
  m_setup->Recalculate();

  std::string maxHit = std::to_string(m_setup->MaxDamage());

  char accCStr[16];
  sprintf(accCStr, "%.3f%%", (m_setup->Accuracy() * 100));
  std::string accuracy(accCStr);

  char dpsCStr[16];
  sprintf(dpsCStr, "%.3f", m_setup->DPS());
  std::string dps(dpsCStr);

  m_maxHitEntry.set_text(maxHit);
  m_accuracyEntry.set_text(accuracy);
  m_dpsEntry.set_text(dps);
}