#include "golang_function_table.h"

Error golang_function_table_create(GolangFunctionTable** t_fn_table,
                                   const size_t t_size)
{
  auto& fn_table{*t_fn_table};

  fn_table = new GolangFunctionTable{};
  fn_table->m_entries = new GolangFunction[t_size];
  fn_table->m_size = t_size;

  return {};
}

void golang_function_table_free(GolangFunctionTable** t_fn_table)
{
  auto& fn_table{*t_fn_table};

  delete[] fn_table->m_entries;
  delete fn_table;

  fn_table = nullptr;
}
