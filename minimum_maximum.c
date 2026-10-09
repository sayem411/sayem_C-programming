#include <stdio.h>

int main() {
    int a, b, c;

    // ৩টি সংখ্যা ইনপুট নেওয়া
    scanf("%d %d %d", &a, &b, &c);

    // Ternary operator ব্যবহার করে minimum বের করা
    // লজিক: (a < b এবং a < c) হলে a, নয়তো b ও c এর মধ্যে যেটা ছোট সেটা।
    int min = (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);

    // Ternary operator ব্যবহার করে maximum বের করা
    // লজিক: (a > b এবং a > c) হলে a, নয়তো b ও c এর মধ্যে যেটা বড় সেটা।
    int max = (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);

    // ফলাফল প্রিন্ট করা
    printf("%d %d\n", min, max);

    return 0;
}