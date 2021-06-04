#include <stdio.h>
#include <stdlib.h>
#include <imged/imged.h>
#include <imged/imged_rw.h>
#include "rom.h"
	
/*
	Copyright (C) 2020  Gabriel Martins

	This file is part of nesdump2ff.

	nesdump2ff is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	nesdump2ff is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with nesdump2ff.  If not, see <https://www.gnu.org/licenses/>.
	Contact: gabrielmartinsthe@gmail.com
*/

rom* mainRom = NULL;

ImgColor colors[] = {
	{0, 0, 0, 0},
	{0, 255, 0, 255},
	{255, 0, 0, 255},
	{0, 0, 255, 255},
};

int main(int argc, char** argv){
	if(argc == 1){
		fprintf(stderr, "nesdump2ff: Please enter argument\n");
		exit(1);
	}
	else mainRom = rom_load(argv[1]);
	if(mainRom == NULL){
		fprintf(stderr, "nesdump2ff: %s: No such file or directory\n", argv[1]);
		exit(1);
	}

	int offset_chrom = (16+mainRom->rom_buffer[4]*16*1024)/mainRom->bytes_per_sprite;
	int num_of_sprites = mainRom->size/mainRom->bytes_per_sprite-offset_chrom;
	int sprites_width = 16;
	int sprites_height = num_of_sprites/16;

	ImgCanvas* image = img_createCanvas(sprites_width*8, sprites_height*8);
	for(int i = 0; i < sprites_width; i++){
		for(int j = 0; j < sprites_height; j++){
			int offset = offset_chrom+i+j*sprites_width;
			for(int k = 0; k < 8; k++){
				for(int l = 0; l < 8; l++){
					int current_color = rom_getPixel(mainRom, offset, 7-k, l);
					img_putPixel(image, i*8+k, j*8+l, colors[current_color]);
				}
			}
		}
	}

	img_saveFF(image, NULL);
	img_destroyCanvas(image);
	rom_destroy(mainRom);
	return 0;
}
