/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:07:23 by gwolf             #+#    #+#             */
/*   Updated: 2023/08/18 23:46:02 by gwolf            ###   ########.fr       */
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
 * @param has_value Saves if the variable was assigned a value (with '=')
 * @param value Pointer to the start of the env value.
 * @param export Set to true if var is in environment.
 * @param next Pointer to the next node in this hashtable bucket.
 */
typedef struct s_env_var {
	char				*env_string;
	size_t				keylen;
	bool				has_value;
	char				*value;
	bool				export;
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
 * @param num_elements How many elements are save in hashtable.
 * @param num_exports How many elements have status export.
 * @param num_values How many of the saved elements have a value saved.
 * @param elements Pointer to the individual buckets.
 */
typedef struct s_hashtable {
	uint32_t		size;
	t_hashfunction	*hash;
	uint32_t		num_elements;
	uint32_t		num_exports;
	uint32_t		num_values;
	t_env_var		**elements;
}	t_hashtable;

//hashtable_generate.c
uint64_t	ft_hash_fnv1(const char *string, size_t len);
t_hashtable	*ft_hashtable_create(uint32_t size, t_hashfunction *hf);
void		ft_hashtable_destroy(t_hashtable *ht);

//hashtable_ops.c
t_err		ft_hashtable_insert(
				t_hashtable *ht, char *string, size_t keylen, bool has_value);
t_err		ft_hashtable_delete(
				t_hashtable *ht, char *string, size_t keylen);
t_err		ft_hashtable_swap(
				t_hashtable *ht, char *string, size_t keylen, bool has_value);
t_err		ft_hashtable_set_export(
				t_hashtable *ht, char *string, size_t keylen);
t_err		ft_hashtable_insert_export(
				t_hashtable *ht, char *string, size_t keylen, bool has_value);

//hashtable_utils.c
size_t		ft_hashtable_index(t_hashtable *ht, const char *key, size_t keylen);
t_env_var	*ft_hashtable_lookup(
				t_hashtable *ht, const char *string, size_t keylen);
void		ft_hashtable_vary_nums(t_hashtable *ht, t_env_var *tmp, int num);

#endif
