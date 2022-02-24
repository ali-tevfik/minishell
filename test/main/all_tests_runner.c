/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   all_tests_runner.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 23:00:07 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/24 15:03:49 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "unity_fixture.h"

TEST_GROUP_RUNNER(UnsetBuiltin)
{
	RUN_TEST_CASE(UnsetBuiltin, DeleteFromMiddle);
	RUN_TEST_CASE(UnsetBuiltin, DeleteLast);
	RUN_TEST_CASE(UnsetBuiltin, DeleteFirst);
	RUN_TEST_CASE(UnsetBuiltin, DeleteAll);
	RUN_TEST_CASE(UnsetBuiltin, DeleteAllAndExtra);
	RUN_TEST_CASE(UnsetBuiltin, NonExisting0);
	RUN_TEST_CASE(UnsetBuiltin, NonExisting1);
	RUN_TEST_CASE(UnsetBuiltin, NoArgument);
	RUN_TEST_CASE(UnsetBuiltin, WrongArgument);
}

 TEST_GROUP_RUNNER(ExportBuiltin)
{
	RUN_TEST_CASE(ExportBuiltin, ExportOneVariable);
	RUN_TEST_CASE(ExportBuiltin, ExportTwoVariables);
	RUN_TEST_CASE(ExportBuiltin, ExportThreeVariables);
	RUN_TEST_CASE(ExportBuiltin, ExportSameVariableAssignment0);
	RUN_TEST_CASE(ExportBuiltin, ExportSameVariableAssignment1);
	RUN_TEST_CASE(ExportBuiltin, ExportNoInput);
	RUN_TEST_CASE(ExportBuiltin, ExportAssignEmpty0);
	RUN_TEST_CASE(ExportBuiltin, ExportAssignEmpty1);
	RUN_TEST_CASE(ExportBuiltin, ExportVariableNameStartsWithUnderscore);
	RUN_TEST_CASE(ExportBuiltin, ExportVariableNameAndValueStartsWithUnderscore);
	RUN_TEST_CASE(ExportBuiltin, ExportAssignWithSpaceBeforeEqualSign);
	RUN_TEST_CASE(ExportBuiltin, ExportAssignWithSpaceAfterEqualSign);
	RUN_TEST_CASE(ExportBuiltin, ExportAssignWithSpaceBeforeAndAfterEqualSign);
	RUN_TEST_CASE(ExportBuiltin, ExportCaseSensitivity);
	RUN_TEST_CASE(ExportBuiltin, ExportInvalidOption);
	RUN_TEST_CASE(ExportBuiltin, ExportSpaceInValue);
 	RUN_TEST_CASE(ExportBuiltin, ExportUnderScoreAsKey);
	RUN_TEST_CASE(ExportBuiltin, ExportWithExpansion0);
}

/* Tokenizer */

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


TEST_GROUP_RUNNER(TokenizeRedirection)
{
	RUN_TEST_CASE(TokenizeRedirection, TakeRedirRightOnce);
	RUN_TEST_CASE(TokenizeRedirection, TakeRedirRightTwice);
	RUN_TEST_CASE(TokenizeRedirection, TakeRedirLeftOnce);
	RUN_TEST_CASE(TokenizeRedirection, TakeRedirLeftTwice);
	RUN_TEST_CASE(TokenizeRedirection, TakeRedirLeftRight);
}

TEST_GROUP_RUNNER(TokenizeWord)
{
	RUN_TEST_CASE(TokenizeWord, TakeWordSimple0);
	RUN_TEST_CASE(TokenizeWord, TakeWordSimple1);
	RUN_TEST_CASE(TokenizeWord, TakeWordSimple2);
	RUN_TEST_CASE(TokenizeWord, TakeWordSimple3);
	RUN_TEST_CASE(TokenizeWord, TakeWordHard0);
	RUN_TEST_CASE(TokenizeWord, TakeWordWithDoubleQuotes);
	RUN_TEST_CASE(TokenizeWord, TakeWordWithSingleQuotes);
	RUN_TEST_CASE(TokenizeWord, TakeWordWithUnclosedDoubleQuotes);
	RUN_TEST_CASE(TokenizeWord, TakeWordWithUnclosedSingleQuotes);
	RUN_TEST_CASE(TokenizeWord, TakeWordWithFourDoubleQuotes);
	RUN_TEST_CASE(TokenizeWord, TakeWordWithOpeningDoubleQuoteAndClosingSingleQuote);
	RUN_TEST_CASE(TokenizeWord, TakeWordWithOpeningSingleQuoteAndClosingDoubleQuote);
}

TEST_GROUP_RUNNER(Tokenizer)
{
	RUN_TEST_CASE(Tokenizer, Command);
	RUN_TEST_CASE(Tokenizer, CommandPlusArgument);
	RUN_TEST_CASE(Tokenizer, CommandPlusArgumentStartingWithSomeSpaces);
	RUN_TEST_CASE(Tokenizer, MultipleCommandsPlusArgumentsWithPipes);
	RUN_TEST_CASE(Tokenizer, CommandPlusRedirection);
	RUN_TEST_CASE(Tokenizer, CommandPlusRedirectionPlusPipes);
	RUN_TEST_CASE(Tokenizer, CommandPlusDquotes);
	RUN_TEST_CASE(Tokenizer, CommandPlusDquotesEmpty);
	RUN_TEST_CASE(Tokenizer, CommandPlusDquotesPlusPipes);
	RUN_TEST_CASE(Tokenizer, CommandPlusQuotes);
	RUN_TEST_CASE(Tokenizer, CommandPlusUnclosedQuotes);
	RUN_TEST_CASE(Tokenizer, MultiplePipesBackToBack);
	RUN_TEST_CASE(Tokenizer, WeirdSpacing);
}

TEST_GROUP_RUNNER(RemoveQuotesFromTokens)
{
	RUN_TEST_CASE(RemoveQuotesFromTokens, NoQuotes);
	RUN_TEST_CASE(RemoveQuotesFromTokens, DoubleQuotesPresent);
	RUN_TEST_CASE(RemoveQuotesFromTokens, SingleQuotesPresent);
	RUN_TEST_CASE(RemoveQuotesFromTokens, MultipleMixedQuotesPresent);
	RUN_TEST_CASE(RemoveQuotesFromTokens, WordAppendWithDoubleQuotes);
	RUN_TEST_CASE(RemoveQuotesFromTokens, WordAppendWithSingleQuotes);
	RUN_TEST_CASE(RemoveQuotesFromTokens, PipesAndRedirectionOperatorsPresent);
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
	RUN_TEST_CASE(CheckGrammer, NoClosingDQuote);
	RUN_TEST_CASE(CheckGrammer, NoClosingQuote);
	RUN_TEST_CASE(CheckGrammer, SingleDoubleSingleDoubleQuotesSequence);
	RUN_TEST_CASE(CheckGrammer, DoubleSingleDoubleSingleQuotesSequence);
	RUN_TEST_CASE(CheckGrammer, CorrectGrammer0);
	RUN_TEST_CASE(CheckGrammer, CorrectGrammer1);
	RUN_TEST_CASE(CheckGrammer, CorrectGrammer2);
}

/* Parser */
TEST_GROUP_RUNNER(CreateSimpleCommand)
{
	RUN_TEST_CASE(CreateSimpleCommand, CreateCommandFromTokenList);
	RUN_TEST_CASE(CreateSimpleCommand, CreateCommandFromTokenListTakeCommandAfterPipe);
	RUN_TEST_CASE(CreateSimpleCommand, CreateCommandFromTokenListWithRedirectionOutFile);
	RUN_TEST_CASE(CreateSimpleCommand, CreateCommandFromTokenListWithMultipleRedirectionOutFile);
	RUN_TEST_CASE(CreateSimpleCommand, CreateCommandFromTokenListWithRedirectionOutFileBeforeCommand);
	RUN_TEST_CASE(CreateSimpleCommand, CreateCommandFromTokenListWithRedirectionOutFileInTheMiddleOfCommand);
	RUN_TEST_CASE(CreateSimpleCommand, CreateCommandFromTokenListWithAppendOutFileInTheMiddleOfCommand);
	RUN_TEST_CASE(CreateSimpleCommand, CreateCommandFromTokenListNoPipeNoRedirection);
	RUN_TEST_CASE(CreateSimpleCommand, CreateCommandFromTokenListWithHereDoc);
	// RUN_TEST_CASE(CreateSimpleCommand, CreateCommandFromTokenListStderrRedirect);
}

TEST_GROUP_RUNNER(CreateParseList)
{
	RUN_TEST_CASE(CreateParseList, SimplePipelineNoPipes);
	RUN_TEST_CASE(CreateParseList, SimplePipelineOnePipe);
	RUN_TEST_CASE(CreateParseList, SimplePipelineTwoPipes);
	RUN_TEST_CASE(CreateParseList, SimplePipelineTwoPipesChangeOrderCommandAndRedirection);
	RUN_TEST_CASE(CreateParseList, SimplePipelineNoPipeWeirdRedirectionOrder);
}

/* Expander */

TEST_GROUP_RUNNER(ExpandInputString)
{
	RUN_TEST_CASE(ExpandInputString, SingleVariableExisting0);
	RUN_TEST_CASE(ExpandInputString, SingleVariableExisting1);
	RUN_TEST_CASE(ExpandInputString, SingleVariableExisting2);
	RUN_TEST_CASE(ExpandInputString, SingleVariableExisting3);
	RUN_TEST_CASE(ExpandInputString, SingleVariableExisting4);
	RUN_TEST_CASE(ExpandInputString, SingleVariableExisting5);
	RUN_TEST_CASE(ExpandInputString, SingleVariableExisting6);
	RUN_TEST_CASE(ExpandInputString, SingleVariableExisting7);
	RUN_TEST_CASE(ExpandInputString, SingleVariableExisting8);
	RUN_TEST_CASE(ExpandInputString, SingleVariableExisting9);
	RUN_TEST_CASE(ExpandInputString, SingleVariableExisting10);
	RUN_TEST_CASE(ExpandInputString, SingleVariableExisting11);
	RUN_TEST_CASE(ExpandInputString, SingleVariableNonExisting0);
	RUN_TEST_CASE(ExpandInputString, SingleVariableNonExisting1);
	RUN_TEST_CASE(ExpandInputString, SingleVariableNonExisting2);
	RUN_TEST_CASE(ExpandInputString, SingleVariableNonExisting3);
	RUN_TEST_CASE(ExpandInputString, SingleVariableNonExisting4);
	RUN_TEST_CASE(ExpandInputString, SingleVariableNonExisting5);
	RUN_TEST_CASE(ExpandInputString, SingleVariableNonExisting6);
	RUN_TEST_CASE(ExpandInputString, SingleVariableNonExisting7);
	RUN_TEST_CASE(ExpandInputString, SingleVariableNonExisting8);
	RUN_TEST_CASE(ExpandInputString, SingleVariableNonExisting9);
	RUN_TEST_CASE(ExpandInputString, MultipleVariables0);
	RUN_TEST_CASE(ExpandInputString, MultipleVariables1);
	RUN_TEST_CASE(ExpandInputString, MultipleVariables2);
	RUN_TEST_CASE(ExpandInputString, MultipleVariables3);
	RUN_TEST_CASE(ExpandInputString, MultipleVariables4);
	RUN_TEST_CASE(ExpandInputString, MultipleVariables5);



	
}

// TEST_GROUP_RUNNER(ExpandSingleVariable)
// {
// 	RUN_TEST_CASE(ExpandSingleVariable, Existing0);
// 	RUN_TEST_CASE(ExpandSingleVariable, Existing1);
// 	RUN_TEST_CASE(ExpandSingleVariable, Existing2);
// 	RUN_TEST_CASE(ExpandSingleVariable, Existing3);
// 	RUN_TEST_CASE(ExpandSingleVariable, Existing4);
// 	RUN_TEST_CASE(ExpandSingleVariable, Existing5);
// 	RUN_TEST_CASE(ExpandSingleVariable, Existing6);
// 	RUN_TEST_CASE(ExpandSingleVariable, Existing7);
// 	RUN_TEST_CASE(ExpandSingleVariable, Existing8);
// 	RUN_TEST_CASE(ExpandSingleVariable, Existing9);
// 	RUN_TEST_CASE(ExpandSingleVariable, NonExisting0);
// 	RUN_TEST_CASE(ExpandSingleVariable, NonExisting1);
// 	RUN_TEST_CASE(ExpandSingleVariable, NonExisting2);
// 	RUN_TEST_CASE(ExpandSingleVariable, NonExisting3);
// 	RUN_TEST_CASE(ExpandSingleVariable, NonExisting4);
// }

// TEST_GROUP_RUNNER(FindCommand)
// {
// 	RUN_TEST_CASE(FindCommand, CommandExistsWithoutPathLs);
// 	RUN_TEST_CASE(FindCommand, CommandExistsWithoutPathGrep);
// 	RUN_TEST_CASE(FindCommand, CommandExistsWithRelativePath);
// 	RUN_TEST_CASE(FindCommand, CommandDoesntExistsWithRelativePath);
// 	RUN_TEST_CASE(FindCommand, CommandExistsWithAbsolutePath);
// 	RUN_TEST_CASE(FindCommand, CommandDoesntExistsWithAbsolutePath);
// 	RUN_TEST_CASE(FindCommand, CommandDoesntExist);
// 	// RUN_TEST_CASE(FindCommand, NoPathAvailable);
// }
