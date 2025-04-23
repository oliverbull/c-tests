#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// change 0 to 1
void test1() {
    uint32_t val = 8103060;

    // loop over each number
    uint32_t proc_val = val;
    uint32_t dig_num = 1;
    uint32_t res_val = val;
    while (dig_num < val) {
        // mod the process val
        if ((proc_val % 10) == 0) {
            res_val = res_val + (1 * dig_num);
        }
        // move on to next digit
        proc_val = proc_val / 10; 
        dig_num *= 10;
    }

    printf("%d\n", res_val);
}

// bin to dec
void test2() {
    uint32_t bin = 10111011;
    uint32_t proc_bin = bin;
    uint32_t res = 0;

    // run through each digit and convert to a bit
    for (int bitIdx = 0; bitIdx < 32 && proc_bin != 0; bitIdx++) {
        if ((proc_bin % 10) == 1) {
            res = res | 1 << bitIdx;
        }
        // move onto next digit
        proc_bin = proc_bin / 10;
    }

    printf("%x\n", res);
    printf("%d\n", res);
}

// leap year
void test3() {
    time_t time_now = time(NULL);
    struct tm tm = *localtime(&time_now);
    // every 4th year
    if (tm.tm_year % 4 == 0) {
        printf("leap year\n");
    } else {
        printf("not leap year\n");
    }
}

// factorial
void test4(int num) {
    uint64_t res = 1;
    while(num > 0) {
        res *= num;
        num-=1;
    }
    printf("%ld\n", res);
}

// armstrong 1^3+5^3+3^3 == 153
void test5(int num) {

    // work through each digit
    uint32_t dig_count = 0;
    uint8_t dig_val[10] = {};
    uint32_t proc_num = num;
    while (proc_num != 0) {
        // get the digit
        dig_val[dig_count] = proc_num % 10;
        // move on
        proc_num /= 10;
        // keep count
        dig_count++;
    }
    // run the calculation
    uint32_t res = 0;
    for (uint8_t dig_idx = 0; dig_idx < dig_count; dig_idx++) {
        res += (uint32_t)pow(dig_val[dig_idx], dig_count);
    }
    // check for match
    printf("input: %d, calc: %d\n", num, res);
    if (res == num) {
        printf("armstrong\n");
    } else {
        printf("not armstrong\n");
    }
}

// quadratic roots
void test6(float a, float b, float c) {

    // ax^2 + bx + c = 0
    // x = (-b +- sqr(b^2 - 4ac))/2a

    float x_plus = (-b + sqrt(pow(b, 2.0) - (4*a*c))) / (2*a);
    float x_minus = (-b - sqrt(pow(b, 2.0) - (4*a*c))) / (2*a);

    printf("roots: %f, %f\n", x_plus, x_minus);
}

// reverse a number
void test7(uint32_t num) {

    // work through each digit
    uint32_t digit_mult = 1;
    uint32_t proc_num = num;
    uint32_t ret = 0;
    // get the muliplier
    while (proc_num >= 10) {
        proc_num /= 10;
        digit_mult *= 10;
    }
    // now build the reverse
    proc_num = num;
    while (proc_num != 0) {
        // get the digit
        uint8_t digit = proc_num % 10;
        // save the on going number
        ret = ret + (digit * digit_mult);
        // move on
        proc_num /= 10;
        digit_mult /= 10;
    }
    printf("input: %d, reverse: %d\n", num, ret);
}

// palindrome number
void test8(uint32_t num) {

    // extract each digit
    uint8_t digits[10] = {};
    uint32_t proc_num = num;
    uint8_t digit_idx = 0;
    while (proc_num != 0) {
        // get the digit
        digits[digit_idx] = proc_num % 10;
        // move on
        proc_num /= 10;
        digit_idx++;
    }
    // clear the last increment
    digit_idx--;
    // now loop over each digit and compare with its peer - jump out on fail
    uint8_t pal = 1;
    for (uint8_t idx = 0; idx <= digit_idx; idx++, digit_idx--) {
        if (digits[idx] != digits[digit_idx]) {
            pal = 0;
            break;
        }
    }
    if (pal) {
        printf("%d is a palindrome\n", num);
    } else {
        printf("%d is not a palindrome\n", num);
    }
}

// pyramid pattern
void test9(uint32_t layers) {

    const uint8_t max_layers = 20;
    const uint8_t max_width = max_layers*2; // one space bewteen
    // maximum size check
    if (layers > max_layers) {
        printf("max layers exceeded, cannot continue\n");
        return;
    }
    // char storage
    char output[max_layers][max_width] = {};
    // actual width in chars (inc trailing space)
    uint8_t width = (layers*2);
    // build the pyramid layer by layer
    for (int layer = 0; layer < layers; layer++) {
        // calculate the start of the layer
        uint8_t start = layers - layer;
        uint8_t star = 1;
        uint8_t star_count = 0;
        // char at a time
        for (int idx = 0; idx < width; idx++) {
            // build spaces until the start
            if (idx < start) {
                output[layer][idx] = ' ';
            } else {
                // toggle star / space
                if (star) {
                    output[layer][idx] = '*';
                    star_count++;
                    star = 0;
                } else {
                    output[layer][idx] = ' ';
                    star = 1;
                }
                // bail on the layer when complete
                if (star_count > layer) {
                    break;
                }
            }
        }
        printf("%s\n", output[layer]);
    }
}

// pascal triangle
void test10(uint32_t layers) {

    const uint8_t max_layers = 20;
    // maximum size check
    if (layers > max_layers) {
        printf("max layers exceeded, cannot continue\n");
        return;
    }
    // number storage - fixed size
    uint8_t output[max_layers][max_layers] = {};

    // populate the output numbers
    for (int layer = 0; layer < layers; layer++) {
        // entry at a time
        for (int idx = 0; idx < layer+1; idx++) {
            // first two layers are 1's as are all the outers
            if (layer < 2 || idx == 0 || idx == layer) {
                output[layer][idx] = 1;
            } else {
                // now we need to calculate
                output[layer][idx] = output[layer-1][idx-1] + output[layer-1][idx];
            }            
        }
    }

    // print the pyramid layer by layer
    for (int layer = 0; layer < layers; layer++) {
        // calculate the start of the layer
        uint8_t start = layers - layer;
        // print the starting spaces
        for (int idx = 0; idx < start; idx++) {
            printf("  ");
        }
        // entry at a time
        for (int idx = 0; idx < layer+1; idx++) {
            printf("%d", output[layer][idx]);
            if (output[layer][idx] < 10) {
                printf("   ");
            } else if (output[layer][idx] < 100) {
                printf("  ");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

// reverse array
void test11() {
    uint8_t input[] = {1,2,3,4,5,6};
    uint8_t *output;

    output = malloc(sizeof(input));
    if (output == NULL) {
        printf("malloc failed\n");
        return;
    }

    for (int8_t idx = sizeof(input)-1, out_idx = 0; idx >= 0; idx--, out_idx++) {
        output[out_idx] = input[idx];
        printf("%d ", output[out_idx]);
    }
    printf("\n");

    free(output);
}

// find max and min in array
void test12() {
    uint8_t input[] = {1,2,3,13,5,6};
    uint8_t min = 255;
    uint8_t max = 0;

    for (uint8_t idx = 0; idx < (sizeof(input) / sizeof(input[0])); idx++) {
        if (input[idx] < min) {
            min = input[idx];
        }
        if (input[idx] > max) {
            max = input[idx];
        }
    }
    printf("min: %d, max: %d\n", min, max);
}

// tanspose matrix
void test13() {
    uint16_t matrix[][4] = {
        {1,2,3,4}, 
        {5,6,7,8}
    };
    uint16_t *output[4];

    // loop over the rows
    uint8_t num_rows = sizeof(matrix) / sizeof(matrix[0]);
    uint8_t num_col = sizeof(matrix[0]) / sizeof(matrix[0][0]);
    for (uint8_t row_idx = 0; row_idx < num_rows; row_idx++) {
        // loop over the columns
        for (uint8_t col_idx = 0; col_idx < num_col; col_idx++) {
            // allocate the new row when input row is 0
            if (row_idx == 0) {
                output[col_idx] = malloc(num_rows * sizeof(matrix[0][0]));
                if (output[col_idx] == NULL) {
                    printf("malloc failed\n");
                    return;
                }            
            }
            output[col_idx][row_idx] = matrix[row_idx][col_idx];
        }
    }
    // loop over the transposed result for printing
    for (uint8_t row_idx = 0; row_idx < num_col; row_idx++) {
        for (uint8_t col_idx = 0; col_idx < num_rows; col_idx++) {
            printf("%d ", output[row_idx][col_idx]);
        }
        printf("\n");
    }
}

// sum of numbers in a string
void test14(char *str) {

    // working pointers
    char *pos = str;
    char *start = str;
    uint16_t idx = 0;
    char word[30];
    int sum = 0;
    uint16_t len = strlen(str);

    // loop string length
    while (idx < len) {
        // split string on ' ' and catch the end
        while (*pos != ' ' && idx < len) {
            pos++;
            idx++;
        }
        // copy the word
        strncpy(word, start, pos-start);
        // attempt an atoi - non number just returns 0
        int val = atoi(word);
        sum += val;
        // move on to the next word
        start = ++pos;
        idx++;
    }
    printf("sum: %d\n", sum);
}

// lexicographically sorted order of characters
void test15(char *str) {

    // letter index
    char letter_pos[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    uint8_t letter_count[26] = {};
    size_t len = strlen(str);
    // loop for each character
    for (uint16_t idx = 0; idx < len; idx++) {
        uint8_t pos = 0;
        // find the position - ignore any non [a..z]
        while (pos < 26) {
            if (str[idx] == letter_pos[pos]) {
                letter_count[pos]++;
                break;
            }
            pos++;
        }
    }
    // now rebuild a string with the letters
    char *reorder = malloc(len);
    char *reorder_w = reorder;
    for (uint8_t pos = 0; pos < 26; pos++) {
        for (uint16_t count = 0; count < letter_count[pos]; count++) {
            *reorder_w = letter_pos[pos];
            reorder_w++;
        }

    }
    printf("%s\n", reorder);
    free(reorder);
}

// power of a number using recursion
uint32_t test16a(uint32_t num, uint32_t tot, uint8_t run) {
    // stop at 2 as that is a 'run once' version
    tot = tot * num;
    if (run == 2) {
        return tot;
    }
    // otherwise keep going
    tot = test16a(num, tot, run-1);
    return tot;
}
void test16(uint32_t num, uint8_t pow) {
    uint32_t val = test16a(num, num, pow);
    printf("%d\n", val);
}

// reverse a linked list
typedef struct ll_t {
    struct ll_t *next;
    struct ll_t *prev;
    uint32_t value;
} ll_t;

void test17() {
    // first populate a linked list with 5 entries
    const uint8_t NUM_ENTRIES = 5;
    ll_t *start;
    ll_t *end;
    ll_t *prev;
    for (uint8_t idx = 0; idx < NUM_ENTRIES; idx++) {
        ll_t *entry = calloc(1, sizeof(ll_t));
        printf("entry: %p\n", entry);
        // todo - NULL pointer check
        entry->value = idx;
        // special handling for first one
        if (idx == 0) {
            start = entry;
        } else {
            // setup the ll pointers
            prev->next = entry;
            entry->prev = prev;
            // update end
            end = entry;
        }
        // always update prev
        prev = entry;
    }

    // now reverse
    ll_t *entry = end;
    for (uint8_t idx = 0; idx < NUM_ENTRIES; idx++) {
        // save prev
        ll_t *prev = entry->prev;
        // update links
        if (idx == 0) {
            entry->next = entry->prev;
            entry->prev = NULL;
        } else {
            // save next
            ll_t *next = entry->next;
            entry->next = entry->prev;
            entry->prev = next;
        }
        // move on
        entry = prev;
    }

    // print out the values
    ll_t *result = end;
    for (uint8_t idx = 0; idx < NUM_ENTRIES; idx++) {
        printf("idx %d: %d\n", idx, result->value);
        result = result->next;
    }

    // now free each one
    entry = end;
    for (uint8_t idx = 0; idx < NUM_ENTRIES; idx++) {
        ll_t *next = entry->next;
        free(entry);
        entry = next;
    }
}

// right rotate an array by defined amount
int test18(uint8_t arr[], uint8_t len, uint8_t k) {
    // check sensible inputs
    if (len == 0 || k >= len) {
        return 1;
    }
    // find the rotated start point - handling zero edge case
    uint8_t idx = (k != 0) ? len-k : 0;
    // playout from the rotation
    for (uint8_t element = 0; element < len; element++, idx++) {
        printf("%d ", arr[idx]);
        // check for wrap
        if (idx == len-1) {
            idx = -1;
        }
    }
    printf("\n");

    return 0;
}

//     #
// #ooo#
// #ooo#oo#   
// #o#o#o##o#
// ==============
// uint8_t arr[] = {3, 0, 1, 0, 4, 0, 1, 2, 0, 1};

// trapped rain water
int test19(uint8_t arr[], uint8_t len) {
    // check sensible len
    if (len < 3) {
        return 1;
    }
    // check there are sides at the end
    if (arr[0] == 0 || arr[len-1] == 0) {
        return 2;
    }

    // keep volume count for each section - with a left/right max running total
    uint16_t vol;
    // maintain left max and right max
    uint8_t left_max = arr[0];
    uint8_t right_max = arr[len-1];
    // maintain left and right indexes
    uint8_t left_idx = 1;
    uint8_t right_idx = len-2;
    // loop over [1..len-2]
    while (left_idx != right_idx) {
        //printf("max: %d, %d, idx: %d, %d\n", left_max, right_max, left_idx, right_idx);
        // decide if we are going left or right based on largest column value
        if (left_max > right_max) {
            // right to left
            // check for a hole
            if (arr[right_idx] < right_max) {
                // store the hole at the max right level
                vol += (right_max - arr[right_idx]);
            }
            // check if we need to reset right max
            if (arr[right_idx] > right_max) {
                right_max = arr[right_idx];
            } else {
                // move left by 1
                right_idx--;
            }
        } else {
            // left to right
            // check for a hole
            if (arr[left_idx] < left_max) {
                // store the hole at the max left level
                vol += (left_max - arr[left_idx]);
            }
            // check if we need to reset left max
            if (arr[left_idx] > left_max) {
                left_max = arr[left_idx];
            } else {
                // move right by 1
                left_idx++;
            }
        }
    }
    printf("%d\n", vol);
}

// b sort decending
void b_sort(uint8_t arr[], uint8_t len, uint8_t count) {
    // check params
    if (len == 0 || arr == NULL) {
        return;
    }
    // protect stack depth
    if (count > 40) {
        return;
    }

    // keep track of switches
    uint8_t switch_count = 0;
    uint8_t switch_idx = 0;
    uint8_t store;
    // go left to right - one short to not overrun
    for (uint8_t idx = 0; idx < len-1; idx++) {
        // less, switch
        if (arr[idx] < arr[idx+1]) {
            store = arr[idx];
            arr[idx] = arr[idx+1];
            arr[idx+1] = store;
            // keep count
            switch_count++;
        }
    }
    // go again until switch count is 0
    if (switch_count != 0) {
        b_sort(arr, len, ++count);
    }
}


// in leu of header file
int8_t coins(uint8_t arr[], uint8_t len, int8_t target, int8_t coin_num);
// coin denomination - reentrant
int8_t coins(uint8_t arr[], uint8_t len, int8_t target, int8_t coin_num) {

    //printf("arr[0]: %d, len: %d, target: %d, coin_num: %d\n", arr[0], len, target, coin_num);

    // if len is zero, exhausted so return -1
    if (len == 0) {
        return -1;
    }

    // pull the first entry and check value - not enough, just right, too much
    if ((target - arr[0]) > 0) {
        // not enough, update and go again
        printf("selected one coin of value: %d\n", arr[0]);
        coin_num = coins(arr, len, target - arr[0], ++coin_num);
    } else if ((target - arr[0]) == 0) {
        // found the quantity, include this one and return
        printf("selected one coin of value: %d\n", arr[0]);
        return ++coin_num;
    } else {
        // too much, move on and go again
        coin_num = coins(++arr, len-1, target, coin_num);
    }
    
    // return the ultimate coin num
    return coin_num;
}

// coin denomination - main
int test20(uint8_t arr[], uint8_t len, uint8_t target) {

    // coins() only works if sorted, so sort first
    b_sort(arr, len, 0);
    printf("final sort:\n");
    for (uint8_t idx = 0; idx < len; idx++) {
        printf("%d ", arr[idx]);
    }
    printf("\n");
    // run coins and print the quantity
    printf("number of coins required: %d\n", coins(arr, len, target, 0));

    return 0;
}

// median of 2 sorted arrays - 2-pointer approach - bin search is 'better'
double test21(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    // check lengths and ptrs
    if (nums1 == NULL || nums2 == NULL || nums1Size == 0 || nums2Size == 0) {
        printf("bad input\n");
        return 0.0;
    }
    int full_length = nums1Size+nums2Size;
    // walk backwards to the middle
    int walk_idx = full_length-1;
    // prepare the return value
    int ret_val;
    // overload sizes as indexes
    nums1Size--;
    nums2Size--;
    // handle based on odd or even set
    if (full_length % 2 == 1) { // odd, so there's a middle
        int med_idx = full_length / 2;
        // walk to median, then decrement idx and save running value
        while (walk_idx >= med_idx) {
            // check for exhausted array
            if (nums1Size == -1) {
                ret_val = nums2[nums2Size];
                nums2Size--;
            } else if (nums2Size == -1) {
                ret_val = nums1[nums1Size];
                nums1Size--;
            } else if (nums1[nums1Size] > nums2[nums2Size]) {
                ret_val = nums1[nums1Size];
                nums1Size--;
            } else {
                ret_val = nums2[nums2Size];
                nums2Size--;
            }
            walk_idx--;
        }
        // we have our answer
        return ret_val;
    } else {
        int med_idx1 = full_length / 2; // higher idx
        int med_idx2 = med_idx1-1; // lower idx
        int running_val1 = 0; // higher val
        int running_val2 = 0; // lower val
        // walk to one-after lower median, then decrement idx and save running value
        while (walk_idx >= med_idx2) {
            // always save the last value
            running_val1 = running_val2;
            // check for exhausted array
            if (nums1Size == -1) {
                running_val2 = nums2[nums2Size];
                nums2Size--;
            } else if (nums2Size == -1) {
                running_val2 = nums1[nums1Size];
                nums1Size--;
            } else if (nums1[nums1Size] > nums2[nums2Size]) {
                running_val2 = nums1[nums1Size];
                nums1Size--;
            } else {
                running_val2 = nums2[nums2Size];
                nums2Size--;
            }
            walk_idx--;
        }
        // we have our answer
        return ((double)running_val1 + (double)running_val2) / 2.0;
    }
}

// merge a number of ordered linked lists - pick the lowest at the start of each list
ll_t* test22(ll_t** lists, uint8_t num_lists) {

    // check input
    if (lists == NULL || num_lists == 0) {
        return NULL;
    }
    // skip checking each list for now
    // todo
    
    uint16_t perf_count = 0;
    // prepare the result
    ll_t* res = NULL;
    ll_t* cur = NULL;
    uint8_t empty_lists = 0;
    // run over each list until exhausted
    while (empty_lists != num_lists) {
        // start with the first
        ll_t *selected = lists[0];
        // step through each list
        uint8_t selected_idx = 0;
        for (uint8_t list_idx = 0; list_idx < num_lists; list_idx++) {
            perf_count++;
            // look for populated list AND less or equal
            if (lists[list_idx] != NULL && lists[list_idx]->value <= selected->value) {
                selected = lists[list_idx];
                selected_idx = list_idx;
            }
        }
        // pop the selected from the list
        lists[selected_idx] = lists[selected_idx]->next;
        // keep counter of emptied lists
        empty_lists += (lists[selected_idx] == NULL) ? 1 : 0;
        // save the first
        if (res == NULL) {
            res = selected;
            cur = res;
            selected->next = NULL;
        } else {
            // move selected into the result
            cur->next = selected;
            selected->next = NULL;
            cur = selected;
        }
    }
    printf("loop count: %d\n", perf_count);
    return res;
}

// merge a number of ordered linked lists - walk input from 1 once, finding the right place with single walk per line
ll_t* test22b(ll_t** lists, uint8_t num_lists) {

    // check input
    if (lists == NULL || num_lists == 0) {
        return NULL;
    }
    // skip checking each list for now
    // todo
    
    uint16_t perf_count = 0;
    // start with list 0 and merge in each subsequent lists
    ll_t *start = lists[0];
    // loop each list from the second
    for (uint8_t list_idx = 1; list_idx < num_lists; list_idx++) {
        // keep going for the whole input list
        ll_t *inp = lists[list_idx];
        ll_t *srch = start;
        ll_t *srch_prv = NULL;
        while (inp != NULL) {
            perf_count++;
            // check for the end of the search
            if (srch == NULL) {
                // save the next input entry
                ll_t *next = inp->next;
                // input must be greater, so insert
                srch_prv->next = inp;
                inp->next = NULL;
                // update srch_prv to this new end entry
                srch_prv = inp;
                // move input on to the saved next
                inp = next;
            }
            // check for input less than current search
            else if (inp->value <= srch->value) {
                // save the next input entry
                ll_t *next = inp->next;
                // insert input into the result
                inp->next = srch;
                // if inserted before start, update start to this input
                if (srch == start) {
                    start = inp;
                } else {
                    if (srch_prv != NULL) {
                        // move prv to the inserted one if there is one
                        srch_prv->next = inp;
                    }
                    // update srch_prv to the inserted one
                    srch_prv = inp;
                }
                // move input on to the saved next
                inp = next;
            } else {
                // update srch and srch_prv if not inserted
                srch_prv = srch;
                srch = srch->next;
            }
        }
    }
    printf("loop count: %d\n", perf_count);
    return start;
}

// )()(()))(((((())())(()())(()
// longest valid parenthesis
uint16_t test23(char *str) {

    // running checks
    uint16_t longest_count = 0;
    int16_t count_l = 0;
    uint16_t longest_l = 0;
    int16_t count_r = 0;
    uint16_t longest_r = 0;
    // loop over each char and process state
    for (uint16_t idx_l = 0, idx_r = strlen(str)-1; idx_l < strlen(str); idx_l++, idx_r--) {
        // keep counts - left to right
        if (str[idx_l] == '(') {
            count_l++;
            longest_l++;
        } else {
            count_l--;
            longest_l++;
        }
        // keep counts - right to left
        if (str[idx_r] == ')') {
            count_r++;
            longest_r++;
        } else {
            count_r--;
            longest_r++;
        }
        //printf("%d, %d, %d, %d\n", count_l, longest_l, count_r, longest_r);
        // as soon as count goes negative, we're done, so save and reset
        if (count_l < 0) {
            // save if greater
            if ((longest_l-1) > longest_count) {
                longest_count = longest_l-1;
                printf("longest count updated (l->r): %d\n", longest_count);
            }
            // now reset the running check
            count_l = 0;
            longest_l = 0;
        }
        if (count_r < 0) {
            // save if greater
            if ((longest_r-1) > longest_count) {
                longest_count = longest_r-1;
                printf("longest count updated (r->l): %d\n", longest_count);
            }
            // now reset the running check
            count_r = 0;
            longest_r = 0;
        }
    }
    return longest_count;
}


int main() {

    char *str = "this is a test string with some words and letters";

    printf("longest parenthesis: %d\n", test23(")()(()))(((((())())(()())(()"));

    // {{4, 6, 9, 11, 16},
    //  {1, 3, 6, 19},
    //  {2, 4, 4}};

    // build the lists
    // ll_t *arr[3];
    // ll_t *prev;
    // ll_t *entry = calloc(sizeof(ll_t), 1);
    // arr[0] = entry;
    // entry->value = 4;
    // prev = entry;
    // entry = calloc(sizeof(ll_t), 1);
    // entry->value = 6;
    // prev->next = entry;
    // prev = entry;
    // entry = calloc(sizeof(ll_t), 1);
    // entry->value = 9;
    // prev->next = entry;
    // prev = entry;
    // entry = calloc(sizeof(ll_t), 1);
    // entry->value = 11;
    // prev->next = entry;
    // prev = entry;
    // entry = calloc(sizeof(ll_t), 1);
    // entry->value = 16;
    // prev->next = entry;
    // prev = entry;

    // entry = calloc(sizeof(ll_t), 1);
    // arr[1] = entry;
    // entry->value = 1;
    // prev = entry;
    // entry = calloc(sizeof(ll_t), 1);
    // entry->value = 3;
    // prev->next = entry;
    // prev = entry;
    // entry = calloc(sizeof(ll_t), 1);
    // entry->value = 6;
    // prev->next = entry;
    // prev = entry;
    // entry = calloc(sizeof(ll_t), 1);
    // entry->value = 19;
    // prev->next = entry;
    // prev = entry;

    // entry = calloc(sizeof(ll_t), 1);
    // arr[2] = entry;
    // entry->value = 2;
    // prev = entry;
    // entry = calloc(sizeof(ll_t), 1);
    // entry->value = 4;
    // prev->next = entry;
    // prev = entry;
    // entry = calloc(sizeof(ll_t), 1);
    // entry->value = 4;
    // prev->next = entry;
    // prev = entry;

    // ll_t *res = test22b(arr, 3);
    // while (res != NULL) {
    //     printf("%d, ", res->value);
    //     res = res->next;
    // }
    // printf("\n");

    return 0;
}

