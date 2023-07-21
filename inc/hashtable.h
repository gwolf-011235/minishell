/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqiu <sqiu@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:07:23 by gwolf             #+#    #+#             */
/*   Updated: 2023/07/21 11:51:37 by sqiu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file
 * @brief Header for hashtable stuff.
 */

#ifndef HASHTABLE_H
# define HASHTABLE_H

# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdbool.h>

# include "libft.h"
# include "minishell_error.h"

/**
 * @brief 64-bit FNV1 offset basis
 *
 * Initial hash value for the FNV1 hash function
 */
# define FNV_OFFSET 0xCBF29CE48422325UL
/**
 * @brief 64-bit FNV1 prime value
 *
 * Number with which to multiply in FNV1 hash function
 */
# define FNV_PRIME 0x100000001b3

typedef uint64_t			t_hashfunction (const char *, size_t);

/**
 * @brief Node to store env_strings.
 *
 * This node saves one env variable.
 * @param env_string The whole env string (e.g. PWD=path/to/pwd).
 * @param keylen The length of the env variable name.
 * @param value Pointer to the start of the env value.
 * @param next Pointer to the next node in this hashtable bucket.
 */
typedef struct s_env_var {
	char				*env_string;
	size_t				keylen;
	char				*value;
	struct s_env_var	*next;
}	t_env_var;

/**
 * @brief Hashtable with external chaining.
 *
 * This hashtable is used to store the env_vars.
 * It has <size> * buckets in which to save elements.
 * Hash function is used to generate index from the env_var name (e.g. PWD).
 * The env_var string is then saved in a node at the index.
 * If the index is already used external chaining is used.
 * The new node is inserted at the front of this linked list.
 *
 * @param size How many buckets hashtable has.
 * @param hash The used hash function.
 * @param elements Pointer to the individual buckets.
 */
typedef struct s_hashtable {
	uint32_t		size;
	t_hashfunction	*hash;
	uint32_t		num_elements;
	t_env_var		**elements;
}	t_hashtable;

//hashtable_generate.c
uint64_t	ft_hash_fnv1(const char *string, size_t len);
t_hashtable	*ft_hashtable_create(uint32_t size, t_hashfunction *hf);
void		ft_hashtable_destroy(t_hashtable *ht);

//hashtable_utils.c
t_err		ft_hashtable_insert(
				t_hashtable *ht, char *string, size_t keylen);
t_env_var	*ft_hashtable_lookup(
				t_hashtable *ht, const char *string, size_t keylen);
t_err		ft_hashtable_delete(
				t_hashtable *ht, char *string, size_t keylen);
void		ft_hashtable_print(t_hashtable *ht);

//hashtable_utils2.c
t_err		ft_hashtable_swap(
				t_hashtable *ht, char *string, size_t keylen);

#endif