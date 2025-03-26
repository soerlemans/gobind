#ifndef GOLANG_MODULE_HPP
#define GOLANG_MODULE_HPP

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// Constants:
#define GOLANG_MODULE_MAX_NAME_LENGTH (256)

// Structs:
typedef struct {
  char m_name[GOLANG_MODULE_MAX_NAME_LENGTH];
} GolangModule;

// Functions:
GolangModule* golang_module_create(const char* t_module_name);
void golang_module_free(GolangModule* t_module);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // GOLANG_MODULE_HPP
