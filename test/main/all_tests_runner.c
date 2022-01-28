/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   all_tests_runner.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 23:00:07 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/28 19:13:32 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unity_fixture.h>

TEST_GROUP_RUNNER(AddNumbers)
{
	RUN_TEST_CASE(AddNumbers, Simple);
	RUN_TEST_CASE(AddNumbers, ABC);
}

TEST_GROUP_RUNNER(unset)
{
	RUN_TEST_CASE(envp, delete);
}
