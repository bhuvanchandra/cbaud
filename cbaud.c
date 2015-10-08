/*
 * cbaud.c
 *
 * Copyright (C) 2015 - Bhuvanchandra DV <bhuvanchandra.dv@gmail.com>
 *
 * cabud is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * cbaud is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with cbaud If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <asm/termios.h>

int main(int argc, char* argv[]) {

	int retval, fd, speed;
	struct termios2 ntio;

	if (argc != 3) {
		printf("Usage: %s /dev/ttyXXX 20000\n", argv[0], argv[0]);                   
		return -1;
	}

	speed = atoi(argv[2]);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0) {
		perror("Open");
		return -1;
	}

	ioctl(fd, TCGETS2, &ntio);
	ntio.c_cflag &= ~CBAUD;
	ntio.c_cflag |= BOTHER;
	ntio.c_ispeed = speed;
	ntio.c_ospeed = speed;
	retval = ioctl(fd, TCSETS2, &ntio);
	close(fd);

	if (retval == 0)
		printf("New baud configured\n");
	else
		perror("ioctl");

	return 0;
}
