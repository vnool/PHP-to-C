/* NO LIMIT SUPPORT */
php_var str_replace(php_var search, php_var replace, php_var subject) {
	php_var retval=subject;
	int i;
	if(search.type == PHP_STRING) {
		char *tmp1;
		char *tmp2;
		char *ptr;
		tmp1=(char*)malloc(strlen(subject)+1);
		memset(tmp1,0,strlen(subject));
		strcpy(tmp1,subject);
		while(ptr = strstr(tmp1, (const char *)search))
		{
			*ptr = '\0';
			i=strlen(tmp1)+(int)(strlen(replace))+(int)(strlen(search))+1;
			tmp2=(char*)malloc(i);
			memset(tmp2,0,i);
			sprintf(tmp2,"%s%s%s",tmp1,(const char*)replace,(const char*)(ptr+(int)(strlen(search))));
			sprintf(tmp1,"%s",tmp2);
			free(tmp2);
		}
		retval=(char*)tmp1;
		free(tmp1);
	} else if (search.type == PHP_ARRAY) {
		for(i = 0;i < search.data.size(); ++i)
		{
			retval=str_replace(search.data[i],replace.data[i],retval);
		}
	}
	return retval;
}