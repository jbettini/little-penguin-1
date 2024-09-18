#!/bin/bash

TXT_RED="\033[1;31m"
TXT_GREEN="\033[1;32m"
TXT_YELLOW="\033[1;33m"
TXT_BLUE="\033[1;34m"
FANCY_RESET="\033[0m"

print_color () {
    echo -e "$1$2$FANCY_RESET"
}

LOGIN="jbettini"

print_color "$TXT_YELLOW" "TEST ID FILE\n"

print_color "$TXT_GREEN" "Checking multiple read\n"

exec 3< /sys/kernel/debug/fortytwo/id

read -n 7 first <&3
read -n 8 second <&3

echo "First read : $first"
echo "Second read : $second"

exec 3<&-

print_color "$TXT_GREEN" "\nChecking cat\n"

cat /dev/fortytwo

print_color "$TXT_GREEN" "\n\nChecking wrong write\n"

echo "lol" > /dev/fortytwo

print_color "$TXT_GREEN" "\nChecking good write\n"

echo -n "$LOGIN" > /dev/fortytwo

print_color "$TXT_GREEN" "\nChecking file rights - must be \"-rw-rw-rw-\", output : \n"
ls -la /sys/kernel/debug/fortytwo/id


print_color "$TXT_YELLOW" "\nTest finished for id file\n-------------------------------\n"

print_color "$TXT_YELLOW" "TEST JIFFIES FILE\n"

print_color "$TXT_GREEN" "There could be a minor difference between the real jiffies  and our:\nReal: \n\n"

grep -E "^cpu|^jiff" /proc/timer_list

print_color "$TXT_GREEN" "\nOur: \n"

cat /sys/kernel/debug/fortytwo/jiffies

print_color "$TXT_GREEN" "\n\nChecking file rights - must be \"-r--r--r--\", output : \n"

ls -la /sys/kernel/debug/fortytwo/jiffies

print_color "$TXT_YELLOW" "\nTest finished for jiffies file\n-------------------------------\n"
print_color "$TXT_YELLOW" "TEST FOO FILE\n"

print_color "$TXT_GREEN" "\nChecking simple write: \"lol\" is written"

echo "lol" >  /sys/kernel/debug/fortytwo/foo

print_color "$TXT_GREEN" "\nChecking simple read"

cat /sys/kernel/debug/fortytwo/foo

print_color "$TXT_GREEN" "\nChecking multiple read, 1 byte by 1 byte\n"

exec 3< /sys/kernel/debug/fortytwo/foo

read -n 1 first <&3
read -n 1 second <&3
read -n 1 third <&3
read -n 1 fourth <&3

echo "First read : $first"
echo "Second read : $second"
echo "Third read : $third"
echo "Fourth read : $fourth"

exec 3<&-

print_color "$TXT_GREEN" "\nChecking to write more than one page_size:\n"

printf '%.5000d' 0 > /sys/kernel/debug/fortytwo/foo

print_color "$TXT_GREEN" "\nChecking foo content normally only 0:\n\n"

cat /sys/kernel/debug/fortytwo/foo

print_color "$TXT_GREEN" "\n\nChecking foo len, normaly one page_size ~4096:\n"

cat /sys/kernel/debug/fortytwo/foo | wc -c

print_color "$TXT_GREEN" "\n\nChecking file rights - must be \"-rw-r--r--\", output : \n"

ls -la /sys/kernel/debug/fortytwo/foo
print_color "$TXT_YELLOW" "\nTest finished\n-------------------------------\n"
