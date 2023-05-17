/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:07:23 by gwolf             #+#    #+#             */
/*   Updated: 2023/05/17 18:08:34 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASHTABLE_H

# include <stdint.h>
# include <stdlib.h>
# include <stdbool.h>

# define FNV_PRIME 0x100000001B3
# define FNV_OFFSET 0xCBF29CE48422325UL

typedef uint64_t	t_hashfunction (const char *, size_t);

typedef struct s_env_var {
	const char			*env_string;
	size_t				keylen;
	const char			*value;
	struct s_env_var	*next;
}	t_env_var;

typedef struct s_hashtable {
	uint32_t		size;
	t_hashfunction	*hash;
	t_env_var		**elements;
}	t_hashtable;

t_hashtable	*ft_hashtable_create(uint32_t size, t_hashfunction *hf);
void		ft_hashtable_destroy(t_hashtable *ht);
void		ft_hashtable_print(t_hashtable *ht);
bool		ft_hashtable_insert(t_hashtable *ht, const char *string, size_t keylen);
t_env_var	*ft_hashtable_lookup(t_hashtable *ht, const char *string, size_t keylen);
const char	*ft_hashtable_delete(t_hashtable *ht, const char *string, size_t keylen);
uint64_t	ft_hash_fnv1(const char *string, size_t len);

#endif