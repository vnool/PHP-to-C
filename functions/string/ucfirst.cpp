php_var ucfirst(php_var str)
{
	for(int i = 0; i < str.container.length(); ++i)
	{
		if(str.container[i] != ' ')
		{
			str.container[i] = toupper(str.container[i]);
			break;
		}
	}
	return str;
}
