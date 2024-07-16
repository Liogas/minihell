/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_libft.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:52:49 by glions            #+#    #+#             */
/*   Updated: 2024/05/15 13:56:02 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_LIBFT_H
# define GL_LIBFT_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

// CHAR
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);

// MEMORY
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);

// STR
size_t	ft_strlen(char *str);
int		ft_strlen_stop_c(char *str, char c);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strnstr(const char *big, const char *little, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_w_free(char *s1, char const *s2);
char	*ft_strdup(char *src);
char	*ft_strndup(char *src, int n);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
void	ft_split_free(char **m);
char	*ft_strupper(char *str);
int		ft_constr(const char *str, const char c);

// CONVERSION
int		ft_atoi(const char *nptr);
int		ft_atoin(const char *nptr, int end);
char	*ft_itoa(int n);
char	*ft_itoa_hex(unsigned int n);
char	*ft_utoa(unsigned int n);
char	*ft_ptoa(unsigned long long n);

// PUT FD
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putnbr_u_fd(unsigned int n, int fd);
void	ft_putnbr_hex_fd(long long n, int fd, int upper);
void	ft_putptr_hex_fd(unsigned long long n, int fd);
void	ft_put_tab2d_int_gl(int **tab, int height, int width);

// ALLOC MEMORY
void	*ft_calloc(size_t elementCount, size_t elementSize);

// FREE
void	ft_free_tab2d_int_gl(int **tab, int height);

// DUP
int		**ft_dup_tab2d_int_gl(int **target, int height, int width);
char	*ft_strdup(char *src);

#endif