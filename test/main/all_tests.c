/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   all_tests.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 22:57:18 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/24 20:31:19 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "unity_fixture.h"

static void	run_all_tests(void)
{
	RUN_TEST_GROUP(AddNumbers);
	RUN_TEST_GROUP(IteratorAPI);
	RUN_TEST_GROUP(TokenizePipe);
	RUN_TEST_GROUP(TokenizeWord);
	RUN_TEST_GROUP(TokenizeRedirection);
	RUN_TEST_GROUP(TokenizeDquotes);
	RUN_TEST_GROUP(TokenizeQuotes);
	RUN_TEST_GROUP(Tokenizer);
	RUN_TEST_GROUP(CheckGrammer);
	RUN_TEST_GROUP(ParserUtils);
}

int	main(int argc, const char *argv[])
{
	return (UnityMain(argc, argv, run_all_tests));
}