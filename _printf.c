#include "main.h"
#include <stdarg.h>
#include <unistd.h>
#include <stddef.h>

/**
 * _printf - Custom printf function
 * @format: Format string
 * Return: Number of characters printed
 */
int _printf(const char *format, ...)
{
	va_list args;
	int index = 0, cCount = 0, strLength = 0;
	char newline = '\n', curChar, *currentStr;

	va_start(args, format);
	if (format == NULL)
		return (-1);
	while (format[index])
	{
		if (format[index] == '%' && format[index + 1] == 'c')
		{
			curChar = (char)va_arg(args, int);
			write(1, &curChar, 1), index += 2, cCount++;
		}
		else if (format[index] == '%' && format[index + 1] == 's')
		{
			currentStr = va_arg(args, char *);
			if (currentStr == NULL)
				currentStr = "(null)";
			while (currentStr[strLength])
				strLength++;
			write(1, currentStr, strLength), index += 2;
			cCount += strLength, strLength = 0;
		}
		else if (format[index] == '%' && format[index + 1] == '%')
			curChar = '%', write(1, &curChar, 1), index += 2, cCount++;
		else if (format[index] == '%' && format[index + 1] == '\0')
			return (-1);
		else if (format[index] == '\\' && format[index + 1] == 'n')
			write(1, &newline, 1), index += 2, cCount++;
		else
			curChar = format[index], write(1, &curChar, 1), index++, cCount++;
	}
	va_end(args);
	return (cCount);
}

