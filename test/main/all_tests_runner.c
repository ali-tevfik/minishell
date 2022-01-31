/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   all_tests_runner.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 23:00:07 by hyilmaz       #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2022/01/31 17:55:30 by adoner        ########   odam.nl         */
=======
/*   Updated: 2022/01/27 13:06:28 by hyilmaz       ########   odam.nl         */
>>>>>>> 277b7cf308323f6d60a828ebfd84a34ee4de1e7f
/*                                                                            */
/* ************************************************************************** */

#include <unity_fixture.h>

TEST_GROUP_RUNNER(unset)
{
<<<<<<< HEAD
	RUN_TEST_CASE(unset, delete_first);
	RUN_TEST_CASE(unset, delete_third);
	RUN_TEST_CASE(unset, delete_all);
	RUN_TEST_CASE(unset, delete_nooit);
	RUN_TEST_CASE(unset, delete_last);
	RUN_TEST_CASE(unset, delete_all_and_extra);
	RUN_TEST_CASE(unset, export_and_delete);

}


TEST_GROUP_RUNNER(export)
{
	RUN_TEST_CASE(export, wrong);
	RUN_TEST_CASE(export, add_normal);
	RUN_TEST_CASE(export, check_tab);
}

TEST_GROUP_RUNNER(expander)
{

	RUN_TEST_CASE(expander, expander_find_first);
	RUN_TEST_CASE(expander, expander_find_second);
	RUN_TEST_CASE(expander, expander_find_middle);
	RUN_TEST_CASE(expander, expander_find_last);
	RUN_TEST_CASE(expander, expander_dont_find);
}
=======
	RUN_TEST_CASE(AddNumbers, Simple);
	RUN_TEST_CASE(AddNumbers, ABC);
}

/* Tokenizer */

TEST_GROUP_RUNNER(Tokenizer)
{
	RUN_TEST_CASE(Tokenizer, Command);
	RUN_TEST_CASE(Tokenizer, CommandPlusArgument);
	RUN_TEST_CASE(Tokenizer, CommandPlusArgumentStartingWithSomeSpaces);
	RUN_TEST_CASE(Tokenizer, MultipleCommandsPlusArgumentsWithPipes);
	RUN_TEST_CASE(Tokenizer, CommandPlusRedirection);
	RUN_TEST_CASE(Tokenizer, CommandPlusRedirectionPlusPipes);
	RUN_TEST_CASE(Tokenizer, CommandPlusDquotes);
	RUN_TEST_CASE(Tokenizer, CommandPlusDquotesPlusPipes);
	RUN_TEST_CASE(Tokenizer, CommandPlusQuotes);
	RUN_TEST_CASE(Tokenizer, CommandPlusUnclosedQuotes);
	RUN_TEST_CASE(Tokenizer, MultiplePipesBackToBack);
	RUN_TEST_CASE(Tokenizer, WeirdSpacing);
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
	RUN_TEST_CASE(TokenizeRedirection, TakeRedirLeftOnce);
	RUN_TEST_CASE(TokenizeRedirection, TakeRedirLeftTwice);
	RUN_TEST_CASE(TokenizeRedirection, TakeRedirLeftRight);
}

TEST_GROUP_RUNNER(TokenizeDquotes)
{
	RUN_TEST_CASE(TokenizeDquotes, TakeDoubleQuotesSimple0);
	RUN_TEST_CASE(TokenizeDquotes, TakeDoubleQuotesSimple1);
	RUN_TEST_CASE(TokenizeDquotes, TakeDoubleQuotesNoClosingQuote);
	RUN_TEST_CASE(TokenizeDquotes, TakeDoubleQuotesBackToBack);
}

TEST_GROUP_RUNNER(TokenizeQuotes)
{
	RUN_TEST_CASE(TokenizeQuotes, TakeSingleQuotesSimple0);
	RUN_TEST_CASE(TokenizeQuotes, TakeSingleQuotesSimple1);
}

TEST_GROUP_RUNNER(CheckGrammer)
{
	RUN_TEST_CASE(CheckGrammer, PipesBackToBack);
	RUN_TEST_CASE(CheckGrammer, RedirectionBeforePipe);
	RUN_TEST_CASE(CheckGrammer, RedirectionAfterPipe);
	RUN_TEST_CASE(CheckGrammer, RedirectionAfterRedirection);
	RUN_TEST_CASE(CheckGrammer, ErrorTokenAmpersandInList);
	RUN_TEST_CASE(CheckGrammer, ErrorTokenSemiColonInList);
	RUN_TEST_CASE(CheckGrammer, OnlyPipeToken);
	RUN_TEST_CASE(CheckGrammer, OnlyRedirectionToken);
	RUN_TEST_CASE(CheckGrammer, OnlyRedirectionToken1);
	RUN_TEST_CASE(CheckGrammer, CorrectGrammer0);
	RUN_TEST_CASE(CheckGrammer, CorrectGrammer1);
	RUN_TEST_CASE(CheckGrammer, CorrectGrammer2);
}

/* Parser */
TEST_GROUP_RUNNER(ParserUtils)
{
	RUN_TEST_CASE(ParserUtils, CreateCommandFromTokenList);
	RUN_TEST_CASE(ParserUtils, CreateCommandFromTokenListTakeCommandAfterPipe);
	RUN_TEST_CASE(ParserUtils, CreateCommandFromTokenListWithRedirectionOutFile);
	RUN_TEST_CASE(ParserUtils, CreateCommandFromTokenListWithMultipleRedirectionOutFile);
	RUN_TEST_CASE(ParserUtils, CreateCommandFromTokenListNoPipeNoRedirection);
	RUN_TEST_CASE(ParserUtils, CreateCommandFromTokenListWithRedirectionOutFileBeforeCommand);
	RUN_TEST_CASE(ParserUtils, CreateCommandFromTokenListWithRedirectionOutFileInTheMiddleOfCommand);
	RUN_TEST_CASE(ParserUtils, CreateCommandFromTokenListWithAppendOutFileInTheMiddleOfCommand);
}

TEST_GROUP_RUNNER(CreateParseList)
{
	RUN_TEST_CASE(CreateParseList, SimplePipelineNoPipes);
	RUN_TEST_CASE(CreateParseList, SimplePipelineOnePipe);
	RUN_TEST_CASE(CreateParseList, SimplePipelineTwoPipes);
	RUN_TEST_CASE(CreateParseList, SimplePipelineTwoPipesChangeOrderCommandAndRedirection);
	RUN_TEST_CASE(CreateParseList, SimplePipelineNoPipeWeirdRedirectionOrder);
}
>>>>>>> 277b7cf308323f6d60a828ebfd84a34ee4de1e7f
