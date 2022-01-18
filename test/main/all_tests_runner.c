/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   all_tests_runner.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 23:00:07 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/18 18:00:49 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unity_fixture.h>

TEST_GROUP_RUNNER(AddNumbers)
{
	RUN_TEST_CASE(AddNumbers, Simple);
	RUN_TEST_CASE(AddNumbers, ABC);
}

TEST_GROUP_RUNNER(Tokenizer)
{
	RUN_TEST_CASE(Tokenizer, SimpleInput);
	RUN_TEST_CASE(Tokenizer, CommandPlusArgument);
}

TEST_GROUP_RUNNER(IteratorAPI)
{
	RUN_TEST_CASE(IteratorAPI, HasNext);
	RUN_TEST_CASE(IteratorAPI, Next);
	RUN_TEST_CASE(IteratorAPI, Peek);
}

TEST_GROUP_RUNNER(TokenizerUtils)
{
	RUN_TEST_CASE(TokenizerUtils, TakeWordSimple0);
	RUN_TEST_CASE(TokenizerUtils, TakeWordSimple1);
	RUN_TEST_CASE(TokenizerUtils, TakeWordSimple2);
	RUN_TEST_CASE(TokenizerUtils, TakeWordSimple3);
	RUN_TEST_CASE(TokenizerUtils, TakePipeSimple);
	RUN_TEST_CASE(TokenizerUtils, TakeRedirRightOnce);
	RUN_TEST_CASE(TokenizerUtils, TakeRedirRightTwice);
	RUN_TEST_CASE(TokenizerUtils, TakeRedirRightTriple);
}