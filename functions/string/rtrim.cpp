php_var rtrim(php_var str, php_var charlist = "")
{
	string chrs = charlist.container + " " + "\t" + "\n" + "\r" + "\0" + "\x0B";
	int i = 0;
	int j = 0;
	bool changed = true;
	for(i = str.container.length() - 1; changed == true && i >= 0; --i)
	{
		changed = false;
		for(j = 0; j < chrs.length(); ++j)
		{
			if(str.container[i] == chrs[j])
			{
                str.container.erase(i, 1);
				changed = true;
				break;
			}
		}
	}
	return str;
}
