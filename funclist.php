<?php
	require 'functions.php';
	if(!empty($_SERVER['DOCUMENT_ROOT']))
		header('Content-Type: text/plain');
	$files = array('tokenflow.php', 'convert.php', 'tokenizer.php');
	$functions = array();
	foreach($files as $file)
	{
		$tokens = token_get_all(file_get_contents($file));
		foreach($tokens as $token)
		{
			if(is_array($token) && $token[0] == T_STRING)
			{
				if(!in_array($token[1], $functions) && function_exists($token[1]) && !isset($funcs[$token[1]]))
					$functions[] = $token[1];
			}
		}
	}
	sort($functions);
	foreach($functions as $function)
		echo $function, "\n";
	echo 'Functions left to code: ', count($functions);
?>