/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   all_tests.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 22:57:18 by hyilmaz       #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2022/01/31 17:08:38 by adoner        ########   odam.nl         */
=======
/*   Updated: 2022/01/26 18:43:08 by hyilmaz       ########   odam.nl         */
>>>>>>> 277b7cf308323f6d60a828ebfd84a34ee4de1e7f
/*                                                                            */
/* ************************************************************************** */

#include "unity_fixture.h"

static void	run_all_tests(void)
{
<<<<<<< HEAD
	RUN_TEST_GROUP(unset);
	RUN_TEST_GROUP(export);
	RUN_TEST_GROUP(expander);
=======
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
	RUN_TEST_GROUP(CreateParseList);
>>>>>>> 277b7cf308323f6d60a828ebfd84a34ee4de1e7f
}

int	main(int argc, const char *argv[])
{
	return (UnityMain(argc, argv, run_all_tests));
}
