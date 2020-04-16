#ifndef STANCE_COMBOBOX_H
#define STANCE_COMBOBOX_H

#include <gtkmm.h>
#include "Weapon.h"

class StanceComboBox
{
public:
  StanceComboBox(Gtk::Grid* i_grid, int i_row, std::string i_labelStr, Weapon i_weapon);

  void SetWeapon(Weapon i_weapon);
  int StanceIndex() const;

  sigc::signal<void, int> signal_stance_changed();

protected:
  Weapon m_weapon;
  int m_stanceIndex;

  Gtk::ComboBox m_combo;
  Gtk::Label m_label;

  void PopulateComboBox();
  std::string CreateStanceName(int i_stanceIndex);

  class ModelColumns : public Gtk::TreeModel::ColumnRecord
  {
  public:
    ModelColumns()
    {
      add(m_colIndex);
      add(m_colName);
    }

    Gtk::TreeModelColumn<int> m_colIndex;
    Gtk::TreeModelColumn<Glib::ustring> m_colName;
  };

  ModelColumns m_columns;
  Glib::RefPtr<Gtk::EntryCompletion> m_refEntryCompletion;
  Glib::RefPtr<Gtk::TreeStore> m_refTreeModel, m_refCompletionModel;

  void on_combo_changed();
  sigc::signal<void, int> m_stance_changed;
};

#endif