/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_delete_element_linked_list.c                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 15:58:21 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/01/28 13:39:40 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "unity_fixture.h"
#include "../src/libft/libft.h"

#include <stdio.h>
#include <stdlib.h>

t_list	*expected_list;
t_list	*actual_list;

// static void	print_list(t_list *head)
// {
// 	printf("\n");
// 	while (head != NULL)
// 	{
// 		printf("%s\n", (char *)(head->content));
// 		head = head->next;
// 	}
// }

static void	delete_nth_element_from_list(t_list **list, size_t n)
{
	size_t	i;
	t_list	*previous;
	t_list	*to_delete;

	i = 0;
	previous = *list;
	if (n == 0)
	{
		*list = (*list)->next;
		free(previous->content);
		free(previous);
		return ;
	}
	while (i < n - 1)
	{
		previous = previous->next;
		i++;
	}
	/* previous --> to_delete */
	to_delete = previous->next;
	previous->next = to_delete->next;
	free(to_delete->content);
	free(to_delete);
}

TEST_GROUP(DeleteElementFromLinkedList);

TEST_SETUP(DeleteElementFromLinkedList)
{
	expected_list = NULL;
	actual_list = NULL;
}

TEST_TEAR_DOWN(DeleteElementFromLinkedList)
{
}

TEST(DeleteElementFromLinkedList, DeleteElementInTheMiddle)
{
	t_list	*input_list = NULL;
	
	/* Input list */
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("hello")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("codam")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("coding")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("college")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("amsterdam")));

	/* Expected list (Removing 3rd element) */
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("hello")));
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("codam")));
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("college")));
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("amsterdam")));

	/* My list */
	delete_nth_element_from_list(&input_list, 2);

	/* Compare length of lists */
	TEST_ASSERT_EQUAL_INT(ft_lstsize(expected_list), ft_lstsize(input_list));

	/* Compare contents */
	while (expected_list)
	{
		TEST_ASSERT_EQUAL_STRING((char *)(expected_list->content), (char *)(input_list->content));
		expected_list = expected_list->next;
		input_list = input_list->next;
	}
}

TEST(DeleteElementFromLinkedList, DeleteFirstElement)
{
	t_list	*input_list = NULL;
	
	/* Input list */
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("hello")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("codam")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("coding")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("college")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("amsterdam")));

	/* Expected list (Removing 1st element) */
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("codam")));
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("coding")));
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("college")));
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("amsterdam")));

	/* My list */
	delete_nth_element_from_list(&input_list, 0);

	/* Compare length of lists */
	TEST_ASSERT_EQUAL_INT(ft_lstsize(expected_list), ft_lstsize(input_list));

	/* Compare contents */
	while (expected_list)
	{
		TEST_ASSERT_EQUAL_STRING((char *)(expected_list->content), (char *)(input_list->content));
		expected_list = expected_list->next;
		input_list = input_list->next;
	}
}

TEST(DeleteElementFromLinkedList, DeleteLastElement)
{
	t_list	*input_list = NULL;
	
	/* Input list */
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("hello")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("codam")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("coding")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("college")));
	ft_lstadd_back(&input_list, ft_lstnew(ft_strdup("amsterdam")));

	/* Expected list (Removing 1st element) */
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("hello")));
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("codam")));
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("coding")));
	ft_lstadd_back(&expected_list, ft_lstnew(ft_strdup("college")));

	/* My list */
	delete_nth_element_from_list(&input_list, 4);

	/* Compare length of lists */
	TEST_ASSERT_EQUAL_INT(ft_lstsize(expected_list), ft_lstsize(input_list));

	/* Compare contents */
	while (expected_list)
	{
		TEST_ASSERT_EQUAL_STRING((char *)(expected_list->content), (char *)(input_list->content));
		expected_list = expected_list->next;
		input_list = input_list->next;
	}
}