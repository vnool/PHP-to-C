<?php
	class Tokenizer
	{
		var $tokens = array();
		var $code;
		function Parse($file)
		{
			$this->code = file_get_contents($file);
			$this->Tokenize();
		}
		function Tokenize()
		{
			$this->tokens = token_get_all($this->code);
		}
		function Strip()
		{
			$strip = array(T_WHITESPACE, T_COMMENT, T_ML_COMMENT);
			$tokens = array();
			foreach($this->tokens as $token)
			{
				if(is_array($token))
				{
					if(!in_array($token[0], $strip))
						$tokens[] = $token;
				}
				else
					$tokens[] = $token;
			}
			$this->tokens = $tokens;
		}
		function Display()
		{
			foreach($this->tokens as $token)
			{
				if(is_array($token))
					print token_name((int) $token[0]) . ' -- \'' . $token[1] . '\'' . "\n";
			}
		}
		function Reassemble()
		{
			$code = (string)null;
			foreach($this->tokens as $token)
			{
				if(is_array($token))
					$code .= $token[1];
				else
					$code .= $token;
			}
			return $code;
		}
	}
?>
