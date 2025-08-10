#include <stdio.h>
#include <regex.h>

int main() {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, "^hello", REG_EXTENDED);
    if (ret) {
        printf("Could not compile regex\n");
        return 1;
    }

    ret = regexec(&regex, "hello world", 0, NULL, 0);
    if (!ret) {
        printf("Match\n");
    } else if (ret == REG_NOMATCH) {
        printf("No match\n");
    }

    regfree(&regex);
    return 0;
}
