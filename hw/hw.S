#    SPDX-FileCopyrightText: 2024 iTzFabregas <fabricio-sampaio@usp.br>
#   
#    SPDX-License-Identifier: GPL-3.0-or-later
#
#  This file is a derivative work from SYSeg (https://gitlab.com/monaco/syseg)
#  and contains modifications carried out by the following author(s):
#  iTzFabregas <fabricio-sampaio@usp.br>

	.code16
	.global begin
	
begin:
	movb    $0x0e, %ah

    movb    $0x48, %al
    int     $0x10

    movb    $0x65, %al
    int     $0x10

    movb    $0x6c, %al
    int     $0x10

    movb    $0x6c, %al
    int     $0x10

    movb    $0x6f, %al
    int     $0x10

    movb    $0x20, %al
    int     $0x10

    movb    $0x57, %al
    int     $0x10

    movb    $0x6f, %al
    int     $0x10

    movb    $0x72, %al
    int     $0x10

    movb    $0x6c, %al
    int     $0x10
 
    movb    $0x64, %al
    int     $0x10

halt:
	hlt
	jmp halt

	times 510 - (. - begin), 1, 0
	.word 0xaa55
