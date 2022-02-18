/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   all_tests.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 22:57:18 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/16 19:04:23 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "unity_fixture.h"

static void	run_all_tests(void)
{
	RUN_TEST_GROUP(IteratorAPI);
	RUN_TEST_GROUP(TokenizePipe);
	RUN_TEST_GROUP(TokenizeWord);
	RUN_TEST_GROUP(TokenizeRedirection);
	RUN_TEST_GROUP(TokenizeDquotes);
	RUN_TEST_GROUP(TokenizeQuotes);
	RUN_TEST_GROUP(Tokenizer);
	RUN_TEST_GROUP(CheckGrammer);
	RUN_TEST_GROUP(CreateSimpleCommand);
	RUN_TEST_GROUP(CreateParseList);
	RUN_TEST_GROUP(FindCommand);
	// RUN_TEST_GROUP(ExportBuiltin);
	RUN_TEST_GROUP(UnsetBuiltin);
	RUN_TEST_GROUP(ExpandSingleVariable);
}

int	main(int argc, const char *argv[])
{
	return (UnityMain(argc, argv, run_all_tests));
}
