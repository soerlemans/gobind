# Add source files
target_sources(${TARGET_GOBIND} PRIVATE
  cpp_backend.cpp
  prototype_generator.cpp
  type_variant2cpp_type.cpp
  clang_frontend_invoker.cpp
)
