#!/bin/bash

TXT_RED="\033[1;31m"
TXT_GREEN="\033[1;32m"
TXT_YELLOW="\033[1;33m"
TXT_BLUE="\033[1;34m"
FANCY_RESET="\033[0m"

print_color () {
    echo -e "$1$2$FANCY_RESET"
}

print_color "$TXT_GREEN" "Checking multiple read\n"

exec 3< /dev/fortytwo

read -n 7 first <&3
read -n 8 second <&3

echo "Première lecture : $first"
echo "Deuxième lecture : $second"

exec 3<&-

print_color "$TXT_GREEN" "\nChecking cat\n"

cat /dev/fortytwo

print_color "$TXT_GREEN" "\n\nChecking wrong write\n"

echo "lol" > /dev/fortytwo

print_color "$TXT_GREEN" "\nChecking good write\n"

echo -n "jbettini" > /dev/fortytwo

print_color "$TXT_GREEN" "\nTest finished\n"