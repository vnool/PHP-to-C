php_var explode(php_var delim_, php_var str_, php_var max = 0)
{
	string delim = delim_.container;
	string str = str_.container;
	php_var arr = array();
	unsigned long int pos =  0;
	unsigned long int lastPos = 0;
	string temp;
	int i = 0;
	if((pos = str.find(delim)) != string::npos)
	{
		temp = str.substr(0, pos);
		arr[i] = temp;
		lastPos = pos;
		pos++;
	}
	for(i = 1; (pos = str.find(delim, pos)) != string::npos; ++i)
	{
		temp = str.substr(lastPos + delim.size(), pos - lastPos - 1);
		arr[i] = temp;
		lastPos = pos;
		pos++;
	}
	temp = str.substr(lastPos + delim.size() > str.size() ? 0 : lastPos + delim.size(), str.size() - 1);
	arr[i] = temp;
	return arr;
}
