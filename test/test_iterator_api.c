/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_iterator_api.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 12:58:01 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/18 13:46:37 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "unity_fixture.h"
#include "../src/parser/iterator_api.h"

TEST_GROUP(IteratorAPI);

TEST_SETUP(IteratorAPI)
{
}

TEST_TEAR_DOWN(IteratorAPI)
{
}

TEST(IteratorAPI, HasNext)
{
	char		*input = "ls\n -l";
	t_char_iter	itr;

	itr = input;
	TEST_ASSERT_TRUE(has_next(itr));

	itr += 2;
	TEST_ASSERT_FALSE(has_next(itr));	/* newline here */

	itr += 2;
	TEST_ASSERT_TRUE(has_next(itr));

	itr += 2;
	TEST_ASSERT_FALSE(has_next(itr));	/* null-terminator here */
}

TEST(IteratorAPI, Next)
{
	char		*input = "ls -n";
	t_char_iter	itr;
	char		result;

	itr = input;

	result = next(&itr);
	TEST_ASSERT_EQUAL_CHAR('l', result);
	TEST_ASSERT_EQUAL_CHAR('s', *itr);

	result = next(&itr);
	TEST_ASSERT_EQUAL_CHAR('s', result);
	TEST_ASSERT_EQUAL_CHAR(' ', *itr);

	next(&itr);
	next(&itr);
	next(&itr);
	result = next(&itr);
	TEST_ASSERT_EQUAL_CHAR('\0', result);
}