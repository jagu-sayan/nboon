/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzak <jagu.sayan@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 23:32:04 by jzak              #+#    #+#             */
/*   Updated: 2014/03/12 18:38:50 by jzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNICODE_H
# define UNICODE_H

# define IS_UTF(c) (((c)&0xC0)!=0x80)

#endif /* !UNICODE_H */