/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   all_tests_runner.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 23:00:07 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/01 15:17:16 by adoner        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "unity_fixture.h"

TEST_GROUP_RUNNER(unset)
{
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
