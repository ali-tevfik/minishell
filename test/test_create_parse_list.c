/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_create_parse_list.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 12:58:27 by hyilmaz       #+#    #+#                 */
/*   Updated: 2022/02/21 15:01:29 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "unity_fixture.h"

/* File to test */
#include "../src/parser/create_parse_list.h"

/* User defined headers */
#include "../src/libft/libft.h"
#include "../src/parser/parser_data_structs.h"
#include "../src/tokenizer/tokenizer.h"
#include "../src/tokenizer/tokenizer_utils.h"
#include "utils.h"

/* System headers */
#include <stdio.h>
#include <stdlib.h>

/* Variables */
t_list			*token_list;
char			**command;
t_pipeline		*pipeline_element;
t_list			*redirection_list;
t_list			*expected_pipeline_list;
t_list			*actual_pipeline_list;

// static t_list	*env_list;
// static char		*env[] = {	"SHELL=/bin/zsh",
// 							"Apple_PubSub_Socket_Render=/private/tmp/com.apple.launchd.uPX6eF400O/Render",
// 							"SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.qrlSCvg4Sx/Listeners",
// 							"PATH=/Users/hyilmaz/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/opt/X11/bin:/Users/hyilmaz/.brew/bin:/Users/hyilmaz/.cargo/bin",
// 							"LOGNAME=hyilmaz",
// 							"HOME=/home/hilmi",
// 							"DISPLAY=/private/tmp/com.apple.launchd.eWCZ6RGiQ4/org.macosforge.xquartz:0",
// 							"ali=s -l",
// 							"hilmi=ep",
// 							"codam_=",
// 							NULL,
// 						};

TEST_GROUP(CreateParseList);

TEST_SETUP(CreateParseList)
{
	expected_pipeline_list = NULL;
}

TEST_TEAR_DOWN(CreateParseList)
{
	ft_lstclear(&expected_pipeline_list, free_pipeline);
	ft_lstclear(&actual_pipeline_list, free_pipeline);
	ft_lstclear(&token_list, free);
}

TEST(CreateParseList, SimplePipelineNoPipes)
{
	char	*input = "ls -l";

	/* Generated token list */
	token_list = tokenize_input(input);

	/* Expected pipeline list */
	command = create_command(2, "ls", "-l");
	redirection_list = create_redirection_list(0);
	pipeline_element = create_pipeline_element(command, redirection_list);
	ft_lstadd_back(&expected_pipeline_list, ft_lstnew(pipeline_element));

	/* Actual pipeline list */
	actual_pipeline_list = create_parse_list(token_list);

	/* Compare pipelines */
	t_list	*head_expected = expected_pipeline_list;
	t_list	*head_actual = actual_pipeline_list;
	TEST_ASSERT_EQUAL_size_t(ft_lstsize(head_expected), ft_lstsize(head_actual));
	while (head_expected != NULL)
	{
		compare_pipelines((t_pipeline *)head_expected->content, (t_pipeline *)head_actual->content);
		head_expected = head_expected->next;
		head_actual = head_actual->next;
	}
}

TEST(CreateParseList, SimplePipelineOnePipe)
{
	char	*input = "ls -l | grep codam > out_file";

	/* Generated token list */
	token_list = tokenize_input(input);

	/* Expected pipeline list */
	command = create_command(2, "ls", "-l");
	redirection_list = create_redirection_list(0);
	pipeline_element = create_pipeline_element(command, redirection_list);
	ft_lstadd_back(&expected_pipeline_list, ft_lstnew(pipeline_element));

	command = create_command(2, "grep", "codam");
	redirection_list = create_redirection_list(2, "out_file", WRITE);
	pipeline_element = create_pipeline_element(command, redirection_list);
	ft_lstadd_back(&expected_pipeline_list, ft_lstnew(pipeline_element));

	/* Actual pipeline list */
	actual_pipeline_list = create_parse_list(token_list);

	/* Compare pipelines */
	t_list	*head_expected = expected_pipeline_list;
	t_list	*head_actual = actual_pipeline_list;
	TEST_ASSERT_EQUAL_size_t(ft_lstsize(head_expected), ft_lstsize(head_actual));
	while (head_expected != NULL)
	{
		compare_pipelines((t_pipeline *)head_expected->content, (t_pipeline *)head_actual->content);
		head_expected = head_expected->next;
		head_actual = head_actual->next;
	}
}

TEST(CreateParseList, SimplePipelineTwoPipes)
{
	char	*input = "ls -l | grep codam > out_file | < in_file wc -l -a > out_file_2";

	/* Generated token list */
	token_list = tokenize_input(input);

	/* Expected pipeline list */
	command = create_command(2, "ls", "-l");
	redirection_list = create_redirection_list(0);
	pipeline_element = create_pipeline_element(command, redirection_list);
	ft_lstadd_back(&expected_pipeline_list, ft_lstnew(pipeline_element));

	command = create_command(2, "grep", "codam");
	redirection_list = create_redirection_list(2, "out_file", WRITE);
	pipeline_element = create_pipeline_element(command, redirection_list);
	ft_lstadd_back(&expected_pipeline_list, ft_lstnew(pipeline_element));

	command = create_command(3, "wc", "-l", "-a");
	redirection_list = create_redirection_list(4, "in_file", READ, "out_file_2", WRITE);
	pipeline_element = create_pipeline_element(command, redirection_list);
	ft_lstadd_back(&expected_pipeline_list, ft_lstnew(pipeline_element));

	/* Actual pipeline list */
	actual_pipeline_list = create_parse_list(token_list);

	/* Compare pipelines */
	t_list	*head_expected = expected_pipeline_list;
	t_list	*head_actual = actual_pipeline_list;
	TEST_ASSERT_EQUAL_size_t(ft_lstsize(head_expected), ft_lstsize(head_actual));
	while (head_expected != NULL)
	{
		compare_pipelines((t_pipeline *)head_expected->content, (t_pipeline *)head_actual->content);
		head_expected = head_expected->next;
		head_actual = head_actual->next;
	}
}

TEST(CreateParseList, SimplePipelineTwoPipesChangeOrderCommandAndRedirection)
{
	char	*input = "ls -l | > out_file grep codam | < in_file wc > out_file_2 -l";

	/* Generated token list */
	token_list = tokenize_input(input);

	/* Expected pipeline list */
	command = create_command(2, "ls", "-l");
	redirection_list = create_redirection_list(0);
	pipeline_element = create_pipeline_element(command, redirection_list);
	ft_lstadd_back(&expected_pipeline_list, ft_lstnew(pipeline_element));

	command = create_command(2, "grep", "codam");
	redirection_list = create_redirection_list(2, "out_file", WRITE);
	pipeline_element = create_pipeline_element(command, redirection_list);
	ft_lstadd_back(&expected_pipeline_list, ft_lstnew(pipeline_element));

	command = create_command(2, "wc", "-l");
	redirection_list = create_redirection_list(4, "in_file", READ, "out_file_2", WRITE);
	pipeline_element = create_pipeline_element(command, redirection_list);
	ft_lstadd_back(&expected_pipeline_list, ft_lstnew(pipeline_element));

	/* Actual pipeline list */
	actual_pipeline_list = create_parse_list(token_list);

	/* Compare pipelines */
	t_list	*head_expected = expected_pipeline_list;
	t_list	*head_actual = actual_pipeline_list;
	TEST_ASSERT_EQUAL_size_t(ft_lstsize(head_expected), ft_lstsize(head_actual));
	while (head_expected != NULL)
	{
		compare_pipelines((t_pipeline *)head_expected->content, (t_pipeline *)head_actual->content);
		head_expected = head_expected->next;
		head_actual = head_actual->next;
	}
}

TEST(CreateParseList, SimplePipelineNoPipeWeirdRedirectionOrder)
{
	char	*input = "grep < infile codam >> outfile -i";

	/* Generated token list */
	token_list = tokenize_input(input);

	/* Expected pipeline list */
	command = create_command(3, "grep", "codam", "-i");
	redirection_list = create_redirection_list(4, "infile", READ, "outfile", APPEND);
	pipeline_element = create_pipeline_element(command, redirection_list);
	ft_lstadd_back(&expected_pipeline_list, ft_lstnew(pipeline_element));
	
	/* Actual pipeline list */
	actual_pipeline_list = create_parse_list(token_list);

	/* Compare pipelines */
	t_list	*head_expected = expected_pipeline_list;
	t_list	*head_actual = actual_pipeline_list;
	TEST_ASSERT_EQUAL_size_t(ft_lstsize(head_expected), ft_lstsize(head_actual));
	while (head_expected != NULL)
	{
		compare_pipelines((t_pipeline *)head_expected->content, (t_pipeline *)head_actual->content);
		head_expected = head_expected->next;
		head_actual = head_actual->next;
	}
}

TEST(CreateParseList, SimplePipelineNoPipeWithExpansion)
{
	/* 
	** ali="s -l" 
	** hilmi="ep"
	*/
	char	*input = "l\"$ali\" | gr$hilmi uni | wc -l";

	/* Environment */
	// env_list = add_envp(env);

	/* Generated token list */
	token_list = tokenize_input(input);

	/* Expander */


	/* Expected pipeline list */
	command = create_command(1, "ls -l");
	redirection_list = create_redirection_list(0);
	pipeline_element = create_pipeline_element(command, redirection_list);
	ft_lstadd_back(&expected_pipeline_list, ft_lstnew(pipeline_element));

	command = create_command(2, "grep", "uni");
	redirection_list = create_redirection_list(0);
	pipeline_element = create_pipeline_element(command, redirection_list);
	ft_lstadd_back(&expected_pipeline_list, ft_lstnew(pipeline_element));

	command = create_command(2, "wc", "-l");
	redirection_list = create_redirection_list(0);
	pipeline_element = create_pipeline_element(command, redirection_list);
	ft_lstadd_back(&expected_pipeline_list, ft_lstnew(pipeline_element));
	
	/* Actual pipeline list */
	actual_pipeline_list = create_parse_list(token_list);

	/* Compare pipelines */
	t_list	*head_expected = expected_pipeline_list;
	t_list	*head_actual = actual_pipeline_list;
	TEST_ASSERT_EQUAL_size_t(ft_lstsize(head_expected), ft_lstsize(head_actual));
	while (head_expected != NULL)
	{
		compare_pipelines((t_pipeline *)head_expected->content, (t_pipeline *)head_actual->content);
		head_expected = head_expected->next;
		head_actual = head_actual->next;
	}
}
