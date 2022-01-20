/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   all_tests_runner.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 23:00:07 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/20 17:26:15 by hyilmaz       ########   odam.nl         */
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

TEST_GROUP_RUNNER(TokenizePipe)
{
	RUN_TEST_CASE(TokenizePipe, TakePipeSimple);
}

TEST_GROUP_RUNNER(TokenizeWord)
{
	RUN_TEST_CASE(TokenizeWord, TakeWordSimple0);
	RUN_TEST_CASE(TokenizeWord, TakeWordSimple1);
	RUN_TEST_CASE(TokenizeWord, TakeWordSimple2);
	RUN_TEST_CASE(TokenizeWord, TakeWordSimple3);
}

TEST_GROUP_RUNNER(TokenizeRedirection)
{
	RUN_TEST_CASE(TokenizeRedirection, TakeRedirRightOnce);
	RUN_TEST_CASE(TokenizeRedirection, TakeRedirRightTwice);
	RUN_TEST_CASE(TokenizeRedirection, TakeRedirRightTriple);
	RUN_TEST_CASE(TokenizeRedirection, TakeRedirLeftOnce);
	RUN_TEST_CASE(TokenizeRedirection, TakeRedirLeftTwice);
}

TEST_GROUP_RUNNER(TokenizeDquotes)
{
	RUN_TEST_CASE(TokenizeDquotes, TakeDoubleQuotesSimple0);
	RUN_TEST_CASE(TokenizeDquotes, TakeDoubleQuotesSimple1);
	RUN_TEST_CASE(TokenizeDquotes, TakeDoubleQuotesNoClosingQuote);
	RUN_TEST_CASE(TokenizeDquotes, TakeDoubleQuotesBackToBack);
	// RUN_TEST_CASE(TokenizeDquotes, TakeDoubleQuotesNestedHard0);
	// RUN_TEST_CASE(TokenizeDquotes, TakeDoubleQuotesNestedHard1);
}

TEST_GROUP_RUNNER(TokenizerUtils)
{
	// RUN_TEST_CASE(TokenizerUtils, TakeDoubleQuotesSimple0);
	// RUN_TEST_CASE(TokenizerUtils, TakeDoubleQuotesSimple1);
	// RUN_TEST_CASE(TokenizerUtils, TakeDoubleQuotesNoClosingQuote);
	// RUN_TEST_CASE(TokenizerUtils, TakeDoubleQuotesNestedHard0);
	// RUN_TEST_CASE(TokenizerUtils, TakeDoubleQuotesNestedHard1);
}