/* This script follows LS35.5 - Tokenization video on Youtube
 * We are creating a tokenizer for a loldigit language.
 *
 * The following exists in the loldigit language:
 *
 * digit        ->  [0-9]
 * out_louds    ->  [ol]    (an o or l letter)
 * lol          ->  'l' 'o' 'l' outlouds*   (lol with 0 or more 'o's or 'l's.
 */

#include <stdbool.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

/* Simple API around Character Iteration */
typedef char* CharItr;

typedef enum TokenType
{
    ERROR = 0,
    DIGIT = 1,
    LOL = 2,
}   TokenType;

typedef struct Slice
{
    char    *start;
    size_t  len;
}           Slice;

typedef struct Token
{
    TokenType   type;
    Slice       location;
}               Token;

bool    has_next(char *itr)
{
    return (*itr != '\0' && *itr != '\n');
}

/* Return the current value and increments the iterator */
char    next(CharItr *itr)
{
    char    next;

    next = **itr;
    (*itr)++;
    return (next);
}

/* Peek at the next item of the iterator */
char    peek(CharItr itr)
{
    return (*itr);
}

Token   take_digit(CharItr *itr)
{
    Token   token;
    Slice   location;

    location.start = *itr;
    location.len = 1;
    next(itr);
    token.type = DIGIT;
    token.location = location;
    return (token);
}

Token   take_error(CharItr *itr)
{
    Token   token;
    Slice   location;

    location.start = *itr;
    location.len = 1;
    next(itr);
    token.type = ERROR;
    token.location = location;
    return (token);
}

Token   take_lol(CharItr *itr)
{
    size_t  len;
    char    valid;
    CharItr start;
    Slice   location;
    Token   token;

    len = 1;
    valid = true;
    start = *itr;
    /* Consume the leading 'l' */
    next(itr);

    /* Check the next character */
    if (peek(*itr) == 'o')
    {
        len++;
        next(itr);
    }
    else
        valid = false;

    /* Check the next character again */
    if (valid && peek(*itr) == 'l')
    {
        len++;
        next(itr);
    }
    else
        valid = false;

    if (valid)
    {
        while (peek(*itr) == 'l' || peek(*itr) == 'o')
        {
            len++;
            next(itr);
        }
    }
    location.start = start;
    location.len = len;
    if (valid)
    {
        token.type = LOL;
        token.location = location;
    }
    else
    {
        token.type = ERROR;
        token.location = location;
    }
    return (token);
}

void    print_token(Token *token)
{
    if (token->type == ERROR)
        printf("ERROR");
    else if (token->type == DIGIT)
        printf("DIGIT");
    else
        printf("LOL");
    printf("(%.*s)\n", (int)token->location.len, token->location.start);
}

int main(void)
{
    char    *line;
    CharItr itr;
    Token   token;

    while (1)
    {
        line = readline("$ ");
        itr = line;
        while (has_next(itr))
        {
            if (*itr == '0' || *itr == '1' || *itr == '2' || \
                *itr == '3' || *itr == '4' || *itr == '5' || \
                *itr == '6' || *itr == '7' || *itr == '8' || \
                *itr == '9')
            {
                token = take_digit(&itr);
                print_token(&token);
            }
            else if (*itr == 'l')
            {
                token = take_lol(&itr);
                print_token(&token);
            }
            else
            {
                token = take_error(&itr);
                print_token(&token);
                break ;
            }
        }
        free(line);
    }
    return (0);
}
