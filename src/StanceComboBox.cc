#include "StanceCombBox.h"

StanceComboBox::StanceComboBox(Gtk::Grid* i_grid, int i_row, std::string i_labelStr, Weapon i_weapon)
  : m_combo(),
    m_label{i_labelStr},
    m_weapon(i_weapon)
{

  m_refTreeModel = Gtk::TreeStore::create(m_columns);
  m_combo.set_model(m_refTreeModel);
  
  PopulateComboBox();

  m_combo.pack_start(m_columns.m_colName);

  m_label.set_alignment(Gtk::Align::ALIGN_START, Gtk::Align::ALIGN_CENTER);

  m_combo.signal_changed().connect(sigc::mem_fun(*this, &StanceComboBox::on_combo_changed));

  i_grid->attach(m_label, 0, i_row);
  i_grid->attach(m_combo, 1, i_row);
}

void StanceComboBox::SetWeapon(Weapon i_weapon)
{
  m_weapon = i_weapon;
  m_refTreeModel->clear();
  PopulateComboBox();
}

void StanceComboBox::PopulateComboBox()
{
  std::vector<STANCE_T> stances = m_weapon.WeaponStats().Stances;

  for (int i = 0; i < stances.size(); ++i)
  {
    Gtk::TreeModel::Row row = *(m_refTreeModel->append());

    row[m_columns.m_colIndex] = i;
    row[m_columns.m_colName] = CreateStanceName(i);

    if (i == 0)
    {
      m_combo.set_active(row);
      m_stanceIndex = 0;
    }
  }
}

int StanceComboBox::StanceIndex() const
{
  return m_stanceIndex;
}

void StanceComboBox::on_combo_changed()
{
  Gtk::TreeModel::iterator it = m_combo.get_active();

  if (it)
  {
    Gtk::TreeModel::Row row = *it;

    if (row)
    {
      m_stanceIndex = row[m_columns.m_colIndex];
      m_stance_changed.emit(m_stanceIndex);
    }
  }
}

sigc::signal<void, int> StanceComboBox::signal_stance_changed()
{
  return m_stance_changed;
}

std::string StanceComboBox::CreateStanceName(int i_stanceIndex)
{
  COMBAT_STYLE_E::Type combatStyle = m_weapon.GetCombatStyle(i_stanceIndex);
  STANCE_T stance = m_weapon.WeaponStats().Stances[i_stanceIndex];

  std::string name;

  switch (combatStyle)
  {
    case COMBAT_STYLE_E::MELEE:
      name = stance.AttackStyle + " (" + stance.AttackType + ")";
      break;
    case COMBAT_STYLE_E::RANGED:
    case COMBAT_STYLE_E::MAGIC:
      name = stance.CombatStyle + " (" + stance.Experience + ")";
      break;
    default:
      name = "";
      break;
  }

  return name;
}