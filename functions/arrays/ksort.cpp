php_var ksort(php_var &arr)
{
	php_var temp;
	int i = 0;
	for(;;)
	{
		if(i >= arr.keys.size())
			return 1;
		if((arr.keys[i].type == PHP_STRING && arr.keys[i+1].type == PHP_STRING &&
			(arr.keys[i].container.compare(arr.keys[i+1].container)) > 0) ||
			(arr.keys[i].type == PHP_STRING && arr.keys[i+1].type == PHP_INT) ||
			(arr.keys[i].type == PHP_INT && arr.keys[i+1].type == PHP_INT &&
			arr.keys[i] > arr.keys[i+1]))
		{
			temp = arr.keys[i];
			arr.keys[i] = arr.keys[i+1];
			arr.keys[i+1] = temp;
			temp = arr.data[i];
			arr.data[i] = arr.data[i+1];
			arr.data[i+1] = temp;
			if(i > 0)
				--i;
			else
				++i;
		}
		else
			++i;
	}
}

