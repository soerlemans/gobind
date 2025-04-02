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
Error gobind_function_table_create(GobindFunctionTable** t_fn_table,
                                   size_t t_size)
{
  using gobind::malloc;

  auto& ptr{*t_fn_table};
  ptr = malloc<GobindFunctionTable>();
  ptr->m_functions = malloc<GobindFunction>(t_size);
  ptr->m_size = 0;
  ptr->m_capacity = t_size;

  return {};
}

Error gobind_function_table_add(GobindFunctionTable* t_fn_table,
                                GobindFunction* t_function)
{
  Error error{};

  auto& [functions, size, capacity] = *t_fn_table;

  // Reallocate if necessary.
  if(size == capacity) {
    const auto new_capacity{capacity * 2};
    auto* mem{std::realloc(functions, new_capacity)};
    if(mem) {
      functions = static_cast<GobindFunction*>(mem);
      capacity = new_capacity;
    } else {
      error_fail(&error, EGB_FUNCTION_TABLE_BAD_ALLOC);
    }
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

  // Free function table array and the the struct itself.
  std::free(fn_table_ptr->m_functions);
  std::free(fn_table_ptr);

  fn_table_ptr = nullptr;
}
