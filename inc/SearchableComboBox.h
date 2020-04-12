#ifndef SEARCHABLE_COMBOBOX_H
#define SEARCHABLE_COMBOBOX_H

#include "gtkmm.h"
#include <vector>

template <class T>
class SearchableComboBox : public Gtk::ComboBox
{
public:
  SearchableComboBox(std::vector<T> i_db);
  virtual ~SearchableComboBox();

  const T& Selected() const;

protected:
  std::vector<T> m_db;
  T m_selectedItem;

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
};

#endif