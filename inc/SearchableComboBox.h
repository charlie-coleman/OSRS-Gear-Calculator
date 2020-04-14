#ifndef SEARCHABLE_COMBOBOX_H
#define SEARCHABLE_COMBOBOX_H

#include "gtkmm.h"
#include "enums.h"
#include <vector>

template <class T>
class SearchableComboBox
{
public:
  SearchableComboBox(Gtk::Grid* i_grid, int i_row, std::string i_labelStr, std::vector<T> i_db, DB_TYPE_E::Type i_type);
  virtual ~SearchableComboBox();

  T Selected() const;

  sigc::signal<void, DB_TYPE_E::Type> signal_selected_change();

protected:
  std::vector<T> m_db;
  T m_selectedItem;
  DB_TYPE_E::Type m_type;

  Gtk::Label m_label;
  Gtk::ComboBox m_combo;

  class ModelColumns : public Gtk::TreeModel::ColumnRecord
  {
  public:
    ModelColumns()
    {
      add(m_colIndex);
      add(m_colName);
      add(m_colId);
    }

    Gtk::TreeModelColumn<int> m_colIndex;
    Gtk::TreeModelColumn<Glib::ustring> m_colName;
    Gtk::TreeModelColumn<int> m_colId;
  };

  ModelColumns m_columns;
  Glib::RefPtr<Gtk::TreeStore> m_refTreeModel;

  void PopulateComboBox();

  void on_combo_changed();

  sigc::signal<void, DB_TYPE_E::Type> m_selected_change;
};

#endif