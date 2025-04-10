#include "gobind_function_table.h"

// STL Includes:
#include <cstring>

// Local Includes:
#include "alloc.hpp"

/*
// Internal:
namespace {
template<typename T>
auto reallocate(T** array, size_t& capacity) -> void
{
  if(new_capacity <= capacity)
    return; // No need to shrink

  T* new_array = new T[new_capacity];

  // Copy existing elements to the new array
  std::memcpy(new_array, array, capacity * sizeof(T));

  // Delete the old array
  delete[] array;

  // Update pointer and capacity
  array = new_array;
  capacity = new_capacity;
}
} // namespace
*/


// Functions:
Error gobind_function_table_create(GobindFunctionTable** t_fn_table)
{
  using gobind::malloc;

  auto& ptr{*t_fn_table};
  ptr = malloc<GobindFunctionTable>();
  ptr->m_functions = malloc<GobindFunction>();
  ptr->m_size = 0;
  ptr->m_capacity = 0;

  return {};
}

Error gobind_function_table_resize(GobindFunctionTable* t_fn_table,
                                   const size_t t_size)
{
  Error error{};

  auto& [functions, size, capacity] = *t_fn_table;

  auto* mem{std::realloc(functions, t_size)};
  if(mem) {
    functions = static_cast<GobindFunction*>(mem);
    capacity = t_size;
  } else {
    error_fail(&error, EGB_FUNCTION_TABLE_BAD_ALLOC);
  }

  return error;
}

Error gobind_function_table_add(GobindFunctionTable* t_fn_table,
                                GobindFunction* t_function)
{
  Error error{};

  auto& [functions, size, capacity] = *t_fn_table;

  // Reallocate if necessary.
  if(size == capacity) {
    const auto new_capacity{capacity * 2};

    const auto resize_error{
      gobind_function_table_resize(t_fn_table, new_capacity)};
    error_assert(&resize_error);
  } else if(size >= capacity) {
    error_fail(&error, EGB_FUNCTION_TABLE_BAD_STATE);
  }

  // Construct new GobindFunction entry for function table.
  functions[size] = *t_function;

  // Increase size at the end.
  size++;

  return error;
}

void gobind_function_table_free(GobindFunctionTable** t_fn_table)
{
  // FIXME: Check if t_fn_table is nullptr (nullptr dereference).
  // FIXME: Then check if fn_table_ptr is nullptr (prevent double free).
  auto& fn_table_ptr{*t_fn_table};

  auto& functions{fn_table_ptr->m_functions};
  auto& size{fn_table_ptr->m_size};

  // Free gobind type array, function table array and the the struct itself.
  for(size_t index{0}; index < size; index++) {
    auto& params{functions[index].m_params};

    if(params) {
      std::free(params);
    }
  }

  std::free(fn_table_ptr->m_functions);
  std::free(fn_table_ptr);

  fn_table_ptr = nullptr;
}
