/******************************************************************************
 * Function: strend
 * Description:
 *     This function checks if string t occurs at the end of string s.
 *
 * Parameters:
 *     const char * s : Pointer to main string
 *     const char * t : Pointer to substring
 *
 * Return:
 *     1 if t is at the end of s
 *     0 otherwise
 *
 ******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stddef.h>

/******************************************************************************
 * Constants
 ******************************************************************************/

#define NULL_PTR ((void *)0)

/******************************************************************************
 * Function Prototype
 ******************************************************************************/

int strend(const char * s, const char * t);

/******************************************************************************
 * Function: strend
 ******************************************************************************/

int strend(const char * s, const char * t)
{
    size_t len_s;
    size_t len_t;
    size_t i;

    /* kiểm tra con trỏ NULL */
    if ((s == NULL_PTR) || (t == NULL_PTR))
    {
        return 0;
    }

    /* lấy độ dài chuỗi */
    len_s = strlen(s);
    len_t = strlen(t);

    /* t dài hơn s -> không thể là suffix */
    if (len_t > len_s)
    {
        return 0;
    }

    /* t rỗng -> luôn là suffix */
    if (len_t == 0U)
    {
        return 1;
    }

    /* so sánh từ cuối chuỗi */
    for (i = 0U; i < len_t; i++)
    {
        if (s[len_s - len_t + i] != t[i])
        {
            return 0;
        }
    }

    /* t nằm ở cuối s */
    return 1;
}

/******************************************************************************
 * Function: main
 * Description:
 *     Test strend function
 ******************************************************************************/

int main(void)
{
    /* s: chuỗi chính
       t: chuỗi cần kiểm tra */

    /* Case 1: t nằm ở cuối s */
    printf("Case 1: %d\n", strend("hello world", "world"));

    /* Case 2: t không nằm ở cuối s */
    printf("Case 2: %d\n", strend("hello world", "hello"));

    /* Case 3: t dài hơn s */
    printf("Case 3: %d\n", strend("hi", "hello"));

    /* Case 4: t là chuỗi rỗng */
    printf("Case 4: %d\n", strend("hello", ""));

    /* Case 5: s = NULL */
    printf("Case 5: %d\n", strend(NULL_PTR, "abc"));

    /* Case 6: s và t giống nhau */
    printf("Case 6: %d\n", strend("abc", "abc"));

    return 0;
}
