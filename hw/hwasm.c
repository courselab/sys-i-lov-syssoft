/*
 *    SPDX-FileCopyrightText: 2024 iTzFabregas <fabricio-sampaio@usp.br>
 *   
 *    SPDX-License-Identifier: GPL-3.0-or-later
 *
 *  This file is a derivative work from SYSeg (https://gitlab.com/monaco/syseg)
 *  and contains modifications carried out by the following author(s):
 *  iTzFabregas <fabricio-sampaio@usp.br>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOV_TO_AH 0xB4  // 0xb4 ____
#define MOV_TO_AL 0xB0  // 0xb0 ____
#define INT 0xCD,0x10 // 0xcd 0x10
#define JUMP 0xEB       // 0xeb ____
#define HALT 0xF4       // 0xf4
#define EMPTY 0x00
#define SIGNATURE 0x55, 0xAA

int main(int argc, char *argv[]) {

    FILE *in_file, *out_file;

    in_file = fopen(argv[1], "r");
    if (in_file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    out_file = fopen("hw.bin", "wb+");
    if (out_file == NULL) {
        printf("Error creating file\n");
        return 1;
    }

    char command[256];
    while (fgets(command, sizeof(command), in_file)) {

        if (strstr(command, "hlt") != NULL) {
            unsigned char opcode[] = {HALT};
            fwrite(opcode, sizeof(opcode), 1, out_file);
            continue;
        }

        if (strstr(command, "jmp") != NULL) {
            unsigned char opcode[] = {JUMP, 0xFD};                  // WHY THE ARGUMENT IS 0xFD?
            fwrite(opcode, sizeof(opcode), 1, out_file);
            continue;
        }

        if (strstr(command, "int") != NULL) {
            unsigned char opcode[] = {INT};
            fwrite(opcode, sizeof(opcode), 1, out_file);
            continue;
        }

        if (strstr(command, "movb") != NULL) {

            unsigned char *buffer = strchr(command, '$'); // grab the string after the '$'
            unsigned char value = (unsigned char) strtol(buffer + 1, NULL, 16);

            if (strstr(command, "ah") != NULL) {
                unsigned char opcode[] = {MOV_TO_AH, value};
                fwrite(opcode, sizeof(opcode), 1, out_file);
            } else {
                unsigned char opcode[] = {MOV_TO_AL, value};
                fwrite(opcode, sizeof(opcode), 1, out_file);
            }
        }
    }

    for (int i = 50; i <= 510; i++) { // fill the rest with 0x00 (from byte 50 to 510)
        unsigned char opcode[] = {EMPTY};
        fwrite(opcode, sizeof(opcode), 1, out_file);
    }

    unsigned char opcode[] = {SIGNATURE};
    fwrite(opcode, sizeof(opcode), 1, out_file);


    fclose(in_file);
    fclose(out_file);

    return 0;
}