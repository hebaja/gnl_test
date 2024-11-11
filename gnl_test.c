#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "../get_next_line/get_next_line.h"
#include "criterion-2.4.2/include/criterion/assert.h"
#include "criterion-2.4.2/include/criterion/criterion.h"
#include "criterion-2.4.2/include/criterion/redirect.h"

char	*ft_strcat(char *dest, char *src)
{
	int start;
	int count;

	start = ft_strlen(dest);
    
	count = 0;
	while (src[count] != 0)
	{
		dest[start + count] = src[count];
		count++;
	}
	return (dest);
}

void redirect_all_stdout(void)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
}

Test(gnl_test_suite, test_file_lines_more_than_buffer, .init=redirect_all_stdout)
{
	int	fd;
	char	*str;

	fd = open("examples/more_than_buffer.txt", O_RDONLY);
	while ((str = get_next_line(fd)))
		printf("%s", str);
	fflush(stdout);
	cr_assert_stdout_eq_str(
		"This is just random text\n"
		"that is being used to test \n"
		"the function get_next_line.\n"
		"I have already come across this concept in Java,\n"
		"in which we use some libraries such as:\n"
		"BuffereReader, Scanner and File.\n",
		"Output was not expected."
	);
	close(fd);
}

Test(gnl_test_suite, test_file_lines_more_than_buffer_no_end_nl)
{
	int fd;
	char *str;
	char result[1024] = "";

	fd = open("examples/more_than_buffer_no_end_nl.txt", O_RDONLY);
	while ((str = get_next_line(fd)))
	{
		ft_strcat(result, str);
		free(str);
	}
	close(fd);
	cr_assert_str_eq(result,
		"I have already come across this concept in Java,\n"
		"in which we use some libraries such as:\n"
		"BuffereReader, Scanner and File.",
		"Output was not expected."
);
}

Test(gnl_test_suite, test_file_one_line, .init=redirect_all_stdout)
{
	int	fd;
	char	*str;
	fd = open("examples/one_line.txt", O_RDONLY);
	while((str = get_next_line(fd)))
		printf("%s", str);
	fflush(stdout);
	close(fd);
	cr_assert_stdout_eq_str("This file contains one line.\n", "Output not as expected.");	
}

Test(gnl_test_suite, test_file_one_line_no_end_nl)
{
	int fd;
	char *str;
	char result[64] = "";

	fd = open("examples/one_line_no_nl.txt", O_RDONLY);
	while ((str = get_next_line(fd)))
	{
		ft_strcat(result, str);
		free(str);
	}
	close(fd);
	cr_assert_str_eq(result, "This file contains one line.");
}

Test(gnl_test_suite, test_file_one_short_line, .init=redirect_all_stdout)
{
	int	fd;
	char	*str;
	fd = open("examples/one_short_line.txt", O_RDONLY);
	while((str = get_next_line(fd)))
		printf("%s", str);
	fflush(stdout);
	close(fd);
	cr_assert_stdout_eq_str("Short.\n", "Output not as expected.");	
}

Test(gnl_test_suite, test_file_error, .init=redirect_all_stdout)
{
	int	fd;
	char	*str;
	fd = open("examples/nonexistent.txt", O_RDONLY);
	while((str = get_next_line(fd)))
		printf("%s", str);
	fflush(stdout);
	close(fd);
	cr_assert_stdout_eq_str("", "Output not as expected.");	
}

Test(gnl_test_suite, test_file_error_high, .init=redirect_all_stdout)
{
	int	fd;
	char	*str;
	while((str = get_next_line(1000)))
		printf("%s", str);
	fflush(stdout);
	close(fd);
	cr_assert_stdout_eq_str("", "Output not as expected.");	
}

Test(gnl_test_suite, test_empty_file_nl)
{
	int	fd;
	char	*str;
	char	result[8];

	fd = open("examples/empty_nl.txt", O_RDONLY);
	while((str = get_next_line(fd)))
	{
		ft_strcat(result, str);
		free(str);
	}
	close(fd);
	cr_assert_str_eq(result,
		"\n",
		"Output not as expected."
	);
}

Test(gnl_test_suite, test_empty_file)
{
	int	fd;
	char	*str;
	char	result[8];

	fd = open("examples/empty.txt", O_RDONLY);
	while((str = get_next_line(fd)))
	{
		ft_strcat(result, str);
		free(str);
	}
	close(fd);
	cr_assert_str_eq(result,
		"",
		"Output not as expected."
	);
}

Test(gnl_test_suite, test_file_one_shor_line_no_end_nl)
{
	int fd;
	char *str;
	char result[64] = "";

	fd = open("examples/one_short_line_no_nl.txt", O_RDONLY);
	while ((str = get_next_line(fd)))
	{
		ft_strcat(result, str);
		free(str);
	}
	close(fd);
	cr_assert_str_eq(result, "Short.");
}

Test(gnl_test_suite, test_file_nl_start_end)
{
	int fd;
	char *str;
	char result[64] = "";

	fd = open("examples/new_line_start_end.txt", O_RDONLY);
	while ((str = get_next_line(fd)))
	{
		ft_strcat(result, str);
		free(str);
	}
	close(fd);
	cr_assert_str_eq(result, 
		"\n"
		"This file contains new line start & end.\n"
		"\n",
		"Output not as expected."
	);
}

Test(gnl_test_suite, test_short_file_nl_start_end)
{
	int fd;
	char *str;
	char result[64] = "";

	fd = open("examples/short_new_line_start_end.txt", O_RDONLY);
	while ((str = get_next_line(fd)))
	{
		ft_strcat(result, str);
		free(str);
	}
	close(fd);
	cr_assert_str_eq(result, 
		"\n"
		"Short.\n"
		"\n",
		"Output not as expected."
	);
}

Test(gnl_test_suite, test_file_multiple_nls)
{
	int	fd;
	char	*str;
	char	result[64] = "";

	fd = open("examples/multiple_nls.txt", O_RDONLY);
	while((str = get_next_line(fd)))
	{
		ft_strcat(result, str);
		free(str);
	}
	fflush(stdout);
	close(fd);
	cr_assert_str_eq(result,
		"This file contains multiple new lines.\n"
		"\n"	
		"\n"
		"\n"
		"Just for testing.\n"
		"\n"
		"\n"
		"\n", 
		"Output not as expected."
	);	
}

Test(gnl_test_suite, test_file_mixed)
{
	int	fd;
	char	*str;
	char	result[1024] = "";

	fd = open("examples/mixed.txt", O_RDONLY);
	while((str = get_next_line(fd)))
	{
		ft_strcat(result, str);
		free(str);
	}
	close(fd);
	cr_assert_str_eq(result,
		"This is a mixed file....\n"
		"it\n" 
		"contains()\n"
		"\n"
		"\n"
		"\n"
		"lots of lines with differente patterns like this very long line which seems to be quite long and won't end\n"
		"\n"
		"this is a tab\tlet's if we can capture it\n"
		"\n"
		"\n"
		"\n"
		"______________________________\n"
		"////////////\n"
		"--------------------\n"
		"////////////\n"
		"______________________________\n"
		"\n"
		"a\n"
		"bb\n"
		"ccc\n"
		"dddd\n"
		"eeeee\n"
		"ffffff\n"
		"ggggggg\n"
		"hhhhhhhh\n"
		"iiiiiiiii\n"
		"jjjjjjjjjj\n"
		"kkkkkkkkk\n"
		"llllllll\n"
		"mmmmmmm\n"
		"nnnnnn\n"
		"ooooo\n"
		"pppp\n"
		"qqq\n"
		"rr\n"
		"s\n"
		".\n",
		"Output not as expected."
	);
}
