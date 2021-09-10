int	str_array_size(char **array)
{
	int	size;

	size = 0;
	if (!array)
		return (-1);
	while (array[size])
		size++;
	return (size);
}
