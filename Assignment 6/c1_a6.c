#include <stdio.h>
#include <string.h>
#include <stddef.h>

/******************************************************************************
 * Constants
 ******************************************************************************/
#define NULL_PTR ((void *)0)

/**
 * @Function: strend
 * @Description: Kiểm tra xem chuỗi t có xuất hiện ở cuối chuỗi s hay không (Suffix check).
 * Hàm thực hiện so sánh từng ký tự bắt đầu từ vị trí (len_s - len_t) trong s.
 * @Parameter: 
 * - s: Con trỏ tới chuỗi chính.
 * - t: Con trỏ tới chuỗi con cần kiểm tra ở cuối.
 * @Return: int - Trả về 1 nếu t nằm ở cuối s, 0 nếu không khớp hoặc lỗi tham số.
 */
int strend(const char * s, const char * t)
{
    size_t len_s;
    size_t len_t;
    size_t i;

    /* 1. Kiểm tra an toàn: con trỏ NULL */
    if ((s == NULL_PTR) || (t == NULL_PTR))
    {
        return 0;
    }

    /* 2. Lấy độ dài chuỗi */
    len_s = strlen(s);
    len_t = strlen(t);

    /* 3. Logic kiểm tra biên:
     * - Nếu t dài hơn s -> chắc chắn không phải suffix.
     * - Nếu t là chuỗi rỗng "" -> quy ước luôn là suffix của mọi chuỗi.
     */
    if (len_t > len_s)
    {
        return 0;
    }

    if (len_t == 0U)
    {
        return 1;
    }

    /* 4. So sánh các ký tự:
     * Dịch con trỏ của s đến vị trí bắt đầu so sánh: s + (len_s - len_t).
     */
    for (i = 0U; i < len_t; i++)
    {
        if (s[len_s - len_t + i] != t[i])
        {
            return 0; // Phát hiện ký tự không khớp
        }
    }

    /* 5. Khớp hoàn toàn */
    return 1;
}

/**
 * @Function: main
 * @Description: Điểm kiểm thử (Test Bench) cho hàm strend với nhiều kịch bản khác nhau.
 * @Parameter: void
 * @Return: int - 0 nếu kết thúc bình thường.
 */
int main(void)
{
    /* Kiểm tra các trường hợp thực tế */

    // Case 1: Đúng (world nằm cuối hello world)
    printf("Case 1 (Correct suffix): %d\n", strend("hello world", "world"));

    // Case 2: Sai (hello nằm đầu chứ không phải cuối)
    printf("Case 2 (Prefix not suffix): %d\n", strend("hello world", "hello"));

    // Case 3: Sai (chuỗi con dài hơn chuỗi mẹ)
    printf("Case 3 (t longer than s): %d\n", strend("hi", "hello"));

    // Case 4: Đúng (chuỗi rỗng luôn nằm cuối mọi chuỗi)
    printf("Case 4 (Empty string): %d\n", strend("hello", ""));

    // Case 5: Xử lý lỗi (con trỏ NULL)
    printf("Case 5 (NULL pointer): %d\n", strend(NULL_PTR, "abc"));

    // Case 6: Đúng (hai chuỗi giống hệt nhau)
    printf("Case 6 (Identical strings): %d\n", strend("abc", "abc"));

    return 0;
}
