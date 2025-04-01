#include "gobind_function_table.h"

Error gobind_function_table_create(GobindFunctionTable** t_fn_table,
                                   const size_t t_size)
{
  auto& fn_table{*t_fn_table};

  fn_table = new GobindFunctionTable{};
  fn_table->m_entries = new GobindFunction[t_size];
  fn_table->m_size = t_size;

  return {};
}

void gobind_function_table_free(GobindFunctionTable** t_fn_table)
{
  auto& fn_table{*t_fn_table};

  // Free function table array and the the struct itself.
  delete[] fn_table->m_entries;
  delete fn_table;

  fn_table = nullptr;
}
