#ifndef MACROS_H
#define MACROS_H

// Macros:
#define GOBIND_CONCAT(t_left, t_right)       GOBIND_CONCAT_INNER(t_left, t_right)
#define GOBIND_CONCAT_INNER(t_left, t_right) t_left##t_right
#define GOBIND_STRINGIFY(t_expr)             #t_expr

#endif // MACROS_H
