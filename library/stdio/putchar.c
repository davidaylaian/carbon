/**
 *
 * Copyright 2017 David Aylaian
 * https://github.com/DavidAylaian/Carbon/
 *
 */

#include <stdio.h>

static uint16_t xpos = 0;
static uint16_t ypos = 0;

// clears the screen
static void cls()   // the void is infinite
{
	for (uint32_t i = 0; i < vga_get_width() * vga_get_height(); i++)
	{
		vga_set_char(0x0, i, 0);
	}

	xpos = 0;
	ypos = 0;
}

// scrolls up
static void scroll()
{
	xpos = 0;

	if (ypos + 1 == vga_get_height())
	{
		for (uint32_t i = 0; i < vga_get_width() * vga_get_height(); i++)
		{
			vga_set_char(vga_get_char(i + vga_get_width(), 0), i, 0);
		}
	}
	else
	{
		ypos++;
	}
}

// writes a character to stdout
void putchar(char c)
{
	switch (c)
	{
		case '\a':
		{
			// nothing for now; we have no audio drivers
			break;
		}

		case '\b':
		{
			if (!xpos)
			{
				if (ypos)
				{
					xpos = vga_get_width() - 1;
					ypos--;
					vga_set_char(0x0, xpos, ypos);
				}
			}
			else
			{
				xpos--;
				vga_set_char(0x0, xpos, ypos);
			}

			break;
		}

		case '\f':
		{
			cls();
			break;
		}

		case '\n':
		{
			scroll();
			break;
		}

		case '\r':
		{
			xpos = 0;
			break;
		}

		case '\t':
		{
			xpos += 8 - xpos % 8;
			break;
		}

		case '\v':
		{
			ypos += 8 - ypos % 8;
			break;
		}

		default:
		{
			vga_set_char(c, xpos, ypos);
			xpos++;
			break;
		}
	}

	if (xpos == vga_get_width())
	{
		scroll();
	}

	vga_set_cursor_pos(xpos, ypos);
}
